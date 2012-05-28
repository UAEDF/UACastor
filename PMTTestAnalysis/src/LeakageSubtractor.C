#include <LeakageSubtractor.h>

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

#define skipAtVChange 100
#define skipAtLedChange 3


LeakageSubtractor::LeakageSubtractor(const std::vector<int> &time, std::vector<float> &current, const std::vector<int> &high_V, const std::vector<int> &led, const float error) : fVerbosity(1), fSize(-1), fX(time), fY(current), fHigh_V(high_V), fLed(led)
{
  fSize = (int)current.size();
  assert(fSize == (int)fHigh_V.size());
  assert(fSize == (int)fX.size());

  for (int i = 0; i < fSize; ++i)
    {
      fYe.push_back(error);
    }

}
void LeakageSubtractor::Run()
{

gStyle->SetOptFit(1);

  int voltageBegin = 0;
  
  // ----loop over all voltage regions----
  while (voltageBegin < fSize)
    {
      // ----Skip 0 voltage run----
      while (abs(fHigh_V[voltageBegin]) < 50 && voltageBegin < fSize)
        {
          ++voltageBegin;
          continue;
        }

      int voltage = fHigh_V[voltageBegin];
      if (fVerbosity)
        std::cout << "Removing leakage for step U=" << voltage << " V" << std::endl;
      std::vector<double> fitX;
      std::vector<double> fitY;
      std::vector<double> fitYe;

      int voltageStep = 0;//don't look at first value because picoamp meter screws this up

      // ----loop in voltage region----
      while (fHigh_V[voltageBegin+voltageStep] > voltage-50 && fHigh_V[voltageBegin+voltageStep] < voltage+50 && voltageBegin+voltageStep < fSize)
        {
          //looking if led changes in last five or next five time bins
          if (voltageStep-skipAtVChange < 0)
            {
              ++voltageStep;
              continue;
            }

          if (voltageBegin+voltageStep > fSize)
            {
              ++voltageStep;
              continue; //don't break because counter used to skip voltage
            }

          if(fY[voltageBegin+voltageStep]*1e12 < 0. || fY[voltageBegin+voltageStep]*1e12 > 1e5) //weird value skip
            {
              ++voltageStep;
              continue;
            }

          if(fLed[voltageBegin+voltageStep-skipAtLedChange] || fLed[voltageBegin+voltageStep] || fLed[voltageBegin+voltageStep+skipAtLedChange])
            {
              ++voltageStep;
              continue;
            }

          // copy the x,y values for one voltage set and only where LED was off          
          fitX.push_back(fX[voltageBegin+voltageStep]-fX[voltageBegin]); // always starts at 0
          fitY.push_back(fY[voltageBegin+voltageStep]*1e12);
          fitYe.push_back(fYe[voltageBegin+voltageStep]*1e12);

          ++voltageStep;
        }

      if (fitX.size() <= 5) //not enough data for fit
        {
          if (fVerbosity)
            std::cerr << "no fitting. not enough data in voltage set" << std::endl;
          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }

      if (fVerbosity)
        std::cout << "fitting with " << voltageStep << " datapoints in voltage set " << voltage << std::endl;


      TF1 theFcn("a","[0]+[1]*TMath::Exp(-(x-[2])/[3])");
      theFcn.SetParameters(fitY.back(),40,60,fabs(voltage-800)<50.?650:350);
      theFcn.SetParLimits(3,200.,1200.);
      TGraphErrors theGraph (fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());
     // TFitResultPtr theMin = theGraph.Fit(&theFcn,fVerbosity>1?"S M E 0":"S M E 0 Q");

     TFitResultPtr theMin = theGraph.Fit(&theFcn);
      if (theMin == NULL || !theMin->Status() || theMin->IsValid() == 0)
        {
          std::cerr << "fit unsucessful" << std::endl;

          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }
      else
        {
          if (fVerbosity)
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
          if (fVerbosity>=3)
            std::cout << "x:" << fX[j+voltageBegin] << "/" << fX[voltageBegin+j]-fX[voltageBegin] << " ===  " << fY[j+voltageBegin] *1e12 << " ..... " << theFcn(fX[voltageBegin+j]-fX[voltageBegin]) << std::endl;
          // if any poles in the function just skip the subtraction. only the LED regions are of interest. but if the profile doesn't look nice one can delete this if
          if ((theFcn)(fX[j+voltageBegin]-fX[voltageBegin]) < 1e5 && (theFcn)(fX[j+voltageBegin]-fX[voltageBegin]) > 0)
            fY[j+voltageBegin] -= float(1e-12 * theFcn(fX[j+voltageBegin]-fX[voltageBegin]));
        }//subtract the leakage

      voltageBegin += voltageStep + 1; //jump to next voltage
    }
}

