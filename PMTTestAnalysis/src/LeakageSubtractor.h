#ifndef LEAKAGE_SUBTRACTOR__H__
#define LEAKAGE_SUBTRACTOR__H__

#include <vector>
#include <stdexcept>
#include <iostream>

class LeakageSubtractor
{

 private:
  int fVerbosity;
 int fSize;
  const std::vector<int> &fX;
  std::vector<float> &fY;
  std::vector<float> fYe;
  const std::vector<int> &fHigh_V;
  const std::vector<int> &fLed;

 public:
  LeakageSubtractor(const std::vector<int> &time, std::vector<float> &current, const std::vector<int> &high_V, const std::vector<int> &led, const float error=3.e-12);///Constructor. Add reference to the current. This will be modified. Also needed: time, the high voltage, and led.
  ~LeakageSubtractor()
    {
    }///Destructor
  void Run();///This will do the actual subtraction
  void SetVerbosity(int v) {fVerbosity = v;}
};
///Fits and subtracts the exponential decay in kathode current. Peaks of LED light turned on are isolated by this. Set required voltage.



/* class MyFCN : public ROOT::Minuit2::FCNBase */
/* { */

/*  public: */

/*  MyFCN(const std::vector<int>& x, const std::vector<float>& y, const std::vector<float>& ye, double a = 60., double tau = 450., double c = 80.) : fX(x), fY(y), fYe(ye), fA(a), fTau(tau), fC(c) {} */

/*   double operator() (const std::vector<double> & parameters) const */
/*   { */
/*     assert(parameters.size() == 2); //writes error if notes */
/*     int size = int(fY.size()); */
/*     assert(int(fX.size()) == size); */
/*     assert(int(fYe.size()) == size); */
/*     TF1 calculate("a","[0]+[1]/TMath::Power(x,2.)"); //copy because operator needs to be const */
/*     calculate.SetParameters(parameters[0],parameters[1]); */
/*     double chi2 = 0.; */
/*     for(int n = 0; n < size; n++) */
/*       { */
/*         // Propagation of uncertainty. no correlation taken into account. */
/*         // var= (sigma_meas² + sigma_usp1² + sigma_usp2² +...) */
/*         double resid = double(fY[n]) - calculate(double(fX[n])); */
/*         double var = double(fYe[n]) * double(fYe[n]); */
/*         if (var != 0) */
/*           chi2 += resid * resid / var; */
/*         else */
/*           { */
/*             std::cerr << "!!!USP fit could be compromised (Variance=0)." << std::endl; */
/*             chi2 += 100000000000.; */
/*           } */
/*       } */
/*     return chi2; */
/*   } */

/*   double Up() const { return 1.; } */

/*  private: */

/*   const std::vector<int>& fX; */
/*   const std::vector<float>& fY; */
/*   const std::vector<float>& fYe; */
/*   double fA; */
/*   double fTau; */
/*   double fC; */

/* }; */

#endif //LEAKAGE_SUBTRACTOR__H__
