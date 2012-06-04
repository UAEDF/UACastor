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

/*struct chi2 {
	float c_800V;
	float c_900V;
	float c_1000V;
	float c_1200V;
	float c_1400V;
	float c_1600V;
	float c_1800V;
};*/


// fit function

double fexp(double *x, double *p){
 // if(p[1]<0) return 0;
    return p[0] + p[1] * exp (-(x[0]/p[2] ) );
};

void LeakageSubtractor(const std::vector<int> *time, std::vector<float> *cathode, const std::vector<int> *hv, const std::vector<int> *led, std::string file, std::vector<float>& cathode_out, chi2& fit ){

string str_volt;

gStyle->SetOptFit(1);
int skipAtLedChange = 4;
int size = 0;
float chi2 = 0;
int spike = 0;

std::vector<float> cathode_ye;

float error = (0.5/16.6)*10E-12;

size = cathode->size(); //the number pf voltages stored in the cathode vector
//cout << "size: " << size<< endl;
  
//declare the values of the voltage to fit
std::vector<double> fitX;
std::vector<double> fitXe;
std::vector<double> fitY;
std::vector<double> fitYe;

//int nstep = 7;
int step[7]={800,900,1000,1200,1400,1600,1800}; 
//write the endex of the beginning and the end of the hv regions into an array
int voltageStep[7] = {0,0,0,0,0,0,0};
int index_begin[7] = {0,0,0,0,0,0,0};
int index_end[7] = {0,0,0,0,0,0,0};
int istep, i; 

int fcount=0;
bool repeate=true;
double ini1[8] = {1.0e-7, 1.0e-8, 1.e-6, 1.0e-9, 1.0e-5, 1.0e-10, 1.e-4, 1.0e-11};
double shifts_begin[8] = {0, 50, 100, 150, 200, 250, 300};
double shifts_end[5] = {0, 50, 100, 150, 200};
int begin_count = 0;
int end_count = 0;
int better_chi2 = 0.0;
int better[3] = {0, 0, 0};
double par[3] = {0, 0, 0};

  for (i = 0; i < size; i++)
  {
    cathode_ye.push_back(error);
  }


  //for (i = 0; i < size-1; i++)
  //{
  //  cout << i << " " << size << " " << time->at(i) << " " << hv->at(i) << " " << led->at(i) << " " << cathode->at(i) << endl;
  //}


  //the different hight voltage steps in volt

   for(istep = 0; istep < 7; istep++){
    int index1 = 1;
    int index2 = 1;
    
    //cout<<"trying voltage: "<<step[istep]<<endl;
    
    while((abs(hv->at(index1-1)) > step[istep] + 20 or abs(hv->at(index1-1)) < step[istep] - 20) and index1 < size-1){
      index1++;
      //cout << "begin " <<index1-1 << " " << size << " " << abs(hv->at(index1-1)) << endl;
    }
    //cout << "out of begin" << endl;
    index_begin[istep] = index1;
    //cout << "index_begin " <<index_begin[istep] << endl;
    if (index1 < size) { index2 = index1;
    while((abs(hv->at(index2)) < step[istep] + 20 and abs(hv->at(index2)) > step[istep] - 20) and index2 < size-1){
      index2++;
      //cout << "end " << index2 << " " << size << " " << abs(hv->at(index2)) << endl;
    }
    index_end[istep] = index2;
    //cout << "index_end " << index_end[istep] << endl;
    }
    voltageStep[istep] = index_end[istep] - index_begin[istep];
    //cout << "voltage Step " << voltageStep[istep] << endl;
   //write the voltages into the vector
   // copy the x,y values for one voltage set and only where LED was off 
     
     
   if (voltageStep[istep] > 20)
   {      
    for(i = index_begin[istep]; i < index_end[istep]; i++){
    if (i < size - skipAtLedChange)
    {
    //cout << i << " " << size << " " << time->at(i) << " " << led->at(i) << " " << hv->at(i) << " " << cathode->at(i) << " " << cathode_ye[i] << endl;
    spike_check(i, cathode, spike);
     if(led->at(i) == 0 && led->at(i-skipAtLedChange) == 0 && led->at(i+skipAtLedChange) == 0 && abs(hv->at(i)) < step[istep] + 20 && abs(hv->at(i)) > step[istep] - 20 && cathode->at(i) > 0 && spike == 0){
     	  //cout << "in" << endl;
          if (time->at(i) < 0) { cout << "warning: negative time " << i << " " << time->at(i) << endl; }   
          fitX.push_back(time->at(i)); 
	  fitY.push_back(cathode->at(i));
          fitYe.push_back(cathode_ye[i]);
          fitXe.push_back(0.);
    }
    spike = 0;
    }
   }
	// cout << "========" << hv[index_begin[istep]] << "===========" << endl;

   // TGraphErrors has to be defined befor TF1 (the fit function)
   TGraphErrors *gc0 = new TGraphErrors(fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());

    TVirtualFitter::SetMaxIterations(7000);
    while (repeate && fcount < 8 && begin_count < 8 && end_count < 5) {

	//cout << "fcount = " << fcount << " begin_count = " << begin_count << "end_count = " << end_count << endl;
      TF1 *ff = new TF1("ff", fexp, time->at(index_begin[istep]) + shifts_begin[begin_count], time->at(index_end[istep]) - shifts_end[end_count], 3);
	ff->SetLineColor(2);

      ff->SetParameter(0, ini1[fcount]);
      ff->SetParameter(2, 300.);

      ff->SetParameter(1, ini1[fcount]);
      //cout << "ini par[1] = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << endl;
      gc0->Fit("ff","ERQ");
      //cout << "=> " << gMinuit->fCstatu.Data() << endl;
      chi2 = ff->GetChisquare()/float(ff->GetNDF());
      //cout << "chi2 = " << chi2 << endl;
      repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (ff->GetParameter(1)<0) || (ff->GetParameter(0)<0) || chi2 > 2);
	
	if (better_chi2 == 0.0 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	better_chi2 = chi2;
	better[0] = fcount;
	better[1] = begin_count;
	better[2] = end_count;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	}
	if (better_chi2 > chi2 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	//cout << "ini par[1] = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << endl;
	//cout << "=> " << gMinuit->fCstatu.Data() << endl;
	//cout << "chi2 = " << chi2 << endl;
	better_chi2 = chi2;
	better[0] = fcount;
	better[1] = begin_count;
	better[2] = end_count;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	}
	delete(ff);
	end_count++;
	if (end_count == 5) { begin_count++; end_count = 0; }
	if (begin_count == 8) { fcount++; begin_count = 0; }
	}

	if (better_chi2 > 2)
	{
	cout << "none of the fits was good, using the best one!" << endl;
        int sb = shifts_begin[better[1]];
	int se = shifts_end[better[2]];
	float ig = ini1[better[0]];
	cout << better[0] << " " << better[1] << " " << better[2] << " " << endl;
	cout << ig << " " << sb << " " << se << " " << endl;
	TF1 *ff = new TF1("ff", fexp, time->at(index_begin[istep]) + sb, time->at(index_end[istep]) - se, 3);
	ff->SetLineColor(2);
      	ff->SetParameter(0, ig);
      	ff->SetParameter(2, 300.);
	gc0->Fit("ff","ERQ");
   	cout << "=> " << gMinuit->fCstatu.Data() << endl;
      	chi2 = ff->GetChisquare()/float(ff->GetNDF());
        par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
      	cout << "chi2 = " << chi2 << endl;
	}
	cout << "parameters : " << par[0] << " " << par[1] << " " << par[2] << endl;

      	str_volt = "unknownvoltage";
      	if (hv->at(index_begin[istep]) > -820 and hv->at(index_begin[istep]) < -780)
	{ fit.c_800V = chi2; str_volt = "800V"; }
      	if (hv->at(index_begin[istep]) > -920 and hv->at(index_begin[istep]) < -880)
	{ fit.c_900V = chi2; str_volt = "900V"; }
      	if (hv->at(index_begin[istep]) > -1020 and hv->at(index_begin[istep]) < -980)
	{ fit.c_1000V = chi2; str_volt = "1000V"; }
      	if (hv->at(index_begin[istep]) > -1220 and hv->at(index_begin[istep]) < -1180)
	{ fit.c_1200V = chi2; str_volt = "1200V"; }
      	if (hv->at(index_begin[istep]) > -1420 and hv->at(index_begin[istep]) < -1380)
	{ fit.c_1400V = chi2; str_volt = "1400V"; }
      	if (hv->at(index_begin[istep]) > -1620 and hv->at(index_begin[istep]) < -1580)
	{ fit.c_1600V = chi2; str_volt = "1600V"; }
      	if (hv->at(index_begin[istep]) > -1820 and hv->at(index_begin[istep]) < -1780)
	{ fit.c_1800V = chi2; str_volt = "1800V"; }
        //string name = "fit/" + file + "_" + str_volt + ".png";
      	//if (chi2 > 5)
	//{
	TCanvas * c = new TCanvas("c","c",800,600);
      	gPad->SetLogy();
      	gc0->Draw("AP");
        c->Print(file.c_str());
	c->Close();
	//}
	
	for (i = index_begin[istep]; i < index_end[istep]; i++)
  	{
  	double t = time->at(i);
  	double val = cathode->at(i) - fexp(&t, par); 
    	cathode_out.push_back(val);
  	}
	
	//cout << "delete phase!" << endl;
	delete(gc0);
	//cout << "delete phase2!" << endl;
	fitX.clear(); 
	//cout << "delete phase3!" << endl;
	fitY.clear();
        fitYe.clear();
        fitXe.clear();
	//cout << "delete phase end!" << endl;
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

  for (i = 0; i < size; ++i)
  {
    cathode_out.push_back(cathode->at(i));
  }

}
