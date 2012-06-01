#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TCanvas.h"

//#include <cassert>
//#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//to style
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TVirtualFitter.h"
#include "TMinuit.h"

// fit function

double fexp(double *x, double *p){
 // if(p[1]<0) return 0;
    return p[0] + p[1] * exp (-(x[0]/p[2] ) );
};

void LeakageSubtractor(const std::vector<int> &time, std::vector<float> &cathode, const std::vector<int> &hv, const std::vector<int> &led, std::string file ){

string str_volt;

gStyle->SetOptFit(1);
//int skipAtVChange = 40;
int skipAtLedChange = 4;

int size = 0;

std::vector<float> cathode_ye;

float error = (0.5/16.6)*10E-12;

size = cathode.size(); //the number pf voltages stored in the cathode vector

//declare the values of the voltage to fit
std::vector<double> fitX;
std::vector<double> fitXe;
std::vector<double> fitY;
std::vector<double> fitYe;

  for (int i = 0; i < size; ++i)
  {
    cathode_ye.push_back(error);
  }

  cout << "size: " << size<< endl;

  //the different hight voltage steps in volt
  int nstep = 7;
  int step[7]={800,900,1000,1200,1400,1600,1800}; 
  //write the endex of the beginning and the end of the hv regions into an array
  int voltageStep[nstep];
  int index_begin[nstep];
  int index_end[nstep];
  int istep; 
   
   for(istep = 0; istep < 7; istep++){
    int index1 =0;
    int index2 =0;
    
    cout<<"trying voltage: "<<step[istep]<<endl;
    
    while((abs(hv[index1-1]) > step[istep] + 20 or abs(hv[index1-1]) < step[istep] - 20) and index1 < size){
      index1++;
    }
    index_begin[istep] = index1;
    //cout << "index_begin " <<index_begin[istep] << endl;
    index2 = index1;
    while((abs(hv[index2]) < step[istep] + 20 and abs(hv[index2]) > step[istep] - 20) and index2 < size){
      index2++;
    }
    index_end[istep] = index2;
    //cout << "index_end " << index_end[istep] << endl;

    voltageStep[istep] = index_end[istep] - index_begin[istep];
   // cout << "voltage Step " << voltageStep[istep] << endl;
   //write the voltages into the vector
   // copy the x,y values for one voltage set and only where LED was off 
     
     
   if (voltageStep[istep] > 20)
   {      
    for(int i = index_begin[istep]; i < index_end[istep]; i++){  
     if(led[i] == 0 && led[i-skipAtLedChange] == 0 && led[i+skipAtLedChange] == 0){  
          if (time[i] < 0) { cout << "warning: negative time " << i << " " << time[i] << endl; }     
          fitX.push_back(time[i]); 
	  fitY.push_back(cathode[i]);
          fitYe.push_back(cathode_ye[i]);
          fitXe.push_back(0.);
    }
   }
	// cout << "========" << hv[index_begin[istep]] << "===========" << endl;

   //do the fitting
   // define the fit function
   int shift;
   shift = 100;
   if (abs(hv[index1]) < 820 and abs(hv[index1]) > 780) { shift = 300; }
   if (voltageStep[istep] < 100) { shift = 0; }   

   // TGraphErrors has to be defined befor TF1 (the fit function)
   TGraphErrors *gc0 = new TGraphErrors(fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());

   TF1 *ff  = new TF1("ff", fexp, time[index_begin[istep]] + shift, time[index_end[istep]], 3);
	ff->SetLineColor(2);
    int fcount=0;
    bool repeate=true;
    double ini1[5] = {1.0e-7, 0.1e-7, 10.e-7, 0.01e-7, 100.e-7};
   //    double ini1[5] = {1.0e-9, 0.1e-9, 10.e-9, 0.01e-9, 100.e-9};
    TVirtualFitter::SetMaxIterations(7000);
    while (repeate && fcount<5){


      ff->SetParameter(0, 0.01e-9);
      ff->SetParameter(2, 300.);

      ff->SetParameter(1, ini1[fcount]);
      cout << "ini par[1] = " << ini1[fcount] << endl;
      gc0->Fit("ff","ERQ");
      cout << "=> " << gMinuit->fCstatu.Data() << endl;    
      repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (ff->GetParameter(1)<0) || (ff->GetParameter(0)<0));
	
      fcount++;

	}

      	//TCanvas * c = new TCanvas("c","c",800,600);
      	//gPad->SetLogy();
      	//gc0->Draw("AP");
      	str_volt = "unknownvoltage";
      	if (hv[index_begin[istep]] > -820 and hv[index_begin[istep]] < -780) { str_volt = "800V"; }
      	if (hv[index_begin[istep]] > -920 and hv[index_begin[istep]] < -880) { str_volt = "900V"; }
      	if (hv[index_begin[istep]] > -1020 and hv[index_begin[istep]] < -980) { str_volt = "1000V"; }
      	if (hv[index_begin[istep]] > -1220 and hv[index_begin[istep]] < -1180) { str_volt = "1200V"; }
      	if (hv[index_begin[istep]] > -1420 and hv[index_begin[istep]] < -1380) { str_volt = "1400V"; }
      	if (hv[index_begin[istep]] > -1620 and hv[index_begin[istep]] < -1580) { str_volt = "1600V"; }
      	if (hv[index_begin[istep]] > -1820 and hv[index_begin[istep]] < -1780) { str_volt = "1800V"; }
        string name = "fit/" + file + "_" + str_volt + ".png";
        //c->Print(name.c_str());
	//c->Close();
	
	delete(gc0);
	fitX.clear(); 
	fitY.clear();
        fitYe.clear();
        fitXe.clear();
       }
       else
       { cout << "voltage not found!" << endl;
       }
 /*     for (int j=0; j < index_end[0]-index_begin[0]; j++)
        {
            std::cout << "x:" << time[j+index_begin[0]] << "/" << time[index_begin[0]+j]-time[index_begin[0]] << " ===  " << cathode[j+index_begin[0]] << " ..... " << theFcn(time[index_begin[0]+j]-time[index_begin[0]]) << std::endl;
          // if any poles in the function just skip the subtraction. only the LED regions are of interest. but if the profile doesn't look nice one can delete this if
          if ((theFcn)(time[j+index_begin[0]]-time[index_begin[0]]) < 1e-6 && (theFcn)(time[j+index_begin[0]]-time[index_begin[0]]) > 0)
            cathode[j+index_begin[0]] -= float( theFcn(time[j+index_begin[0]]-time[index_begin[0]]));
        }//subtract the leakage
*/

//from Colin
/*  // ----loop over all voltage regions----
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
*/
}
}
