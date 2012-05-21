#include <LeakageSubtractor.h>

#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

#define skipAtVChange 10
#define skipAtLedChange 10


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
          if (voltageBegin+voltageStep-skipAtVChange < 0)
            {
              ++voltageStep;
              continue;
            }

          if (voltageBegin+voltageStep+skipAtVChange > fSize)
            {
              ++voltageStep;
              continue; //don't break because counter used to skip voltage
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
            std::cerr << "no fitting. not enoogh data in voltage set" << std::endl;
          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }

      if (fVerbosity)
        std::cout << "fitting with " << voltageStep << " datapoints in voltage set " << voltage << std::endl;

      TF1 theFcn ("a","[0]+[1]/TMath::Power(x,2.)");
      TGraphErrors theGraph(fitX.size(),&fitX.front(),&fitY.front(),NULL,&fitYe.front());
      TFitResultPtr theMin = theGraph.Fit(&theFcn,"S M E 0");
      int status = theMin;
      if (!status)
        {
          if (fVerbosity)
            std::cerr << "fit unsucessful" << std::endl;

          voltageBegin += voltageStep + 1; //jump to next voltage
          continue;
        }
      else
        {
          if (fVerbosity)
            std::cerr << "fit sucessful" << std::endl;
        }

      for (int j=0; j < voltageStep; j++)
        {
          theFcn.SetParameters(theMin->Parameter(0),theMin->Parameter(1));
          //std::cout << "x:" << fX[j+voltageBegin] << "/" << fX[voltageBegin+j]-fX[voltageBegin] << " ===  " << fY[j+voltageBegin] *1e12 << " ..... " << theFcn(fX[voltageBegin+j]-fX[voltageBegin]) << std::endl;
          fY[j+voltageBegin] -= float(1e-12 * theFcn(fX[j]-fX[voltageBegin]));
         // fY[j+voltageBegin] *= 1e12;
        }//subtract the leakage

      voltageBegin += voltageStep + 1; //jump to next voltage
    }
}

