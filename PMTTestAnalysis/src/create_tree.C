#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"

//user
#include "LeakageSubtractor.h"

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

//calculate the gain
if (vec_led->at(cent_val-1) == 0)
{
cath = vec_cath->at(cent_val-6) - vec_cath->at(cent_val+5);
anode = vec_adut->at(cent_val-6) - vec_adut->at(cent_val+5);
ref = vec_aref->at(cent_val-6) - vec_aref->at(cent_val+5);
}
if (vec_led->at(cent_val-1) > 0)
{
cath = vec_cath->at(cent_val+5) - vec_cath->at(cent_val-6);
anode = vec_adut->at(cent_val+5) - vec_adut->at(cent_val-6);
ref = vec_aref->at(cent_val+5) - vec_aref->at(cent_val-6);
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
int entries, time, hv, led;

char read_time[20];
char ini_time[20], end_time[20];
string pmt;

std::vector<int> vec_time, vec_hv, vec_led;
std::vector<float> vec_cath, vec_adut, vec_aref;
std::vector<int> *pvec_time, *pvec_hv, *pvec_led;
std::vector<float> *pvec_cath, *pvec_adut, *pvec_aref;

int found1, found2, found3;

int index_800V_led1_up, index_800V_led1_down;
int index_800V_led2_up, index_800V_led2_down;
int index_800V_led3_up, index_800V_led3_down;
int index_800V_led4_up, index_800V_led4_down;
int index_1000V_led1_up, index_1000V_led1_down;
int index_1200V_led1_up, index_1200V_led1_down;
int index_1200V_led2_up, index_1200V_led2_down;
int index_1200V_led3_up, index_1200V_led3_down;
int index_1200V_led4_up, index_1200V_led4_down;
int index_1400V_led1_up, index_1400V_led1_down;

float cath_800V_led1_up, cath_800V_led1_down;
float cath_800V_led2_up, cath_800V_led2_down;
float cath_800V_led3_up, cath_800V_led3_down;
float cath_800V_led4_up, cath_800V_led4_down;
float cath_1000V_led1_up, cath_1000V_led1_down;
float cath_1200V_led1_up, cath_1200V_led1_down;
float cath_1200V_led2_up, cath_1200V_led2_down;
float cath_1200V_led3_up, cath_1200V_led3_down;
float cath_1200V_led4_up, cath_1200V_led4_down;
float cath_1400V_led1_up, cath_1400V_led1_down;

float anode_800V_led1_up, anode_800V_led1_down;
float anode_800V_led2_up, anode_800V_led2_down;
float anode_800V_led3_up, anode_800V_led3_down;
float anode_800V_led4_up, anode_800V_led4_down;
float anode_1000V_led1_up, anode_1000V_led1_down;
float anode_1200V_led1_up, anode_1200V_led1_down;
float anode_1200V_led2_up, anode_1200V_led2_down;
float anode_1200V_led3_up, anode_1200V_led3_down;
float anode_1200V_led4_up, anode_1200V_led4_down;
float anode_1400V_led1_up, anode_1400V_led1_down;

float ref_800V_led1_up, ref_800V_led1_down;
float ref_800V_led2_up, ref_800V_led2_down;
float ref_800V_led3_up, ref_800V_led3_down;
float ref_800V_led4_up, ref_800V_led4_down;
float ref_1000V_led1_up, ref_1000V_led1_down;
float ref_1200V_led1_up, ref_1200V_led1_down;
float ref_1200V_led2_up, ref_1200V_led2_down;
float ref_1200V_led3_up, ref_1200V_led3_down;
float ref_1200V_led4_up, ref_1200V_led4_down;
float ref_1400V_led1_up, ref_1400V_led1_down;

//tree declaration
TTree *tree = new TTree("Castor_PMT_Caracterization_2012","Castor PMT Caracterization 2012");
tree->Branch("PMT",&pmt,"Reference code of the PMT");
tree->Branch("Measurement_begin",&ini_time,"Begin of the measurement");
tree->Branch("Measurement_end",&end_time,"End of the measurement");
tree->Branch("Entries",&entries,"Number of entries");
tree->Branch("Measured_time","std::vector<int>",&pvec_time);
tree->Branch("HV","std::vector<int>",&pvec_hv);
tree->Branch("Cathode","std::vector<float>",&pvec_cath);
tree->Branch("Anode","std::vector<float>",&pvec_adut);
tree->Branch("Reference PMT","std::vector<float>",&pvec_aref);
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
strcpy (ini_time, "");
strcpy (end_time, "");
pvec_time = &vec_time;
pvec_hv = &vec_hv;
pvec_cath = &vec_cath;
pvec_adut = &vec_adut;
pvec_aref = &vec_aref;
pvec_led = &vec_led;
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

cath_800V_led1_up = 0;
cath_800V_led1_down = 0;
cath_800V_led2_up = 0;
cath_800V_led2_down = 0;
cath_800V_led3_up = 0;
cath_800V_led3_down = 0;
cath_800V_led4_up = 0;
cath_800V_led4_down = 0;
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

anode_800V_led1_up = 0;
anode_800V_led1_down = 0;
anode_800V_led2_up = 0;
anode_800V_led2_down = 0;
anode_800V_led3_up = 0;
anode_800V_led3_down = 0;
anode_800V_led4_up = 0;
anode_800V_led4_down = 0;
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

ref_800V_led1_up = 0;
ref_800V_led1_down = 0;
ref_800V_led2_up = 0;
ref_800V_led2_down = 0;
ref_800V_led3_up = 0;
ref_800V_led3_down = 0;
ref_800V_led4_up = 0;
ref_800V_led4_down = 0;
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
if (time == 0) { strcpy (ini_time, read_time); } //set begin time of the measurement
vec_time.push_back(time);
vec_hv.push_back(hv);
vec_cath.push_back(cath);
vec_adut.push_back(adut);
vec_aref.push_back(aref);
vec_led.push_back(led);
entries = entries + 1; //update the number of stored entries
}

//set the end time of the measurement
strcpy (end_time, read_time);

//output the details of the measurement
cout<<"PMT code: "<<pmt<<endl;
cout<<"Begin: "<<ini_time<<endl;
cout<<"End "<<end_time<<endl;
cout<<"Entries "<<entries<<endl;
cout<<endl;

//finding the transition indexes
for (int j=0; j < entries; j++)
{
if (vec_hv[j] < -750 and vec_hv[j] > -850)
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

if (vec_hv[j] < -950 and vec_hv[j] > -1050)
{
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1000V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1000V_led1_down = j; }
}

if (vec_hv[j] < -1150 and vec_hv[j] > -1250)
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

if (vec_hv[j] < -1350 and vec_hv[j] > -1450)
{
if (vec_led[j] == 1 and vec_led[j-1] == 0 ) { index_1400V_led1_up = j; }
if (vec_led[j] == 0 and vec_led[j-1] == 1 ) { index_1400V_led1_down = j; }
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
calc_dif(index_800V_led2_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led2_up, anode_800V_led2_up, ref_800V_led2_up);
calc_dif(index_800V_led2_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led2_down, anode_800V_led2_down, ref_800V_led2_down);
calc_dif(index_800V_led3_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led3_up, anode_800V_led3_up, ref_800V_led3_up);
calc_dif(index_800V_led3_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led3_down, anode_800V_led3_down, ref_800V_led3_down);
calc_dif(index_800V_led4_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led4_up, anode_800V_led4_up, ref_800V_led4_up);
calc_dif(index_800V_led4_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_800V_led4_down, anode_800V_led4_down, ref_800V_led4_down);
calc_dif(index_1000V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1000V_led1_up, anode_1000V_led1_up, ref_1000V_led1_up);
calc_dif(index_1000V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1000V_led1_down, anode_1000V_led1_down, ref_1000V_led1_down);
calc_dif(index_1200V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led1_up, anode_1200V_led1_up, ref_1200V_led1_up);
calc_dif(index_1200V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led1_down, anode_1200V_led1_down, ref_1200V_led1_down);
calc_dif(index_1200V_led2_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led2_up, anode_1200V_led2_up, ref_1200V_led2_up);
calc_dif(index_1200V_led2_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led2_down, anode_1200V_led2_down, ref_1200V_led2_down);
calc_dif(index_1200V_led3_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led3_up, anode_1200V_led3_up, ref_1200V_led3_up);
calc_dif(index_1200V_led3_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led3_down, anode_1200V_led3_down, ref_1200V_led3_down);
calc_dif(index_1200V_led4_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led4_up, anode_1200V_led4_up, ref_1200V_led4_up);
calc_dif(index_1200V_led4_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1200V_led4_down, anode_1200V_led4_down, ref_1200V_led4_down);
calc_dif(index_1400V_led1_up, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1400V_led1_up, anode_1400V_led1_up, ref_1400V_led1_up);
calc_dif(index_1400V_led1_down, &vec_hv, &vec_cath, &vec_adut, &vec_aref, &vec_led, cath_1400V_led1_down, anode_1400V_led1_down, ref_1400V_led1_down);
//fill the tree
tree->Fill();

}

//write to file
TFile *data_output= TFile::Open( tree_out.c_str() , "RECREATE");
tree->Write();
data_output->Close();
cout<<tree_out<<" created sucessfully!"<<endl;

}
