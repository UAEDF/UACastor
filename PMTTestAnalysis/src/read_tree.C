#include <stdio.h>
#include <iostream>

//root libs
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void read_tree(string tree_in)
{
//opening the file
TFile f(tree_in.c_str());

//declaring the tree
TTree *tree = (TTree*)f.Get("Castor_PMT_Caracterization_2012");

//declaring variables
char pmt[10];
std::vector<int> *begin, *end, *led, *hv, *time;
std::vector<float> *cath, *cath_ori, *anode, *ref;

int total_spikes, entries, module, sector;

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

float ee_800V_led1;
float ee_800V_led2;
float ee_800V_led3;
float ee_800V_led4;
float ee_900V_led1;
float ee_1000V_led1;
float ee_1200V_led1;
float ee_1200V_led2;
float ee_1200V_led3;
float ee_1200V_led4;
float ee_1400V_led1;
float ee_1600V_led1;
float qe_800V_led1;
float qe_800V_led2;
float qe_800V_led3;
float qe_800V_led4;
float qe_900V_led1;
float qe_1000V_led1;
float qe_1200V_led1;
float qe_1200V_led2;
float qe_1200V_led3;
float qe_1200V_led4;
float qe_1400V_led1;
float qe_1600V_led1;

//setting the branches
tree->SetBranchAddress("PMT",&pmt);
tree->SetBranchAddress("Measurement_begin",&begin);
tree->SetBranchAddress("Measurement_end",&end);
tree->SetBranchAddress("Entries",&entries);
tree->SetBranchAddress("Measured_time",&time);
tree->SetBranchAddress("HV",&hv);
tree->SetBranchAddress("Cathode",&cath_ori);
tree->SetBranchAddress("Cathode_after_background_subtraction",&cath);
tree->SetBranchAddress("Anode",&anode);
tree->SetBranchAddress("Reference_PMT",&ref);
tree->SetBranchAddress("Led",&led);
tree->SetBranchAddress("Module",&module);
tree->SetBranchAddress("Sector",&sector);
tree->SetBranchAddress("Number_of_spikes",&total_spikes);
tree->SetBranchAddress("Cath_800V_led1",&cath_800V_led1);
tree->SetBranchAddress("Cath_800V_led1_error",&cath_800V_led1_error);
tree->SetBranchAddress("Cath_800V_led1_spikes",&cath_800V_led1_spikes);
tree->SetBranchAddress("Cath_800V_led1_n",&cath_800V_led1_n);
tree->SetBranchAddress("Cath_800V_led2",&cath_800V_led2);
tree->SetBranchAddress("Cath_800V_led2_error",&cath_800V_led2_error);
tree->SetBranchAddress("Cath_800V_led2_spikes",&cath_800V_led2_spikes);
tree->SetBranchAddress("Cath_800V_led2_n",&cath_800V_led2_n);
tree->SetBranchAddress("Cath_800V_led3",&cath_800V_led3);
tree->SetBranchAddress("Cath_800V_led3_error",&cath_800V_led3_error);
tree->SetBranchAddress("Cath_800V_led3_spikes",&cath_800V_led3_spikes);
tree->SetBranchAddress("Cath_800V_led3_n",&cath_800V_led3_n);
tree->SetBranchAddress("Cath_800V_led4",&cath_800V_led4);
tree->SetBranchAddress("Cath_800V_led4_error",&cath_800V_led4_error);
tree->SetBranchAddress("Cath_800V_led4_spikes",&cath_800V_led4_spikes);
tree->SetBranchAddress("Cath_800V_led4_n",&cath_800V_led4_n);
tree->SetBranchAddress("Cath_900V_led1",&cath_900V_led1);
tree->SetBranchAddress("Cath_900V_led1_error",&cath_900V_led1_error);
tree->SetBranchAddress("Cath_900V_led1_spikes",&cath_900V_led1_spikes);
tree->SetBranchAddress("Cath_900V_led1_n",&cath_900V_led1_n);
tree->SetBranchAddress("Cath_1000V_led1",&cath_1000V_led1);
tree->SetBranchAddress("Cath_1000V_led1_error",&cath_1000V_led1_error);
tree->SetBranchAddress("Cath_1000V_led1_spikes",&cath_1000V_led1_spikes);
tree->SetBranchAddress("Cath_1000V_led1_n",&cath_1000V_led1_n);
tree->SetBranchAddress("Cath_1200V_led1",&cath_1200V_led1);
tree->SetBranchAddress("Cath_1200V_led1_error",&cath_1200V_led1_error);
tree->SetBranchAddress("Cath_1200V_led1_spikes",&cath_1200V_led1_spikes);
tree->SetBranchAddress("Cath_1200V_led1_n",&cath_1200V_led1_n);
tree->SetBranchAddress("Cath_1200V_led2",&cath_1200V_led2);
tree->SetBranchAddress("Cath_1200V_led2_error",&cath_1200V_led2_error);
tree->SetBranchAddress("Cath_1200V_led2_spikes",&cath_1200V_led2_spikes);
tree->SetBranchAddress("Cath_1200V_led2_n",&cath_1200V_led2_n);
tree->SetBranchAddress("Cath_1200V_led3",&cath_1200V_led3);
tree->SetBranchAddress("Cath_1200V_led3_error",&cath_1200V_led3_error);
tree->SetBranchAddress("Cath_1200V_led3_spikes",&cath_1200V_led3_spikes);
tree->SetBranchAddress("Cath_1200V_led3_n",&cath_1200V_led3_n);
tree->SetBranchAddress("Cath_1200V_led4",&cath_1200V_led4);
tree->SetBranchAddress("Cath_1200V_led4_error",&cath_1200V_led4_error);
tree->SetBranchAddress("Cath_1200V_led4_spikes",&cath_1200V_led4_spikes);
tree->SetBranchAddress("Cath_1200V_led4_n",&cath_1200V_led4_n);
tree->SetBranchAddress("Cath_1400V_led1",&cath_1400V_led1);
tree->SetBranchAddress("Cath_1400V_led1_error",&cath_1400V_led1_error);
tree->SetBranchAddress("Cath_1400V_led1_spikes",&cath_1400V_led1_spikes);
tree->SetBranchAddress("Cath_1400V_led1_n",&cath_1400V_led1_n);
tree->SetBranchAddress("Cath_1600V_led1",&cath_1600V_led1);
tree->SetBranchAddress("Cath_1600V_led1_error",&cath_1600V_led1_error);
tree->SetBranchAddress("Cath_1600V_led1_spikes",&cath_1600V_led1_spikes);
tree->SetBranchAddress("Cath_1600V_led1_n",&cath_1600V_led1_n);
tree->SetBranchAddress("Anode_800V_led1_up",&anode_800V_led1_up); 
tree->SetBranchAddress("Anode_800V_led1_down",&anode_800V_led1_down); 
tree->SetBranchAddress("Anode_800V_led2_up",&anode_800V_led2_up); 
tree->SetBranchAddress("Anode_800V_led2_down",&anode_800V_led2_down); 
tree->SetBranchAddress("Anode_800V_led3_up",&anode_800V_led3_up); 
tree->SetBranchAddress("Anode_800V_led3_down",&anode_800V_led3_down);
tree->SetBranchAddress("Anode_800V_led4_up",&anode_800V_led4_up); 
tree->SetBranchAddress("Anode_800V_led4_down",&anode_800V_led4_down); 
tree->SetBranchAddress("Anode_900V_led1_up",&anode_900V_led1_up); 
tree->SetBranchAddress("Anode_900V_led1_down",&anode_900V_led1_down); 
tree->SetBranchAddress("Anode_1000V_led1_up",&anode_1000V_led1_up); 
tree->SetBranchAddress("Anode_1000V_led1_down",&anode_1000V_led1_down); 
tree->SetBranchAddress("Anode_1200V_led1_up",&anode_1200V_led1_up); 
tree->SetBranchAddress("Anode_1200V_led1_down",&anode_1200V_led1_down); 
tree->SetBranchAddress("Anode_1200V_led2_up",&anode_1200V_led2_up); 
tree->SetBranchAddress("Anode_1200V_led2_down",&anode_1200V_led2_down); 
tree->SetBranchAddress("Anode_1200V_led3_up",&anode_1200V_led3_up); 
tree->SetBranchAddress("Anode_1200V_led3_down",&anode_1200V_led3_down);
tree->SetBranchAddress("Anode_1200V_led4_up",&anode_1200V_led4_up); 
tree->SetBranchAddress("Anode_1200V_led4_down",&anode_1200V_led4_down); 
tree->SetBranchAddress("Anode_1400V_led1_up",&anode_1400V_led1_up);
tree->SetBranchAddress("Anode_1400V_led1_down",&anode_1400V_led1_down);
tree->SetBranchAddress("Anode_1600V_led1_up",&anode_1600V_led1_up); 
tree->SetBranchAddress("Anode_1600V_led1_down",&anode_1600V_led1_down); 
tree->SetBranchAddress("Reference_800V_led1_up",&ref_800V_led1_up); 
tree->SetBranchAddress("Reference_800V_led1_down",&ref_800V_led1_down); 
tree->SetBranchAddress("Reference_800V_led2_up",&ref_800V_led2_up); 
tree->SetBranchAddress("Reference_800V_led2_down",&ref_800V_led2_down); 
tree->SetBranchAddress("Reference_800V_led3_up",&ref_800V_led3_up); 
tree->SetBranchAddress("Reference_800V_led3_down",&ref_800V_led3_down);
tree->SetBranchAddress("Reference_800V_led4_up",&ref_800V_led4_up); 
tree->SetBranchAddress("Reference_800V_led4_down",&ref_800V_led4_down);
tree->SetBranchAddress("Reference_900V_led1_up",&ref_900V_led1_up); 
tree->SetBranchAddress("Reference_900V_led1_down",&ref_900V_led1_down); 
tree->SetBranchAddress("Reference_1000V_led1_up",&ref_1000V_led1_up); 
tree->SetBranchAddress("Reference_1000V_led1_down",&ref_1000V_led1_down); 
tree->SetBranchAddress("Reference_1200V_led1_up",&ref_1200V_led1_up); 
tree->SetBranchAddress("Reference_1200V_led1_down",&ref_1200V_led1_down); 
tree->SetBranchAddress("Reference_1200V_led2_up",&ref_1200V_led2_up); 
tree->SetBranchAddress("Reference_1200V_led2_down",&ref_1200V_led2_down); 
tree->SetBranchAddress("Reference_1200V_led3_up",&ref_1200V_led3_up); 
tree->SetBranchAddress("Reference_1200V_led3_down",&ref_1200V_led3_down);
tree->SetBranchAddress("Reference_1200V_led4_up",&ref_1200V_led4_up); 
tree->SetBranchAddress("Reference_1200V_led4_down",&ref_1200V_led4_down); 
tree->SetBranchAddress("Reference_1400V_led1_up",&ref_1400V_led1_up);
tree->SetBranchAddress("Reference_1400V_led1_down",&ref_1400V_led1_down);
tree->SetBranchAddress("Reference_1600V_led1_up",&ref_1600V_led1_up);
tree->SetBranchAddress("Reference_1600V_led1_down",&ref_1600V_led1_down);
tree->SetBranchAddress("EE_800V_led1",&ee_800V_led1);
tree->SetBranchAddress("QE_800V_led1",&qe_800V_led1);
tree->SetBranchAddress("EE_800V_led2",&ee_800V_led2);
tree->SetBranchAddress("QE_800V_led2",&qe_800V_led2);
tree->SetBranchAddress("EE_800V_led3",&ee_800V_led3);
tree->SetBranchAddress("QE_800V_led3",&qe_800V_led3);
tree->SetBranchAddress("EE_800V_led4",&ee_800V_led4);
tree->SetBranchAddress("QE_800V_led4",&qe_800V_led4);
tree->SetBranchAddress("EE_900V_led1",&ee_900V_led1);
tree->SetBranchAddress("QE_900V_led1",&qe_900V_led1);
tree->SetBranchAddress("EE_1000V_led1",&ee_1000V_led1);
tree->SetBranchAddress("QE_1000V_led1",&qe_1000V_led1);
tree->SetBranchAddress("EE_1200V_led1",&ee_1200V_led1);
tree->SetBranchAddress("QE_1200V_led1",&qe_1200V_led1);
tree->SetBranchAddress("EE_1200V_led2",&ee_1200V_led2);
tree->SetBranchAddress("QE_1200V_led2",&qe_1200V_led2);
tree->SetBranchAddress("EE_1200V_led3",&ee_1200V_led3);
tree->SetBranchAddress("QE_1200V_led3",&qe_1200V_led3);
tree->SetBranchAddress("EE_1200V_led4",&ee_1200V_led4);
tree->SetBranchAddress("QE_1200V_led4",&qe_1200V_led4);
tree->SetBranchAddress("EE_1400V_led1",&ee_1400V_led1);
tree->SetBranchAddress("QE_1400V_led1",&qe_1400V_led1);
tree->SetBranchAddress("EE_1600V_led1",&ee_1600V_led1);
tree->SetBranchAddress("QE_1600V_led1",&qe_1600V_led1);


//loop over the measurements
int tests = tree->GetEntries();

  TH2F *pmt_inv_qe_800;
  TH2F *pmt_inv_ee_800;
  TH2F *pmt_inv_gain_800;
  TH2F *pmt_inv_qe_1200;
  TH2F *pmt_inv_ee_1200;
  TH2F *pmt_inv_gain_1200;
  TH2F *pmt_inv_gain_1400;
  TH2F *pmt_spikes;
  TH2F *measurements;

  pmt_inv_qe_800 =  new TH2F("Inverse_qe_800V","inverse_qe_800V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_ee_800 =  new TH2F("Inverse_ee_800V","inverse_ee_800V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_800 =  new TH2F("Inverse_gain_800V","inverse_gain_800V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_qe_1200 =  new TH2F("Inverse_qe_1200V","inverse_qe_1200V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_ee_1200 =  new TH2F("Inverse_ee_1200V","inverse_ee_1200V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_1200 =  new TH2F("Inverse_gain_1200V","inverse_gain_1200V;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_1400 =  new TH2F("Inverse_gain_1400V","inverse_gain_1400V;Sector;Module", 14,0,14,16,0,16);
  pmt_spikes =  new TH2F("Number_of_spikes","number_of_spikes;Sector;Module", 14,0,14,16,0,16);
  measurements =  new TH2F("Number_of_measurements","number_of_measurements;Sector;Module", 14,0,14,16,0,16);

for (int i = 0; i < tests ;i++)
{
tree->GetEvent(i);
cout<<"Measurement "<<i+1<<"; PMT code: "<<pmt<<" (Sector : "<<sector<<" ; Module : "<<module<<")"<<endl;
cout<<"Begin of the measurement: "<<begin->at(0)<<"/"<<begin->at(1)<<"/"<<begin->at(2)<<" - "<<begin->at(3)<<":"<<begin->at(4)<<":"<<begin->at(5)<<endl;
cout<<"End of the measurement: "<<end->at(0)<<"/"<<end->at(1)<<"/"<<end->at(2)<<" - "<<end->at(3)<<":"<<end->at(4)<<":"<<end->at(5)<<endl;
cout<<"Number of identified and rejected spikes : "<<total_spikes<<endl;
cout<<"Cathode   |                 |led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (cath_800V_led2 > 0.0)
{
cout<<"800V      |Gain             |"<<cath_800V_led1<<"   "<<cath_800V_led2<<"   "<<cath_800V_led3<<"   "<<cath_800V_led4<<endl;
cout<<"          |Error            |"<<cath_800V_led1_error<<"   "<<cath_800V_led2_error<<"   "<<cath_800V_led3_error<<"   "<<cath_800V_led4_error<<endl;
cout<<"          |Number of Spikes |"<<cath_800V_led1_spikes<<"   "<<cath_800V_led2_spikes<<"   "<<cath_800V_led3_spikes<<"   "<<cath_800V_led4_spikes<<endl;
cout<<"          |Points used      |"<<cath_800V_led1_n<<"   "<<cath_800V_led2_n<<"   "<<cath_800V_led3_n<<"   "<<cath_800V_led4_n<<endl;
}
if (cath_800V_led2 == 0.0 and cath_800V_led3 == 0.0 and cath_800V_led4 == 0.0)
{
cout<<"800V      |Gain             |"<<cath_800V_led1<<endl;
cout<<"          |Error            |"<<cath_800V_led1_error<<endl;
cout<<"          |Number of Spikes |"<<cath_800V_led1_spikes<<endl;
cout<<"          |Points used      |"<<cath_800V_led1_n<<endl;
}
if (cath_900V_led1 > 0.0)
{
cout<<"900V      |Gain             |"<<cath_900V_led1<<endl;
cout<<"          |Error            |"<<cath_900V_led1_error<<endl;
cout<<"          |Number of Spikes |"<<cath_900V_led1_spikes<<endl;
cout<<"          |Points used      |"<<cath_900V_led1_n<<endl;
}
cout<<"1000V     |Gain             |"<<cath_1000V_led1<<endl;
cout<<"          |Error            |"<<cath_1000V_led1_error<<endl;
cout<<"          |Number of Spikes |"<<cath_1000V_led1_spikes<<endl;
cout<<"          |Points used      |"<<cath_1000V_led1_n<<endl;
cout<<"1200V     |Gain             |"<<cath_1200V_led1<<"   "<<cath_1200V_led2<<"   "<<cath_1200V_led3<<"   "<<cath_1200V_led4<<endl;
cout<<"          |Error            |"<<cath_1200V_led1_error<<"   "<<cath_1200V_led2_error<<"   "<<cath_1200V_led3_error<<"   "<<cath_1200V_led4_error<<endl;
cout<<"          |Number of Spikes |"<<cath_1200V_led1_spikes<<"   "<<cath_1200V_led2_spikes<<"   "<<cath_1200V_led3_spikes<<"   "<<cath_1200V_led4_spikes<<endl;
cout<<"          |Points used      |"<<cath_1200V_led1_n<<"   "<<cath_1200V_led2_n<<"   "<<cath_1200V_led3_n<<"   "<<cath_1200V_led4_n<<endl;
cout<<"1400V     |Gain             |"<<cath_1400V_led1<<endl;
cout<<"          |Error            |"<<cath_1400V_led1_error<<endl;
cout<<"          |Number of Spikes |"<<cath_1400V_led1_spikes<<endl;
cout<<"          |Points used      |"<<cath_1400V_led1_n<<endl;
if (cath_1600V_led1 > 0.0)
{
cout<<"1600V     |Gain             |"<<cath_1600V_led1<<endl;
cout<<"          |Error            |"<<cath_1600V_led1_error<<endl;
cout<<"          |Number of Spikes |"<<cath_1600V_led1_spikes<<endl;
cout<<"          |Points used      |"<<cath_1600V_led1_n<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Anode     | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (anode_800V_led2_up > 0.0)
{
cout<<"800V      |"<<anode_800V_led1_up<<"   "<<anode_800V_led2_up<<"   "<<anode_800V_led3_up<<"   "<<anode_800V_led4_up<<endl;
cout<<"          |"<<anode_800V_led1_down<<"   "<<anode_800V_led2_down<<"   "<<anode_800V_led3_down<<"   "<<anode_800V_led4_down<<endl;
}
if (anode_800V_led2_up == 0.0 and anode_800V_led3_up == 0.0 and anode_800V_led4_up == 0.0)
{
cout<<"800V      |"<<anode_800V_led1_up<<endl;
cout<<"          |"<<anode_800V_led1_down<<endl;
}
if (anode_900V_led1_up > 0.0)
{
cout<<"900V      |"<<anode_900V_led1_up<<endl;
cout<<"          |"<<anode_900V_led1_down<<endl;
}
cout<<"1000V     |"<<anode_1000V_led1_up<<endl;
cout<<"          |"<<anode_1000V_led1_down<<endl;
cout<<"1200V     |"<<anode_1200V_led1_up<<"   "<<anode_1200V_led2_up<<"   "<<anode_1200V_led3_up<<"   "<<anode_1200V_led4_up<<endl;
cout<<"          |"<<anode_1200V_led1_down<<"   "<<anode_1200V_led2_down<<"   "<<anode_1200V_led3_down<<"   "<<anode_1200V_led4_down<<endl;
cout<<"1400V     |"<<anode_1400V_led1_up<<endl;
cout<<"          |"<<anode_1400V_led1_down<<endl;
if (anode_1600V_led1_up > 0.0)
{
cout<<"1600V     |"<<anode_1600V_led1_up<<endl;
cout<<"          |"<<anode_1600V_led1_down<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Reference | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (ref_800V_led2_up > 0.0)
{
cout<<"800V      |"<<ref_800V_led1_up<<"   "<<ref_800V_led2_up<<"   "<<ref_800V_led3_up<<"   "<<ref_800V_led4_up<<endl;
cout<<"          |"<<ref_800V_led1_down<<"   "<<ref_800V_led2_down<<"   "<<ref_800V_led3_down<<"   "<<ref_800V_led4_down<<endl;
}
if (ref_800V_led2_up == 0.0 and ref_800V_led3_up == 0.0 and ref_800V_led4_up == 0.0)
{
cout<<"800V      |"<<ref_800V_led1_up<<endl;
cout<<"          |"<<ref_800V_led1_down<<endl;
}
if (ref_900V_led1_up > 0.0)
{
cout<<"900V      |"<<ref_900V_led1_up<<endl;
cout<<"          |"<<ref_900V_led1_down<<endl;
}
cout<<"1000V     |"<<ref_1000V_led1_up<<endl;
cout<<"          |"<<ref_1000V_led1_down<<endl;
cout<<"1200V     |"<<ref_1200V_led1_up<<"   "<<ref_1200V_led2_up<<"   "<<ref_1200V_led3_up<<"   "<<ref_1200V_led4_up<<endl;
cout<<"          |"<<ref_1200V_led1_down<<"   "<<ref_1200V_led2_down<<"   "<<ref_1200V_led3_down<<"   "<<ref_1200V_led4_down<<endl;
cout<<"1400V     |"<<ref_1400V_led1_up<<endl;
cout<<"          |"<<ref_1400V_led1_down<<endl;
if (ref_1600V_led1_up > 0.0)
{
cout<<"1600V     |"<<ref_1600V_led1_up<<endl;
cout<<"          |"<<ref_1600V_led1_down<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Eletrical Efficiency| led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (ee_800V_led2 > 0.0)
{
cout<<"800V                |"<<ee_800V_led1<<"   "<<ee_800V_led2<<"   "<<ee_800V_led3<<"   "<<ee_800V_led4<<endl;
}
if (ee_800V_led2 == 0.0 and ee_800V_led3 == 0.0 and ee_800V_led4 == 0.0)
{
cout<<"800V                |"<<ee_800V_led1<<endl;
}
if (ee_900V_led1 > 0.0)
{
cout<<"900V                |"<<ee_900V_led1<<endl;
}
cout<<"1000V               |"<<ee_1000V_led1<<endl;
cout<<"1200V               |"<<ee_1200V_led1<<"   "<<ee_1200V_led2<<"   "<<ee_1200V_led3<<"   "<<ee_1200V_led4<<endl;
cout<<"1400V               |"<<ee_1400V_led1<<endl;
if (ee_1600V_led1 > 0.0)
{
cout<<"1600V               |"<<ee_1600V_led1<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Quantum Efficiency  | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (qe_800V_led2 > 0.0)
{
cout<<"800V                |"<<qe_800V_led1<<"   "<<qe_800V_led2<<"   "<<qe_800V_led3<<"   "<<qe_800V_led4<<endl;
}
if (qe_800V_led2 == 0.0 and qe_800V_led3 == 0.0 and qe_800V_led4 == 0.0)
{
cout<<"800V                |"<<qe_800V_led1<<endl;
}
if (ee_900V_led1 > 0.0)
{
cout<<"900V                |"<<qe_900V_led1<<endl;
}
cout<<"1000V               |"<<qe_1000V_led1<<endl;
cout<<"1200V               |"<<qe_1200V_led1<<"   "<<qe_1200V_led2<<"   "<<qe_1200V_led3<<"   "<<qe_1200V_led4<<endl;
cout<<"1400V               |"<<qe_1400V_led1<<endl;
if (ee_1600V_led1 > 0.0)
{
cout<<"1600V               |"<<qe_1600V_led1<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<" "<<endl;


pmt_inv_qe_1200->SetBinContent(module,sector,50000.0/qe_1200V_led1);
pmt_inv_ee_1200->SetBinContent(module,sector,22000.0/ee_1200V_led1);
pmt_inv_gain_1200->SetBinContent(module,sector,5.0e-07/anode_1200V_led1_up);
pmt_inv_gain_1400->SetBinContent(module,sector,1.3e-06/anode_1400V_led1_up);
pmt_inv_qe_800->SetBinContent(module,sector,50000.0/qe_800V_led1);
pmt_inv_ee_800->SetBinContent(module,sector,2000.0/ee_800V_led1);
pmt_inv_gain_800->SetBinContent(module,sector,4.0e-08/anode_800V_led1_up);
pmt_spikes->SetBinContent(module,sector,total_spikes);
measurements->Fill(module-0.5,sector-0.5);
}


TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_qe_800->Draw("colz");
pmt_inv_qe_800->Draw("text same");
c01->Print("Inverse_Quantum_Efficiency_800V.png");
c01->Close();

TCanvas *c02 = new TCanvas("c02","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_qe_1200->Draw("colz");
pmt_inv_qe_1200->Draw("text same");
c02->Print("Inverse_Quantum_Efficiency_1200V.png");
c02->Close();

TCanvas *c03 = new TCanvas("c03","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_gain_800->Draw("colz");
pmt_inv_gain_800->Draw("text same");
c03->Print("Inverse_Gain_800V.png");
c03->Close();

TCanvas *c04 = new TCanvas("c04","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_gain_1200->Draw("colz");
pmt_inv_gain_1200->Draw("text same");
c04->Print("Inverse_Gain_1200V.png");
c04->Close();

TCanvas *c05 = new TCanvas("c05","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_spikes->Draw("colz");
pmt_spikes->Draw("text same");
c05->Print("Number_of_Spikes.png");
c05->Close();

TCanvas *c06 = new TCanvas("c06","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

measurements->Draw("colz");
measurements->Draw("text same");
c06->Print("Number_of_Measurements.png");
c06->Close();

TCanvas *c07 = new TCanvas("c07","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_ee_800->Draw("colz");
pmt_inv_ee_800->Draw("text same");
c07->Print("Inverse_Eletrical_Efficiency_800V.png");
c07->Close();

TCanvas *c08 = new TCanvas("c08","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_ee_1200->Draw("colz");
pmt_inv_ee_1200->Draw("text same");
c08->Print("Inverse_Eletrical_Efficiency_1200V.png");
c08->Close();


TCanvas *c09 = new TCanvas("c09","Canvas",0,29,1200,800);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(kFALSE);
gStyle->SetPalette(1);
gStyle->SetPaintTextFormat("3.2g");
gPad->SetFillColor(0);
gPad->SetBorderMode(0);
gPad->SetBorderSize(2);
gPad->SetLeftMargin(0.10);
gPad->SetRightMargin(0.20);
gPad->SetTopMargin(0.01);
gPad->SetFrameBorderMode(0);

pmt_inv_gain_1400->Draw("colz");
pmt_inv_gain_1400->Draw("text same");
c09->Print("Inverse_Gain_1400V.png");
c09->Close();

}
