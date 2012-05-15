#include <LeakageSubtractor.h>
#include <TFitterMinuit.h>
#include <cassert>
#include <stdexcept>
#include <iostream>

LeakageSubtractor::LeakageSubtractor(std::vector<double> &current, const std::vector<double> &high_V, const std::vector<double> &time, const std::vector<double> &led, const double error=2.) : fVerbosity(1), fSize(-1), fX(time), fY(current), fHigh_V(high_V), fLed(led)
{
  //gSystem->Load("libMinuit2");

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
  int i;
  for (i = 0; i<fSize; i++)
    {
      double voltage = fHigh_V[i];
      if (fVerbosity)
        std::cout << "Removing leakage for step U=" << voltage << " V" << std::endl;
      std::vector<double> fitX;
      std::vector<double> fitY;
      std::vector<double> fitYe;

      int xcounter = i + 1;//don't look at first value because picoamp meter screws this up
      while (fHigh_V[xcounter] == voltage)
        {
          if(fLed[xcounter] == 0)
            {
              fitY.push_back(xcounter); // always starts at 0
              fitY.push_back(fY[xcounter]*1e12);
              fitYe.push_back(fYe[xcounter]*1e12);
            } // copy the x,y values for one voltage set and only where LED was off
          ++xcounter;
        }
      //also don't look at last value
      fitX.pop_back();
      fitY.pop_back();
      fitYe.pop_back();

      TFitterMinuit theFitter;
      MyFCN fcn(fitX,fitY,fitYe);
      theFitter.SetMinuitFCN(&fcn);

      theFitter.SetParameter(0,"factor",60.,6.,10.,200.);
      theFitter.SetParameter(1,"decay length",450.,50.,50.,1000.);
      theFitter.SetParameter(2,"constant",80.,8.,0.,200.);

      // create Minimizer (default is Migrad)
      theFitter.CreateMinimizer();
      int iret = theFitter.Minimize();
      if (iret == 0) //fit successful
        {
          if (fVerbosity)
            std::cerr << "fit unsucessful" << std::endl;
          return;
        }

      for (int j=0; j < xcounter; j++)
        {
          fY[j+xcounter] -= theFitter.GetParameter(0) * exp(-fX[j+xcounter]/theFitter.GetParameter(1)) + theFitter.GetParameter(2);
        }//subtract the leakage

      i+=xcounter; //jump to next voltage
    }
}

