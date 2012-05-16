#include <LeakageSubtractor.h>

#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameters.h"
#include "Minuit2/MnMigrad.h"
#include "TF1.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

LeakageSubtractor::LeakageSubtractor(const std::vector<int> &time, std::vector<float> &current, const std::vector<int> &high_V, const std::vector<int> &led, const float error) : fVerbosity(1), fSize(-1), fX(time), fY(current), fHigh_V(high_V), fLed(led)
{
  //gSystem->Load("libMinuit2");

  fSize = (int)current.size();
  assert(fSize == (int)fHigh_V.size());
  assert(fSize == (int)fX.size());

  for (int i = 0; i < fSize; ++i)
    {
      fYe.push_back(error);
    }


  theStartingValues.Add("constant",45.,4.5);
  theStartingValues.Add("factor",2e6,2e5);
}
void LeakageSubtractor::Run()
{
  int i = 0;
  while (i < fSize)
    {
      while (abs(fHigh_V[i]) < 50)
        {
          ++i;
          continue;
        }//Skip 0 voltage run

      int voltage = fHigh_V[i];
      if (fVerbosity)
        std::cout << "Removing leakage for step U=" << voltage << " V" << std::endl;
      std::vector<int> fitX;
      std::vector<float> fitY;
      std::vector<float> fitYe;

      int row = i + 5;//don't look at first value because picoamp meter screws this up
      if (row >= fSize)
        {
          if(fVerbosity)
            std::cout << "row at end" << std::endl;
          continue;
        }
      // loop in voltage region
      int newX = 0;
      while (fHigh_V[row] > voltage-50 && fHigh_V[row] < voltage+50 )
        {
          //looking if led changes in last five or next five time bins
          if (row-5 < 0)
            {
              ++row;
              continue;
            }
          if (row+5 >= fSize)
            break;
          if(fLed[row-5] == 0 && fLed[row] == 0 && fLed[row+5] == 0)
            {
              fitX.push_back(newX); // always starts at 0
              fitY.push_back(fY[row]*1e12);
              fitYe.push_back(fYe[row]*1e12);
            } // copy the x,y values for one voltage set and only where LED was off
          ++newX;
          ++row;
        }
      if (row <= 10) //not enough data for fit
        {
          if (fVerbosity)
            std::cerr << "no fitting. not enoogh data in voltage set" << std::endl;
          i+=row; //jump to next voltage
          continue;
        }

      //also don't look at last value
      fitX.pop_back();
      fitY.pop_back();
      fitYe.pop_back();

      if (fVerbosity)
        std::cout << "fitting with " << row << " datapoints in voltage set " << voltage << std::endl;

      MyFCN fcn(fitX,fitY,fitYe);

      ROOT::Minuit2::MnMigrad theMinimizer(fcn,theStartingValues);

      //Fitting
      ROOT::Minuit2::FunctionMinimum theMin = theMinimizer();
      if (theMin.IsValid() != 1)
        {
          if (fVerbosity)
            std::cerr << "fit unsucessful" << std::endl;

          //i+=row; //jump to next voltage
          //continue;
        }
      else
        {
          if (fVerbosity)
            std::cerr << "fit sucessful" << std::endl;
        }
      std::cout << theMin.Fval() << std::endl;

      for (int j=0; j < row; j++)
        {
          TF1 theFcn ("a","[0]+[1]/TMath::Power(x,2.)");
          theFcn.SetParameters(theMin.UserParameters().Value(0),theMin.UserParameters().Value(1));
          std::cout << "x:" << j+i << "   " << fY[j+i] *1e12 << " - " << theFcn(fX[j+i]) << std::endl;
          fY[j+i] -= float(1e-12 * theFcn(fX[j+i]));
          fY[j+i] *= 1e12;
        }//subtract the leakage

      i+=row; //jump to next voltage
    }
}

