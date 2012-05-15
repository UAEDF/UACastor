#ifndef LEAKAGE_SUBTRACTOR__H__
#define LEAKAGE_SUBTRACTOR__H__

#include "Minuit2/FCNBase.h"
#include "Minuit2/MnUserParameters.h"

#include <vector>
#include <stdexcept>
#include <iostream>

class LeakageSubtractor
{

 private:
  int fVerbosity;
  int fSize;
  ROOT::Minuit2::MnUserParameters theStartingValues;
  const std::vector<double> &fX;
  std::vector<double> &fY;
  std::vector<double> fYe;
  const std::vector<double> &fHigh_V;
  const std::vector<double> &fLed;

  void SetStartParameters();

 public:
  LeakageSubtractor(const std::vector<double> &time, std::vector<double> &current, const std::vector<double> &high_V, const std::vector<double> &led, const double error=2.);///Constructor. Add reference to the current. This will be modified. Also needed: time, the high voltage, and led.
  ~LeakageSubtractor()
    {
    }///Destructor
  void Run();///This will do the actual subtraction
  void SetVerbosity(int v) {fVerbosity = v;}
};
///Fits and subtracts the exponential decay in kathode current. Peaks of LED light turned on are isolated by this. Set required voltage.

class MyFCN : public ROOT::Minuit2::FCNBase
{

 public:

 MyFCN(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& ye, double a = 60., double tau = 450., double c = 80.) : fX(x), fY(y), fYe(ye), fA(a), fTau(tau), fC(c) {}

  double operator() (const std::vector<double> & parameters) const
  {
    assert(parameters.size() % 3 == 0); //writes error if notes
    double chi2 = 0.;
    for(unsigned int n = 0; n < fX.size(); n++)
      {
        // Propagation of uncertainty. no correlation taken into account.
        // var= (sigma_meas² + sigma_usp1² + sigma_usp2² +...)
        double resid = fY[n] - parameters[0] * exp(-fX[n]/parameters[1]) + parameters[2];
        double var = fYe[n] * fYe[n];
        if (var != 0)
          chi2 += resid * resid / var;
        else
          {
            std::cerr << "!!!USP fit could be compromised (Variance=0)." << std::endl;
            chi2 += 100000000000.;
          }
      }
    return chi2;
  }

  double Up() const { return 1.; }

 private:

  const std::vector<double>& fX;
  const std::vector<double>& fY;
  const std::vector<double>& fYe;
  double fA;
  double fTau;
  double fC;

};

#endif //LEAKAGE_SUBTRACTOR__H__
