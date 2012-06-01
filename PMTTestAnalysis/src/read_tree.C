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

void set_code(int module, int sector, int set, string& pmt)
{

if (sector == 4  and module == 1  and set == 1) { pmt = "CA1579"; }
if (sector == 1  and module == 2  and set == 1) { pmt = "CA3399"; }
if (sector == 13 and module == 1  and set == 1) { pmt = "CA0683"; }
if (sector == 13 and module == 2  and set == 1) { pmt = "CA0540"; }
if (sector == 14 and module == 1  and set == 1) { pmt = "CA3362"; }
if (sector == 3  and module == 2  and set == 1) { pmt = "CA0625"; }
if (sector == 15 and module == 2  and set == 1) { pmt = "CA0715"; }
if (sector == 5  and module == 2  and set == 1) { pmt = "CA1832"; }
if (sector == 14 and module == 2  and set == 1) { pmt = "CA0857"; }
if (sector == 15 and module == 1  and set == 1) { pmt = "CA0886"; }
if (sector == 5  and module == 1  and set == 1) { pmt = "CA1549"; }
if (sector == 6  and module == 1  and set == 1) { pmt = "CA1617"; }
if (sector == 6  and module == 2  and set == 1) { pmt = "CA0742"; }
if (sector == 11 and module == 2  and set == 1) { pmt = "CA3236"; }
if (sector == 10 and module == 1  and set == 1) { pmt = "CA0829"; }
if (sector == 12 and module == 1  and set == 1) { pmt = "CA0948"; }
if (sector == 10 and module == 2  and set == 1) { pmt = "CA1263"; }
if (sector == 9  and module == 2  and set == 1) { pmt = "CA1200"; }
if (sector == 9  and module == 1  and set == 1) { pmt = "CA1829"; }
if (sector == 11 and module == 1  and set == 1) { pmt = "CA1431"; }
if (sector == 12 and module == 2  and set == 1) { pmt = "CA1593"; }
if (sector == 2  and module == 2  and set == 1) { pmt = "CA0327"; }
if (sector == 16 and module == 2  and set == 1) { pmt = "CA1680"; }
if (sector == 16 and module == 1  and set == 1) { pmt = "CA0558"; }
if (sector == 1  and module == 1  and set == 1) { pmt = "CA0574"; }
if (sector == 2  and module == 1  and set == 1) { pmt = "CA1842"; }
if (sector == 4  and module == 2  and set == 1) { pmt = "CA0812"; }
if (sector == 3  and module == 1  and set == 1) { pmt = "CA1592"; }
if (sector == 8  and module == 10 and set == 1) { pmt = "CA0892"; }
if (sector == 7  and module == 10 and set == 1) { pmt = "CA1620"; }
if (sector == 7  and module == 1  and set == 1) { pmt = "CA1321"; }
if (sector == 8  and module == 1  and set == 1) { pmt = "CA1537"; }
if (sector == 7  and module == 2  and set == 1) { pmt = "CA3386"; }
if (sector == 8  and module == 2  and set == 1) { pmt = "CA1954"; }


if (sector == 4  and module == 1  and set == 2) { pmt = "BA0263"; }
if (sector == 4  and module == 2  and set == 2) { pmt = "BA0264"; }
if (sector == 4  and module == 3  and set == 2) { pmt = "BA0265"; }
if (sector == 4  and module == 4  and set == 2) { pmt = "BA0267"; }
if (sector == 4  and module == 5  and set == 2) { pmt = "BA0274"; }
if (sector == 3  and module == 1  and set == 2) { pmt = "BA0275"; }
if (sector == 3  and module == 2  and set == 2) { pmt = "BA0277"; }
if (sector == 3  and module == 3  and set == 2) { pmt = "BA0278"; }
if (sector == 3  and module == 4  and set == 2) { pmt = "BA0279"; }
if (sector == 3  and module == 5  and set == 2) { pmt = "BA0287"; }
if (sector == 2  and module == 1  and set == 2) { pmt = "BA0288"; }
if (sector == 2  and module == 2  and set == 2) { pmt = "BA0291"; }
if (sector == 2  and module == 3  and set == 2) { pmt = "BA0297"; }
if (sector == 2  and module == 4  and set == 2) { pmt = "BA0300"; }
if (sector == 2  and module == 5  and set == 2) { pmt = "BA0303"; }
if (sector == 1  and module == 1  and set == 2) { pmt = "BA0304"; }
if (sector == 1  and module == 2  and set == 2) { pmt = "BA0305"; }
if (sector == 1  and module == 3  and set == 2) { pmt = "BA0307"; }
if (sector == 1  and module == 4  and set == 2) { pmt = "BA0309"; }
if (sector == 1  and module == 5  and set == 2) { pmt = "BA0311"; }

if (pmt == "") { cout<<"Unknown PMT"<<endl; }

}


void read_tree(string tree_in)
{
//cout << "load tree"<<endl;
//opening the file
TFile f(tree_in.c_str());

//cout << "declare the tree" << endl;
//declaring the tree
TTree *tree = (TTree*)f.Get("Castor_PMT_Caracterization_2012");

//tree->Show(0);

//cout << "variables" << endl;
//declaring variables
string pmt;
std::vector<int> *begin, *end, *led, *hv, *time;
std::vector<float> *cath, *cath_ori, *anode, *ref;

int total_spikes, bad_fits, entries, module, sector, set;

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

//setting the branches
//tree->SetBranchAddress("PMT",&pmt); //we got the code from the coordinates
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
tree->SetBranchAddress("Set",&set);
tree->SetBranchAddress("Number_of_spikes",&total_spikes);
tree->SetBranchAddress("Number_of_bad_fits",&bad_fits);
tree->SetBranchAddress("m_800V_led1",&m_800V_led1);
tree->SetBranchAddress("m_800V_led2",&m_800V_led2);
tree->SetBranchAddress("m_800V_led3",&m_800V_led3);
tree->SetBranchAddress("m_800V_led4",&m_800V_led4);
tree->SetBranchAddress("m_900V_led1",&m_900V_led1);
tree->SetBranchAddress("m_1000V_led1",&m_1000V_led1);
tree->SetBranchAddress("m_1200V_led1",&m_1200V_led1);
tree->SetBranchAddress("m_1200V_led2",&m_1200V_led2);
tree->SetBranchAddress("m_1200V_led3",&m_1200V_led3);
tree->SetBranchAddress("m_1200V_led4",&m_1200V_led4);
tree->SetBranchAddress("m_1400V_led1",&m_1400V_led1);
tree->SetBranchAddress("m_1600V_led1",&m_1600V_led1);
tree->SetBranchAddress("m_1800V_led4",&m_1800V_led4);
tree->SetBranchAddress("Leakage_0V",&leakage_0V);
tree->SetBranchAddress("Leakage_0V_error",&leakage_0V_error);
tree->SetBranchAddress("Leakage_0V_n",&leakage_0V_n);
tree->SetBranchAddress("Leakage_0V_spikes",&leakage_0V_spikes);
tree->SetBranchAddress("Leakage_800V",&leakage_800V);
tree->SetBranchAddress("Leakage_800V_error",&leakage_800V_error);
tree->SetBranchAddress("Leakage_800V_n",&leakage_800V_n);
tree->SetBranchAddress("Leakage_800V_spikes",&leakage_800V_spikes);
tree->SetBranchAddress("Leakage_900V",&leakage_900V);
tree->SetBranchAddress("Leakage_900V_error",&leakage_900V_error);
tree->SetBranchAddress("Leakage_900V_n",&leakage_900V_n);
tree->SetBranchAddress("Leakage_900V_spikes",&leakage_900V_spikes);
tree->SetBranchAddress("Leakage_1000V",&leakage_1000V);
tree->SetBranchAddress("Leakage_1000V_error",&leakage_1000V_error);
tree->SetBranchAddress("Leakage_1000V_n",&leakage_1000V_n);
tree->SetBranchAddress("Leakage_1000V_spikes",&leakage_1000V_spikes);
tree->SetBranchAddress("Leakage_1200V",&leakage_1200V);
tree->SetBranchAddress("Leakage_1200V_error",&leakage_1200V_error);
tree->SetBranchAddress("Leakage_1200V_n",&leakage_1200V_n);
tree->SetBranchAddress("Leakage_1200V_spikes",&leakage_1200V_spikes);
tree->SetBranchAddress("Leakage_1400V",&leakage_1400V);
tree->SetBranchAddress("Leakage_1400V_error",&leakage_1400V_error);
tree->SetBranchAddress("Leakage_1400V_n",&leakage_1400V_n);
tree->SetBranchAddress("Leakage_1400V_spikes",&leakage_1400V_spikes);
tree->SetBranchAddress("Leakage_1600V",&leakage_1600V);
tree->SetBranchAddress("Leakage_1600V_error",&leakage_1600V_error);
tree->SetBranchAddress("Leakage_1600V_n",&leakage_1600V_n);
tree->SetBranchAddress("Leakage_1600V_spikes",&leakage_1600V_spikes);
tree->SetBranchAddress("Leakage_1800V",&leakage_1800V);
tree->SetBranchAddress("Leakage_1800V_error",&leakage_1800V_error);
tree->SetBranchAddress("Leakage_1800V_n",&leakage_1800V_n);
tree->SetBranchAddress("Leakage_1800V_spikes",&leakage_1800V_spikes);

//cout << "entering the loop" << endl;
//loop over the measurements
int tests = tree->GetEntries();

  TH2F *pmt_inv_qe_800_old;
  TH2F *pmt_inv_ee_800_old;
  TH2F *pmt_inv_gain_800_old;
  TH2F *pmt_inv_qe_1200_old;
  TH2F *pmt_inv_ee_1200_old;
  TH2F *pmt_inv_gain_1200_old;
  TH2F *pmt_inv_gain_1400_old;
  TH2F *pmt_spikes_old;
  TH2F *measurements_old;

  pmt_inv_qe_800_old =  new TH2F("Inverse_qe_800V_old","inverse_qe_800V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_ee_800_old =  new TH2F("Inverse_ee_800V_old","inverse_ee_800V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_800_old =  new TH2F("Inverse_gain_800V_old","inverse_gain_800V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_qe_1200_old =  new TH2F("Inverse_qe_1200V_old","inverse_qe_1200V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_ee_1200_old =  new TH2F("Inverse_ee_1200V_old","inverse_ee_1200V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_1200_old =  new TH2F("Inverse_gain_1200V_old","inverse_gain_1200V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_inv_gain_1400_old =  new TH2F("Inverse_gain_1400V_old","inverse_gain_1400V_old;Sector;Module", 14,0,14,16,0,16);
  pmt_spikes_old =  new TH2F("Number_of_spikes_old","number_of_spikes_old;Sector;Module", 14,0,14,16,0,16);
  measurements_old =  new TH2F("Number_of_measurements_old","number_of_measurements_old;Sector;Module", 14,0,14,16,0,16);

  TH2F *pmt_inv_qe_800_new1;
  TH2F *pmt_inv_ee_800_new1;
  TH2F *pmt_inv_gain_800_new1;
  TH2F *pmt_inv_qe_1200_new1;
  TH2F *pmt_inv_ee_1200_new1;
  TH2F *pmt_inv_gain_1200_new1;
  TH2F *pmt_inv_gain_1400_new1;
  TH2F *pmt_spikes_new1;
  TH2F *measurements_new1;

  pmt_inv_qe_800_new1 =  new TH2F("Inverse_qe_800V_new1","inverse_qe_800V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_ee_800_new1 =  new TH2F("Inverse_ee_800V_new1","inverse_ee_800V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_gain_800_new1 =  new TH2F("Inverse_gain_800V_new1","inverse_gain_800V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_qe_1200_new1 =  new TH2F("Inverse_qe_1200V_new1","inverse_qe_1200V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_ee_1200_new1 =  new TH2F("Inverse_ee_1200V_new1","inverse_ee_1200V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_gain_1200_new1 =  new TH2F("Inverse_gain_1200V_new1","inverse_gain_1200V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_inv_gain_1400_new1 =  new TH2F("Inverse_gain_1400V_new1","inverse_gain_1400V_new1;Sector;Module", 5,0,5,4,0,4);
  pmt_spikes_new1 =  new TH2F("Number_of_spikes_new1","number_of_spikes_new1;Sector;Module", 5,0,5,4,0,4);
  measurements_new1 =  new TH2F("Number_of_measurements_new1","number_of_measurements_new1;Sector;Module", 5,0,5,4,0,4);

for (int i = 0; i < tests ;i++)
{

//cout << "getting the event : "<< i << endl;
tree->GetEvent(i);
//cout << "empty string" << endl;
pmt = "";
//cout << "set code" << endl;
set_code(module, sector, set, pmt);
//cout << "output" << endl;

cout<<"Measurement "<<i+1<<"; PMT code: "<<pmt<<" (Sector : "<<sector<<" ; Module : "<<module<<" ; Set : "<<set<<")"<<endl;
cout<<"Begin of the measurement: "<<begin->at(0)<<"/"<<begin->at(1)<<"/"<<begin->at(2)<<" - "<<begin->at(3)<<":"<<begin->at(4)<<":"<<begin->at(5)<<endl;
cout<<"End of the measurement: "<<end->at(0)<<"/"<<end->at(1)<<"/"<<end->at(2)<<" - "<<end->at(3)<<":"<<end->at(4)<<":"<<end->at(5)<<endl;
cout<<"Number of identified and rejected spikes : "<<total_spikes<<endl;
cout<<"Number of bad fits: "<<bad_fits<<endl;
cout<<"Cathode   |                 |led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.cath_value > 0.0)
{
cout<<"800V      |Current          |"<<m_800V_led1.cath_value<<"   "<<m_800V_led2.cath_value<<"   "<<m_800V_led3.cath_value<<"   "<<m_800V_led4.cath_value<<endl;
cout<<"          |Error            |"<<m_800V_led1.cath_error<<"   "<<m_800V_led2.cath_error<<"   "<<m_800V_led3.cath_error<<"   "<<m_800V_led4.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_800V_led1.cath_spikes<<"   "<<m_800V_led2.cath_spikes<<"   "<<m_800V_led3.cath_spikes<<"   "<<m_800V_led4.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_800V_led1.cath_points<<"   "<<m_800V_led2.cath_points<<"   "<<m_800V_led3.cath_points<<"   "<<m_800V_led4.cath_points<<endl;
}
if (m_800V_led2.cath_value == 0.0 and m_800V_led3.cath_value == 0.0 and m_800V_led4.cath_value == 0.0)
{
cout<<"800V      |Current          |"<<m_800V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_800V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_800V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_800V_led1.cath_points<<endl;
}
if (m_900V_led1.cath_value > 0.0)
{
cout<<"900V      |Current          |"<<m_900V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_900V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_900V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_900V_led1.cath_points<<endl;
}
cout<<"1000V     |Current          |"<<m_1000V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1000V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1000V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_1000V_led1.cath_points<<endl;
if (m_1200V_led2.cath_value > 0.0)
{
cout<<"1200V     |Current          |"<<m_1200V_led1.cath_value<<"   "<<m_1200V_led2.cath_value<<"   "<<m_1200V_led3.cath_value<<"   "<<m_1200V_led4.cath_value<<endl;
cout<<"          |Error            |"<<m_1200V_led1.cath_error<<"   "<<m_1200V_led2.cath_error<<"   "<<m_1200V_led3.cath_error<<"   "<<m_1200V_led4.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1200V_led1.cath_spikes<<"   "<<m_1200V_led2.cath_spikes<<"   "<<m_1200V_led3.cath_spikes<<"   "<<m_1200V_led4.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_1200V_led1.cath_points<<"   "<<m_1200V_led2.cath_points<<"   "<<m_1200V_led3.cath_points<<"   "<<m_1200V_led4.cath_points<<endl;
}
if (m_1200V_led2.cath_value == 0.0 and m_1200V_led3.cath_value == 0.0 and m_1200V_led4.cath_value == 0.0)
{
cout<<"1200V     |Current          |"<<m_1200V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1200V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1200V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_1200V_led1.cath_points<<endl;
}
cout<<"1400V     |Current          |"<<m_1400V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1400V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1400V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_1400V_led1.cath_points<<endl;
if (m_1600V_led1.cath_value > 0.0)
{
cout<<"1600V     |Current          |"<<m_1600V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1600V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1600V_led1.cath_spikes<<endl;
cout<<"          |Points used      |"<<m_1600V_led1.cath_points<<endl;
}
if (m_1800V_led4.cath_value > 0.0)
{
cout<<"1800V     |Current          |                                    "<<m_1800V_led4.cath_value<<endl;
cout<<"          |Error            |                                    "<<m_1800V_led4.cath_error<<endl;
cout<<"          |Number of Spikes |                                    "<<m_1800V_led4.cath_spikes<<endl;
cout<<"          |Points used      |                                    "<<m_1800V_led4.cath_points<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Anode     | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.anode_up > 0.0)
{
cout<<"800V      |"<<m_800V_led1.anode_up<<"   "<<m_800V_led2.anode_up<<"   "<<m_800V_led3.anode_up<<"   "<<m_800V_led4.anode_up<<endl;
cout<<"          |"<<m_800V_led1.anode_down<<"   "<<m_800V_led2.anode_down<<"   "<<m_800V_led3.anode_down<<"   "<<m_800V_led4.anode_down<<endl;
}
if (m_800V_led2.anode_up == 0.0 and m_800V_led3.anode_up == 0.0 and m_800V_led4.anode_up == 0.0)
{
cout<<"800V      |"<<m_800V_led1.anode_up<<endl;
cout<<"          |"<<m_800V_led1.anode_down<<endl;
}
if (m_900V_led1.anode_up > 0.0)
{
cout<<"900V      |"<<m_900V_led1.anode_up<<endl;
cout<<"          |"<<m_900V_led1.anode_down<<endl;
}
cout<<"1000V     |"<<m_1000V_led1.anode_up<<endl;
cout<<"          |"<<m_1000V_led1.anode_down<<endl;
if (m_1200V_led2.anode_up > 0.0)
{
cout<<"1200V     |"<<m_1200V_led1.anode_up<<"   "<<m_1200V_led2.anode_up<<"   "<<m_1200V_led3.anode_up<<"   "<<m_1200V_led4.anode_up<<endl;
cout<<"          |"<<m_1200V_led1.anode_down<<"   "<<m_1200V_led2.anode_down<<"   "<<m_1200V_led3.anode_down<<"   "<<m_1200V_led4.anode_down<<endl;
}
if (m_1200V_led2.anode_up == 0.0 and m_1200V_led3.anode_up == 0.0 and m_1200V_led4.anode_up == 0.0)
{
cout<<"1200V     |"<<m_1200V_led1.anode_up<<endl;
cout<<"          |"<<m_1200V_led1.anode_down<<endl;
}
cout<<"1400V     |"<<m_1400V_led1.anode_up<<endl;
cout<<"          |"<<m_1400V_led1.anode_down<<endl;
if (m_1600V_led1.anode_up > 0.0)
{
cout<<"1600V     |"<<m_1600V_led1.anode_up<<endl;
cout<<"          |"<<m_1600V_led1.anode_down<<endl;
}
if (m_1800V_led4.anode_up > 0.0)
{
cout<<"1800V     |                                          "<<m_1800V_led4.anode_up<<endl;
cout<<"          |                                          "<<m_1800V_led4.anode_down<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Reference | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.ref_up > 0.0)
{
cout<<"800V      |"<<m_800V_led1.ref_up<<"   "<<m_800V_led2.ref_up<<"   "<<m_800V_led3.ref_up<<"   "<<m_800V_led4.ref_up<<endl;
cout<<"          |"<<m_800V_led1.ref_down<<"   "<<m_800V_led2.ref_down<<"   "<<m_800V_led3.ref_down<<"   "<<m_800V_led4.ref_down<<endl;
}
if (m_800V_led2.ref_up == 0.0 and m_800V_led3.ref_up == 0.0 and m_800V_led4.ref_up == 0.0)
{
cout<<"800V      |"<<m_800V_led1.ref_up<<endl;
cout<<"          |"<<m_800V_led1.ref_down<<endl;
}
if (m_900V_led1.ref_up > 0.0)
{
cout<<"900V      |"<<m_900V_led1.ref_up<<endl;
cout<<"          |"<<m_900V_led1.ref_down<<endl;
}
cout<<"1000V     |"<<m_1000V_led1.ref_up<<endl;
cout<<"          |"<<m_1000V_led1.ref_down<<endl;
if (m_1200V_led2.ref_up > 0.0)
{
cout<<"1200V     |"<<m_1200V_led1.ref_up<<"   "<<m_1200V_led2.ref_up<<"   "<<m_1200V_led3.ref_up<<"   "<<m_1200V_led4.ref_up<<endl;
cout<<"          |"<<m_1200V_led1.ref_down<<"   "<<m_1200V_led2.ref_down<<"   "<<m_1200V_led3.ref_down<<"   "<<m_1200V_led4.ref_down<<endl;
}
if (m_1200V_led2.ref_up == 0.0 and m_1200V_led3.ref_up == 0.0 and m_1200V_led4.ref_up == 0.0)
{
cout<<"1200V     |"<<m_1200V_led1.ref_up<<endl;
cout<<"          |"<<m_1200V_led1.ref_down<<endl;
}
cout<<"1400V     |"<<m_1400V_led1.ref_up<<endl;
cout<<"          |"<<m_1400V_led1.ref_down<<endl;
if (m_1600V_led1.ref_up > 0.0)
{
cout<<"1600V     |"<<m_1600V_led1.ref_up<<endl;
cout<<"          |"<<m_1600V_led1.ref_down<<endl;
}
if (m_1800V_led4.ref_up > 0.0)
{
cout<<"1800V     |                                      "<<m_1800V_led4.ref_up<<endl;
cout<<"          |                                      "<<m_1800V_led4.ref_down<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Gain                | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.gain > 0.0)
{
cout<<"800V                |"<<m_800V_led1.gain<<"   "<<m_800V_led2.gain<<"   "<<m_800V_led3.gain<<"   "<<m_800V_led4.gain<<endl;
}
if (m_800V_led2.gain == 0.0 and m_800V_led3.gain == 0.0 and m_800V_led4.gain == 0.0)
{
cout<<"800V                |"<<m_800V_led1.gain<<endl;
}
if (m_900V_led1.gain > 0.0)
{
cout<<"900V                |"<<m_900V_led1.gain<<endl;
}
cout<<"1000V               |"<<m_1000V_led1.gain<<endl;
if (m_1200V_led2.gain > 0.0)
{
cout<<"1200V               |"<<m_1200V_led1.gain<<"   "<<m_1200V_led2.gain<<"   "<<m_1200V_led3.gain<<"   "<<m_1200V_led4.gain<<endl;
}
if (m_1200V_led2.gain == 0.0 and m_1200V_led3.gain == 0.0 and m_1200V_led4.gain == 0.0)
{
cout<<"1200V               |"<<m_1200V_led1.gain<<endl;
}
cout<<"1400V               |"<<m_1400V_led1.gain<<endl;
if (m_1600V_led1.gain > 0.0)
{
cout<<"1600V               |"<<m_1600V_led1.gain<<endl;
}
if (m_1800V_led4.gain > 0.0)
{
cout<<"1800V               |                                    "<<m_1800V_led4.gain<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Quantum Efficiency  | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.qe > 0.0)
{
cout<<"800V                |"<<m_800V_led1.qe<<"   "<<m_800V_led2.qe<<"   "<<m_800V_led3.qe<<"   "<<m_800V_led4.qe<<endl;
}
if (m_800V_led2.qe == 0.0 and m_800V_led3.qe == 0.0 and m_800V_led4.qe == 0.0)
{
cout<<"800V                |"<<m_800V_led1.qe<<endl;
}
if (m_900V_led1.qe > 0.0)
{
cout<<"900V                |"<<m_900V_led1.qe<<endl;
}
cout<<"1000V               |"<<m_1000V_led1.qe<<endl;
if (m_1200V_led2.qe > 0.0)
{
cout<<"1200V               |"<<m_1200V_led1.qe<<"   "<<m_1200V_led2.qe<<"   "<<m_1200V_led3.qe<<"   "<<m_1200V_led4.qe<<endl;
}
if (m_1200V_led2.qe == 0.0 and m_1200V_led3.qe == 0.0 and m_1200V_led4.qe == 0.0)
{
cout<<"1200V               |"<<m_1200V_led1.qe<<endl;
}
cout<<"1400V               |"<<m_1400V_led1.qe<<endl;
if (m_1600V_led1.qe > 0.0)
{
cout<<"1600V               |"<<m_1600V_led1.qe<<endl;
}
if (m_1800V_led4.qe > 0.0)
{
cout<<"1800V               |                                    "<<m_1800V_led4.qe<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Leakage             |Value         Error    Spikes Points"<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"0V                  |"<<leakage_0V<<"  "<<leakage_0V_error<<"  "<<leakage_0V_spikes<<"    "<<leakage_0V_n<<endl;
if (leakage_800V > 0.0)
{
cout<<"800V                |"<<leakage_800V<<"  "<<leakage_800V_error<<"  "<<leakage_800V_spikes<<"    "<<leakage_800V_n<<endl;
}
if (leakage_900V > 0.0)
{
cout<<"900V                |"<<leakage_900V<<"  "<<leakage_900V_error<<"  "<<leakage_900V_spikes<<"    "<<leakage_900V_n<<endl;
}
cout<<"1000V               |"<<leakage_1000V<<"  "<<leakage_1000V_error<<"  "<<leakage_1000V_spikes<<"    "<<leakage_1000V_n<<endl;
cout<<"1200V               |"<<leakage_1200V<<"  "<<leakage_1200V_error<<"  "<<leakage_1200V_spikes<<"    "<<leakage_1200V_n<<endl;
cout<<"1400V               |"<<leakage_1400V<<"  "<<leakage_1400V_error<<"  "<<leakage_1400V_spikes<<"    "<<leakage_1400V_n<<endl;
if (leakage_1600V > 0.0)
{
cout<<"1800V               |"<<leakage_1600V<<"  "<<leakage_1600V_error<<"  "<<leakage_1600V_spikes<<"    "<<leakage_1600V_n<<endl;
}
if (leakage_1800V > 0.0)
{
cout<<"1800V               |"<<leakage_1800V<<"  "<<leakage_1800V_error<<"  "<<leakage_1800V_spikes<<"    "<<leakage_1800V_n<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<" "<<endl;

if (set == 1)
{
pmt_inv_gain_800_old->SetBinContent(module,sector,4.0e-08/m_800V_led1.anode_up);
pmt_inv_gain_1200_old->SetBinContent(module,sector,5.0e-07/m_1200V_led1.gain);
pmt_inv_gain_1400_old->SetBinContent(module,sector,1.3e-06/m_1400V_led1.gain);
pmt_inv_qe_800_old->SetBinContent(module,sector,50000.0/m_800V_led1.qe);
pmt_inv_qe_1200_old->SetBinContent(module,sector,50000.0/m_1200V_led1.qe);
pmt_spikes_old->SetBinContent(module,sector,total_spikes);
measurements_old->Fill(module-0.5,sector-0.5);
}

if (set == 2)
{
pmt_inv_gain_800_new1->SetBinContent(module,sector,4.0e-08/m_800V_led1.anode_up);
pmt_inv_gain_1200_new1->SetBinContent(module,sector,5.0e-07/m_1200V_led1.gain);
pmt_inv_gain_1400_new1->SetBinContent(module,sector,1.3e-06/m_1400V_led1.gain);
pmt_inv_qe_800_new1->SetBinContent(module,sector,50000.0/m_800V_led1.qe);
pmt_inv_qe_1200_new1->SetBinContent(module,sector,50000.0/m_1200V_led1.qe);
pmt_spikes_new1->SetBinContent(module,sector,total_spikes);
measurements_new1->Fill(module-0.5,sector-0.5);
}
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

pmt_inv_qe_800_old->Draw("colz");
pmt_inv_qe_800_old->Draw("text same");
c01->Print("Inverse_Quantum_Efficiency_800V_old.png");
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

pmt_inv_qe_1200_old->Draw("colz");
pmt_inv_qe_1200_old->Draw("text same");
c02->Print("Inverse_Quantum_Efficiency_1200V_old.png");
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

pmt_inv_gain_800_old->Draw("colz");
pmt_inv_gain_800_old->Draw("text same");
c03->Print("Inverse_Gain_800V_old.png");
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

pmt_inv_gain_1200_old->Draw("colz");
pmt_inv_gain_1200_old->Draw("text same");
c04->Print("Inverse_Gain_1200V_old.png");
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

pmt_spikes_old->Draw("colz");
pmt_spikes_old->Draw("text same");
c05->Print("Number_of_Spikes_old.png");
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

measurements_old->Draw("colz");
measurements_old->Draw("text same");
c06->Print("Number_of_Measurements_old.png");
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

pmt_inv_ee_800_old->Draw("colz");
pmt_inv_ee_800_old->Draw("text same");
c07->Print("Inverse_Eletrical_Efficiency_800V_old.png");
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

pmt_inv_ee_1200_old->Draw("colz");
pmt_inv_ee_1200_old->Draw("text same");
c08->Print("Inverse_Eletrical_Efficiency_1200V_old.png");
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

pmt_inv_gain_1400_old->Draw("colz");
pmt_inv_gain_1400_old->Draw("text same");
c09->Print("Inverse_Gain_1400V_old.png");
c09->Close();


TCanvas *c11 = new TCanvas("c11","Canvas",0,29,1200,800);
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

pmt_inv_qe_800_new1->Draw("colz");
pmt_inv_qe_800_new1->Draw("text same");
c11->Print("Inverse_Quantum_Efficiency_800V_new1.png");
c11->Close();

TCanvas *c12 = new TCanvas("c12","Canvas",0,29,1200,800);
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

pmt_inv_qe_1200_new1->Draw("colz");
pmt_inv_qe_1200_new1->Draw("text same");
c12->Print("Inverse_Quantum_Efficiency_1200V_new1.png");
c12->Close();

TCanvas *c13 = new TCanvas("c13","Canvas",0,29,1200,800);
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

pmt_inv_gain_800_new1->Draw("colz");
pmt_inv_gain_800_new1->Draw("text same");
c13->Print("Inverse_Gain_800V_new1.png");
c13->Close();

TCanvas *c14 = new TCanvas("c14","Canvas",0,29,1200,800);
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

pmt_inv_gain_1200_new1->Draw("colz");
pmt_inv_gain_1200_new1->Draw("text same");
c14->Print("Inverse_Gain_1200V_new1.png");
c14->Close();

TCanvas *c15 = new TCanvas("c15","Canvas",0,29,1200,800);
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

pmt_spikes_new1->Draw("colz");
pmt_spikes_new1->Draw("text same");
c15->Print("Number_of_Spikes_new1.png");
c15->Close();

TCanvas *c16 = new TCanvas("c16","Canvas",0,29,1200,800);
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

measurements_new1->Draw("colz");
measurements_new1->Draw("text same");
c16->Print("Number_of_Measurements_new1.png");
c16->Close();

TCanvas *c17 = new TCanvas("c17","Canvas",0,29,1200,800);
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

pmt_inv_ee_800_new1->Draw("colz");
pmt_inv_ee_800_new1->Draw("text same");
c17->Print("Inverse_Eletrical_Efficiency_800V_new1.png");
c17->Close();

TCanvas *c18 = new TCanvas("c18","Canvas",0,29,1200,800);
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

pmt_inv_ee_1200_new1->Draw("colz");
pmt_inv_ee_1200_new1->Draw("text same");
c18->Print("Inverse_Eletrical_Efficiency_1200V_new1.png");
c18->Close();


TCanvas *c19 = new TCanvas("c19","Canvas",0,29,1200,800);
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

pmt_inv_gain_1400_new1->Draw("colz");
pmt_inv_gain_1400_new1->Draw("text same");
c19->Print("Inverse_Gain_1400V_new1.png");
c19->Close();

}
