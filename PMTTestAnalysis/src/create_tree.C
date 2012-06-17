//to do:	correct bug on the index finding for the estimation of the dark current
//		sometimes the qe plot is missing
//		sometimes the range for the fit plot is wrong!
//		fix the range for the gain plot -> use an empty histogram
//		rms plus deviation from 0 for anodes
//		rms plus deviation from 0 for reference
//		anode plateau variation
//		fix the plots on the reference for led 2, 3 and 4

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//root lib
#include "TH1.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFile.h"

//structures
struct measurement {
	float cath_value;
	float cath_error;
	int cath_spikes;
	int cath_points;
	float anode_up;
	float anode_down;
	float ref_up;
	float ref_down;
	float gain;
	float qe;
};

struct chi2 {
	float c_800V;
	float c_900V;
	float c_1000V;
	float c_1200V;
	float c_1400V;
	float c_1600V;
	float c_1800V;
};

float chi2_threshold = 15.0;

void spike_check(float point, std::vector<float> *vec_cath, int& spike)
{

float ave, dev;

//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;

ave = (vec_cath->at(point-2) + vec_cath->at(point-1) + vec_cath->at(point+1) + vec_cath->at(point+2))/4.0;

dev = (vec_cath->at(point) - ave)/ave;

if (dev > 0.15 and abs(vec_cath->at(point)) > 1e-13)
{
cout<<"Positive spike! "<<dev<<endl;
//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;
spike = 1;
}
if (dev < -0.15 and abs(vec_cath->at(point)) > 1e-13)
{
cout<<"Negative spike! "<<dev<<endl;
//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;
spike = 1;
}

}

//user
#include "LeakageSubtractor.C"

void set_coordinates(string pmt, int& module, int& sector, int& set)
{

//old pmts in castor
if (pmt == "CA1579") { sector = 4;  module = 1;  set = 1; }
if (pmt == "CA3399") { sector = 1;  module = 2;  set = 1; }
if (pmt == "CA0683") { sector = 13; module = 1;  set = 1; }
if (pmt == "CA0540") { sector = 13; module = 2;  set = 1; }
if (pmt == "CA3362") { sector = 14; module = 1;  set = 1; }
if (pmt == "CA0625") { sector = 3;  module = 2;  set = 1; }
if (pmt == "CA0715") { sector = 15; module = 2;  set = 1; }
if (pmt == "CA1832") { sector = 5;  module = 2;  set = 1; }
if (pmt == "CA0857") { sector = 14; module = 2;  set = 1; }
if (pmt == "CA0886") { sector = 15; module = 1;  set = 1; }
if (pmt == "CA1549") { sector = 5;  module = 1;  set = 1; }
if (pmt == "CA1617") { sector = 6;  module = 1;  set = 1; }
if (pmt == "CA0742") { sector = 6;  module = 2;  set = 1; }
if (pmt == "CA3236") { sector = 11; module = 2;  set = 1; }
if (pmt == "CA0829") { sector = 10; module = 1;  set = 1; }
if (pmt == "CA0948") { sector = 12; module = 1;  set = 1; }
if (pmt == "CA1263") { sector = 10; module = 2;  set = 1; }
if (pmt == "CA1200") { sector = 9;  module = 2;  set = 1; }
if (pmt == "CA1829") { sector = 9;  module = 1;  set = 1; }
if (pmt == "CA1431") { sector = 11; module = 1;  set = 1; }
if (pmt == "CA1593") { sector = 12; module = 2;  set = 1; }
if (pmt == "CA0327") { sector = 2;  module = 2;  set = 1; }
if (pmt == "CA1680") { sector = 16; module = 2;  set = 1; }
if (pmt == "CA0558") { sector = 16; module = 1;  set = 1; }
if (pmt == "CA0574") { sector = 1;  module = 1;  set = 1; }
if (pmt == "CA1842") { sector = 2;  module = 1;  set = 1; }
if (pmt == "CA0812") { sector = 4;  module = 2;  set = 1; }
if (pmt == "CA1592") { sector = 3;  module = 1;  set = 1; }
if (pmt == "CA0892") { sector = 8;  module = 10; set = 1; }
if (pmt == "CA1620") { sector = 7;  module = 10; set = 1; }
if (pmt == "CA1321") { sector = 7;  module = 1;  set = 1; }
if (pmt == "CA1537") { sector = 8;  module = 1;  set = 1; }
if (pmt == "CA3386") { sector = 7;  module = 2;  set = 1; }
if (pmt == "CA1954") { sector = 8;  module = 2;  set = 1; }
if (pmt == "CA0723") { sector = 4;  module = 3;  set = 1; }
if (pmt == "CA1438") { sector = 3;  module = 3;  set = 1; }
if (pmt == "CA0640") { sector = 2;  module = 3;  set = 1; }
if (pmt == "CA0126") { sector = 1;  module = 3;  set = 1; }
if (pmt == "CA1524") { sector = 4;  module = 4;  set = 1; }
if (pmt == "CA1434") { sector = 3;  module = 4;  set = 1; }
if (pmt == "CA0885") { sector = 2;  module = 4;  set = 1; }
if (pmt == "CA1410") { sector = 1;  module = 4;  set = 1; }
if (pmt == "CA1387") { sector = 4;  module = 5;  set = 1; }
if (pmt == "CA1228") { sector = 3;  module = 5;  set = 1; }
if (pmt == "CA2044") { sector = 2;  module = 5;  set = 1; }
if (pmt == "CA0315") { sector = 1;  module = 5;  set = 1; }
if (pmt == "CA2623") { sector = 4;  module = 6;  set = 1; }
if (pmt == "CA0354") { sector = 3;  module = 6;  set = 1; }
if (pmt == "CA0979") { sector = 2;  module = 6;  set = 1; }
if (pmt == "CA0811") { sector = 1;  module = 6;  set = 1; }
if (pmt == "CA1984") { sector = 16; module = 3;  set = 1; }
if (pmt == "CA1316") { sector = 15; module = 3;  set = 1; }
if (pmt == "CA1634") { sector = 14; module = 3;  set = 1; }
if (pmt == "CA0535") { sector = 13; module = 3;  set = 1; }
if (pmt == "CA1141") { sector = 16; module = 4;  set = 1; }
if (pmt == "CA0793") { sector = 15; module = 4;  set = 1; }
if (pmt == "CA3184") { sector = 14; module = 4;  set = 1; }
if (pmt == "CA1327") { sector = 13; module = 4;  set = 1; }
if (pmt == "CA1759") { sector = 16; module = 5;  set = 1; }
if (pmt == "CA1161") { sector = 15; module = 5;  set = 1; }
if (pmt == "CA1131") { sector = 14; module = 5;  set = 1; }
if (pmt == "CA0792") { sector = 13; module = 5;  set = 1; }
if (pmt == "CA1495") { sector = 16; module = 6;  set = 1; }
if (pmt == "CA1538") { sector = 15; module = 6;  set = 1; }
if (pmt == "CA1844") { sector = 14; module = 6;  set = 1; }
if (pmt == "CA0292") { sector = 13; module = 6;  set = 1; }
if (pmt == "CA0045") { sector = 5;  module = 3;  set = 1; }
if (pmt == "CA0018") { sector = 6;  module = 3;  set = 1; }
if (pmt == "CA1350") { sector = 7;  module = 3;  set = 1; }
if (pmt == "CA1170") { sector = 8;  module = 3;  set = 1; }
if (pmt == "CA0326") { sector = 9;  module = 3;  set = 1; }
if (pmt == "CA1931") { sector = 10; module = 3;  set = 1; }
if (pmt == "CA1795") { sector = 11; module = 3;  set = 1; }
if (pmt == "CA0843") { sector = 12; module = 3;  set = 1; }
if (pmt == "CA1328") { sector = 5;  module = 4;  set = 1; }
if (pmt == "CA1442") { sector = 6;  module = 4;  set = 1; }
if (pmt == "CA2023") { sector = 7;  module = 4;  set = 1; }
if (pmt == "CA2022") { sector = 8;  module = 4;  set = 1; }
if (pmt == "CA0790") { sector = 9;  module = 4;  set = 1; }
if (pmt == "CA0143") { sector = 10; module = 4;  set = 1; }
if (pmt == "CA2034") { sector = 11; module = 4;  set = 1; }
if (pmt == "CA2018") { sector = 12; module = 4;  set = 1; }
if (pmt == "CA0977") { sector = 5;  module = 5;  set = 1; }
if (pmt == "CA0708") { sector = 6;  module = 5;  set = 1; }
if (pmt == "CA0072") { sector = 7;  module = 5;  set = 1; }
if (pmt == "CA1513") { sector = 8;  module = 5;  set = 1; }
if (pmt == "CA0299") { sector = 9;  module = 5;  set = 1; }
if (pmt == "CA0584") { sector = 10; module = 5;  set = 1; }
if (pmt == "CA1325") { sector = 11; module = 5;  set = 1; }
if (pmt == "CA1450") { sector = 12; module = 5;  set = 1; }
if (pmt == "CA1870") { sector = 5;  module = 6;  set = 1; }
if (pmt == "CA2060") { sector = 6;  module = 6;  set = 1; }
if (pmt == "CA1509") { sector = 7;  module = 6;  set = 1; }
if (pmt == "CA0796") { sector = 8;  module = 6;  set = 1; }
if (pmt == "CA1655") { sector = 9;  module = 6;  set = 1; }
if (pmt == "CA1525") { sector = 10; module = 6;  set = 1; }
if (pmt == "CA1966") { sector = 11; module = 6;  set = 1; }
if (pmt == "CA2046") { sector = 12; module = 6;  set = 1; }
if (pmt == "CA1530") { sector = 5; module = 7;  set = 1; }
if (pmt == "CA1501") { sector = 6; module = 7;  set = 1; }
if (pmt == "CA1979") { sector = 7; module = 7;  set = 1; }
if (pmt == "CA1808") { sector = 8; module = 7;  set = 1; }
if (pmt == "CA1760") { sector = 9; module = 7;  set = 1; }
if (pmt == "CA1691") { sector = 10; module = 7;  set = 1; }
if (pmt == "CA0696") { sector = 11; module = 7;  set = 1; }
if (pmt == "CA1377") { sector = 12; module = 7;  set = 1; }
if (pmt == "CA0084") { sector = 5; module = 8;  set = 1; }


//new ones first delivery
if (pmt == "BA0263") { sector = 4;  module = 1;  set = 2; }
if (pmt == "BA0264") { sector = 4;  module = 2;  set = 2; }
if (pmt == "BA0265") { sector = 4;  module = 3;  set = 2; }
if (pmt == "BA0267") { sector = 4;  module = 4;  set = 2; }
if (pmt == "BA0274") { sector = 4;  module = 5;  set = 2; }
if (pmt == "BA0275") { sector = 3;  module = 1;  set = 2; }
if (pmt == "BA0277") { sector = 3;  module = 2;  set = 2; }
if (pmt == "BA0278") { sector = 3;  module = 3;  set = 2; }
if (pmt == "BA0279") { sector = 3;  module = 4;  set = 2; }
if (pmt == "BA0287") { sector = 3;  module = 5;  set = 2; }
if (pmt == "BA0288") { sector = 2;  module = 1;  set = 2; }
if (pmt == "BA0291") { sector = 2;  module = 2;  set = 2; }
if (pmt == "BA0297") { sector = 2;  module = 3;  set = 2; }
if (pmt == "BA0300") { sector = 2;  module = 4;  set = 2; }
if (pmt == "BA0303") { sector = 2;  module = 5;  set = 2; }
if (pmt == "BA0304") { sector = 1;  module = 1;  set = 2; }
if (pmt == "BA0305") { sector = 1;  module = 2;  set = 2; }
if (pmt == "BA0307") { sector = 1;  module = 3;  set = 2; }
if (pmt == "BA0309") { sector = 1;  module = 4;  set = 2; }
if (pmt == "BA0311") { sector = 1;  module = 5;  set = 2; }

if (sector == 0 and module == 0 and set == 0) { cout<<"Unknown PMT"<<endl; }

}

void estimate_leakage(float ini_point, float end_point, std::vector<float> *vec_cath, float& leakage_mean, int& tot_points, int& total_spikes, float& leakage_error)
{

TH1D *leakage;

int spike = 0;
float l_low = 0, l_high = 0;

if (ini_point > 0 and end_point > 0)
{

for (int i = ini_point + 5; i <= end_point - 5; i++)
{
if (i == ini_point + 5) { l_low = vec_cath->at(i); }
if (l_high < vec_cath->at(i)) { l_high = vec_cath->at(i); }
if (l_low > vec_cath->at(i)) { l_low = vec_cath->at(i); }
}

leakage =  new TH1D("leakage","leakage;current", 100,l_low,l_high);

for (int i = ini_point + 5; i <= end_point - 5; i++)
{
spike_check(i, vec_cath, spike);
if (spike == 1) { total_spikes = total_spikes + 1;}
else { leakage->Fill(vec_cath->at(i));  tot_points = tot_points + 1; }
spike = 0;
}

leakage_mean = leakage->GetMean();
leakage_error = leakage->GetRMS();

delete(leakage);
}

//cout<<"Leakage estimated with "<<tot_points<<" points."<<endl;
}

void calc_eff(float cathode, float anode_up, float anode_down, float ref_up, float ref_down, float& gain, float& qe)
{

float anode_ave, ref_ave;

anode_ave = (anode_up + anode_down)/2;
ref_ave = (ref_up + ref_down)/2;

if (cathode > 0.0) { gain = anode_ave / cathode; }
if (ref_ave > 0.0) { qe =  cathode / ref_ave; }

//cout<<"ee = "<<ee<<" qe = "<<qe<<endl;

}


void gain_cathode(int ini_val, int end_val, std::vector<float> *vec_cath, double chi2, float& cath_gain, int& cath_spikes, float& cath_error, int& n_middle)
{
int lenght = vec_cath->size();

//cout<<"lenght = "<<lenght;

if (ini_val > 0 and end_val > 0 and end_val+30 < lenght)
{

TH1D *val_before;
TH1D *val_middle;
TH1D *val_after;

int spike;

float low_before = 0.0, high_before = 0.0;
float low_middle = 0.0, high_middle = 0.0;
float low_after  = 0.0, high_after  = 0.0;

int n_before = 0, n_after = 0;

float ave_before = 0.0, error_before = 0.0;
float ave_middle = 0.0, error_middle = 0.0;
float ave_after  = 0.0, error_after  = 0.0;

float ave_low = 0.0;
float dif_low = 0.0;

for (int i = 1; i <= 30; i++)
{
if (i == 1) { low_before = vec_cath->at(ini_val-1-i); }
if (high_before < vec_cath->at(ini_val-1-i)) { high_before = vec_cath->at(ini_val-1-i); }
if (low_before > vec_cath->at(ini_val-1-i)) { low_before = vec_cath->at(ini_val-1-i); }
}

for (int i = ini_val+7; i <= end_val-7; i++)
{
if (i == ini_val+7) { low_middle = vec_cath->at(i); }
if (high_middle < vec_cath->at(i)) { high_middle = vec_cath->at(i); }
if (low_middle > vec_cath->at(i)) { low_middle = vec_cath->at(i); }
}

for (int i = 1; i <= 30; i++)
{
if (i == 1) { low_after = vec_cath->at(end_val+6+i); }
if (high_after < vec_cath->at(end_val+6+i)) { high_after = vec_cath->at(end_val+6+i); }
if (low_after > vec_cath->at(end_val+6+i)) { low_after = vec_cath->at(end_val+6+i); }
}

val_before =  new TH1D("val_before","val_before;current", 100, low_before, high_before);
val_middle =  new TH1D("val_middle","val_middle;current", 100, low_middle, high_middle);
val_after  =  new TH1D("val_after","val_after;current", 100, low_after, high_after);

for (int i = 1; i <= 30; i++)
{
spike_check(ini_val-1-i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_before->Fill(vec_cath->at(ini_val-1-i)); n_before = n_before + 1; }
spike = 0;
}

for (int i = ini_val+7; i <= end_val-7; i++)
{
spike_check(i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_middle->Fill(vec_cath->at(i)); n_middle = n_middle + 1; }
spike = 0;
}

for (int i = 1; i <= 30; i++)
{
spike_check(end_val+6+i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_after->Fill(vec_cath->at(end_val+6+i)); n_after = n_after + 1; }
spike = 0;
//cout << "after " << i << " -> " << vec_cath->at(end_val+6+i) << " " << spike << endl;
} 

ave_before = val_before->GetMean();
error_before = val_before->GetRMS();
ave_middle = val_middle->GetMean();
error_middle = val_middle->GetRMS();
ave_after = val_after->GetMean();
error_after = val_after->GetRMS();

ave_low = (ave_before*n_before + ave_after*n_after)/(n_before+n_after);
dif_low = (ave_before*n_before - ave_after*n_after)/(n_before+n_after);

if (chi2 > chi2_threshold)
{
cath_gain = ave_middle - ave_low;
cath_error = (error_before*n_before + error_middle*n_middle + error_after+n_after)/(n_before + n_middle + n_after);
cath_error = sqrt(cath_error*cath_error*cath_gain*cath_gain + dif_low*dif_low);
cout << "Doing geometrical subtraction!" << endl;
}
else
{
cath_gain = ave_middle;
cath_error = sqrt(cath_gain*cath_gain*error_middle*error_middle + ave_low*ave_low);
}

if (chi2 > chi2_threshold)
{
cout << "chi2 : " << chi2 << endl;
cout << "value before : " << ave_before << endl;
cout << "value middle : " << ave_middle << endl;
cout << "value after  : " << ave_after  << endl;
cout << "value low    : " << ave_low  << endl;
cout << "cath gain    : " << cath_gain  << endl;
cout << "cath error   : " << cath_error  << endl;
}

delete(val_before);
delete(val_middle);
delete(val_after);

}

}

void calc_dif(size_t cent_val, std::vector<float> *vec_adut, std::vector<float> *vec_aref, std::vector<float> *vec_led, float& anode, float& ref)
{

size_t lenght = vec_adut->size();

//check the inputed values
//cout<<"central value = "<<cent_val<<endl;
if (cent_val > 0 and cent_val+20 < lenght)
{
//cout<<"hv begin = "<<vec_hv->at(cent_val-6)<<endl;
//cout<<"hv end = "<<vec_hv->at(cent_val+5)<<endl;
//cout<<"cath begin = "<<vec_cath->at(cent_val-6)<<endl;
//cout<<"cath end = "<<vec_cath->at(cent_val+5)<<endl;
//cout<<"anode begin = "<<vec_adut->at(cent_val-6)<<endl;
//cout<<"anode end = "<<vec_adut->at(cent_val+6)<<endl;
//cout<<"ref begin = "<<vec_aref->at(cent_val-5)<<endl;
//cout<<"ref end = "<<vec_aref->at(cent_val+6)<<endl;
//cout<<"led begin = "<<vec_led->at(cent_val-5)<<endl;
//cout<<"led end = "<<vec_led->at(cent_val+6)<<endl;

float ave_anode_before = 0, ave_anode_after = 0;
float ave_ref_before = 0, ave_ref_after = 0;

int tot_up = 30, tot_down = 30;

for (int i = 1; i <= 30; i++)
{
ave_anode_before = ave_anode_before + vec_adut->at(cent_val-1-i);
ave_ref_before = ave_ref_before + vec_aref->at(cent_val-1-i);
ave_anode_after = ave_anode_after + vec_adut->at(cent_val+6+i);
ave_ref_after = ave_ref_after + vec_aref->at(cent_val+6+i);

//cout<<i<<" anode A = "<<vec_adut->at(cent_val-1-i)<<endl;

//cout<<i<<" anode B = "<<vec_adut->at(cent_val+5+i)<<endl;

//cout<<i<<" ref A = "<<vec_aref->at(cent_val-1-i)<<endl;

//cout<<i<<" ref B = "<<vec_aref->at(cent_val+5+i)<<endl;
}
ave_anode_before = ave_anode_before/tot_up;
ave_anode_after = ave_anode_after/tot_down;
ave_ref_before = ave_ref_before/tot_up;
ave_ref_after = ave_ref_after/tot_down;

//cout<<"cath before = "<<ave_cath_before<<endl;
//cout<<"cath after = "<<ave_cath_after<<endl;
//cout<<"anode before = "<<ave_anode_before<<endl;
//cout<<"anode after = "<<ave_anode_after<<endl;
//cout<<"ref before = "<<ave_ref_before<<endl;
//cout<<"ref after = "<<ave_ref_after<<endl;

//calculate the gain
if (vec_led->at(cent_val-1) == 0)
{
anode = ave_anode_before - ave_anode_after;
ref = ave_ref_before - ave_ref_after;
}
if (vec_led->at(cent_val-1) > 0)
{
anode = ave_anode_after - ave_anode_before;
ref = ave_ref_after - ave_ref_before;
}

//check if it was correctly calculated
//cout<<"cath = "<<cath<<endl;
//cout<<"anode = "<<anode<<endl;
//cout<<"ref = "<<ref<<endl;
}

}


void do_measurement(int index_led_up, int index_led_down, std::vector<float> *vec_cath, std::vector<float> *vec_adut, std::vector<float> *vec_aref, std::vector<float> *vec_led, double chi2, measurement& meas, int& total_spikes)
{
//step on the anode and reference up
calc_dif(index_led_up, vec_adut, vec_aref, vec_led, meas.anode_up, meas.ref_up);
//step on the anode and reference down
calc_dif(index_led_down, vec_adut, vec_aref, vec_led, meas.anode_down, meas.ref_down);
//gain on the cathode
//cout << "cath amplitude before = " << meas.cath_value << endl;
gain_cathode(index_led_up, index_led_down, vec_cath, chi2, meas.cath_value, meas.cath_spikes, meas.cath_error, meas.cath_points);
//quantum efficiency and gain
//cout << "cath amplitude after = " << meas.cath_value << endl;
//cout << "cath error after = " << meas.cath_error << endl;
calc_eff(meas.cath_value, meas.anode_up, meas.anode_down, meas.ref_up, meas.ref_down, meas.gain, meas.qe);
//total number of spikes
//cout << "total spikes" << meas.cath_spikes << endl;
total_spikes = total_spikes + meas.cath_spikes;
}

void create_tree(string *files_in, int ini_file, int end_file, string tree_out)
{

double errorx = (0.5/16.6)*10E-12;
//double errory = 0.0;
std::vector<float> cathode_ye;


/*
//for the reports
int page_old = 1;
int canv_old = 1;
int page_new = 1;
int canv_new = 1;
TCanvas * r_new_gain = 0;
TCanvas * r_old_gain = 0;
TCanvas * r_new_qe = 0;
TCanvas * r_old_qe = 0;
TCanvas * r_new_cath = 0;
TCanvas * r_old_cath = 0;
*/

string title;

//float wave_lenght[4] = {400.0, 470.0, 500.0, 517.0};
float wave_lenght[3] = {400.0, 470.0, 500.0};
float wave1 = 400.0;
float voltages[7] = {800.0, 900.0, 1000.0, 1200.0, 1400.0, 1600.0, 1800.0};

float max_graph, min_graph;

//variable declaration
float cath, adut, aref, time, hv, led;
int entries, aux_int;

char read_time[20];
string ini_time, end_time;
string pmt, aux_str;

std::vector<int> vec_begin, vec_end;
std::vector<int> *pvec_begin, *pvec_end;

std::vector<float> vec_cath, control_anode_ref;
std::vector<float> vec_time, vec_cath_ori, vec_adut, vec_aref, vec_hv, vec_led;
std::vector<float> *pvec_time, *pvec_cath, *pvec_cath_ori, *pvec_adut, *pvec_aref, *pvec_hv, *pvec_led;
int total_spikes, sector, module, set, bad_fits;

int found1, found2, found3, set_unknown;
int total_unknown = 0;
int total_bad_fits = 0;

int index_800V_led1_up, index_800V_led1_down;
int index_800V_led2_up, index_800V_led2_down;
int index_800V_led3_up, index_800V_led3_down;
int index_800V_led4_up, index_800V_led4_down;
int index_900V_led1_up, index_900V_led1_down;
int index_1000V_led1_up, index_1000V_led1_down;
int index_1200V_led1_up, index_1200V_led1_down;
int index_1200V_led2_up, index_1200V_led2_down;
int index_1200V_led3_up, index_1200V_led3_down;
int index_1200V_led4_up, index_1200V_led4_down;
int index_1400V_led1_up, index_1400V_led1_down;
int index_1600V_led1_up, index_1600V_led1_down;
int index_1800V_led4_up, index_1800V_led4_down;

int index_leakage_0V_begin, index_leakage_0V_end;
int index_leakage_800V_begin, index_leakage_800V_end;
int index_leakage_900V_begin, index_leakage_900V_end;
int index_leakage_1000V_begin, index_leakage_1000V_end;
int index_leakage_1200V_begin, index_leakage_1200V_end;
int index_leakage_1400V_begin, index_leakage_1400V_end;
int index_leakage_1600V_begin, index_leakage_1600V_end;
int index_leakage_1800V_begin, index_leakage_1800V_end;

measurement m_800V_led1;
measurement m_800V_led2;
measurement m_800V_led3;
measurement m_800V_led4;

measurement m_900V_led1;

measurement m_1000V_led1;

measurement m_1200V_led1;
measurement m_1200V_led2;
measurement m_1200V_led3;
measurement m_1200V_led4;

measurement m_1400V_led1;

measurement m_1600V_led1;

measurement m_1800V_led4;

float leakage_0V, leakage_0V_error;
float leakage_800V, leakage_800V_error;
float leakage_900V, leakage_900V_error;
float leakage_1000V, leakage_1000V_error;
float leakage_1200V, leakage_1200V_error;
float leakage_1400V, leakage_1400V_error;
float leakage_1600V, leakage_1600V_error;
float leakage_1800V, leakage_1800V_error;

int leakage_0V_n, leakage_0V_spikes;
int leakage_800V_n, leakage_800V_spikes;
int leakage_900V_n, leakage_900V_spikes;
int leakage_1000V_n, leakage_1000V_spikes;
int leakage_1200V_n, leakage_1200V_spikes;
int leakage_1400V_n, leakage_1400V_spikes;
int leakage_1600V_n, leakage_1600V_spikes;
int leakage_1800V_n, leakage_1800V_spikes;

chi2 fit;

std::vector<float> chi2_temp;
std::vector<float> gains, gainsb, gainsc, gainsd, gains_bad;
std::vector<float> voltages_temp, voltages_tempb, voltages_tempc, voltages_tempd, voltages_temp_bad;
std::vector<float> volt_anodes, volt_anodesb, volt_anodesc, volt_anodesd;
std::vector<float> reference, referenceb, referencec, referenced;
std::vector<float> anodes, anodesb, anodesc, anodesd;
std::vector<float> cathodes, cathodesb, cathodesc, cathodesd;
std::vector<float> cathode_errors, cathode_errorsb, cathode_errorsc, cathode_errorsd;

int index_anodes = 0;
int index_anodesb = 0;
int index_anodesc = 0;
int index_anodesd = 0;

float volt1200V = 1200.0;

int index_temp2 = 0;
float max_volt = 0;
int index_temp = 0;
int index_tempb = 0;
int index_tempc = 0;
int index_tempd = 0;

float min_anode_plot;

float gain1200V;
float dum = 0.0;

TGraph *gc4a;
TGraph *gc4b;
TGraph *gc4c;
TGraph *gc4d;
TGraph *gc4e;
TGraph *gc4f;

//tree declaration
TTree *tree = new TTree("Castor_PMT_Caracterization_2012","Castor PMT Caracterization 2012");
tree->Branch("Measurement_begin","std::vector<int>",&pvec_begin);
tree->Branch("Measurement_end","std::vector<int>",&pvec_end);
tree->Branch("Entries",&entries,"Number of entries/I");
tree->Branch("Module",&module,"Castor module/I");
tree->Branch("Sector",&sector,"Castor sector/I");
tree->Branch("Set",&set,"Set of pmts/I");
tree->Branch("Measured_time","std::vector<float>",&pvec_time);
tree->Branch("HV","std::vector<float>",&pvec_hv);
tree->Branch("Cathode","std::vector<float>",&pvec_cath_ori);
tree->Branch("Cathode_after_background_subtraction","std::vector<float>",&pvec_cath);
tree->Branch("Anode","std::vector<float>",&pvec_adut);
tree->Branch("Reference_PMT","std::vector<float>",&pvec_aref);
tree->Branch("Led","std::vector<float>",&pvec_led);
tree->Branch("Number_of_spikes",&total_spikes,"Number of spikes found during the analysis/I");
tree->Branch("Number_of_bad_fits",&bad_fits,"Number of bad fits found during the analysis/I");
tree->Branch("m_800V_led1",&m_800V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_800V_led2",&m_800V_led2.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_800V_led3",&m_800V_led3.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_800V_led4",&m_800V_led4.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_900V_led1",&m_900V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1000V_led1",&m_1000V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1200V_led1",&m_1200V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1200V_led2",&m_1200V_led2.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1200V_led3",&m_1200V_led3.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1200V_led4",&m_1200V_led4.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1400V_led1",&m_1400V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1600V_led1",&m_1600V_led1.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("m_1800V_led4",&m_1800V_led4.cath_value,"cath_value/F:cath_error/F:cath_spikes/I:cath_points/I:anode_up/F:anode_down/F:ref_up/F:ref_down/F:gain/F:qe/F");
tree->Branch("Leakage_0V",&leakage_0V,"Current leakage at 0V");
tree->Branch("Leakage_0V_error",&leakage_0V_error,"Error on the current leakage at 0V");
tree->Branch("Leakage_0V_n",&leakage_0V_n,"Number of points used to estimate the current leakage at 0V/I");
tree->Branch("Leakage_0V_spikes",&leakage_0V_spikes,"Number of spikes found when estimate the current leakage at 0V/I");
tree->Branch("Leakage_800V",&leakage_800V,"Current leakage at 800V");
tree->Branch("Leakage_800V_error",&leakage_800V_error,"Error on the current leakage at 800V");
tree->Branch("Leakage_800V_n",&leakage_800V_n,"Number of points used to estimate the current leakage at 800V/I");
tree->Branch("Leakage_800V_spikes",&leakage_800V_spikes,"Number of spikes found when estimate the current leakage at 800V/I");
tree->Branch("Leakage_900V",&leakage_900V,"Current leakage at 900V");
tree->Branch("Leakage_900V_error",&leakage_900V_error,"Error on the current leakage at 900V");
tree->Branch("Leakage_900V_n",&leakage_900V_n,"Number of points used to estimate the current leakage at 900V/I");
tree->Branch("Leakage_900V_spikes",&leakage_900V_spikes,"Number of spikes found when estimate the current leakage at 900V/I");
tree->Branch("Leakage_1000V",&leakage_1000V,"Current leakage at 1000V");
tree->Branch("Leakage_1000V_error",&leakage_1000V_error,"Error on the current leakage at 1000V");
tree->Branch("Leakage_1000V_n",&leakage_1000V_n,"Number of points used to estimate the current leakage at 1000V/I");
tree->Branch("Leakage_1000V_spikes",&leakage_1000V_spikes,"Number of spikes found when estimate the current leakage at 1000V/I");
tree->Branch("Leakage_1200V",&leakage_1200V,"Current leakage at 1200V");
tree->Branch("Leakage_1200V_error",&leakage_1200V_error,"Error on the current leakage at 1200V");
tree->Branch("Leakage_1200V_n",&leakage_1200V_n,"Number of points used to estimate the current leakage at 1200V/I");
tree->Branch("Leakage_1200V_spikes",&leakage_1200V_spikes,"Number of spikes found when estimate the current leakage at 1200V/I");
tree->Branch("Leakage_1400V",&leakage_1400V,"Current leakage at 1400V");
tree->Branch("Leakage_1400V_error",&leakage_1400V_error,"Error on the current leakage at 1400V");
tree->Branch("Leakage_1400V_n",&leakage_1400V_n,"Number of points used to estimate the current leakage at 1400V/I");
tree->Branch("Leakage_1400V_spikes",&leakage_1400V_spikes,"Number of spikes found when estimate the current leakage at 1400V/I");
tree->Branch("Leakage_1600V",&leakage_1600V,"Current leakage at 1600V");
tree->Branch("Leakage_1600V_error",&leakage_1600V_error,"Error on the current leakage at 1600V");
tree->Branch("Leakage_1600V_n",&leakage_1600V_n,"Number of points used to estimate the current leakage at 1600V/I");
tree->Branch("Leakage_1600V_spikes",&leakage_1600V_spikes,"Number of spikes found when estimate the current leakage at 1600V/I");
tree->Branch("Leakage_1800V",&leakage_1800V,"Current leakage at 1800V");
tree->Branch("Leakage_1800V_error",&leakage_1800V_error,"Error on the current leakage at 1800V");
tree->Branch("Leakage_1800V_n",&leakage_1800V_n,"Number of points used to estimate the current leakage at 1800V/I");
tree->Branch("Leakage_1800V_spikes",&leakage_1800V_spikes,"Number of spikes found when estimate the current leakage at 1800V/I");
tree->Branch("Fit_chi2",&fit.c_800V,"c_800V/F:c_900V/F:c_1000V/F:c_1200V/F:c_1400V/F:c_1600V/F:c_1800V/F");

//loop over the pmt files
for (int i=ini_file-1; i < end_file; i++)
{

//open the cpt file
  string file = files_in[i];
  cout<<"File "<<i+1<<"/"<<end_file<<" -> "<<file<<endl;
  FILE *f = fopen( file.c_str() , "r");
  if(f==NULL) {
    std::cout << "can't find file\n";
    exit(1);
  }

//reseting the variables
entries = 0;
pmt = "";
ini_time = "";
end_time = "";
pvec_begin = &vec_begin;
pvec_end = &vec_end;
pvec_time = &vec_time;
pvec_hv = &vec_hv;
pvec_cath = &vec_cath;
pvec_cath_ori = &vec_cath_ori;
pvec_adut = &vec_adut;
pvec_aref = &vec_aref;
pvec_led = &vec_led;
vec_begin.clear();
vec_end.clear();
vec_time.clear();
vec_hv.clear();
vec_cath.clear();
vec_cath_ori.clear();
vec_adut.clear();
vec_aref.clear();
vec_led.clear();
control_anode_ref.clear();

total_spikes = 0;
bad_fits = 0;
module = 0;
sector = 0;
set = 0;

index_800V_led1_up = 0;
index_800V_led1_down = 0;
index_800V_led2_up = 0;
index_800V_led2_down = 0;
index_800V_led3_up = 0;
index_800V_led3_down = 0;
index_800V_led4_up = 0;
index_800V_led4_down = 0;
index_900V_led1_up = 0;
index_900V_led1_down = 0;
index_1000V_led1_up = 0;
index_1000V_led1_down = 0;
index_1200V_led1_up = 0;
index_1200V_led1_down = 0;
index_1200V_led2_up = 0;
index_1200V_led2_down = 0;
index_1200V_led3_up = 0;
index_1200V_led3_down = 0;
index_1200V_led4_up = 0;
index_1200V_led4_down = 0;
index_1400V_led1_up = 0;
index_1400V_led1_down = 0;
index_1600V_led1_up = 0;
index_1600V_led1_down = 0;
index_1800V_led4_up = 0;
index_1800V_led4_down = 0;

index_leakage_0V_begin = 0;
index_leakage_800V_begin = 0;
index_leakage_900V_begin = 0;
index_leakage_1000V_begin = 0;
index_leakage_1200V_begin = 0;
index_leakage_1400V_begin = 0;
index_leakage_1600V_begin = 0;
index_leakage_1800V_begin = 0;

index_leakage_0V_end = 0;
index_leakage_800V_end = 0;
index_leakage_900V_end = 0;
index_leakage_1000V_end = 0;
index_leakage_1200V_end = 0;
index_leakage_1400V_end = 0;
index_leakage_1600V_end = 0;
index_leakage_1800V_end = 0;

m_800V_led1.cath_value = 0.0;
m_800V_led1.cath_error = 0.0;
m_800V_led1.cath_spikes = 0;
m_800V_led1.cath_points = 0;
m_800V_led1.anode_up = 0.0;
m_800V_led1.anode_down = 0.0;
m_800V_led1.ref_up = 0.0;
m_800V_led1.ref_down = 0.0;
m_800V_led1.gain = 0.0;
m_800V_led1.qe = 0.0;

m_800V_led2.cath_value = 0.0;
m_800V_led2.cath_error = 0.0;
m_800V_led2.cath_spikes = 0;
m_800V_led2.cath_points = 0;
m_800V_led2.anode_up = 0.0;
m_800V_led2.anode_down = 0.0;
m_800V_led2.ref_up = 0.0;
m_800V_led2.ref_down = 0.0;
m_800V_led2.gain = 0.0;
m_800V_led2.qe = 0.0;

m_800V_led3.cath_value = 0.0;
m_800V_led3.cath_error = 0.0;
m_800V_led3.cath_spikes = 0;
m_800V_led3.cath_points = 0;
m_800V_led3.anode_up = 0.0;
m_800V_led3.anode_down = 0.0;
m_800V_led3.ref_up = 0.0;
m_800V_led3.ref_down = 0.0;
m_800V_led3.gain = 0.0;
m_800V_led3.qe = 0.0;

m_800V_led4.cath_value = 0.0;
m_800V_led4.cath_error = 0.0;
m_800V_led4.cath_spikes = 0;
m_800V_led4.cath_points = 0;
m_800V_led4.anode_up = 0.0;
m_800V_led4.anode_down = 0.0;
m_800V_led4.ref_up = 0.0;
m_800V_led4.ref_down = 0.0;
m_800V_led4.gain = 0.0;
m_800V_led4.qe = 0.0;

m_900V_led1.cath_value = 0.0;
m_900V_led1.cath_error = 0.0;
m_900V_led1.cath_spikes = 0;
m_900V_led1.cath_points = 0;
m_900V_led1.anode_up = 0.0;
m_900V_led1.anode_down = 0.0;
m_900V_led1.ref_up = 0.0;
m_900V_led1.ref_down = 0.0;
m_900V_led1.gain = 0.0;
m_900V_led1.qe = 0.0;

m_1000V_led1.cath_value = 0.0;
m_1000V_led1.cath_error = 0.0;
m_1000V_led1.cath_spikes = 0;
m_1000V_led1.cath_points = 0;
m_1000V_led1.anode_up = 0.0;
m_1000V_led1.anode_down = 0.0;
m_1000V_led1.ref_up = 0.0;
m_1000V_led1.ref_down = 0.0;
m_1000V_led1.gain = 0.0;
m_1000V_led1.qe = 0.0;

m_1200V_led1.cath_value = 0.0;
m_1200V_led1.cath_error = 0.0;
m_1200V_led1.cath_spikes = 0;
m_1200V_led1.cath_points = 0;
m_1200V_led1.anode_up = 0.0;
m_1200V_led1.anode_down = 0.0;
m_1200V_led1.ref_up = 0.0;
m_1200V_led1.ref_down = 0.0;
m_1200V_led1.gain = 0.0;
m_1200V_led1.qe = 0.0;

m_1200V_led2.cath_value = 0.0;
m_1200V_led2.cath_error = 0.0;
m_1200V_led2.cath_spikes = 0;
m_1200V_led2.cath_points = 0;
m_1200V_led2.anode_up = 0.0;
m_1200V_led2.anode_down = 0.0;
m_1200V_led2.ref_up = 0.0;
m_1200V_led2.ref_down = 0.0;
m_1200V_led2.gain = 0.0;
m_1200V_led2.qe = 0.0;

m_1200V_led3.cath_value = 0.0;
m_1200V_led3.cath_error = 0.0;
m_1200V_led3.cath_spikes = 0;
m_1200V_led3.cath_points = 0;
m_1200V_led3.anode_up = 0.0;
m_1200V_led3.anode_down = 0.0;
m_1200V_led3.ref_up = 0.0;
m_1200V_led3.ref_down = 0.0;
m_1200V_led3.gain = 0.0;
m_1200V_led3.qe = 0.0;

m_1200V_led4.cath_value = 0.0;
m_1200V_led4.cath_error = 0.0;
m_1200V_led4.cath_spikes = 0;
m_1200V_led4.cath_points = 0;
m_1200V_led4.anode_up = 0.0;
m_1200V_led4.anode_down = 0.0;
m_1200V_led4.ref_up = 0.0;
m_1200V_led4.ref_down = 0.0;
m_1200V_led4.gain = 0.0;
m_1200V_led4.qe = 0.0;

m_1400V_led1.cath_value = 0.0;
m_1400V_led1.cath_error = 0.0;
m_1400V_led1.cath_spikes = 0;
m_1400V_led1.cath_points = 0;
m_1400V_led1.anode_up = 0.0;
m_1400V_led1.anode_down = 0.0;
m_1400V_led1.ref_up = 0.0;
m_1400V_led1.ref_down = 0.0;
m_1400V_led1.gain = 0.0;
m_1400V_led1.qe = 0.0;

m_1600V_led1.cath_value = 0.0;
m_1600V_led1.cath_error = 0.0;
m_1600V_led1.cath_spikes = 0;
m_1600V_led1.cath_points = 0;
m_1600V_led1.anode_up = 0.0;
m_1600V_led1.anode_down = 0.0;
m_1600V_led1.ref_up = 0.0;
m_1600V_led1.ref_down = 0.0;
m_1600V_led1.gain = 0.0;
m_1600V_led1.qe = 0.0;

m_1800V_led4.cath_value = 0.0;
m_1800V_led4.cath_error = 0.0;
m_1800V_led4.cath_spikes = 0;
m_1800V_led4.cath_points = 0;
m_1800V_led4.anode_up = 0.0;
m_1800V_led4.anode_down = 0.0;
m_1800V_led4.ref_up = 0.0;
m_1800V_led4.ref_down = 0.0;
m_1800V_led4.gain = 0.0;
m_1800V_led4.qe = 0.0;

leakage_0V = 0.0;
leakage_800V = 0.0;
leakage_900V = 0.0;
leakage_1000V = 0.0;
leakage_1200V = 0.0;
leakage_1400V = 0.0;
leakage_1600V = 0.0;
leakage_1800V = 0.0;

leakage_0V_n = 0;
leakage_800V_n = 0;
leakage_900V_n = 0;
leakage_1000V_n = 0;
leakage_1200V_n = 0;
leakage_1400V_n = 0;
leakage_1600V_n = 0;
leakage_1800V_n = 0;

leakage_0V_spikes = 0;
leakage_800V_spikes = 0;
leakage_900V_spikes = 0;
leakage_1000V_spikes = 0;
leakage_1200V_spikes = 0;
leakage_1400V_spikes = 0;
leakage_1600V_spikes = 0;
leakage_1800V_spikes = 0;

leakage_0V_error = 0;
leakage_800V_error = 0;
leakage_900V_error = 0;
leakage_1000V_error = 0;
leakage_1200V_error = 0;
leakage_1400V_error = 0;
leakage_1600V_error = 0;
leakage_1800V_error = 0;

fit.c_800V = 0.0;
fit.c_900V = 0.0;
fit.c_1000V = 0.0;
fit.c_1200V = 0.0;
fit.c_1400V = 0.0;
fit.c_1600V = 0.0;
fit.c_1800V = 0.0;

set_unknown = 0;

chi2_temp.clear();

gains.clear();
gainsb.clear();
gainsc.clear();
gainsd.clear();
gains_bad.clear();

voltages_temp.clear();
voltages_tempb.clear();
voltages_tempc.clear();
voltages_tempd.clear();
voltages_temp_bad.clear();

anodes.clear();
anodesb.clear();
anodesc.clear();
anodesd.clear();

cathodes.clear();
cathodesb.clear();
cathodesc.clear();
cathodesd.clear();

cathode_errors.clear();
cathode_errorsb.clear();
cathode_errorsc.clear();
cathode_errorsd.clear();

reference.clear();
referenceb.clear();
referencec.clear();
referenced.clear();

volt_anodes.clear();
volt_anodesb.clear();
volt_anodesc.clear();
volt_anodesd.clear();

index_anodes = 0;
index_anodesb = 0;
index_anodesc = 0;
index_anodesd = 0;
index_temp = 0;
index_tempb = 0;
index_tempc = 0;
index_tempd = 0;

index_temp2 = 0;
max_volt = 0;

//find the code of the pmt
found1 = file.find("_");
found2 = file.find("_",found1+1);
found3 = file.find("_",found2+1);
pmt = file.substr(found2+1,found3-found2-1);

//reading the cpt file
while(!feof(f))
{
fscanf(f,"%s %f %f %f %f %f %f", read_time, &time, &hv, &cath, &adut, &aref, &led);
//cout<<read_time<<" "<<time<<" "<<hv<<" "<<cath<<" "<<adut<<" "<<aref<<" "<<led<<endl;
if (time == 0) { ini_time = (string) read_time; } //set begin time of the measurement
vec_time.push_back(time);
vec_hv.push_back(hv);
vec_cath_ori.push_back(cath);
//vec_cath.push_back(cath);
vec_adut.push_back(adut);
vec_aref.push_back(aref);
if (aref != 0 and adut != 0)
{
control_anode_ref.push_back(adut/aref);
}
else
{
control_anode_ref.push_back(0.0);
}
vec_led.push_back(led);
entries = entries + 1; //update the number of stored entries
}

/*
LeakageSubtractor theSubtractor(vec_time,vec_cath,vec_hv,vec_led);
theSubtractor.SetVerbosity(0);
theSubtractor.Run();
*/

max_graph = 0.0;
min_graph = 1;

  for (unsigned int j = 0; j < vec_cath_ori.size(); j++)
  {
    cathode_ye.push_back(errorx);
    if (vec_cath_ori.at(j) > max_graph and vec_led.at(j) > 0) { max_graph = vec_cath_ori.at(j); }
    if (vec_cath_ori.at(j) < min_graph and vec_cath_ori.at(j) > 0.0 and abs(vec_hv.at(j)) > 20.0) { min_graph = vec_cath_ori.at(j); }
  }
max_graph = max_graph * 1.5;
min_graph = min_graph * 0.8;

string file2 = file.substr(15,26);
string name2 = "plots/" + file2 + ".pdf";

//cout << "minimum for the graph = " << min_graph << endl;

	TCanvas * c1 = new TCanvas("c","c",800,600);
	TGraphErrors *gc1 = new TGraphErrors(entries,&vec_time.front(),&vec_cath_ori.front(),NULL,&cathode_ye.front());
	gc1->SetTitle("Cathode current as function of time before the background subtraction;time [s];Current [A]");
	gc1->SetMinimum(min_graph);
	gc1->SetMaximum(max_graph);
      	gc1->Draw("AP");
      	string name1 = "plots/" + file2 + ".pdf(";
        c1->Print(name1.c_str());
	c1->Close();

//cout << "size before : " << vec_cath_ori.size() << endl;
//cout << "begin of subtraction" << endl;
LeakageSubtractor(&vec_time, &vec_cath_ori, &vec_hv, &vec_led, name2, vec_cath, fit);
//cout << "end of subtraction" << endl;
//set the end time of the measurement
end_time = (string) read_time; 

//turn timestring into vector to get the year
aux_str = ini_time.substr(0,4);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(0,4);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

//turn timestring into vector to get the month
aux_str = ini_time.substr(5,2);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(5,2);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

//turn timestring into vector to get the day
aux_str = ini_time.substr(8,2);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(8,2);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

//turn timestring into vector to get the hour
aux_str = ini_time.substr(11,2);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(11,2);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

//turn timestring into vector to get the minutes
aux_str = ini_time.substr(14,2);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(14,2);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

//turn timestring into vector to get the secunds
aux_str = ini_time.substr(17,2);
aux_int = atoi( aux_str.c_str() );
vec_begin.push_back(aux_int);
aux_str = end_time.substr(17,2);
aux_int = atoi( aux_str.c_str() );
vec_end.push_back(aux_int);

set_coordinates(pmt, module, sector, set);
if (sector == 0 and module == 0 and set == 0) { total_unknown = total_unknown + 1; set_unknown = 1; }

//output the details of the measurement
cout<<"PMT code: "<<pmt<<" (Sector : "<<sector<<" ; Module : "<<module<<" ; Set: "<<set<<")"<<endl;
cout<<"Begin: "<<ini_time<<endl;
cout<<"End: "<<end_time<<endl;
cout<<"Entries "<<entries<<endl;
cout<<endl;

//finding the transition indexes
for (int j=0; j < entries; j++)
{
if (vec_hv[j] < -20 and vec_hv[j] > -780) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -820 and vec_hv[j] > -880) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -920 and vec_hv[j] > -980) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -1020 and vec_hv[j] > -1180) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -1220 and vec_hv[j] > -1380) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -1420 and vec_hv[j] > -1580) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -1620 and vec_hv[j] > -1780) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }
if (vec_hv[j] < -1820) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }

if (vec_hv[j] < 20 and vec_hv[j] > -20)
{
if (vec_hv[j+1] > 20 or vec_hv[j+1] < -20) { index_leakage_0V_end = j; }
if (vec_hv[j-1] > 20 or vec_hv[j-1] < -20) { index_leakage_0V_begin = j; index_leakage_0V_end = 0; }
if (vec_led[j-1] > 1) { index_leakage_0V_begin = j; index_leakage_0V_end = 0; }
}

if (vec_hv[j] < -780 and vec_hv[j] > -820)
{
if (vec_hv[j+1] > -780 or vec_hv[j+1] < -820) { index_leakage_800V_end = j; }
if (vec_hv[j-1] > -780 or vec_hv[j-1] < -820) { index_leakage_800V_begin = j; index_leakage_800V_end = 0; }
if (vec_led[j-1] > 0) { index_leakage_800V_begin = j; index_leakage_800V_end = 0; } 
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_800V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_800V_led1_down = j; }
if (vec_led[j] == 2 and vec_led[j-1] == 0 ) { index_800V_led2_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 2 ) { index_800V_led2_down = j; }
if (vec_led[j] == 3 and vec_led[j-1] == 0 ) { index_800V_led3_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 3 ) { index_800V_led3_down = j; }
if (vec_led[j] == 4 and vec_led[j-1] == 0 ) { index_800V_led4_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 4 ) { index_800V_led4_down = j; }
}

if (vec_hv[j] < -880 and vec_hv[j] > -920)
{
if (vec_hv[j+1] > -880 or vec_hv[j+1] < -920) { index_leakage_900V_end = j; }
if (vec_hv[j-1] > -880 or vec_hv[j-1] < -920) { index_leakage_900V_begin = j; index_leakage_900V_end = 0; }
if (vec_led[j-1] > 0) { index_leakage_900V_begin = j; index_leakage_900V_end = 0; }
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_900V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_900V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -980 and vec_hv[j] > -1020)
{
if (vec_hv[j+1] > -980 or vec_hv[j+1] < -1020) { index_leakage_1000V_end = j; }
if (vec_hv[j-1] > -980 or vec_hv[j-1] < -1020) { index_leakage_1000V_begin = j; index_leakage_1000V_end = 0;}
if (vec_led[j-1] > 0) { index_leakage_1000V_begin = j; index_leakage_1000V_end = 0;}
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1000V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1000V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -1180 and vec_hv[j] > -1220)
{
if (vec_hv[j+1] > -1180 or vec_hv[j+1] < -1220) { index_leakage_1200V_end = j; }
if (vec_hv[j-1] > -1180 or vec_hv[j-1] < -1220) { index_leakage_1200V_begin = j; index_leakage_1200V_end = 0; }
if (vec_led[j-1] > 0)  { index_leakage_1200V_begin = j; index_leakage_1200V_end = 0; }
if (vec_led[j] == 1 && vec_led[j-1] == 0 ) { index_1200V_led1_up = j; }
if (vec_led[j] == 0 && vec_led[j-1] == 1 ) { index_1200V_led1_down = j; }
if (vec_led[j] == 2 && vec_led[j-1] == 0 ) { index_1200V_led2_up = j; }
if (vec_led[j] == 0 && vec_led[j-1] == 2 ) { index_1200V_led2_down = j; }
if (vec_led[j] == 3 && vec_led[j-1] == 0 ) { index_1200V_led3_up = j; }
if (vec_led[j] == 0 && vec_led[j-1] == 3 ) { index_1200V_led3_down = j; }
if (vec_led[j] == 4 && vec_led[j-1] == 0 ) { index_1200V_led4_up = j; }
if (vec_led[j] == 0 && vec_led[j-1] == 4 ) { index_1200V_led4_down = j; }
}

if (vec_hv[j] < -1380 and vec_hv[j] > -1420)
{
if (vec_hv[j+1] > -1380 or vec_hv[j+1] < -1420) { index_leakage_1400V_end = j; }
if (vec_hv[j-1] > -1380 or vec_hv[j-1] < -1420) { index_leakage_1400V_begin = j; index_leakage_1400V_end = 0; }
if (vec_led[j-1] > 0) { index_leakage_1400V_begin = j; index_leakage_1400V_end = 0; }
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1400V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1400V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -1580 and vec_hv[j] > -1620)
{
if (vec_hv[j+1] > -1580 or vec_hv[j+1] < -1620) { index_leakage_1600V_end = j; }
if (vec_hv[j-1] > -1580 or vec_hv[j-1] < -1620) { index_leakage_1600V_begin = j; index_leakage_1600V_end = 0; }
if (vec_led[j-1] > 0) { index_leakage_1600V_begin = j; index_leakage_1600V_end = 0; }
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1600V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1600V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}


if (vec_hv[j] < -1780 and vec_hv[j] > -1820)
{
if (vec_hv[j+1] > -1780 or vec_hv[j+1] < -1820) { index_leakage_1800V_end = j; }
if (vec_hv[j-1] > -1780 or vec_hv[j-1] < -1820) { index_leakage_1800V_begin = j; index_leakage_1800V_end = 0; }
if (vec_led[j-1] > 0) { index_leakage_1800V_begin = j; index_leakage_1800V_end = 0; }
if (vec_led[j] == 4 and vec_led[j-1] == 0 ) { index_1800V_led4_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 4 ) { index_1800V_led4_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 1 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

}

//cout<<"so far so good!"<<endl;

//output the transition indexes
//cout<<"index 800V led1 up    = "<<index_800V_led1_up<<endl;
//cout<<"index 800V led1 down  = "<<index_800V_led1_down<<endl;
//cout<<"index 800V led2 up    = "<<index_800V_led2_up<<endl;
//cout<<"index 800V led2 down  = "<<index_800V_led2_down<<endl;
//cout<<"index 800V led3 up    = "<<index_800V_led3_up<<endl;
//cout<<"index 800V led3 down  = "<<index_800V_led3_down<<endl;
//cout<<"index 800V led4 up    = "<<index_800V_led4_up<<endl;
//cout<<"index 800V led4 down  = "<<index_800V_led4_down<<endl;
//cout<<"index 1000V led1 up    = "<<index_1000V_led1_up<<endl;
//cout<<"index 1000V led1 down  = "<<index_1000V_led1_down<<endl;
//cout<<"index 1200V led1 up   = "<<index_1200V_led1_up<<endl;
//cout<<"index 1200V led1 down = "<<index_1200V_led1_down<<endl;
//cout<<"index 1200V led2 up   = "<<index_1200V_led2_up<<endl;
//cout<<"index 1200V led2 down = "<<index_1200V_led2_down<<endl;
//cout<<"index 1200V led3 up   = "<<index_1200V_led3_up<<endl;
//cout<<"index 1200V led3 down = "<<index_1200V_led3_down<<endl;
//cout<<"index 1200V led4 up   = "<<index_1200V_led4_up<<endl;
//cout<<"index 1200V led4 down = "<<index_1200V_led4_down<<endl;
//cout<<"index 1400V led1 up    = "<<index_1400V_led1_up<<endl;
//cout<<"index 1400V led1 down  = "<<index_1400V_led1_down<<endl;

cout << "800V" << endl;
do_measurement(index_800V_led1_up, index_800V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_800V, m_800V_led1, total_spikes);
do_measurement(index_800V_led2_up, index_800V_led2_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_800V, m_800V_led2, total_spikes);
do_measurement(index_800V_led3_up, index_800V_led3_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_800V, m_800V_led3, total_spikes);
do_measurement(index_800V_led4_up, index_800V_led4_down, &vec_cath_ori, &vec_adut, &vec_aref, &vec_led, fit.c_800V, m_800V_led4, total_spikes);

cout << "900V" << endl;
do_measurement(index_900V_led1_up, index_900V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_900V, m_900V_led1, total_spikes);

cout << "1000V" << endl;
do_measurement(index_1000V_led1_up, index_1000V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1000V, m_1000V_led1, total_spikes);

cout << "1200V" << endl;
do_measurement(index_1200V_led1_up, index_1200V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1200V, m_1200V_led1, total_spikes);
do_measurement(index_1200V_led2_up, index_1200V_led2_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1200V, m_1200V_led2, total_spikes);
do_measurement(index_1200V_led3_up, index_1200V_led3_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1200V, m_1200V_led3, total_spikes);
do_measurement(index_1200V_led4_up, index_1200V_led4_down, &vec_cath_ori, &vec_adut, &vec_aref, &vec_led, fit.c_1200V, m_1200V_led4, total_spikes);

cout << "1400V" << endl;
do_measurement(index_1400V_led1_up, index_1400V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1400V, m_1400V_led1, total_spikes);

cout << "1600V" << endl;
do_measurement(index_1600V_led1_up, index_1600V_led1_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1600V, m_1600V_led1, total_spikes);

cout << "1800V" << endl;
do_measurement(index_1800V_led4_up, index_1800V_led4_down, &vec_cath, &vec_adut, &vec_aref, &vec_led, fit.c_1800V, m_1800V_led4, total_spikes);

//index output for the leakage estimation
//cout<<"0V     "<<index_leakage_0V_begin<<" "<<index_leakage_0V_end<<endl;
//cout<<"800V   "<<index_leakage_800V_begin<<" "<<index_leakage_800V_end<<endl;
//cout<<"900V   "<<index_leakage_900V_begin<<" "<<index_leakage_900V_end<<endl;
//cout<<"1000V  "<<index_leakage_1000V_begin<<" "<<index_leakage_1000V_end<<endl;
//cout<<"1200V  "<<index_leakage_1200V_begin<<" "<<index_leakage_1200V_end<<endl;
//cout<<"1400V  "<<index_leakage_1400V_begin<<" "<<index_leakage_1400V_end<<endl;
//cout<<"1600V  "<<index_leakage_1600V_begin<<" "<<index_leakage_1600V_end<<endl;
//cout<<"1800V  "<<index_leakage_1800V_begin<<" "<<index_leakage_1800V_end<<endl;

//leakage 0V
estimate_leakage(index_leakage_0V_begin, index_leakage_0V_end, &vec_cath_ori, leakage_0V, leakage_0V_n, leakage_0V_spikes, leakage_0V_error);
total_spikes = total_spikes + leakage_0V_spikes;

//leakage 800V
estimate_leakage(index_leakage_800V_begin, index_leakage_800V_end, &vec_cath_ori, leakage_800V, leakage_800V_n, leakage_800V_spikes, leakage_800V_error);
total_spikes = total_spikes + leakage_800V_spikes;

//leakage 900V
estimate_leakage(index_leakage_900V_begin, index_leakage_900V_end, &vec_cath_ori, leakage_900V, leakage_900V_n, leakage_900V_spikes, leakage_900V_error);
total_spikes = total_spikes + leakage_900V_spikes;

//leakage 1000V
estimate_leakage(index_leakage_1000V_begin, index_leakage_1000V_end, &vec_cath_ori, leakage_1000V, leakage_1000V_n, leakage_1000V_spikes, leakage_1000V_error);
total_spikes = total_spikes + leakage_1000V_spikes;

//leakage 1200V
estimate_leakage(index_leakage_1200V_begin, index_leakage_1200V_end, &vec_cath_ori, leakage_1200V, leakage_1200V_n, leakage_1200V_spikes, leakage_1200V_error);
total_spikes = total_spikes + leakage_1200V_spikes;

//leakage 1400V
estimate_leakage(index_leakage_1400V_begin, index_leakage_1400V_end, &vec_cath_ori, leakage_1400V, leakage_1400V_n, leakage_1400V_spikes, leakage_1400V_error);
total_spikes = total_spikes + leakage_1400V_spikes;

//leakage 1600V
estimate_leakage(index_leakage_1600V_begin, index_leakage_1600V_end, &vec_cath_ori, leakage_1600V, leakage_1600V_n, leakage_1600V_spikes, leakage_1600V_error);
total_spikes = total_spikes + leakage_1600V_spikes;

//leakage 1800V
estimate_leakage(index_leakage_1800V_begin, index_leakage_1800V_end, &vec_cath_ori, leakage_1800V, leakage_1800V_n, leakage_1800V_spikes, leakage_1800V_error);
total_spikes = total_spikes + leakage_1600V_spikes;

if (fit.c_800V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_900V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_1000V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_1200V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_1400V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_1600V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }
if (fit.c_1800V > chi2_threshold) { bad_fits = bad_fits + 1; total_bad_fits = total_bad_fits + 1; }

cout<<"Total spikes = "<<total_spikes<<endl;
cout<<"Total bad fits = "<<bad_fits<<endl;

float temp1[7] = {m_800V_led1.anode_up, m_900V_led1.anode_up, m_1000V_led1.anode_up, m_1200V_led1.anode_up, m_1400V_led1.anode_up, m_1600V_led1.anode_up, 0.0};
float temp3[7] = {m_800V_led1.anode_down, m_900V_led1.anode_down, m_1000V_led1.anode_down, m_1200V_led1.anode_down, m_1400V_led1.anode_down, m_1600V_led1.anode_down, 0.0};
float temp1b[7] = {m_800V_led2.anode_up, 0.0, 0.0, m_1200V_led2.anode_up, 0.0, 0.0, 0.0};
float temp3b[7] = {m_800V_led2.anode_down, 0.0, 0.0, m_1200V_led2.anode_down, 0.0, 0.0, 0.0};
float temp1c[7] = {m_800V_led3.anode_up, 0.0, 0.0, m_1200V_led3.anode_up, 0.0, 0.0, 0.0};
float temp3c[7] = {m_800V_led3.anode_down, 0.0, 0.0, m_1200V_led3.anode_down, 0.0, 0.0, 0.0};
float temp1d[7] = {m_800V_led4.anode_up, 0.0, 0.0, m_1200V_led4.anode_up, 0.0, 0.0, m_1800V_led4.anode_up};
float temp3d[7] = {m_800V_led4.anode_down, 0.0, 0.0, m_1200V_led4.anode_down, 0.0, 0.0, m_1800V_led4.anode_down};
float temp2[7] = {m_800V_led1.cath_value, m_900V_led1.cath_value, m_1000V_led1.cath_value, m_1200V_led1.cath_value, m_1400V_led1.cath_value, m_1600V_led1.cath_value, 0.0};
float temp2b[7] = {m_800V_led2.cath_value, 0.0, 0.0, m_1200V_led2.cath_value, 0.0, 0.0, 0.0};
float temp2c[7] = {m_800V_led3.cath_value, 0.0, 0.0, m_1200V_led3.cath_value, 0.0, 0.0, 0.0};
float temp2d[7] = {m_800V_led4.cath_value, 0.0, 0.0, m_1200V_led4.cath_value, 0.0, 0.0, m_1800V_led4.cath_value};
float temp4[7] = {m_800V_led1.ref_up, m_900V_led1.ref_up, m_1000V_led1.ref_up, m_1200V_led1.ref_up, m_1400V_led1.ref_up, m_1600V_led1.ref_up, 0.0};
float temp5[7] = {m_800V_led1.ref_down, m_900V_led1.ref_down, m_1000V_led1.ref_down, m_1200V_led1.ref_down, m_1400V_led1.ref_down, m_1600V_led1.ref_down, 0.0};
float temp4b[7] = {m_800V_led2.ref_up, 0.0, 0.0, m_1200V_led2.ref_up, 0.0, 0.0, 0.0};
float temp5b[7] = {m_800V_led2.ref_down, 0.0, 0.0, m_1200V_led2.ref_down, 0.0, 0.0, 0.0};
float temp4c[7] = {m_800V_led3.ref_up, 0.0, 0.0, m_1200V_led3.ref_up, 0.0, 0.0, 0.0};
float temp5c[7] = {m_800V_led3.ref_down, 0.0, 0.0, m_1200V_led3.ref_down, 0.0, 0.0, 0.0};
float temp4d[7] = {m_800V_led4.ref_up, 0.0, 0.0, m_1200V_led4.ref_up, 0.0, 0.0, m_1800V_led4.ref_up};
float temp5d[7] = {m_800V_led4.ref_down, 0.0, 0.0, m_1200V_led4.ref_down, 0.0, 0.0, m_1800V_led4.ref_down};
float temp6[7] = {m_800V_led1.cath_error, m_900V_led1.cath_error, m_1000V_led1.cath_error, m_1200V_led1.cath_error, m_1400V_led1.cath_error, m_1600V_led1.cath_error, 0.0};
float temp6b[7] = {m_800V_led2.cath_error, 0.0, 0.0, m_1200V_led2.cath_error, 0.0, 0.0, 0.0};
float temp6c[7] = {m_800V_led3.cath_error, 0.0, 0.0, m_1200V_led3.cath_error, 0.0, 0.0, 0.0};
float temp6d[7] = {m_800V_led4.cath_error, 0.0, 0.0, m_1200V_led4.cath_error, 0.0, 0.0, m_1800V_led4.cath_error};
float chi2s[7] = {fit.c_800V, fit.c_900V, fit.c_1000V, fit.c_1200V, fit.c_1400V, fit.c_1600V, fit.c_1800V};

gain1200V = (temp1[3]+temp3[3])/(2*temp2[3]);

min_anode_plot = (temp1[0]+temp3[0])/2;

//cout << "loop" << endl;

for (int j=0; j < 7; j++)
{
if (temp1[j] != 0 && temp3[j] != 0)
{
volt_anodes.push_back(voltages[j]);
anodes.push_back((temp1[j]+temp3[j])/(2));
cathodes.push_back(temp2[j]);
cathode_errors.push_back(temp6[j]);
reference.push_back((temp4[j]+temp5[j])/2);
index_anodes = index_anodes + 1;
}
if (temp1b[j] != 0 && temp3b[j] != 0)
{
volt_anodesb.push_back(voltages[j]);
anodesb.push_back((temp1b[j]+temp3b[j])/(2));
cathodesb.push_back(temp2b[j]);
cathode_errorsb.push_back(temp6b[j]);
referenceb.push_back((temp4b[j]+temp5b[j])/2);
cout << volt_anodesb.at(index_anodesb) << " -> refb = " << referenceb.at(index_anodesb) << endl;
index_anodesb = index_anodesb + 1;
}
if (temp1c[j] != 0 && temp3c[j] != 0)
{
volt_anodesc.push_back(voltages[j]);
anodesc.push_back((temp1c[j]+temp3c[j])/(2));
cathodesc.push_back(temp2c[j]);
cathode_errorsc.push_back(temp6c[j]);
referencec.push_back((temp4c[j]+temp5c[j])/2);
cout << volt_anodesc.at(index_anodesc) << " -> refc = " << referencec.at(index_anodesc) << endl;
index_anodesc = index_anodesc + 1;
}
if (temp1d[j] != 0 && temp3d[j] != 0)
{
volt_anodesd.push_back(voltages[j]);
anodesd.push_back((temp1d[j]+temp3d[j])/(2));
cathodesd.push_back(temp2d[j]);
cathode_errorsd.push_back(temp6d[j]);
referenced.push_back((temp4d[j]+temp5d[j])/2);
cout << volt_anodesd.at(index_anodesd) << " -> refd = " << referenced.at(index_anodesd) << endl;
if (anodesd.at(index_anodesd) < min_anode_plot) { min_anode_plot = anodesd.at(index_anodesd); }
index_anodesd = index_anodesd + 1;
}
}

cout << "index anodes b = " << index_anodesb << endl;
cout << "index anodes c = " << index_anodesc << endl;
cout << "index anodes d = " << index_anodesd << endl;

//cout << "2nd loop" << endl;

for (int j=0; j < 7; j++)
{
if (temp1[j] != 0 && temp2[j] != 0 && chi2s[j] < chi2_threshold)
{
voltages_temp.push_back(voltages[j]);
gains.push_back((temp1[j]+temp3[j])/(2*temp2[j]));
chi2_temp.push_back(chi2s[j]);
index_temp = index_temp + 1;
}
if (temp1b[j] != 0 && temp2b[j] != 0 && chi2s[j] < chi2_threshold)
{
voltages_tempb.push_back(voltages[j]);
gainsb.push_back((temp1b[j]+temp3b[j])/(2*temp2b[j]));
index_tempb = index_tempb + 1;
}
if (temp1c[j] != 0 && temp2c[j] != 0 && chi2s[j] < chi2_threshold)
{
voltages_tempc.push_back(voltages[j]);
gainsc.push_back((temp1c[j]+temp3c[j])/(2*temp2c[j]));
index_tempc = index_tempc + 1;
}
if (temp1d[j] != 0 && temp2d[j] != 0 && chi2s[j] < chi2_threshold)
{
voltages_tempd.push_back(voltages[j]);
gainsd.push_back((temp1d[j]+temp3d[j])/(2*temp2d[j]));
index_tempd = index_tempd + 1;
}
}

//cout << "3rd loop" << endl;

for (int j=0; j < 7; j++)
{
if (temp1[j] != 0 && temp2[j] != 0 && chi2s[j] > chi2_threshold)
{
voltages_temp_bad.push_back(voltages[j]);
gains_bad.push_back((temp1[j]+temp3[j])/(2*temp2[j]));
index_temp2 = index_temp2 + 1;
max_volt = voltages[j];
}
}

//cout << "max val plot " << endl;

int status_index[3] = {1, 2, 3};
int status_values[3] = {bad_fits, total_spikes, set_unknown};

max_graph = 0.0;
min_graph = 1;

  for (unsigned int j = 0; j < vec_cath_ori.size(); j++)
  {
    if (vec_cath.at(j) > max_graph and vec_led.at(j) > 0) { max_graph = vec_cath.at(j); }
    //if (vec_cath.at(j) < min_graph and abs(vec_hv.at(j)) > 20.0) { min_graph = vec_cath.at(j); }
  }
max_graph = max_graph * 1.5;
min_graph = -2e-12;

//cout << "plotting" << endl;

	TCanvas * c2 = new TCanvas("c2","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc2 = new TGraph(entries,&vec_time.front(),&vec_cath.front());
	gc2->SetTitle("Cathode current as function of time after background subtraction;Time [s];Current [V]");
	gc2->SetMinimum(min_graph);
	gc2->SetMaximum(max_graph);
      	gc2->Draw("AP");
        c2->Print(name2.c_str());
	c2->Close();

	TCanvas * c2b = new TCanvas("c2b","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc2b = new TGraph(entries,&vec_time.front(),&vec_hv.front());
	gc2b->SetTitle("High voltage as function of time;time [s];High voltage [V]");
      	gc2b->Draw("AP");
        c2b->Print(name2.c_str());
	c2b->Close();
	
	TCanvas * c2c = new TCanvas("c2c","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc2c = new TGraph(entries,&vec_time.front(),&vec_led.front());
	gc2c->SetTitle("Led light as function of time;time [s];Led light");
      	gc2c->Draw("AP");
        c2c->Print(name2.c_str());
	c2c->Close();
	
	TCanvas * c3b = new TCanvas("c3b","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc3b = new TGraph(entries,(float*)&vec_time.front(),&vec_adut.front());
	gc3b->SetTitle("Anode current as function of time;Time [s];Current [V]");
      	gc3b->Draw("AP");
        c3b->Print(name2.c_str());
	c3b->Close();
	
	TCanvas * c3c = new TCanvas("c3c","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc3c = new TGraph(entries,(float*)&vec_time.front(),&vec_aref.front());
	gc3c->SetTitle("Reference anode current as function of time;Time [s];Current [V]");
      	gc3c->Draw("AP");
        c3c->Print(name2.c_str());
	c3c->Close();

max_graph = 0.0;

  for (unsigned int j = 0; j < control_anode_ref.size(); j++)
  {
    if (control_anode_ref.at(j) > max_graph and control_anode_ref.at(j) > 0 and vec_led.at(j) > 0) { max_graph = control_anode_ref.at(j); }
    //if (vec_cath.at(j) < min_graph and abs(vec_hv.at(j)) > 20.0) { min_graph = vec_cath.at(j); }
  }
max_graph = max_graph * 1.2;

	TCanvas *c9 = new TCanvas("c9","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc9 = new TGraph(entries,(float*)&vec_time.front(),&control_anode_ref.front());
	gc9->SetTitle("Control Anode divided by Reference;Time [s];Ratio of the currents");
	gc9->SetMinimum(0.0);
	gc9->SetMaximum(max_graph);
      	gc9->Draw("AP");
        c9->Print(name2.c_str());
	c9->Close();

	TCanvas *c3d = new TCanvas("c3d","c",800,600);
      	gPad->SetLogy();
        gPad->SetLogx();
	TGraph *gc3d = new TGraph(index_anodes,&volt_anodes.front(),&anodes.front());
	gc3d->SetTitle("Anode Corrent as function of voltage;Voltage [V];Corrent [A]");
	gc3d->SetMinimum(min_anode_plot);
        gc3d->SetMarkerStyle(20);
      	gc3d->Draw("APL");
        //c3d->Print(name2.c_str());
	//c3d->Close();
	
	//TCanvas *c3db = new TCanvas("c3db","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3db = new TGraph(index_anodesb,&volt_anodesb.front(),&anodesb.front());
	gc3db->SetTitle("Anode Corrent for led 2 as function of voltage;Voltage [V];Current [A]");
	gc3db->SetLineColor(3);
	gc3db->SetMarkerColor(3);
        gc3db->SetMarkerStyle(20);
      	gc3db->Draw("PL same");
        //c3db->Print(name2.c_str());
	//c3db->Close();
	
	//TCanvas *c3dc = new TCanvas("c3dc","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3dc = new TGraph(index_anodesc,&volt_anodesc.front(),&anodesc.front());
	gc3dc->SetTitle("Anode Corrent for led 3 as function of voltage;Voltage [V];Current [A]");
	gc3dc->SetLineColor(4);
	gc3dc->SetMarkerColor(4);
        gc3dc->SetMarkerStyle(20);
      	gc3dc->Draw("PL same");
        //c3dc->Print(name2.c_str());
	//c3dc->Close();
	
	//TCanvas *c3dd = new TCanvas("c3d","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3dd = new TGraph(index_anodesd,&volt_anodesd.front(),&anodesd.front());
	gc3dd->SetTitle("Anode Corrent for led 4 as function of voltage;Voltage [V];Current [A]");
	gc3dd->SetLineColor(5);
	gc3dd->SetMarkerColor(5);
        gc3dd->SetMarkerStyle(20);
      	gc3dd->Draw("PL same");
        //c3dd->Print(name2.c_str());
	//c3dd->Close();
	
	TLegend *leg3 = new TLegend(0.12,0.65,0.32,0.88);
   	leg3->AddEntry(gc3d,"400 nm","lp");
   	leg3->AddEntry(gc3db,"470 nm","lp");
   	leg3->AddEntry(gc3dc,"500 nm","lp");
   	leg3->AddEntry(gc3dd,"513 nm","lp");
   	leg3->Draw();
	
	c3d->Print(name2.c_str());
	c3d->Close();

	TCanvas *c3e = new TCanvas("c3e","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraphErrors *gc3e = new TGraphErrors(index_anodes,&volt_anodes.front(),&cathodes.front(),NULL,&cathode_errors.front());
	gc3e->SetTitle("Cathode Current for led 1 as function of voltage;Voltage [V];Current [A]");
        gc3e->SetMarkerStyle(20);
        //gc3e->SetMinimum(0.0);
      	gc3e->Draw("APL");
      	c3e->Print(name2.c_str());
	c3e->Close();
	
	TCanvas *c3eb = new TCanvas("c3eb","c",800,600);
	TGraphErrors *gc3eb = new TGraphErrors(index_anodesb,&volt_anodesb.front(),&cathodesb.front(),NULL,&cathode_errorsb.front());
	gc3eb->SetTitle("Cathode Current for led 2 as function of voltage;Voltage [V];Current [A]");
	gc3eb->SetMarkerStyle(20);
      	gc3eb->Draw("APL");
        c3eb->Print(name2.c_str());
	c3eb->Close();
	
	TCanvas *c3ec = new TCanvas("c3ec","c",800,600);
	TGraphErrors *gc3ec = new TGraphErrors(index_anodesc,&volt_anodesc.front(),&cathodesc.front(),NULL,&cathode_errorsc.front());
	gc3ec->SetTitle("Cathode Current for led 3 as function of voltage;Voltage [V];Current [A]");
	gc3ec->SetMarkerStyle(20);
      	gc3ec->Draw("APL");
        c3ec->Print(name2.c_str());
	c3ec->Close();
	
	TCanvas * c3ed = new TCanvas("c3ed","c",800,600);
	TGraphErrors *gc3ed = new TGraphErrors(index_anodesd,&volt_anodesd.front(),&cathodesd.front(),NULL,&cathode_errorsd.front());
	gc3ed->SetTitle("Cathode Current for led 4 as function of voltage;Voltage [V];Current [A]");
	gc3ed->SetMarkerStyle(20);
      	gc3ed->Draw("APL");
        c3ed->Print(name2.c_str());
	c3ed->Close();
	
	TCanvas *c3f = new TCanvas("c3f","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3f = new TGraph(index_anodes,&volt_anodes.front(),&reference.front());
	gc3f->SetTitle("Reference Anode for led 1 as function of voltage;Voltage [V];Current [A]");
        gc3f->SetMarkerStyle(20);
      	gc3f->Draw("APL");
        c3f->Print(name2.c_str());
	c3f->Close();

	TCanvas *c3fb = new TCanvas("c3fb","c",800,600);
      	//gPad->SetLogy();
        gPad->SetLogx();
	TGraph *gc3fb = new TGraph(index_anodesb,&volt_anodesb.front(),&referenceb.front());
	gc3fb->SetTitle("Reference Anode for led 2 as function of voltage;Voltage [V];Current [A]");
        gc3fb->SetMarkerStyle(20);
      	gc3fb->Draw("APL");
        c3fb->Print(name2.c_str());
	c3fb->Close();

	TCanvas *c3fc = new TCanvas("c3fc","c",800,600);
      	gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3fc = new TGraph(index_anodesc,&volt_anodesc.front(),&referencec.front());
	gc3fc->SetTitle("Reference Anode for led 3 as function of voltage;Voltage [V];Current [A]");
        gc3fc->SetMarkerStyle(20);
      	gc3fc->Draw("APL");
        c3fc->Print(name2.c_str());
	c3fc->Close();

	TCanvas *c3fd = new TCanvas("c3fd","c",800,600);
      	gPad->SetLogy();
        gPad->SetLogx();
	TGraph *gc3fd = new TGraph(index_anodesd,&volt_anodesd.front(),&referenced.front());
	gc3fd->SetTitle("Reference Anode for led 4 as function of voltage;Voltage [V];Current [A]");
        gc3fd->SetMarkerStyle(20);
      	gc3fd->Draw("APL");
        c3fd->Print(name2.c_str());
	c3fd->Close();
	
	TCanvas *c3g = new TCanvas("c3g","c",800,600);
      	//gPad->SetLogy();
        //gPad->SetLogx();
	TGraph *gc3g = new TGraph(1,&volt1200V,&gain1200V);
	gc3g->SetTitle("Selection factor: Gain at 1200V;Voltage [V];Gain");
        gc3g->SetMarkerStyle(20);
      	gc3g->Draw("APL");
        c3g->Print(name2.c_str());
	c3g->Close();

	TCanvas *c3 = new TCanvas("c","c",800,600);
      	gPad->SetLogy();
        gPad->SetLogx();
	TGraph *gc3 = new TGraph(index_temp,&voltages_temp.front(),&gains.front());
	gc3->SetTitle("Gain as function of voltage;Voltage [V];Gain");
        gc3->SetMarkerStyle(20);
      	gc3->Draw("APL");
	TGraph *gc3xb = new TGraph(index_tempb,&volt_anodesb.front(),&gainsb.front());
	gc3xb->SetTitle("Gain as function of voltage;Voltage [V];Gain");
        gc3xb->SetMarkerStyle(20);
        gc3xb->SetMarkerColor(3);
        gc3xb->SetLineColor(3);
      	gc3xb->Draw("PL same");
	TGraph *gc3xc = new TGraph(index_tempc,&volt_anodesc.front(),&gainsc.front());
	gc3xc->SetTitle("Gain as function of voltage;Voltage [V];Gain");
        gc3xc->SetMarkerStyle(20);
        gc3xc->SetMarkerColor(4);
        gc3xc->SetLineColor(4);
      	gc3xc->Draw("PL same");
	TGraph *gc3xd = new TGraph(index_tempd,&volt_anodesd.front(),&gainsd.front());
	gc3xd->SetTitle("Gain as function of voltage;Voltage [V];Gain");
        gc3xd->SetMarkerStyle(20);
        gc3xd->SetMarkerColor(5);
	gc3xd->SetLineColor(5);
      	gc3xd->Draw("PL same");
	TGraph *gc3z = new TGraph(index_temp2,&voltages_temp_bad.front(),&gains_bad.front());
        gc3z->SetMarkerStyle(20);
	gc3z->SetLineColor(2);
	gc3z->SetMarkerColor(2);
      	gc3z->Draw("PL same");

   	TLegend *leg3b = new TLegend(0.12,0.65,0.40,0.88);
   	leg3b->AddEntry(gc3,"400 nm","lp");
   	leg3b->AddEntry(gc3xb,"470 nm","lp");
   	leg3b->AddEntry(gc3xc,"500 nm","lp");
   	leg3b->AddEntry(gc3xd,"513 nm","lp");
   	leg3b->AddEntry(gc3z,"Gains computed with bad fit","lp");
   	leg3b->Draw();

        c3->Print(name2.c_str());
	c3->Close();

//cout << "two to last plot" << endl;

float quantum_eff_800V[3] = {0.0, 0.0, 0.0};
float quantum_eff_1200V[3] = {0.0, 0.0, 0.0};

gc4a = new TGraph(1,&dum,&dum);
gc4b = new TGraph(1,&dum,&dum);
gc4c = new TGraph(1,&dum,&dum);
gc4d = new TGraph(1,&dum,&dum);
gc4e = new TGraph(1,&dum,&dum);
gc4f = new TGraph(1,&dum,&dum);

max_graph = m_800V_led1.qe;

if (m_800V_led1.qe > 0.0 && m_800V_led2.qe > 0.0 && m_800V_led3.qe > 0.0 && m_800V_led4.qe > 0.0)
{
quantum_eff_800V[0] = m_800V_led1.qe;
quantum_eff_800V[1] = m_800V_led2.qe;
quantum_eff_800V[2] = m_800V_led3.qe;
//quantum_eff_800V[3] = m_800V_led4.qe;
gc4a = new TGraph(3,wave_lenght,quantum_eff_800V);
}

if (m_800V_led1.qe > 0.0 && m_800V_led2.qe == 0.0 && m_800V_led3.qe == 0.0 && m_800V_led4.qe == 0.0)
{
gc4a = new TGraph(1,&wave1,&m_800V_led1.qe);
}

if (m_900V_led1.qe > 0.0)
{
gc4c = new TGraph(1,&wave1,&m_900V_led1.qe);
}

if (m_1000V_led1.qe > 0.0)
{
gc4d = new TGraph(1,&wave1,&m_1000V_led1.qe);
}

if (m_1400V_led1.qe > 0.0)
{
gc4e = new TGraph(1,&wave1,&m_1400V_led1.qe);
}

if (m_1600V_led1.qe > 0.0)
{
gc4f = new TGraph(1,&wave1,&m_1600V_led1.qe);
}

if (m_1200V_led1.qe > 0 && m_1200V_led2.qe > 0.0 && m_1200V_led3.qe > 0.0 && m_1200V_led4.qe > 0.0)
{
quantum_eff_1200V[0] = m_1200V_led1.qe;
quantum_eff_1200V[1] = m_1200V_led2.qe;
quantum_eff_1200V[2] = m_1200V_led3.qe;
//quantum_eff_1200V[3] = m_1200V_led4.qe;
gc4b = new TGraph(3,wave_lenght,quantum_eff_1200V);
}

if (m_1200V_led1.qe > 0.0 && m_1200V_led2.qe == 0.0 && m_1200V_led3.qe == 0.0 && m_1200V_led4.qe == 0.0)
{
gc4b = new TGraph(1,&wave1,&m_1200V_led1.qe);
}

if (max_graph < m_800V_led1.qe) { max_graph = m_800V_led1.qe; }
if (max_graph < m_1200V_led1.qe) { max_graph = m_1200V_led1.qe; }
if (max_graph < m_800V_led2.qe) { max_graph = m_800V_led2.qe; }
if (max_graph < m_1200V_led2.qe) { max_graph = m_1200V_led2.qe; }
if (max_graph < m_800V_led3.qe) { max_graph = m_800V_led3.qe; }
if (max_graph < m_1200V_led3.qe) { max_graph = m_1200V_led3.qe; }
max_graph = max_graph * 1.2;

cout << "plotting" << endl;

	TCanvas * c4 = new TCanvas("c","c",800,600);
      	//gPad->SetLogy();
	gc4a->SetTitle("Relative quantum efficiency as function of wavelenght;Wave lenght [nm];Relative Quantum efficiency");
	gc4b->SetTitle("Relative quantum efficiency as function of wavelenght;Wave lenght [nm];Relative Quantum efficiency");
        gc4a->SetMarkerStyle(20);
        gc4a->SetMarkerColor(1);
	gc4a->SetLineColor(1);
      	gc4b->SetMarkerStyle(20);
        gc4b->SetMarkerColor(3);
	gc4b->SetLineColor(3);
        if (m_800V_led2.qe > 0.0 && m_800V_led3.qe > 0.0 && m_800V_led4.qe > 0.0)
        {
	gc4a->SetMinimum(0.0);
	gc4a->SetMaximum(max_graph);
        gc4a->Draw("APL");
      	gc4b->Draw("PLsame");
      	}
      	if (m_1200V_led2.qe > 0.0 && m_1200V_led3.qe > 0.0 && m_1200V_led4.qe > 0.0)
        {
	gc4b->SetMinimum(0.0);
	gc4b->SetMaximum(max_graph);
        gc4b->Draw("APL");
      	gc4a->Draw("PLsame");
      	}
      	gc4c->SetMarkerStyle(20);
        gc4c->SetMarkerColor(4);
	gc4c->SetLineColor(4);
      	gc4c->Draw("PLsame");
      	gc4d->SetMarkerStyle(20);
        gc4d->SetMarkerColor(5);
	gc4d->SetLineColor(5);
      	gc4d->Draw("PLsame");
      	gc4e->SetMarkerStyle(20);
        gc4e->SetMarkerColor(6);
	gc4e->SetLineColor(6);
      	gc4e->Draw("PLsame");
      	gc4f->SetMarkerStyle(20);
        gc4f->SetMarkerColor(7);
	gc4f->SetLineColor(7);
      	gc4f->Draw("PLsame");
      	
   	TLegend *leg4 = new TLegend(0.65,0.12,0.88,0.40);
   	leg4->AddEntry(gc4a,"800V","lp");
   	leg4->AddEntry(gc4c,"900V","lp");
   	leg4->AddEntry(gc4d,"1000V","lp");
   	leg4->AddEntry(gc4b,"1200V","lp");
   	leg4->AddEntry(gc4e,"1400V","lp");
   	leg4->AddEntry(gc4f,"1600V","lp");
   	leg4->Draw();
      	
        c4->Print(name2.c_str());
	c4->Close();

cout << "one to last plot" << endl;

	TCanvas * c4z = new TCanvas("c","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc4z = new TGraph(index_temp,&voltages_temp.front(),&chi2_temp.front());
	gc4z->SetTitle("Chi2;Voltage [V];Chi2 of the fit");
        gc4z->SetMarkerStyle(20);
      	gc4z->Draw("APL");
        c4z->Print(name2.c_str());
	c4z->Close();
	
//cout << "last plot" << endl;

	TCanvas * c5 = new TCanvas("c","c",800,600);
      	//gPad->SetLogy();
	TGraph *gc5 = new TGraph(3,status_index,status_values);
	gc5->SetTitle("Final status;Bad fits/Spikes/Unknown PMT;AU");
	gc5->SetMarkerStyle(20);
	if (status_values[0] > 0 or status_values[1] > 0 or status_values[2] > 0) { gc5->SetMarkerColor(2); gc5->SetLineColor(2);}
      	gc5->Draw("APL");
        string name5 = "plots/" + file2 + ".pdf)";
        c5->Print(name5.c_str());
	c5->Close();
/*
if (set == 1)
{
if (canv_old == 1)
{
r_old_gain = new TCanvas("r_old_gain","c",800,600);
//r_old_gain->Divide(3,3);
r_old_qe = new TCanvas("r_old_qe","c",800,600);
//r_old_qe->Divide(3,3);
r_old_cath = new TCanvas("r_old_cath","c",800,600);
//r_old_cath->Divide(3,3);
}

if (total_spikes > 10 and bad_fits > 0)
{
gc3->SetLineColor(2);
gc4a->SetLineColor(2);
gc1->SetLineColor(2);
}
//r_old_gain->cd(canv_old);
r_old_gain->cd();
gPad->SetLogy();
gPad->SetLogx();
title = pmt + ";Voltage [V];Gain";
gc3->SetTitle(title.c_str());
gc3->Draw("APL");
gc3z->SetMarkerStyle(20);
gc3z->SetLineColor(2);
gc3z->SetMarkerColor(2);
gc3z->Draw("PL same");
//r_old_qe->cd(canv_old);
r_old_qe->cd();
title = pmt + ";Wavelenght [nm];Relative Quantum Efficiency";
gc4a->SetTitle(title.c_str());
gc4b->SetTitle(title.c_str());
if (m_800V_led2.qe > 0.0 && m_800V_led3.qe > 0.0 && m_800V_led4.qe > 0.0)
{
gc4a->Draw("APL");
gc4b->Draw("PLsame");
}
if (m_1200V_led2.qe > 0.0 && m_1200V_led3.qe > 0.0 && m_1200V_led4.qe > 0.0)
{
gc4b->Draw("APL");
gc4a->Draw("PLsame");
}
//r_old_cath->cd(canv_old);
r_old_cath->cd();
gPad->SetLogy();
title = pmt + ";Time [s];Current [A]";
gc1->SetTitle(title.c_str());
gc1->Draw("APL");
canv_old = canv_old + 1;

if (canv_old == 2)
{
if (page_old == 1)
{
r_old_gain->Print("report_gains_old.pdf(");
r_old_qe->Print("report_qe_old.pdf(");
r_old_cath->Print("report_cath_old.pdf(");
page_old = 1;
}
if (page_old > 1)
{
r_old_gain->Print("report_gains_old.pdf");
r_old_qe->Print("report_qe.pdf_old");
r_old_cath->Print("report_cath_old.pdf");
page_old = page_old + 1;
}
r_old_gain->Clear();
r_old_qe->Clear();
r_old_cath->Clear();
canv_old = 1;
}
}


if (set == 2)
{
if (canv_new == 1)
{
r_new_gain = new TCanvas("r_new_gain","c",800,600);
//r_new_gain->Divide(3,3);
r_new_qe = new TCanvas("r_new_qe","c",800,600);
//r_new_qe->Divide(3,3);
r_new_cath = new TCanvas("r_new_cath","c",800,600);
//r_new_cath->Divide(3,3);
}

if (total_spikes > 10 and bad_fits > 0)
{
gc3->SetLineColor(2);
gc4a->SetLineColor(2);
gc1->SetLineColor(2);
}
r_new_gain->cd();
gPad->SetLogy();
gPad->SetLogx();
title = pmt + ";Voltage [V];Gain";
gc3->SetTitle(title.c_str());
gc3->Draw("APL");
r_new_qe->cd();
title = pmt + ";Wavelenght [nm];Relative Quantum Efficiency";
gc4a->SetTitle(title.c_str());
gc4a->Draw("APL");
gc4b->Draw("APL same");
r_new_cath->cd();
title = pmt + ";Time [s];Current [A]";
gc1->SetTitle(title.c_str());
gPad->SetLogy();
gc1->Draw("APL");
canv_new = canv_new + 1;


if (canv_new == 2)
{
if (page_new == 1)
{
r_new_gain->Print("report_gains_new.pdf(");
r_new_qe->Print("report_qe_new.pdf(");
r_new_cath->Print("report_cath_new.pdf(");
page_new = 2;
}
if (page_new > 1)
{
r_new_gain->Print("report_gains_new.pdf");
r_new_qe->Print("report_qe_new.pdf");
r_new_cath->Print("report_cath_new.pdf");
page_new = page_new + 1;
}
r_new_gain->Clear();
r_new_qe->Clear();
r_new_cath->Clear();
canv_new = 1;
}
}
*/

//fill the tree
tree->Fill();

}

/*
r_old_gain->Print("report_gains_old.pdf)");
r_old_qe->Print("report_qe_old.pdf)");
r_old_cath->Print("report_cath_old.pdf)");
r_new_gain->Print("report_gains_new.pdf)");
r_new_qe->Print("report_qe_new.pdf)");
r_new_cath->Print("report_cath_new.pdf)");
*/

cout<<"Total unknown PMTs : "<<total_unknown<<endl;
cout<<"Total bad fits : "<<total_bad_fits<<endl;

//write to file
TFile *data_output= TFile::Open( tree_out.c_str() , "RECREATE");
tree->Write();
//tree->Print();

data_output->Close();
cout<<tree_out<<" created sucessfully!"<<endl;

}
