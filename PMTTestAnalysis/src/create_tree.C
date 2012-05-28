#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//root lib
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"

//user
#include "LeakageSubtractor.h"

void set_coordinates(string pmt, int& module, int& sector)
{

if (pmt == "CA1579") { sector = 4; module = 1; }
if (pmt == "CA3399") { sector = 1; module = 2; }
if (pmt == "CA0683") { sector = 13; module = 1; }
if (pmt == "CA0540") { sector = 13; module = 2; }
if (pmt == "CA3362") { sector = 14; module = 1; }
if (pmt == "CA0625") { sector = 3; module = 2; }
if (pmt == "CA0715") { sector = 15; module = 2; }
if (pmt == "CA1832") { sector = 5; module = 2; }
if (pmt == "CA0857") { sector = 14; module = 2; }
if (pmt == "CA0886") { sector = 15; module = 1; }
if (pmt == "CA1549") { sector = 5; module = 1; }
if (pmt == "CA1617") { sector = 6; module = 1; }
if (pmt == "CA0742") { sector = 6; module = 2; }
if (pmt == "CA3236") { sector = 11; module = 2; }
if (pmt == "CA0829") { sector = 10; module = 1; }
if (pmt == "CA0948") { sector = 12; module = 1; }
if (pmt == "CA1263") { sector = 10; module = 2; }
if (pmt == "CA1200") { sector = 9; module = 2; }
if (pmt == "CA1829") { sector = 9; module = 1; }
if (pmt == "CA1431") { sector = 11; module = 1; }
if (pmt == "CA1593") { sector = 12; module = 2; }
if (pmt == "CA0327") { sector = 2; module = 2; }
if (pmt == "CA1680") { sector = 16; module = 2; }
if (pmt == "CA0558") { sector = 16; module = 1; }
if (pmt == "CA0574") { sector = 1; module = 1; }
if (pmt == "CA1842") { sector = 2; module = 1; }
if (pmt == "CA0812") { sector = 4; module = 2; }
if (pmt == "CA1592") { sector = 3; module = 1; }
if (pmt == "CA0892") { sector = 8; module = 10; }
if (pmt == "CA1620") { sector = 7; module = 10; }
if (pmt == "CA1321") { sector = 7; module = 1; }
if (pmt == "CA1537") { sector = 8; module = 1; }
if (pmt == "CA3386") { sector = 7; module = 2; }
if (pmt == "CA1954") { sector = 8; module = 2; }

if (sector == 0 and module == 0) { cout<<"Unknown PMT"<<endl; }

}

void spike_check(float point, std::vector<float> *vec_cath, int& spike)
{

float ave, dev;

//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;

ave = (vec_cath->at(point-2) + vec_cath->at(point-1) + vec_cath->at(point+1) + vec_cath->at(point+2))/4.0;

dev = (vec_cath->at(point) - ave)/ave;

if (dev > 1.00 and vec_cath->at(point) > 1e-12)
{
//cout<<"Positive spike! "<<dev<<endl;
//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;
spike = 1;
}
if (dev < -1.00 and vec_cath->at(point) < -1e-12)
{
//cout<<"Negative spike! "<<dev<<endl;
//cout<<"cath values = "<<vec_cath->at(point-2)<<", "<<vec_cath->at(point-1)<<" "<<vec_cath->at(point)<<" "<<vec_cath->at(point+1)<<" "<<vec_cath->at(point+2)<<endl;
spike = 1;
}

}


void estimate_leakage(float ini_point, float end_point, std::vector<float> *vec_cath, float& leakage_mean, int& tot_points, int& total_spikes, float& leakage_error)
{

TH1D *leakage;

int spike = 0;
float l_low, l_high;

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

cout<<"Leakage estimated with "<<tot_points<<" points."<<endl;
}

void calc_eff(float cathode, float anode_up, float anode_down, float ref_up, float ref_down, float& gain, float& qe)
{

float anode_ave, ref_ave;

anode_ave = (anode_up + anode_down)/2;
ref_ave = (ref_up + ref_down)/2;

if (cathode > 0.0) { gain = anode_ave / cathode; }
if (cathode > 0.0) { qe = ref_ave / cathode; }

//cout<<"ee = "<<ee<<" qe = "<<qe<<endl;

}


void gain_cathode(int ini_val, int end_val, std::vector<float> *vec_cath, float& cath_gain, int& cath_spikes, float& cath_error, int& n_middle)
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

for (int i = 1; i <= 20; i++)
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

for (int i = 1; i <= 20; i++)
{
if (i == 1) { low_after = vec_cath->at(end_val+6+i); }
if (high_after < vec_cath->at(end_val+6+i)) { high_after = vec_cath->at(end_val-1-i); }
if (low_after > vec_cath->at(end_val+6+i)) { low_after = vec_cath->at(end_val-1-i); }
}

val_before =  new TH1D("val_before","val_before;current", 100,low_before,high_before);
val_middle =  new TH1D("val_middle","val_middle;current", 100,low_middle, high_middle);
val_after  =  new TH1D("val_after","val_after;current", 100,low_after,high_after);

for (int i = 1; i <= 20; i++)
{
spike_check(ini_val-1-i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_after->Fill(vec_cath->at(ini_val-1-i)); n_before = n_before + 1; }
spike = 0;
}

for (int i = ini_val+7; i <= end_val-7; i++)
{
spike_check(i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_middle->Fill(vec_cath->at(i)); n_middle = n_middle + 1; }
spike = 0;
}

for (int i = 1; i <= 20; i++)
{
spike_check(end_val+6+i, vec_cath, spike);
if (spike == 1) { cath_spikes = cath_spikes + 1; }
else { val_after->Fill(vec_cath->at(end_val+6+i)); n_after = n_after + 1; }
spike = 0;
} 

ave_before = val_before->GetMean();
error_before = val_before->GetRMS();
ave_middle = val_middle->GetMean();
error_middle = val_middle->GetRMS();
ave_after = val_after->GetMean();
error_after = val_after->GetRMS();

ave_low = (ave_before*n_before + ave_after*n_after)/(n_before+n_after);
cath_gain = ave_middle - ave_low;

cath_error = (error_before*n_before + error_middle*n_middle + error_after+n_after)/(n_before + n_middle + n_after);

delete(val_before);
delete(val_middle);
delete(val_after);

}

}

void calc_dif(size_t cent_val, std::vector<float> *vec_adut, std::vector<float> *vec_aref, std::vector<int> *vec_led, float& anode, float& ref)
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

int tot_up = 10, tot_down = 10;

for (int i = 1; i <= 10; i++)
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

void create_tree(string *files_in, int n_files, string tree_out)
{
//variable declaration
float cath, adut, aref;
int entries, time, hv, led, aux_int;

char read_time[20];
string ini_time, end_time;
string pmt, aux_str;

std::vector<int> vec_begin, vec_end;
std::vector<int> *pvec_begin, *pvec_end;

std::vector<int> vec_time, vec_hv, vec_led;
std::vector<float> vec_cath, vec_cath_ori, vec_adut, vec_aref;
std::vector<int> *pvec_time, *pvec_hv, *pvec_led;
std::vector<float> *pvec_cath, *pvec_cath_ori, *pvec_adut, *pvec_aref;
int total_spikes, sector, module;

int found1, found2, found3;
int total_unknown = 0;

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

int index_leakage_0V_begin, index_leakage_0V_end;
int index_leakage_800V_begin, index_leakage_800V_end;
int index_leakage_900V_begin, index_leakage_900V_end;
int index_leakage_1000V_begin, index_leakage_1000V_end;
int index_leakage_1200V_begin, index_leakage_1200V_end;
int index_leakage_1400V_begin, index_leakage_1400V_end;
int index_leakage_1600V_begin, index_leakage_1600V_end;

float cath_800V_led1, cath_800V_led1_error;
float cath_800V_led2, cath_800V_led2_error;
float cath_800V_led3, cath_800V_led3_error;
float cath_800V_led4, cath_800V_led4_error;
float cath_900V_led1, cath_900V_led1_error;
float cath_1000V_led1, cath_1000V_led1_error;
float cath_1200V_led1, cath_1200V_led1_error;
float cath_1200V_led2, cath_1200V_led2_error;
float cath_1200V_led3, cath_1200V_led3_error;
float cath_1200V_led4, cath_1200V_led4_error;
float cath_1400V_led1, cath_1400V_led1_error;
float cath_1600V_led1, cath_1600V_led1_error;

int cath_800V_led1_spikes, cath_800V_led1_n;
int cath_800V_led2_spikes, cath_800V_led2_n;
int cath_800V_led3_spikes, cath_800V_led3_n;
int cath_800V_led4_spikes, cath_800V_led4_n;
int cath_900V_led1_spikes, cath_900V_led1_n;
int cath_1000V_led1_spikes, cath_1000V_led1_n;
int cath_1200V_led1_spikes, cath_1200V_led1_n;
int cath_1200V_led2_spikes, cath_1200V_led2_n;
int cath_1200V_led3_spikes, cath_1200V_led3_n;
int cath_1200V_led4_spikes, cath_1200V_led4_n;
int cath_1400V_led1_spikes, cath_1400V_led1_n;
int cath_1600V_led1_spikes, cath_1600V_led1_n;

float anode_800V_led1_up, anode_800V_led1_down;
float anode_800V_led2_up, anode_800V_led2_down;
float anode_800V_led3_up, anode_800V_led3_down;
float anode_800V_led4_up, anode_800V_led4_down;
float anode_900V_led1_up, anode_900V_led1_down;
float anode_1000V_led1_up, anode_1000V_led1_down;
float anode_1200V_led1_up, anode_1200V_led1_down;
float anode_1200V_led2_up, anode_1200V_led2_down;
float anode_1200V_led3_up, anode_1200V_led3_down;
float anode_1200V_led4_up, anode_1200V_led4_down;
float anode_1400V_led1_up, anode_1400V_led1_down;
float anode_1600V_led1_up, anode_1600V_led1_down;

float ref_800V_led1_up, ref_800V_led1_down;
float ref_800V_led2_up, ref_800V_led2_down;
float ref_800V_led3_up, ref_800V_led3_down;
float ref_800V_led4_up, ref_800V_led4_down;
float ref_900V_led1_up, ref_900V_led1_down;
float ref_1000V_led1_up, ref_1000V_led1_down;
float ref_1200V_led1_up, ref_1200V_led1_down;
float ref_1200V_led2_up, ref_1200V_led2_down;
float ref_1200V_led3_up, ref_1200V_led3_down;
float ref_1200V_led4_up, ref_1200V_led4_down;
float ref_1400V_led1_up, ref_1400V_led1_down;
float ref_1600V_led1_up, ref_1600V_led1_down;

float gain_800V_led1, qe_800V_led1;
float gain_800V_led2, qe_800V_led2;
float gain_800V_led3, qe_800V_led3;
float gain_800V_led4, qe_800V_led4;
float gain_900V_led1, qe_900V_led1;
float gain_1000V_led1, qe_1000V_led1;
float gain_1200V_led1, qe_1200V_led1;
float gain_1200V_led2, qe_1200V_led2;
float gain_1200V_led3, qe_1200V_led3;
float gain_1200V_led4, qe_1200V_led4;
float gain_1400V_led1, qe_1400V_led1;
float gain_1600V_led1, qe_1600V_led1;

float leakage_0V, leakage_0V_error;
float leakage_800V, leakage_800V_error;
float leakage_900V, leakage_900V_error;
float leakage_1000V, leakage_1000V_error;
float leakage_1200V, leakage_1200V_error;
float leakage_1400V, leakage_1400V_error;
float leakage_1600V, leakage_1600V_error;

int leakage_0V_n, leakage_0V_spikes;
int leakage_800V_n, leakage_800V_spikes;
int leakage_900V_n, leakage_900V_spikes;
int leakage_1000V_n, leakage_1000V_spikes;
int leakage_1200V_n, leakage_1200V_spikes;
int leakage_1400V_n, leakage_1400V_spikes;
int leakage_1600V_n, leakage_1600V_spikes;

//tree declaration
TTree *tree = new TTree("Castor_PMT_Caracterization_2012","Castor PMT Caracterization 2012");
tree->Branch("PMT",&pmt,"Reference code of the PMT");
tree->Branch("Measurement_begin","std::vector<int>",&pvec_begin);
tree->Branch("Measurement_end","std::vector<int>",&pvec_end);
tree->Branch("Entries",&entries,"Number of entries/I");
tree->Branch("Module",&module,"Castor module/I");
tree->Branch("Sector",&sector,"Castor sector/I");
tree->Branch("Measured_time","std::vector<int>",&pvec_time);
tree->Branch("HV","std::vector<int>",&pvec_hv);
tree->Branch("Cathode","std::vector<float>",&pvec_cath_ori);
tree->Branch("Cathode_after_background_subtraction","std::vector<float>",&pvec_cath);
tree->Branch("Anode","std::vector<float>",&pvec_adut);
tree->Branch("Reference_PMT","std::vector<float>",&pvec_aref);
tree->Branch("Led","std::vector<int>",&pvec_led);
tree->Branch("Number_of_spikes",&total_spikes,"Number of spikes found during the analysis/I");
tree->Branch("Cath_800V_led1",&cath_800V_led1,"Cathode Gain when switching on led1 at 800V");
tree->Branch("Cath_800V_led1_error",&cath_800V_led1_error,"Cathode Gain error when switching off led1 at 800V");
tree->Branch("Cath_800V_led1_spikes",&cath_800V_led1_spikes,"Cathode Gain spikes when switching on led1 at 800V/I");
tree->Branch("Cath_800V_led1_n",&cath_800V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 800V/I");
tree->Branch("Anode_800V_led1_up",&anode_800V_led1_up,"Anode Gain when switching on led1 at 800V");
tree->Branch("Anode_800V_led1_down",&anode_800V_led1_down,"Anode Gain when switching off led1 at 800V");
tree->Branch("Reference_800V_led1_up",&ref_800V_led1_up,"Reference Gain when switching on led1 at 800V");
tree->Branch("Reference_800V_led1_down",&ref_800V_led1_down,"Reference Gain when switching off led1 at 800V");
tree->Branch("Cath_800V_led2",&cath_800V_led2,"Cathode Gain when switching on led2 at 800V");
tree->Branch("Cath_800V_led2_error",&cath_800V_led2_error,"Cathode Gain error when switching off led2 at 800V");
tree->Branch("Cath_800V_led2_spikes",&cath_800V_led2_spikes,"Cathode Gain spikes when switching on led2 at 800V/I");
tree->Branch("Cath_800V_led2_n",&cath_800V_led2_n,"Number of points used for cathode gain calculation when switching off led2 at 800V/I");
tree->Branch("Anode_800V_led2_up",&anode_800V_led2_up,"Anode Gain when switching on led2 at 800V");
tree->Branch("Anode_800V_led2_down",&anode_800V_led2_down,"Anode Gain when switching off led2 at 800V");
tree->Branch("Reference_800V_led2_up",&ref_800V_led2_up,"Reference Gain when switching on led2 at 800V");
tree->Branch("Reference_800V_led2_down",&ref_800V_led2_down,"Reference Gain when switching off led2 at 800V");
tree->Branch("Cath_800V_led3",&cath_800V_led3,"Cathode Gain when switching on led3 at 800V");
tree->Branch("Cath_800V_led3_error",&cath_800V_led3_error,"Cathode Gain error when switching off led3 at 800V");
tree->Branch("Cath_800V_led3_spikes",&cath_800V_led3_spikes,"Cathode Gain spikes when switching on led3 at 800V/I");
tree->Branch("Cath_800V_led3_n",&cath_800V_led3_n,"Number of points used for cathode gain calculation when switching off led3 at 800V/I");
tree->Branch("Anode_800V_led3_up",&anode_800V_led3_up,"Anode Gain when switching on led3 at 800V");
tree->Branch("Anode_800V_led3_down",&anode_800V_led3_down,"Anode Gain when switching off led3 at 800V");
tree->Branch("Reference_800V_led3_up",&ref_800V_led3_up,"Reference Gain when switching on led3 at 800V");
tree->Branch("Reference_800V_led3_down",&ref_800V_led3_down,"Reference Gain when switching off led3 at 800V");
tree->Branch("Cath_800V_led4",&cath_800V_led4,"Cathode Gain when switching on led4 at 800V");
tree->Branch("Cath_800V_led4_error",&cath_800V_led4_error,"Cathode Gain error when switching off led4 at 800V");
tree->Branch("Cath_800V_led4_spikes",&cath_800V_led4_spikes,"Cathode Gain spikes when switching on led4 at 800V/I");
tree->Branch("Cath_800V_led4_n",&cath_800V_led4_n,"Number of points used for cathode gain calculation when switching off led4 at 800V/I");
tree->Branch("Anode_800V_led4_up",&anode_800V_led4_up,"Anode Gain when switching on led4 at 800V");
tree->Branch("Anode_800V_led4_down",&anode_800V_led4_down,"Anode Gain when switching off led4 at 800V");
tree->Branch("Reference_800V_led4_up",&ref_800V_led4_up,"Reference Gain when switching on led4 at 800V");
tree->Branch("Reference_800V_led4_down",&ref_800V_led4_down,"Reference Gain when switching off led4 at 800V");
tree->Branch("Cath_900V_led1",&cath_900V_led1,"Cathode Gain when switching on led1 at 900V");
tree->Branch("Cath_900V_led1_error",&cath_900V_led1_error,"Cathode Gain error when switching off led1 at 900V");
tree->Branch("Cath_900V_led1_spikes",&cath_900V_led1_spikes,"Cathode Gain spikes when switching on led1 at 900V/I");
tree->Branch("Cath_900V_led1_n",&cath_900V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 900V/I");
tree->Branch("Anode_900V_led1_up",&anode_900V_led1_up,"Anode Gain when switching on led1 at 900V");
tree->Branch("Anode_900V_led1_down",&anode_900V_led1_down,"Anode Gain when switching off led1 at 900V");
tree->Branch("Reference_900V_led1_up",&ref_900V_led1_up,"Reference Gain when switching on led1 at 900V");
tree->Branch("Reference_900V_led1_down",&ref_900V_led1_down,"Reference Gain when switching off led1 at 900V");
tree->Branch("Cath_1000V_led1",&cath_1000V_led1,"Cathode Gain when switching on led1 at 1000V");
tree->Branch("Cath_1000V_led1_error",&cath_1000V_led1_error,"Cathode Gain error when switching off led1 at 1000V");
tree->Branch("Cath_1000V_led1_spikes",&cath_1000V_led1_spikes,"Cathode Gain spikes when switching on led1 at 1000V/I");
tree->Branch("Cath_1000V_led1_n",&cath_1000V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 1000V/I");
tree->Branch("Anode_1000V_led1_up",&anode_1000V_led1_up,"Anode Gain when switching on led1 at 1000V");
tree->Branch("Anode_1000V_led1_down",&anode_1000V_led1_down,"Anode Gain when switching off led1 at 1000V");
tree->Branch("Reference_1000V_led1_up",&ref_1000V_led1_up,"Reference Gain when switching on led1 at 1000V");
tree->Branch("Reference_1000V_led1_down",&ref_1000V_led1_down,"Reference Gain when switching off led1 at 1000V");
tree->Branch("Cath_1200V_led1",&cath_1200V_led1,"Cathode Gain when switching on led1 at 1200V");
tree->Branch("Cath_1200V_led1_error",&cath_1200V_led1_error,"Cathode Gain error when switching off led1 at 1200V");
tree->Branch("Cath_1200V_led1_spikes",&cath_1200V_led1_spikes,"Cathode Gain spikes when switching on led1 at 1200V/I");
tree->Branch("Cath_1200V_led1_n",&cath_1200V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 1200V/I");
tree->Branch("Anode_1200V_led1_up",&anode_1200V_led1_up,"Anode Gain when switching on led1 at 1200V");
tree->Branch("Anode_1200V_led1_down",&anode_1200V_led1_down,"Anode Gain when switching off led1 at 1200V");
tree->Branch("Reference_1200V_led1_up",&ref_1200V_led1_up,"Reference Gain when switching on led1 at 1200V");
tree->Branch("Reference_1200V_led1_down",&ref_1200V_led1_down,"Reference Gain when switching off led1 at 1200V");
tree->Branch("Cath_1200V_led2",&cath_1200V_led2,"Cathode Gain when switching on led2 at 1200V");
tree->Branch("Cath_1200V_led2_error",&cath_1200V_led2_error,"Cathode Gain error when switching off led2 at 1200V");
tree->Branch("Cath_1200V_led2_spikes",&cath_1200V_led2_spikes,"Cathode Gain spikes when switching on led2 at 1200V/I");
tree->Branch("Cath_1200V_led2_n",&cath_1200V_led2_n,"Number of points used for cathode gain calculation when switching off led2 at 1200V/I");
tree->Branch("Anode_1200V_led2_up",&anode_1200V_led2_up,"Anode Gain when switching on led2 at 1200V");
tree->Branch("Anode_1200V_led2_down",&anode_1200V_led2_down,"Anode Gain when switching off led2 at 1200V");
tree->Branch("Reference_1200V_led2_up",&ref_1200V_led2_up,"Reference Gain when switching on led2 at 1200V");
tree->Branch("Reference_1200V_led2_down",&ref_1200V_led2_down,"Reference Gain when switching off led2 at 1200V");
tree->Branch("Cath_1200V_led3",&cath_1200V_led3,"Cathode Gain when switching on led3 at 1200V");
tree->Branch("Cath_1200V_led3_error",&cath_1200V_led3_error,"Cathode Gain error when switching off led3 at 1200V");
tree->Branch("Cath_1200V_led3_spikes",&cath_1200V_led3_spikes,"Cathode Gain spikes when switching on led3 at 1200V/I");
tree->Branch("Cath_1200V_led3_n",&cath_1200V_led3_n,"Number of points used for cathode gain calculation when switching off led3 at 1200V/I");
tree->Branch("Anode_1200V_led3_up",&anode_1200V_led3_up,"Anode Gain when switching on led3 at 1200V");
tree->Branch("Anode_1200V_led3_down",&anode_1200V_led3_down,"Anode Gain when switching off led3 at 1200V");
tree->Branch("Reference_1200V_led3_up",&ref_1200V_led3_up,"Reference Gain when switching on led3 at 1200V");
tree->Branch("Reference_1200V_led3_down",&ref_1200V_led3_down,"Reference Gain when switching off led3 at 1200V");
tree->Branch("Cath_1200V_led4",&cath_1200V_led4,"Cathode Gain when switching on led4 at 1200V");
tree->Branch("Cath_1200V_led4_error",&cath_1200V_led4_error,"Cathode Gain error when switching off led4 at 1200V");
tree->Branch("Cath_1200V_led4_spikes",&cath_1200V_led4_spikes,"Cathode Gain spikes when switching on led4 at 1200V/I");
tree->Branch("Cath_1200V_led4_n",&cath_1200V_led4_n,"Number of points used for cathode gain calculation when switching off led4 at 1200V/I");
tree->Branch("Anode_1200V_led4_up",&anode_1200V_led4_up,"Anode Gain when switching on led4 at 1200V");
tree->Branch("Anode_1200V_led4_down",&anode_1200V_led4_down,"Anode Gain when switching off led4 at 1200V");
tree->Branch("Reference_1200V_led4_up",&ref_1200V_led4_up,"Reference Gain when switching on led4 at 1200V");
tree->Branch("Reference_1200V_led4_down",&ref_1200V_led4_down,"Reference Gain when switching off led4 at 1200V");
tree->Branch("Cath_1400V_led1",&cath_1400V_led1,"Cathode Gain when switching on led1 at 1400V");
tree->Branch("Cath_1400V_led1_error",&cath_1400V_led1_error,"Cathode Gain error when switching off led1 at 1400V");
tree->Branch("Cath_1400V_led1_spikes",&cath_1400V_led1_spikes,"Cathode Gain spikes when switching on led1 at 1400V/I");
tree->Branch("Cath_1400V_led1_n",&cath_1400V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 1400V/I");
tree->Branch("Anode_1400V_led1_up",&anode_1400V_led1_up,"Anode Gain when switching on led1 at 1400V");
tree->Branch("Anode_1400V_led1_down",&anode_1400V_led1_down,"Anode Gain when switching off led1 at 1400V");
tree->Branch("Reference_1400V_led1_up",&ref_1400V_led1_up,"Reference Gain when switching on led1 at 1400V");
tree->Branch("Reference_1400V_led1_down",&ref_1400V_led1_down,"Reference Gain when switching off led1 at 1400V");
tree->Branch("Cath_1600V_led1",&cath_1600V_led1,"Cathode Gain when switching on led1 at 1600V");
tree->Branch("Cath_1600V_led1_error",&cath_1600V_led1_error,"Cathode Gain error when switching off led1 at 1600V");
tree->Branch("Cath_1600V_led1_spikes",&cath_1600V_led1_spikes,"Cathode Gain spikes when switching on led1 at 1600V/I");
tree->Branch("Cath_1600V_led1_n",&cath_1600V_led1_n,"Number of points used for cathode gain calculation when switching off led1 at 1600V/I");
tree->Branch("Anode_1600V_led1_up",&anode_1600V_led1_up,"Anode Gain when switching on led1 at 1600V");
tree->Branch("Anode_1600V_led1_down",&anode_1600V_led1_down,"Anode Gain when switching off led1 at 1600V");
tree->Branch("Reference_1600V_led1_up",&ref_1600V_led1_up,"Reference Gain when switching on led1 at 1600V");
tree->Branch("Reference_1600V_led1_down",&ref_1600V_led1_down,"Reference Gain when switching off led1 at 1600V");
tree->Branch("Gain_800V_led1",&gain_800V_led1,"Gain for led1 at 800V");
tree->Branch("QE_800V_led1",&qe_800V_led1,"Quantum effeciency for led1 at 800V");
tree->Branch("Gain_800V_led2",&gain_800V_led2,"Gain for led2 at 800V");
tree->Branch("QE_800V_led2",&qe_800V_led2,"Quantum effeciency for led2 at 800V");
tree->Branch("Gain_800V_led3",&gain_800V_led3,"Gain for led3 at 800V");
tree->Branch("QE_800V_led3",&qe_800V_led3,"Quantum effeciency for led3 at 800V");
tree->Branch("Gain_800V_led4",&gain_800V_led4,"Gain for led4 at 800V");
tree->Branch("QE_800V_led4",&qe_800V_led4,"Quantum effeciency for led4 at 800V");
tree->Branch("Gain_900V_led1",&gain_900V_led1,"Gain for led1 at 900V");
tree->Branch("QE_900V_led1",&qe_900V_led1,"Quantum effeciency for led1 at 900V");
tree->Branch("Gain_1000V_led1",&gain_1000V_led1,"Gain for led1 at 1000V");
tree->Branch("QE_1000V_led1",&qe_1000V_led1,"Quantum effeciency for led1 at 1000V");
tree->Branch("Gain_1200V_led1",&gain_1200V_led1,"Gain for led1 at 1200V");
tree->Branch("QE_1200V_led1",&qe_1200V_led1,"Quantum effeciency for led1 at 1200V");
tree->Branch("Gain_1200V_led2",&gain_1200V_led2,"Gain for led2 at 1200V");
tree->Branch("QE_1200V_led2",&qe_1200V_led2,"Quantum effeciency for led2 at 1200V");
tree->Branch("Gain_1200V_led3",&gain_1200V_led3,"Gain for led3 at 1200V");
tree->Branch("QE_1200V_led3",&qe_1200V_led3,"Quantum effeciency for led3 at 1200V");
tree->Branch("Gain_1200V_led4",&gain_1200V_led4,"Gain for led4 at 1200V");
tree->Branch("QE_1200V_led4",&qe_1200V_led4,"Quantum effeciency for led4 at 1200V");
tree->Branch("Gain_1400V_led1",&gain_1400V_led1,"Gain for led1 at 1400V");
tree->Branch("QE_1400V_led1",&qe_1400V_led1,"Quantum effeciency for led1 at 1400V");
tree->Branch("Gain_1600V_led1",&gain_1600V_led1,"Gain for led1 at 1600V");
tree->Branch("QE_1600V_led1",&qe_1600V_led1,"Quantum effeciency for led1 at 1600V");
tree->Branch("Leakage_0V",&leakage_0V,"Current leakage at 0V");
tree->Branch("Leakage_0V_error",&leakage_0V_error,"Error on the current leakage at 0V");
tree->Branch("Leakage_0V_n",&leakage_0V_n,"Number of points used to estimate the current leakage at 0V/I");
tree->Branch("Leakage_0V_spikes",&leakage_0V_spikes,"Number of spikes found when estimate the current leakage at 0V/I");
tree->Branch("Leakage_800V",&leakage_800V,"Current leakage at 800V");
tree->Branch("Leakage_800V_error",&leakage_800V_error,"Error on the current leakage at 800V");
tree->Branch("Leakage_800V_n",&leakage_800V_n,"Number of points used to estimate the current leakage at 800V/I");
tree->Branch("Leakage_800V_spikes",&leakage_800V_spikes,"Number of spikes found when estimate the current leakage at 800V/I");
tree->Branch("Leakage_900V",&leakage_900V,"Current leakage at 900V");
tree->Branch("Leakage_900V_n",&leakage_900V_n,"Number of points used to estimate the current leakage at 900V/I");
tree->Branch("Leakage_900V_spikes",&leakage_900V_spikes,"Number of spikes found when estimate the current leakage at 900V/I");
tree->Branch("Leakage_1000V",&leakage_1000V,"Current leakage at 1000V");
tree->Branch("Leakage_1000V_n",&leakage_1000V_n,"Number of points used to estimate the current leakage at 1000V/I");
tree->Branch("Leakage_1000V_spikes",&leakage_1000V_spikes,"Number of spikes found when estimate the current leakage at 1000V/I");
tree->Branch("Leakage_1200V",&leakage_1200V,"Current leakage at 1200V");
tree->Branch("Leakage_1200V_n",&leakage_1200V_n,"Number of points used to estimate the current leakage at 1200V/I");
tree->Branch("Leakage_1200V_spikes",&leakage_1200V_spikes,"Number of spikes found when estimate the current leakage at 1200V/I");
tree->Branch("Leakage_1400V",&leakage_1400V,"Current leakage at 1400V");
tree->Branch("Leakage_1400V_n",&leakage_1400V_n,"Number of points used to estimate the current leakage at 1400V/I");
tree->Branch("Leakage_1400V_spikes",&leakage_1400V_spikes,"Number of spikes found when estimate the current leakage at 1400V/I");
tree->Branch("Leakage_1600V",&leakage_1600V,"Current leakage at 1600V");
tree->Branch("Leakage_1600V_n",&leakage_1600V_n,"Number of points used to estimate the current leakage at 1600V/I");
tree->Branch("Leakage_1600V_spikes",&leakage_1600V_spikes,"Number of spikes found when estimate the current leakage at 1600V/I");

//loop over the pmt files
for (int i=0; i < n_files; i++)
{

//open the cpt file
  string file = files_in[i];
  cout<<"File "<<i+1<<"/"<<n_files<<" -> "<<file<<endl;
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
pvec_adut = &vec_adut;
pvec_aref = &vec_aref;
pvec_led = &vec_led;
vec_begin.clear();
vec_end.clear();
vec_time.clear();
vec_hv.clear();
vec_cath.clear();
vec_adut.clear();
vec_aref.clear();
vec_led.clear();

total_spikes = 0;
module = 0;
sector = 0;

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

index_leakage_0V_begin = 0;
index_leakage_800V_begin = 0;
index_leakage_900V_begin = 0;
index_leakage_1000V_begin = 0;
index_leakage_1200V_begin = 0;
index_leakage_1400V_begin = 0;
index_leakage_1600V_begin = 0;

index_leakage_0V_end = 0;
index_leakage_800V_end = 0;
index_leakage_900V_end = 0;
index_leakage_1000V_end = 0;
index_leakage_1200V_end = 0;
index_leakage_1400V_end = 0;
index_leakage_1600V_end = 0;

cath_800V_led1 = 0.0;
cath_800V_led1_error = 0.0;
cath_800V_led1_spikes = 0;
cath_800V_led1_n = 0;
cath_800V_led2 = 0.0;
cath_800V_led2_error = 0.0;
cath_800V_led2_spikes = 0;
cath_800V_led2_n = 0;
cath_800V_led3 = 0.0;
cath_800V_led3_error = 0.0;
cath_800V_led3_spikes = 0;
cath_800V_led3_n = 0;
cath_800V_led4 = 0.0;
cath_800V_led4_error = 0.0;
cath_800V_led4_spikes = 0;
cath_800V_led4_n = 0;
cath_900V_led1 = 0.0;
cath_900V_led1_error = 0.0;
cath_900V_led1_spikes = 0;
cath_900V_led1_n = 0;
cath_1000V_led1 = 0.0;
cath_1000V_led1_error = 0.0;
cath_1000V_led1_spikes = 0;
cath_1000V_led1_n = 0;
cath_1200V_led1 = 0.0;
cath_1200V_led1_error = 0.0;
cath_1200V_led1_spikes = 0;
cath_1200V_led1_n = 0;
cath_1200V_led2 = 0.0;
cath_1200V_led2_error = 0.0;
cath_1200V_led2_spikes = 0;
cath_1200V_led2_n = 0;
cath_1200V_led3 = 0.0;
cath_1200V_led3_error = 0.0;
cath_1200V_led3_spikes = 0;
cath_1200V_led3_n = 0;
cath_1200V_led4 = 0.0;
cath_1200V_led4_error = 0.0;
cath_1200V_led4_spikes = 0;
cath_1200V_led4_n = 0;
cath_1400V_led1 = 0.0;
cath_1400V_led1_error = 0.0;
cath_1400V_led1_spikes = 0;
cath_1400V_led1_n = 0;
cath_1600V_led1 = 0.0;
cath_1600V_led1_error = 0.0;
cath_1600V_led1_spikes = 0;
cath_1600V_led1_n = 0;

anode_800V_led1_up = 0.0;
anode_800V_led1_down = 0.0;
anode_800V_led2_up = 0.0;
anode_800V_led2_down = 0.0;
anode_800V_led3_up = 0.0;
anode_800V_led3_down = 0.0;
anode_800V_led4_up = 0.0;
anode_800V_led4_down = 0.0;
anode_900V_led1_up = 0.0;
anode_900V_led1_down = 0.0;
anode_1000V_led1_up = 0.0;
anode_1000V_led1_down = 0.0;
anode_1200V_led1_up = 0.0;
anode_1200V_led1_down = 0.0;
anode_1200V_led2_up = 0.0;
anode_1200V_led2_down = 0.0;
anode_1200V_led3_up = 0.0;
anode_1200V_led3_down = 0.0;
anode_1200V_led4_up = 0.0;
anode_1200V_led4_down = 0.0;
anode_1400V_led1_up = 0.0;
anode_1400V_led1_down = 0.0;
anode_1600V_led1_up = 0.0;
anode_1600V_led1_down = 0.0;

ref_800V_led1_up = 0.0;
ref_800V_led1_down = 0.0;
ref_800V_led2_up = 0.0;
ref_800V_led2_down = 0.0;
ref_800V_led3_up = 0.0;
ref_800V_led3_down = 0.0;
ref_800V_led4_up = 0.0;
ref_800V_led4_down = 0.0;
ref_900V_led1_up = 0.0;
ref_900V_led1_down = 0.0;
ref_1000V_led1_up = 0.0;
ref_1000V_led1_down = 0.0;
ref_1200V_led1_up = 0.0;
ref_1200V_led1_down = 0.0;
ref_1200V_led2_up = 0.0;
ref_1200V_led2_down = 0.0;
ref_1200V_led3_up = 0.0;
ref_1200V_led3_down = 0.0;
ref_1200V_led4_up = 0.0;
ref_1200V_led4_down = 0.0;
ref_1400V_led1_up = 0.0;
ref_1400V_led1_down = 0.0;
ref_1600V_led1_up = 0.0;
ref_1600V_led1_down = 0.0;

gain_800V_led1 = 0.0;
qe_800V_led1 = 0.0;
gain_800V_led2 = 0.0;
qe_800V_led2 = 0.0;
gain_800V_led3 = 0.0;
qe_800V_led3 = 0.0;
gain_800V_led4 = 0.0;
qe_800V_led4 = 0.0;
gain_900V_led1 = 0.0;
qe_900V_led1 = 0.0;
gain_1000V_led1 = 0.0;
qe_1000V_led1 = 0.0;
gain_1200V_led1 = 0.0;
qe_1200V_led1 = 0.0;
gain_1200V_led2 = 0.0;
qe_1200V_led2 = 0.0;
gain_1200V_led3 = 0.0;
qe_1200V_led3 = 0.0;
gain_1200V_led4 = 0.0;
qe_1200V_led4 = 0.0;
gain_1400V_led1 = 0.0;
qe_1400V_led1 = 0.0;
gain_1600V_led1 = 0.0;
qe_1600V_led1 = 0.0;

leakage_0V = 0.0;
leakage_800V = 0.0;
leakage_900V = 0.0;
leakage_1000V = 0.0;
leakage_1200V = 0.0;
leakage_1400V = 0.0;
leakage_1600V = 0.0;

leakage_0V_n = 0;
leakage_800V_n = 0;
leakage_900V_n = 0;
leakage_1000V_n = 0;
leakage_1200V_n = 0;
leakage_1400V_n = 0;
leakage_1600V_n = 0;

leakage_0V_spikes = 0;
leakage_800V_spikes = 0;
leakage_900V_spikes = 0;
leakage_1000V_spikes = 0;
leakage_1200V_spikes = 0;
leakage_1400V_spikes = 0;
leakage_1600V_spikes = 0;

leakage_0V_error = 0;
leakage_800V_error = 0;
leakage_900V_error = 0;
leakage_1000V_error = 0;
leakage_1200V_error = 0;
leakage_1400V_error = 0;
leakage_1600V_error = 0;

//find the code of the pmt
found1 = file.find("_");
found2 = file.find("_",found1+1);
found3 = file.find("_",found2+1);
pmt = file.substr(found2+1,found3-found2-1);

//reading the cpt file
while(!feof(f))
{
fscanf(f,"%s %i %i %f %f %f %i", read_time, &time, &hv, &cath, &adut, &aref, &led);
//cout<<read_time<<" "<<time<<" "<<hv<<" "<<cath<<" "<<adut<<" "<<aref<<" "<<led<<endl;
if (time == 0) { ini_time = (string) read_time; } //set begin time of the measurement
vec_time.push_back(time);
vec_hv.push_back(hv);
vec_cath_ori.push_back(cath);
vec_cath.push_back(cath);
vec_adut.push_back(adut);
vec_aref.push_back(aref);
vec_led.push_back(led);
entries = entries + 1; //update the number of stored entries
}

LeakageSubtractor theSubtractor(vec_time,vec_cath,vec_hv,vec_led);
theSubtractor.SetVerbosity(0);
theSubtractor.Run();

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

set_coordinates(pmt, module, sector);
if (sector == 0 and module == 0) { total_unknown = total_unknown + 1; }

//output the details of the measurement
cout<<"PMT code: "<<pmt<<" (Sector : "<<sector<<" ; Module : "<<module<<")"<<endl;
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
if (vec_hv[j] < -1620) { cout<<"Unknown voltage : "<<vec_hv[j]<<" with led : "<<vec_led[j]<<endl; }

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

//800V led1
calc_dif(index_800V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_800V_led1_up, ref_800V_led1_up);
calc_dif(index_800V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_800V_led1_down, ref_800V_led1_down);
gain_cathode(index_800V_led1_up, index_800V_led1_down, &vec_cath, cath_800V_led1, cath_800V_led1_spikes, cath_800V_led1_error, cath_800V_led1_n);
calc_eff(cath_800V_led1, anode_800V_led1_up, anode_800V_led1_down, ref_800V_led1_up, ref_800V_led1_down, gain_800V_led1, qe_800V_led1);
total_spikes = cath_800V_led1_spikes;

//800V led2
calc_dif(index_800V_led2_up, &vec_adut, &vec_aref, &vec_led, anode_800V_led2_up, ref_800V_led2_up);
calc_dif(index_800V_led2_down, &vec_adut, &vec_aref, &vec_led, anode_800V_led2_down, ref_800V_led2_down);
gain_cathode(index_800V_led2_up, index_800V_led2_down, &vec_cath, cath_800V_led2, cath_800V_led2_spikes, cath_800V_led2_error, cath_800V_led2_n);
calc_eff(cath_800V_led2, anode_800V_led2_up, anode_800V_led2_down, ref_800V_led2_up, ref_800V_led2_down, gain_800V_led2, qe_800V_led2);
total_spikes = total_spikes + cath_800V_led2_spikes;

//800V led3
calc_dif(index_800V_led3_up, &vec_adut, &vec_aref, &vec_led, anode_800V_led3_up, ref_800V_led3_up);
calc_dif(index_800V_led3_down, &vec_adut, &vec_aref, &vec_led, anode_800V_led3_down, ref_800V_led3_down);
gain_cathode(index_800V_led3_up, index_800V_led3_down, &vec_cath, cath_800V_led3, cath_800V_led3_spikes, cath_800V_led3_error, cath_800V_led3_n);
calc_eff(cath_800V_led3, anode_800V_led3_up, anode_800V_led3_down, ref_800V_led3_up, ref_800V_led3_down, gain_800V_led3, qe_800V_led3);
total_spikes = total_spikes + cath_800V_led3_spikes;

//800V led4
calc_dif(index_800V_led4_up, &vec_adut, &vec_aref, &vec_led, anode_800V_led4_up, ref_800V_led4_up);
calc_dif(index_800V_led4_down, &vec_adut, &vec_aref, &vec_led, anode_800V_led4_down, ref_800V_led4_down);
gain_cathode(index_800V_led4_up, index_800V_led4_down, &vec_cath, cath_800V_led4, cath_800V_led4_spikes, cath_800V_led4_error, cath_800V_led4_n);
calc_eff(cath_800V_led4, anode_800V_led4_up, anode_800V_led4_down, ref_800V_led4_up, ref_800V_led4_down, gain_800V_led4, qe_800V_led4);
total_spikes = total_spikes + cath_800V_led4_spikes;

//900V led1
calc_dif(index_900V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_900V_led1_up, ref_900V_led1_up);
calc_dif(index_900V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_900V_led1_down, ref_900V_led1_down);
gain_cathode(index_900V_led1_up, index_900V_led1_down, &vec_cath, cath_900V_led1, cath_900V_led1_spikes, cath_900V_led1_error, cath_900V_led1_n);
calc_eff(cath_900V_led1, anode_900V_led1_up, anode_900V_led1_down, ref_900V_led1_up, ref_900V_led1_down, gain_900V_led1, qe_900V_led1);
total_spikes = total_spikes + cath_900V_led1_spikes;

//1000V led1
calc_dif(index_1000V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_1000V_led1_up, ref_1000V_led1_up);
calc_dif(index_1000V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_1000V_led1_down, ref_1000V_led1_down);
gain_cathode(index_1000V_led1_up, index_1000V_led1_down, &vec_cath, cath_1000V_led1, cath_1000V_led1_spikes, cath_1000V_led1_error, cath_1000V_led1_n);
calc_eff(cath_1000V_led1, anode_1000V_led1_up, anode_1000V_led1_down, ref_1000V_led1_up, ref_1000V_led1_down, gain_1000V_led1, qe_1000V_led1);
total_spikes = total_spikes + cath_1000V_led1_spikes;

//1200V led1
calc_dif(index_1200V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_1200V_led1_up, ref_1200V_led1_up);
calc_dif(index_1200V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_1200V_led1_down, ref_1200V_led1_down);
gain_cathode(index_1200V_led1_up, index_1200V_led1_down, &vec_cath, cath_1200V_led1, cath_1200V_led1_spikes, cath_1200V_led1_error, cath_1200V_led1_n);
calc_eff(cath_1200V_led1, anode_1200V_led1_up, anode_1200V_led1_down, ref_1200V_led1_up, ref_1200V_led1_down, gain_1200V_led1, qe_1200V_led1);
total_spikes = total_spikes + cath_1200V_led1_spikes;

//1200V led2
calc_dif(index_1200V_led2_up, &vec_adut, &vec_aref, &vec_led, anode_1200V_led2_up, ref_1200V_led2_up);
calc_dif(index_1200V_led2_down, &vec_adut, &vec_aref, &vec_led, anode_1200V_led2_down, ref_1200V_led2_down);
gain_cathode(index_1200V_led2_up, index_1200V_led2_down, &vec_cath, cath_1200V_led2, cath_1200V_led2_spikes, cath_1200V_led2_error, cath_1200V_led2_n);
calc_eff(cath_1200V_led2, anode_1200V_led2_up, anode_1200V_led2_down, ref_1200V_led2_up, ref_1200V_led2_down, gain_1200V_led2, qe_1200V_led2);
total_spikes = total_spikes + cath_1200V_led2_spikes;

//1200V led3
calc_dif(index_1200V_led3_up, &vec_adut, &vec_aref, &vec_led, anode_1200V_led3_up, ref_1200V_led3_up);
calc_dif(index_1200V_led3_down, &vec_adut, &vec_aref, &vec_led, anode_1200V_led3_down, ref_1200V_led3_down);
gain_cathode(index_1200V_led3_up, index_1200V_led3_down, &vec_cath, cath_1200V_led3, cath_1200V_led3_spikes, cath_1200V_led3_error, cath_1200V_led3_n);
calc_eff(cath_1200V_led3, anode_1200V_led3_up, anode_1200V_led3_down, ref_1200V_led3_up, ref_1200V_led3_down, gain_1200V_led3, qe_1200V_led3);
total_spikes = total_spikes + cath_1200V_led3_spikes;

//1200V led4
calc_dif(index_1200V_led4_up, &vec_adut, &vec_aref, &vec_led, anode_1200V_led4_up, ref_1200V_led4_up);
calc_dif(index_1200V_led4_down, &vec_adut, &vec_aref, &vec_led, anode_1200V_led4_down, ref_1200V_led4_down);
gain_cathode(index_1200V_led4_up, index_1200V_led4_down, &vec_cath, cath_1200V_led4, cath_1200V_led4_spikes, cath_1200V_led4_error, cath_1200V_led4_n);
calc_eff(cath_1200V_led4, anode_1200V_led4_up, anode_1200V_led4_down, ref_1200V_led4_up, ref_1200V_led4_down, gain_1200V_led4, qe_1200V_led4);
total_spikes = total_spikes + cath_1200V_led4_spikes;

//1400V led1
calc_dif(index_1400V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_1400V_led1_up, ref_1400V_led1_up);
calc_dif(index_1400V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_1400V_led1_down, ref_1400V_led1_down);
gain_cathode(index_1400V_led1_up, index_1400V_led1_down, &vec_cath, cath_1400V_led1, cath_1400V_led1_spikes, cath_1400V_led1_error, cath_1400V_led1_n);
calc_eff(cath_1400V_led1, anode_1400V_led1_up, anode_1400V_led1_down, ref_1400V_led1_up, ref_1400V_led1_down, gain_1400V_led1, qe_1400V_led1);
total_spikes = total_spikes + cath_1400V_led1_spikes;

//1600V led1
calc_dif(index_1600V_led1_up, &vec_adut, &vec_aref, &vec_led, anode_1600V_led1_up, ref_1600V_led1_up);
calc_dif(index_1600V_led1_down, &vec_adut, &vec_aref, &vec_led, anode_1600V_led1_down, ref_1600V_led1_down);
gain_cathode(index_1600V_led1_up, index_1600V_led1_down, &vec_cath, cath_1600V_led1, cath_1600V_led1_spikes, cath_1600V_led1_error, cath_1600V_led1_n);
calc_eff(cath_1600V_led1, anode_1600V_led1_up, anode_1600V_led1_down, ref_1600V_led1_up, ref_1600V_led1_down, gain_1600V_led1, qe_1600V_led1);
total_spikes = total_spikes + cath_1600V_led1_spikes;

//index output for the leakage estimation
cout<<"0V     "<<index_leakage_0V_begin<<" "<<index_leakage_0V_end<<endl;
cout<<"800V   "<<index_leakage_800V_begin<<" "<<index_leakage_800V_end<<endl;
cout<<"900V   "<<index_leakage_900V_begin<<" "<<index_leakage_900V_end<<endl;
cout<<"1000V  "<<index_leakage_1000V_begin<<" "<<index_leakage_1000V_end<<endl;
cout<<"1200V  "<<index_leakage_1200V_begin<<" "<<index_leakage_1200V_end<<endl;
cout<<"1400V  "<<index_leakage_1400V_begin<<" "<<index_leakage_1400V_end<<endl;
cout<<"1600V  "<<index_leakage_1600V_begin<<" "<<index_leakage_1600V_end<<endl;

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

//leakage 1400V
estimate_leakage(index_leakage_1600V_begin, index_leakage_1600V_end, &vec_cath_ori, leakage_1600V, leakage_1600V_n, leakage_1600V_spikes, leakage_1600V_error);
total_spikes = total_spikes + leakage_1600V_spikes;

cout<<"Total spikes = "<<total_spikes<<endl;

//cout<<"the problem is before filling the tree?"<<endl;

//fill the tree
tree->Fill();

}
cout<<"Total unknown PMTs : "<<total_unknown<<endl;

//write to file
TFile *data_output= TFile::Open( tree_out.c_str() , "RECREATE");
tree->Write();
data_output->Close();
cout<<tree_out<<" created sucessfully!"<<endl;

}
