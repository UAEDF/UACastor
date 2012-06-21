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

void LeakageSubtractor(const std::vector<float> *time, std::vector<float> *cathode, const std::vector<float> *hv, const std::vector<float> *led, std::string file, std::vector<float>& cathode_out, chi2& fit ){

// 1 -> tries different values
// 2 -> uses the value of the last fit as input to the next
int type_minimization = 2;

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
int step[7]={800, 900, 1000, 1200, 1400, 1600, 1800}; 
//write the endex of the beginning and the end of the hv regions into an array
int voltageStep[7] = {0,0,0,0,0,0,0};
int index_begin[7] = {0,0,0,0,0,0,0};
int index_end[7] = {0,0,0,0,0,0,0};
int istep, i; 

int fcount=0;
bool repeate=true;
double ini1[5] = {1.0e-12, 1.0e-11, 1.0e-10, 1.0e-9, 1.0e-8};
double shifts_begin[8] = {0, 50, 100, 150, 200, 250, 300, 350};
double shifts_end[6] = {0, 50, 100, 150, 200, 250};
double ini3[5] = {100, 200, 300, 400, 500};
double ini2[6] = {1.0e-12, 1.0e-11, 1.0e-10, 1.0e-9, 1.0e-8, 1.0e-7};
int ini2_count = 0;
int ini3_count = 0;
int begin_count = 0;
int end_count = 0;
float better_chi2 = 0.0;
int better[5] = {0, 0, 0, 0};
double par[3] = {0, 0, 0};

  for (i = 0; i < size; i++)
  {
    cathode_ye.push_back(error);
    cathode_out.push_back(cathode->at(i));
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
	// cout << "========" << hv[index_begin[istep]] << "===========" << endl


   // TGraphErrors has to be defined befor TF1 (the fit function)
   TGraphErrors *gc0 = new TGraphErrors(fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());

	TCanvas * c = new TCanvas("c","c",800,600);
      	//gPad->SetLogy();
	str_volt = str_volt + ";Time [s];Current [V]";
	TF1 *ff = 0;

    TVirtualFitter::SetMaxIterations(3000);

if (type_minimization == 2)
{
	float par_temp[3] = {1e-9, 1e-7, 300.};
	par[0] = 0;
	par[1] = 0;
	par[2] = 0;
	int max_tries = 70;
	int tries = 0;

while (repeate && tries < max_tries && fitX.size() > 100) {

	//cout << "fcount = " << fcount << " begin_count = " << begin_count << "end_count = " << end_count << endl;
      ff = new TF1("ff", fexp, time->at(index_begin[istep]) + 100, time->at(index_end[istep]) - 50, 3);
      ff->SetLineColor(4);
      ff->SetParameter(0, par_temp[0]);
      ff->SetParameter(1, par_temp[1]);
      ff->SetParameter(2, par_temp[2]);
      //cout << "ini par[1] = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << endl;
      gc0->Fit("ff","ERQ");
      //cout << "=> " << gMinuit->fCstatu.Data() << endl;
      chi2 = ff->GetChisquare()/float(ff->GetNDF());
      //cout << "chi2 = " << chi2 << endl;
      repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (ff->GetParameter(1)<0) || (ff->GetParameter(0)<0) || chi2 > 2.0);
	
	if (better_chi2 == 0.0 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	better_chi2 = chi2;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	par_temp[0] = ff->GetParameter(0);
	par_temp[1] = ff->GetParameter(1);
	par_temp[2] = ff->GetParameter(2);
	//cout << "Chi2 of the first approach = " << chi2 << endl;
	}
	if (better_chi2 > chi2 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	//cout << "ini par = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << " ini3 = " << ini3[ini3_count]<< endl;
	//cout << "=> " << gMinuit->fCstatu.Data() << endl;
	//cout << "chi2 = " << chi2 << endl;
	better_chi2 = chi2;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	par_temp[0] = ff->GetParameter(0);
	par_temp[1] = ff->GetParameter(1);
	par_temp[2] = ff->GetParameter(2);
	}
	else
	{
	if (tries%6 == 0) { par_temp[0] = par[0] * 1.1; }
	if (tries%6 == 1) { par_temp[0] = par[0] * 0.9; }
	if (tries%6 == 2) { par_temp[1] = par[1] * 1.1; }
	if (tries%6 == 3) { par_temp[1] = par[1] * 0.9; }
	if (tries%6 == 4) { par_temp[2] = par[2] * 1.1; }
	if (tries%6 == 5) { par_temp[2] = par[2] * 0.9; }
	}
	tries = tries + 1;
	//cout << tries << " > " << better_chi2 << " ~ " << par[0] << " ; " << par[1] << " ; " << par[2] << endl;
	}


if (type_minimization == 1 or chi2 > 5.0)
{

if (chi2 > chi2_threshold)
{
par[0] = 0.0;
par[1] = 0.0;
par[2] = 0.0;
better_chi2 = 0.0;
}

    while (repeate && fcount < 5 && begin_count < 8 && end_count < 6 && ini3_count < 5 && ini2_count < 6 && fitX.size() > 100) {

	//cout << "fcount = " << fcount << " begin_count = " << begin_count << "end_count = " << end_count << endl;
      ff = new TF1("ff", fexp, time->at(index_begin[istep]) + shifts_begin[begin_count], time->at(index_end[istep]) - shifts_end[end_count], 3);
      ff->SetLineColor(3);

      ff->SetParameter(0, ini1[fcount]);
      ff->SetParameter(1, ini2[ini2_count]);
      ff->SetParameter(2, ini3[ini3_count]);

      //cout << "ini par[1] = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << endl;
      gc0->Fit("ff","ERQ");
      //cout << "=> " << gMinuit->fCstatu.Data() << endl;
      chi2 = ff->GetChisquare()/float(ff->GetNDF());
      //cout << "chi2 = " << chi2 << endl;
      repeate = ( (gMinuit->fCstatu.Data()[0]!='S') || (ff->GetParameter(1)<0) || (ff->GetParameter(0)<0) || chi2 > 2.0);
	
	if (better_chi2 == 0.0 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	better_chi2 = chi2;
	better[0] = fcount;
	better[1] = begin_count;
	better[2] = end_count;
	better[3] = ini3_count;
	better[4] = ini2_count;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	cout << "Chi2 of the first approach = " << chi2 << endl;
	}
	if (better_chi2 > chi2 and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
	{
	//cout << "ini par = " << ini1[fcount] << " begin_shift = " << shifts_begin[begin_count] << " end_shift = " << - shifts_end[end_count] << " ini3 = " << ini3[ini3_count]<< endl;
	//cout << "=> " << gMinuit->fCstatu.Data() << endl;
	//cout << "chi2 = " << chi2 << endl;
	better_chi2 = chi2;
	better[0] = fcount;
	better[1] = begin_count;
	better[2] = end_count;
	better[3] = ini3_count;
	better[4] = ini2_count;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	}
	ini2_count++;
	if (ini2_count == 6) { ini3_count++; ini2_count = 0; }
	if (ini3_count == 5) { end_count++; ini3_count = 0; }
	if (end_count == 6) { begin_count++; end_count = 0; }
	if (begin_count == 8) { fcount++; begin_count = 0; }
	}

	if (better_chi2 > 2.0)
	{
	cout << "none of the fits was very good, using the best one!" << endl;
        int sb = shifts_begin[better[1]];
	int se = shifts_end[better[2]];
	float ig = ini1[better[0]];
	float i3 = ini3[better[3]];
	float i2 = ini2[better[4]];
	cout << better[0] << " " << better[1] << " " << better[2] << " " << better[3] << " " << better[4] << endl;
	cout << ig << " " << sb << " " << se << " " << i3 << " " << i2 << endl;
	ff = new TF1("ff", fexp, time->at(index_begin[istep]) + sb, time->at(index_end[istep]) - se, 3);
	ff->SetLineColor(2);
	if (better_chi2 < 15.0) { ff->SetLineColor(3); }
      	ff->SetParameter(0, ig);
	ff->SetParameter(1, i2);
      	ff->SetParameter(2, i3);
	gc0->Fit("ff","ERQ");
   	cout << "=> " << gMinuit->fCstatu.Data() << endl;
      	chi2 = ff->GetChisquare()/float(ff->GetNDF());
	if (chi2 < chi2_threshold and gMinuit->fCstatu.Data()[0]=='S' and ff->GetParameter(1)>0 and ff->GetParameter(0)>0)
        {
        ff->SetLineColor(3);
	better_chi2 = chi2;
	par[0] = ff->GetParameter(0);
	par[1] = ff->GetParameter(1);
	par[2] = ff->GetParameter(2);
	}
	else
	{
        cout << "the fit was bad!" << endl;
	}
      	cout << "chi2 = " << chi2 << endl;
	}
}


	cout << "parameters : " << par[0] << " " << par[1] << " " << par[2] << endl;
	
	if (better_chi2 < chi2_threshold and better_chi2 != 0.0 and par[0]>0 ) // and par[1]>0)
	{
	cout<<"good fit = " << better_chi2 << " subtracting backgroung now!" << endl;
	for (i = index_begin[istep]; i < index_end[istep]; i++)
  	{
  	double t = time->at(i);
  	double val = cathode->at(i) - fexp(&t, par); 
    	cathode_out.at(i) = val;
  	}
	}
	else
	{
	cout << "The fit was bad, no background subtraction will be done" << endl;
	}
}	

	if (chi2 == 0) { cout << "No fit was sucessfull at all!" << endl; chi2 = 1000; }
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

        gc0->SetTitle(str_volt.c_str());
	gc0->SetMaximum(2*par[0]);
	gc0->SetMinimum(0);
      	gc0->Draw("AP");
        c->Print(file.c_str());
	c->Close();


	par[0] = 0.0;
	par[1] = 0.0;
	par[2] = 0.0;
	better_chi2 = 0.0;
	better[0] = 0;
	better[1] = 0;
	better[2] = 0;
	better[3] = 0;
	fcount = 0;
	repeate = true;
	ini3_count = 0;
	begin_count = 0;
	end_count = 0;
	delete(gc0);
	fitX.clear(); 
	fitY.clear();
        fitYe.clear();
        fitXe.clear();
       }
       else
       { cout << "voltage not found!" << endl;
       }
 
}

  //for (i = 0; i < size; ++i)
  //{
  //  cathode_out.push_back(cathode->at(i));
  //}

}
