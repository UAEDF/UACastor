#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TCanvas.h"

#include <cassert>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//to style
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"

void LeakageSubtractor(const std::vector<int> &time, std::vector<float> &cathode, const std::vector<int> &hv, const std::vector<int> &led){

int skipAtVChange = 40;
int skipAtLedChange = 3;

int size = 0;

std::vector<float> cathode_ye;

int voltage; 
int voltageBegin = 0;
int voltageStep = 0; //the lenght of the high voltage steps //don't look at first value because picoamp meter screws this up

float error = (0.5/16.6)*10E-12;

size = cathode.size(); //the number pf voltages stored in the cathode vector

//declare the values of the voltage to fit
std::vector<double> fitX;
std::vector<double> fitY;
std::vector<double> fitYe;

  for (int i = 0; i < size; ++i)
  {
    cathode_ye.push_back(error);
  }

  cout << "size: " << size<< endl;

  //the different hight voltage steps in volt
  int nstep = 7;
  int step[7]={0,800,900,1000,1200,1400,1600}; 
  //write the endex of the beginning and the end of the hv regions into an array
  int index_begin[nstep];
  int index_end[nstep];

  
   for(int istep = 0; istep < 6; istep++){
  int index1 =0;
  int index2 =0;
    while(abs(hv[index1]) < step[istep] +20 ){
	index1++;
     }
	index_begin[istep]= index1;
	cout << "index_begin " <<index_begin[istep] << endl;
    while(abs(hv[index2]) < step[istep+1] +20 ){
	index2++;
     }
	index_end[istep] =index2;
	cout << "index_end " << index_end[istep] << endl;
   }
   //check that led was turned off

   //write the voltages into the vector
   // copy the x,y values for one voltage set and only where LED was off 
	for(int i = index_begin[0]; i < index_end[0]; i++){         
          fitX.push_back(time[i]-time[index_begin[0]]); 
	  fitY.push_back(cathode[i]*1e12);
          fitYe.push_back(cathode_ye[i]*1e12);
	}

  // ----loop over all voltage regions----
  while (voltageBegin < size)
    {
      // ----Skip 0 voltage run----
      while (abs(hv[voltageBegin]) < 20 && voltageBegin < size) //we assume that it varies between 20A
        {
          ++voltageBegin;
          continue;
        }

        // ----loop in voltage region----
      while (hv[voltageBegin+voltageStep] > voltage-20 && hv[voltageBegin+voltageStep] < voltage+20 && voltageBegin+voltageStep < size)
        {
          //looking if voltage changes in last five or next five time bins
//here we define the lenght of voltagestep
          if (voltageStep-skipAtVChange < 0)
            {
              ++voltageStep;
              continue;
            }

          if (voltageBegin+voltageStep > size)
            {
              ++voltageStep;
              continue; //don't break because counter used to skip voltage
            }

          if(cathode[voltageBegin+voltageStep]*1e12 < 0. || cathode[voltageBegin+voltageStep]*1e12 > 1e5) //weird value skip
            {
              ++voltageStep;
              continue;
            }


//remove the parts when I turned on the led, this does not take part in the fitting

          if(led[voltageBegin+voltageStep-skipAtLedChange] || led[voltageBegin+voltageStep] || led[voltageBegin+voltageStep+skipAtLedChange])
            {
              ++voltageStep;
              continue;
            }

          // copy the x,y values for one voltage set and only where LED was off          
       //   fitX.push_back(time[voltageBegin+voltageStep]-time[voltageBegin]); // always starts at 0
	//in pA         
// fitY.push_back(cathode[voltageBegin+voltageStep]*1e12);
         // fitYe.push_back(cathode_ye[voltageBegin+voltageStep]*1e12);
// in A      
 //fitY.push_back(cathode[voltageBegin+voltageStep]*1e12);
   //       fitYe.push_back(cathode_ye[voltageBegin+voltageStep]*1e12);


          ++voltageStep;
        }
	cout << "voltage step after one hv plateau " << voltageStep << endl;
	cout << "voltage hv[voltageBegin+voltageStep]: " << hv[voltageBegin+voltageStep] << endl;
	cout << "time after the plateau " << time[voltageStep+voltageBegin] << endl;

      if (fitX.size() <= 5) //not enough data for fit
        {
            std::cerr << "no fitting. not enough data in voltage set" << std::endl;
          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }

      TF1 theFcn("a","[0]+[1]*TMath::Exp(-(x)/[2])");
      theFcn.SetParameters(fitY.back(),40,60,fabs(voltage-800)<20.?650:350);
      theFcn.SetParLimits(3,200.,1200.);
      TGraphErrors theGraph (fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());

 // TFitResultPtr theMin = theGraph.Fit(&theFcn,fVerbosity>1?"S M E 0":"S M E 0 Q");
	cout << "========" << voltage << "===========" << endl;
	cout << "voltage step: " << voltageStep << endl;
     TFitResultPtr theMin = theGraph.Fit(&theFcn); //do the fit and print out the fit parameters
      if (theMin == NULL || !theMin->Status() || theMin->IsValid() == 0)
        {
          std::cerr << "fit unsucessful" << std::endl;

          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }
      else
        {
          std::cerr << "fit sucessful with f=" << theMin->Chi2()/double(fitX.size()) << std::endl;
          if (theMin->Chi2()/double(fitX.size()) > 50)
            std::cout << " - Warning: fit converged but high chi2/ndf compromised: " << theMin->Chi2()/double(fitX.size()) << std::endl;
        }

      	TCanvas * c = new TCanvas("c","c",800,600);
      	c->cd();
      	theGraph.Draw("AP");
//      theFcn.SetParameters(theMin->Parameter(0),theMin->Parameter(1),theMin->Parameter(2),theMin->Parameter(3));
      theFcn.SetLineColor(kRed);
     // theFcn.Draw("lSAME");
      //cin >> fVerbosity;
      c->Print("example.eps");

      for (int j=0; j < voltageStep; j++)
        {
            std::cout << "x:" << time[j+voltageBegin] << "/" << time[voltageBegin+j]-time[voltageBegin] << " ===  " << cathode[j+voltageBegin] << " ..... " << theFcn(time[voltageBegin+j]-time[voltageBegin]) << std::endl;
          // if any poles in the function just skip the subtraction. only the LED regions are of interest. but if the profile doesn't look nice one can delete this if
          if ((theFcn)(time[j+voltageBegin]-time[voltageBegin]) < 1e-6 && (theFcn)(time[j+voltageBegin]-time[voltageBegin]) > 0)
            cathode[j+voltageBegin] -= float( theFcn(time[j+voltageBegin]-time[voltageBegin]));
        }//subtract the leakage

      voltageBegin += voltageStep + 1; //jump to next voltage
     }

}
