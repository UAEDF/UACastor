#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"

//user
#include "LeakageSubtractor.h"

void calc_eff(float cath_up, float cath_down, float anode_up, float anode_down, float ref_up, float ref_down, float& ee, float& qe)
{

float cath_ave, anode_ave, ref_ave;

cath_ave = (cath_up + cath_down)/2;
anode_ave = (anode_up + anode_down)/2;
ref_ave = (ref_up + ref_down)/2;

if (cath_ave > 0.0) { ee = anode_ave / cath_ave; }
if (cath_ave > 0.0) { qe = ref_ave / cath_ave; }

//cout<<"ee = "<<ee<<" qe = "<<qe<<endl;

}


void calc_dif(size_t cent_val, std::vector<int> *vec_hv, std::vector<float> *vec_cath, std::vector<float> *vec_adut, std::vector<float> *vec_aref, std::vector<int> *vec_led, float& cath, float& anode, float& ref)
{

//check the inputed values
//cout<<"central value = "<<cent_val<<endl;
if (cent_val > 0)
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

float ave_cath_before = 0, ave_cath_after = 0;
float ave_anode_before = 0, ave_anode_after = 0;
float ave_ref_before = 0, ave_ref_after = 0;

for (int i = 1; i <= 5; i++)
{
ave_cath_before = ave_cath_before + vec_cath->at(cent_val-1-i);
//cout<<i<<" cath A = "<<vec_cath->at(cent_val-1-i)<<endl;
ave_cath_after = ave_cath_after + vec_cath->at(cent_val+5+i);
//cout<<i<<" cath B = "<<vec_cath->at(cent_val+5+i)<<endl;
ave_anode_before = ave_anode_before + vec_adut->at(cent_val-1-i);
//cout<<i<<" anode A = "<<vec_adut->at(cent_val-1-i)<<endl;
ave_anode_after = ave_anode_after + vec_adut->at(cent_val+5+i);
//cout<<i<<" anode B = "<<vec_adut->at(cent_val+5+i)<<endl;
ave_ref_before = ave_ref_before + vec_aref->at(cent_val-1-i);
//cout<<i<<" ref A = "<<vec_aref->at(cent_val-1-i)<<endl;
ave_ref_after = ave_ref_after + vec_aref->at(cent_val+5+i);
//cout<<i<<" ref B = "<<vec_aref->at(cent_val+5+i)<<endl;
}

ave_cath_before = ave_cath_before/5.0;
ave_cath_after = ave_cath_after/5.0;
ave_anode_before = ave_anode_before/5.0;
ave_anode_after = ave_anode_after/5.0;
ave_ref_before = ave_ref_before/5.0;
ave_ref_after = ave_ref_after/5.0;

//cout<<"cath before = "<<ave_cath_before<<endl;
//cout<<"cath after = "<<ave_cath_after<<endl;
//cout<<"anode before = "<<ave_anode_before<<endl;
//cout<<"anode after = "<<ave_anode_after<<endl;
//cout<<"ref before = "<<ave_ref_before<<endl;
//cout<<"ref after = "<<ave_ref_after<<endl;

//calculate the gain
if (vec_led->at(cent_val-1) == 0)
{
cath = ave_cath_after - ave_cath_before;
anode = ave_anode_before - ave_anode_after;
ref = ave_ref_before - ave_ref_after;
}
if (vec_led->at(cent_val-1) > 0)
{
cath = ave_cath_before - ave_cath_after;
anode = ave_anode_after - ave_anode_before;
ref = ave_ref_after - ave_ref_before;
}

//check if it was correctly calculated
//cout<<"cath = "<<cath<<endl;
//cout<<"anode = "<<anode<<endl;
//cout<<"ref = "<<ref<<endl;
}

}

void create_tree(string *files_in, int n_files, string tree_out){
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

int found1, found2, found3;

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

float cath_800V_led1_up, cath_800V_led1_down;
float cath_800V_led2_up, cath_800V_led2_down;
float cath_800V_led3_up, cath_800V_led3_down;
float cath_800V_led4_up, cath_800V_led4_down;
float cath_900V_led1_up, cath_900V_led1_down;
float cath_1000V_led1_up, cath_1000V_led1_down;
float cath_1200V_led1_up, cath_1200V_led1_down;
float cath_1200V_led2_up, cath_1200V_led2_down;
float cath_1200V_led3_up, cath_1200V_led3_down;
float cath_1200V_led4_up, cath_1200V_led4_down;
float cath_1400V_led1_up, cath_1400V_led1_down;
float cath_1600V_led1_up, cath_1600V_led1_down;

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

float ee_800V_led1, qe_800V_led1;
float ee_800V_led2, qe_800V_led2;
float ee_800V_led3, qe_800V_led3;
float ee_800V_led4, qe_800V_led4;
float ee_900V_led1, qe_900V_led1;
float ee_1000V_led1, qe_1000V_led1;
float ee_1200V_led1, qe_1200V_led1;
float ee_1200V_led2, qe_1200V_led2;
float ee_1200V_led3, qe_1200V_led3;
float ee_1200V_led4, qe_1200V_led4;
float ee_1400V_led1, qe_1400V_led1;
float ee_1600V_led1, qe_1600V_led1;

//tree declaration
TTree *tree = new TTree("Castor_PMT_Caracterization_2012","Castor PMT Caracterization 2012");
tree->Branch("PMT",&pmt,"Reference code of the PMT");
tree->Branch("Measurement_begin","std::vector<int>",&pvec_begin);
tree->Branch("Measurement_end","std::vector<int>",&pvec_end);
tree->Branch("Entries",&entries,"Number of entries");
tree->Branch("Measured_time","std::vector<int>",&pvec_time);
tree->Branch("HV","std::vector<int>",&pvec_hv);
tree->Branch("Cathode","std::vector<float>",&pvec_cath_ori);
tree->Branch("Cathode_after_background_subtraction","std::vector<float>",&pvec_cath);
tree->Branch("Anode","std::vector<float>",&pvec_adut);
tree->Branch("Reference_PMT","std::vector<float>",&pvec_aref);
tree->Branch("Led","std::vector<int>",&pvec_led);
tree->Branch("Cath_800V_led1_up",&cath_800V_led1_up,"Cathode Gain when switching on led1 at 800V");
tree->Branch("Cath_800V_led1_down",&cath_800V_led1_down,"Cathode Gain when switching off led1 at 800V");
tree->Branch("Anode_800V_led1_up",&anode_800V_led1_up,"Anode Gain when switching on led1 at 800V");
tree->Branch("Anode_800V_led1_down",&anode_800V_led1_down,"Anode Gain when switching off led1 at 800V");
tree->Branch("Reference_800V_led1_up",&ref_800V_led1_up,"Reference Gain when switching on led1 at 800V");
tree->Branch("Reference_800V_led1_down",&ref_800V_led1_down,"Reference Gain when switching off led1 at 800V");
tree->Branch("Cath_800V_led2_up",&cath_800V_led2_up,"Cathode Gain when switching on led2 at 800V");
tree->Branch("Cath_800V_led2_down",&cath_800V_led2_down,"Cathode Gain when switching off led2 at 800V");
tree->Branch("Anode_800V_led2_up",&anode_800V_led2_up,"Anode Gain when switching on led2 at 800V");
tree->Branch("Anode_800V_led2_down",&anode_800V_led2_down,"Anode Gain when switching off led2 at 800V");
tree->Branch("Reference_800V_led2_up",&ref_800V_led2_up,"Reference Gain when switching on led2 at 800V");
tree->Branch("Reference_800V_led2_down",&ref_800V_led2_down,"Reference Gain when switching off led2 at 800V");
tree->Branch("Cath_800V_led3_up",&cath_800V_led3_up,"Cathode Gain when switching on led3 at 800V");
tree->Branch("Cath_800V_led3_down",&cath_800V_led3_down,"Cathode Gain when switching off led3 at 800V");
tree->Branch("Anode_800V_led3_up",&anode_800V_led3_up,"Anode Gain when switching on led3 at 800V");
tree->Branch("Anode_800V_led3_down",&anode_800V_led3_down,"Anode Gain when switching off led3 at 800V");
tree->Branch("Reference_800V_led3_up",&ref_800V_led3_up,"Reference Gain when switching on led3 at 800V");
tree->Branch("Reference_800V_led3_down",&ref_800V_led3_down,"Reference Gain when switching off led3 at 800V");
tree->Branch("Cath_800V_led4_up",&cath_800V_led4_up,"Cathode Gain when switching on led4 at 800V");
tree->Branch("Cath_800V_led4_down",&cath_800V_led4_down,"Cathode Gain when switching off led4 at 800V");
tree->Branch("Anode_800V_led4_up",&anode_800V_led4_up,"Anode Gain when switching on led4 at 800V");
tree->Branch("Anode_800V_led4_down",&anode_800V_led4_down,"Anode Gain when switching off led4 at 800V");
tree->Branch("Reference_800V_led4_up",&ref_800V_led4_up,"Reference Gain when switching on led4 at 800V");
tree->Branch("Reference_800V_led4_down",&ref_800V_led4_down,"Reference Gain when switching off led4 at 800V");
tree->Branch("Cath_900V_led1_up",&cath_900V_led1_up,"Cathode Gain when switching on led1 at 900V");
tree->Branch("Cath_900V_led1_down",&cath_900V_led1_down,"Cathode Gain when switching off led1 at 900V");
tree->Branch("Anode_900V_led1_up",&anode_900V_led1_up,"Anode Gain when switching on led1 at 900V");
tree->Branch("Anode_900V_led1_down",&anode_900V_led1_down,"Anode Gain when switching off led1 at 900V");
tree->Branch("Reference_900V_led1_up",&ref_900V_led1_up,"Reference Gain when switching on led1 at 900V");
tree->Branch("Reference_900V_led1_down",&ref_900V_led1_down,"Reference Gain when switching off led1 at 900V");
tree->Branch("Cath_1000V_led1_up",&cath_1000V_led1_up,"Cathode Gain when switching on led1 at 1000V");
tree->Branch("Cath_1000V_led1_down",&cath_1000V_led1_down,"Cathode Gain when switching off led1 at 1000V");
tree->Branch("Anode_1000V_led1_up",&anode_1000V_led1_up,"Anode Gain when switching on led1 at 1000V");
tree->Branch("Anode_1000V_led1_down",&anode_1000V_led1_down,"Anode Gain when switching off led1 at 1000V");
tree->Branch("Reference_1000V_led1_up",&ref_1000V_led1_up,"Reference Gain when switching on led1 at 1000V");
tree->Branch("Reference_1000V_led1_down",&ref_1000V_led1_down,"Reference Gain when switching off led1 at 1000V");
tree->Branch("Cath_1200V_led1_up",&cath_1200V_led1_up,"Cathode Gain when switching on led1 at 1200V");
tree->Branch("Cath_1200V_led1_down",&cath_1200V_led1_down,"Cathode Gain when switching off led1 at 1200V");
tree->Branch("Anode_1200V_led1_up",&anode_1200V_led1_up,"Anode Gain when switching on led1 at 1200V");
tree->Branch("Anode_1200V_led1_down",&anode_1200V_led1_down,"Anode Gain when switching off led1 at 1200V");
tree->Branch("Reference_1200V_led1_up",&ref_1200V_led1_up,"Reference Gain when switching on led1 at 1200V");
tree->Branch("Reference_1200V_led1_down",&ref_1200V_led1_down,"Reference Gain when switching off led1 at 1200V");
tree->Branch("Cath_1200V_led2_up",&cath_1200V_led2_up,"Cathode Gain when switching on led2 at 1200V");
tree->Branch("Cath_1200V_led2_down",&cath_1200V_led2_down,"Cathode Gain when switching off led2 at 1200V");
tree->Branch("Anode_1200V_led2_up",&anode_1200V_led2_up,"Anode Gain when switching on led2 at 1200V");
tree->Branch("Anode_1200V_led2_down",&anode_1200V_led2_down,"Anode Gain when switching off led2 at 1200V");
tree->Branch("Reference_1200V_led2_up",&ref_1200V_led2_up,"Reference Gain when switching on led2 at 1200V");
tree->Branch("Reference_1200V_led2_down",&ref_1200V_led2_down,"Reference Gain when switching off led2 at 1200V");
tree->Branch("Cath_1200V_led3_up",&cath_1200V_led3_up,"Cathode Gain when switching on led3 at 1200V");
tree->Branch("Cath_1200V_led3_down",&cath_1200V_led3_down,"Cathode Gain when switching off led3 at 1200V");
tree->Branch("Anode_1200V_led3_up",&anode_1200V_led3_up,"Anode Gain when switching on led3 at 1200V");
tree->Branch("Anode_1200V_led3_down",&anode_1200V_led3_down,"Anode Gain when switching off led3 at 1200V");
tree->Branch("Reference_1200V_led3_up",&ref_1200V_led3_up,"Reference Gain when switching on led3 at 1200V");
tree->Branch("Reference_1200V_led3_down",&ref_1200V_led3_down,"Reference Gain when switching off led3 at 1200V");
tree->Branch("Cath_1200V_led4_up",&cath_1200V_led4_up,"Cathode Gain when switching on led4 at 1200V");
tree->Branch("Cath_1200V_led4_down",&cath_1200V_led4_down,"Cathode Gain when switching off led4 at 1200V");
tree->Branch("Anode_1200V_led4_up",&anode_1200V_led4_up,"Anode Gain when switching on led4 at 1200V");
tree->Branch("Anode_1200V_led4_down",&anode_1200V_led4_down,"Anode Gain when switching off led4 at 1200V");
tree->Branch("Reference_1200V_led4_up",&ref_1200V_led4_up,"Reference Gain when switching on led4 at 1200V");
tree->Branch("Reference_1200V_led4_down",&ref_1200V_led4_down,"Reference Gain when switching off led4 at 1200V");
tree->Branch("Cath_1400V_led1_up",&cath_1400V_led1_up,"Cathode Gain when switching on led1 at 1400V");
tree->Branch("Cath_1400V_led1_down",&cath_1400V_led1_down,"Cathode Gain when switching off led1 at 1400V");
tree->Branch("Anode_1400V_led1_up",&anode_1400V_led1_up,"Anode Gain when switching on led1 at 1400V");
tree->Branch("Anode_1400V_led1_down",&anode_1400V_led1_down,"Anode Gain when switching off led1 at 1400V");
tree->Branch("Reference_1400V_led1_up",&ref_1400V_led1_up,"Reference Gain when switching on led1 at 1400V");
tree->Branch("Reference_1400V_led1_down",&ref_1400V_led1_down,"Reference Gain when switching off led1 at 1400V");
tree->Branch("Cath_1600V_led1_up",&cath_1600V_led1_up,"Cathode Gain when switching on led1 at 1400V");
tree->Branch("Cath_1600V_led1_down",&cath_1600V_led1_down,"Cathode Gain when switching off led1 at 1600V");
tree->Branch("Anode_1600V_led1_up",&anode_1600V_led1_up,"Anode Gain when switching on led1 at 1600V");
tree->Branch("Anode_1600V_led1_down",&anode_1600V_led1_down,"Anode Gain when switching off led1 at 1600V");
tree->Branch("Reference_1600V_led1_up",&ref_1600V_led1_up,"Reference Gain when switching on led1 at 1600V");
tree->Branch("Reference_1600V_led1_down",&ref_1600V_led1_down,"Reference Gain when switching off led1 at 1600V");
tree->Branch("EE_800V_led1",&ee_800V_led1,"Eletrical effeciency for led1 at 800V");
tree->Branch("QE_800V_led1",&qe_800V_led1,"Quantum effeciency for led1 at 800V");
tree->Branch("EE_800V_led2",&ee_800V_led2,"Eletrical effeciency for led2 at 800V");
tree->Branch("QE_800V_led2",&qe_800V_led2,"Quantum effeciency for led2 at 800V");
tree->Branch("EE_800V_led3",&ee_800V_led3,"Eletrical effeciency for led3 at 800V");
tree->Branch("QE_800V_led3",&qe_800V_led3,"Quantum effeciency for led3 at 800V");
tree->Branch("EE_800V_led4",&ee_800V_led4,"Eletrical effeciency for led4 at 800V");
tree->Branch("QE_800V_led4",&qe_800V_led4,"Quantum effeciency for led4 at 800V");
tree->Branch("EE_900V_led1",&ee_900V_led1,"Eletrical effeciency for led1 at 900V");
tree->Branch("QE_900V_led1",&qe_900V_led1,"Quantum effeciency for led1 at 900V");
tree->Branch("EE_1000V_led1",&ee_1000V_led1,"Eletrical effeciency for led1 at 1000V");
tree->Branch("QE_1000V_led1",&qe_1000V_led1,"Quantum effeciency for led1 at 1000V");
tree->Branch("EE_1200V_led1",&ee_1200V_led1,"Eletrical effeciency for led1 at 1200V");
tree->Branch("QE_1200V_led1",&qe_1200V_led1,"Quantum effeciency for led1 at 1200V");
tree->Branch("EE_1200V_led2",&ee_1200V_led2,"Eletrical effeciency for led2 at 1200V");
tree->Branch("QE_1200V_led2",&qe_1200V_led2,"Quantum effeciency for led2 at 1200V");
tree->Branch("EE_1200V_led3",&ee_1200V_led3,"Eletrical effeciency for led3 at 1200V");
tree->Branch("QE_1200V_led3",&qe_1200V_led3,"Quantum effeciency for led3 at 1200V");
tree->Branch("EE_1200V_led4",&ee_1200V_led4,"Eletrical effeciency for led4 at 1200V");
tree->Branch("QE_1200V_led4",&qe_1200V_led4,"Quantum effeciency for led4 at 1200V");
tree->Branch("EE_1400V_led1",&ee_1400V_led1,"Eletrical effeciency for led1 at 1400V");
tree->Branch("QE_1400V_led1",&qe_1400V_led1,"Quantum effeciency for led1 at 1400V");
tree->Branch("EE_1600V_led1",&ee_1600V_led1,"Eletrical effeciency for led1 at 1600V");
tree->Branch("QE_1600V_led1",&qe_1600V_led1,"Quantum effeciency for led1 at 1600V");

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
  };

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

cath_800V_led1_up = 0;
cath_800V_led1_down = 0;
cath_800V_led2_up = 0;
cath_800V_led2_down = 0;
cath_800V_led3_up = 0;
cath_800V_led3_down = 0;
cath_800V_led4_up = 0;
cath_800V_led4_down = 0;
cath_900V_led1_up = 0;
cath_900V_led1_down = 0;
cath_1000V_led1_up = 0;
cath_1000V_led1_down = 0;
cath_1200V_led1_up = 0;
cath_1200V_led1_down = 0;
cath_1200V_led2_up = 0;
cath_1200V_led2_down = 0;
cath_1200V_led3_up = 0;
cath_1200V_led3_down = 0;
cath_1200V_led4_up = 0;
cath_1200V_led4_down = 0;
cath_1400V_led1_up = 0;
cath_1400V_led1_down = 0;
cath_1600V_led1_up = 0;
cath_1600V_led1_down = 0;

anode_800V_led1_up = 0;
anode_800V_led1_down = 0;
anode_800V_led2_up = 0;
anode_800V_led2_down = 0;
anode_800V_led3_up = 0;
anode_800V_led3_down = 0;
anode_800V_led4_up = 0;
anode_800V_led4_down = 0;
anode_900V_led1_up = 0;
anode_900V_led1_down = 0;
anode_1000V_led1_up = 0;
anode_1000V_led1_down = 0;
anode_1200V_led1_up = 0;
anode_1200V_led1_down = 0;
anode_1200V_led2_up = 0;
anode_1200V_led2_down = 0;
anode_1200V_led3_up = 0;
anode_1200V_led3_down = 0;
anode_1200V_led4_up = 0;
anode_1200V_led4_down = 0;
anode_1400V_led1_up = 0;
anode_1400V_led1_down = 0;
anode_1600V_led1_up = 0;
anode_1600V_led1_down = 0;

ref_800V_led1_up = 0;
ref_800V_led1_down = 0;
ref_800V_led2_up = 0;
ref_800V_led2_down = 0;
ref_800V_led3_up = 0;
ref_800V_led3_down = 0;
ref_800V_led4_up = 0;
ref_800V_led4_down = 0;
ref_900V_led1_up = 0;
ref_900V_led1_down = 0;
ref_1000V_led1_up = 0;
ref_1000V_led1_down = 0;
ref_1200V_led1_up = 0;
ref_1200V_led1_down = 0;
ref_1200V_led2_up = 0;
ref_1200V_led2_down = 0;
ref_1200V_led3_up = 0;
ref_1200V_led3_down = 0;
ref_1200V_led4_up = 0;
ref_1200V_led4_down = 0;
ref_1400V_led1_up = 0;
ref_1400V_led1_down = 0;
ref_1600V_led1_up = 0;
ref_1600V_led1_down = 0;

ee_800V_led1 = 0;
qe_800V_led1 = 0;
ee_800V_led2 = 0;
qe_800V_led2 = 0;
ee_800V_led3 = 0;
qe_800V_led3 = 0;
ee_800V_led4 = 0;
qe_800V_led4 = 0;
ee_900V_led1 = 0;
qe_900V_led1 = 0;
ee_1000V_led1 = 0;
qe_1000V_led1 = 0;
ee_1200V_led1 = 0;
qe_1200V_led1 = 0;
ee_1200V_led2 = 0;
qe_1200V_led2 = 0;
ee_1200V_led3 = 0;
qe_1200V_led3 = 0;
ee_1200V_led4 = 0;
qe_1200V_led4 = 0;
ee_1400V_led1 = 0;
qe_1400V_led1 = 0;
ee_1600V_led1 = 0;
qe_1600V_led1 = 0;

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
//cout<<read_time<<" "<<time<<" "<<aref<<" "<<led<<endl;
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

//output the details of the measurement
cout<<"PMT code: "<<pmt<<endl;
cout<<"Begin: "<<ini_time<<endl;
cout<<"End: "<<end_time<<endl;
//cout<<"End "<<vec_begin[0]<<":"<<vec_begin[1]<<":"<<vec_begin[2]<<endl;
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

if (vec_hv[j] < -780 and vec_hv[j] > -820)
{
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
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_900V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_900V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -980 and vec_hv[j] > -1020)
{
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1000V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1000V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -1180 and vec_hv[j] > -1220)
{
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
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1400V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1400V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

if (vec_hv[j] < -1580 and vec_hv[j] > -1620)
{
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1600V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1600V_led1_down = j; }
if (vec_led[j] == 2 or vec_led[j] == 3 or vec_led[j] == 4 ) { cout<<"Voltage : "<<vec_hv[j]<<" Unknown led : "<<vec_led[j]<<endl; }
}

}

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

calc_dif(index_800V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led1_up, anode_800V_led1_up, ref_800V_led1_up);
calc_dif(index_800V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led1_down, anode_800V_led1_down, ref_800V_led1_down);
calc_eff(cath_800V_led1_up, cath_800V_led1_down, anode_800V_led1_up, anode_800V_led1_down, ref_800V_led1_up, ref_800V_led1_down, ee_800V_led1, qe_800V_led1);

calc_dif(index_800V_led2_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led2_up, anode_800V_led2_up, ref_800V_led2_up);
calc_dif(index_800V_led2_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led2_down, anode_800V_led2_down, ref_800V_led2_down);
calc_eff(cath_800V_led2_up, cath_800V_led2_down, anode_800V_led2_up, anode_800V_led2_down, ref_800V_led2_up, ref_800V_led2_down, ee_800V_led2, qe_800V_led2);

calc_dif(index_800V_led3_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led3_up, anode_800V_led3_up, ref_800V_led3_up);
calc_dif(index_800V_led3_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led3_down, anode_800V_led3_down, ref_800V_led3_down);
calc_eff(cath_800V_led3_up, cath_800V_led3_down, anode_800V_led3_up, anode_800V_led3_down, ref_800V_led3_up, ref_800V_led3_down, ee_800V_led3, qe_800V_led3);

calc_dif(index_800V_led4_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led4_up, anode_800V_led4_up, ref_800V_led4_up);
calc_dif(index_800V_led4_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led4_down, anode_800V_led4_down, ref_800V_led4_down);
calc_eff(cath_800V_led4_up, cath_800V_led4_down, anode_800V_led4_up, anode_800V_led4_down, ref_800V_led4_up, ref_800V_led4_down, ee_800V_led4, qe_800V_led4);

calc_dif(index_900V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_900V_led1_up, anode_900V_led1_up, ref_900V_led1_up);
calc_dif(index_900V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_900V_led1_down, anode_900V_led1_down, ref_900V_led1_down);
calc_eff(cath_900V_led1_up, cath_900V_led1_down, anode_900V_led1_up, anode_900V_led1_down, ref_900V_led1_up, ref_900V_led1_down, ee_900V_led1, qe_900V_led1);

calc_dif(index_1000V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1000V_led1_up, anode_1000V_led1_up, ref_1000V_led1_up);
calc_dif(index_1000V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1000V_led1_down, anode_1000V_led1_down, ref_1000V_led1_down);
calc_eff(cath_1000V_led1_up, cath_1000V_led1_down, anode_1000V_led1_up, anode_1000V_led1_down, ref_1000V_led1_up, ref_1000V_led1_down, ee_1000V_led1, qe_1000V_led1);

calc_dif(index_1200V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led1_up, anode_1200V_led1_up, ref_1200V_led1_up);
calc_dif(index_1200V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led1_down, anode_1200V_led1_down, ref_1200V_led1_down);
calc_eff(cath_1200V_led1_up, cath_1200V_led1_down, anode_1200V_led1_up, anode_1200V_led1_down, ref_1200V_led1_up, ref_1200V_led1_down, ee_1200V_led1, qe_1200V_led1);

calc_dif(index_1200V_led2_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led2_up, anode_1200V_led2_up, ref_1200V_led2_up);
calc_dif(index_1200V_led2_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led2_down, anode_1200V_led2_down, ref_1200V_led2_down);
calc_eff(cath_1200V_led2_up, cath_1200V_led2_down, anode_1200V_led2_up, anode_1200V_led2_down, ref_1200V_led2_up, ref_1200V_led2_down, ee_1200V_led2, qe_1200V_led2);

calc_dif(index_1200V_led3_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led3_up, anode_1200V_led3_up, ref_1200V_led3_up);
calc_dif(index_1200V_led3_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led3_down, anode_1200V_led3_down, ref_1200V_led3_down);
calc_eff(cath_1200V_led3_up, cath_1200V_led3_down, anode_1200V_led3_up, anode_1200V_led3_down, ref_1200V_led3_up, ref_1200V_led3_down, ee_1200V_led3, qe_1200V_led3);

calc_dif(index_1200V_led4_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led4_up, anode_1200V_led4_up, ref_1200V_led4_up);
calc_dif(index_1200V_led4_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led4_down, anode_1200V_led4_down, ref_1200V_led4_down);
calc_eff(cath_1200V_led4_up, cath_1200V_led4_down, anode_1200V_led4_up, anode_1200V_led4_down, ref_1200V_led4_up, ref_1200V_led4_down, ee_1200V_led4, qe_1200V_led4);

//cout<<"ee = "<<ee_1200V_led4<<" qe = "<<qe_1200V_led4<<" "<<cath_1200V_led4_up<<" "<<cath_1200V_led4_down<<" "<<anode_1200V_led4_up<<" "<<anode_1200V_led4_down<<endl;

calc_dif(index_1400V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1400V_led1_up, anode_1400V_led1_up, ref_1400V_led1_up);
calc_dif(index_1400V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1400V_led1_down, anode_1400V_led1_down, ref_1400V_led1_down);
calc_eff(cath_1400V_led1_up, cath_1400V_led1_down, anode_1400V_led1_up, anode_1400V_led1_down, ref_1400V_led1_up, ref_1400V_led1_down, ee_1400V_led1, qe_1400V_led1);

calc_dif(index_1600V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1600V_led1_up, anode_1600V_led1_up, ref_1600V_led1_up);
calc_dif(index_1600V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1600V_led1_down, anode_1600V_led1_down, ref_1600V_led1_down);
calc_eff(cath_1600V_led1_up, cath_1600V_led1_down, anode_1600V_led1_up, anode_1600V_led1_down, ref_1600V_led1_up, ref_1600V_led1_down, ee_1600V_led1, qe_1600V_led1);

//fill the tree
tree->Fill();

}

//write to file
TFile *data_output= TFile::Open( tree_out.c_str() , "RECREATE");
tree->Write();
data_output->Close();
cout<<tree_out<<" created sucessfully!"<<endl;

}
