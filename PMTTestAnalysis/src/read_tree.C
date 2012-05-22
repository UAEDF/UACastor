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
std::vector<int> *begin, *end, *led;
std::vector<float> *hv, *time, *cath, *cath_ori, *anode, *ref;

int total_spike, entries, module, sector;

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
tree->SetBranchAddress("Number_of_spikes",&total_spike);
tree->SetBranchAddress("Cath_800V_led1_up",&cath_800V_led1_up); 
tree->SetBranchAddress("Cath_800V_led1_down",&cath_800V_led1_down); 
tree->SetBranchAddress("Cath_800V_led2_up",&cath_800V_led2_up); 
tree->SetBranchAddress("Cath_800V_led2_down",&cath_800V_led2_down); 
tree->SetBranchAddress("Cath_800V_led3_up",&cath_800V_led3_up); 
tree->SetBranchAddress("Cath_800V_led3_down",&cath_800V_led3_down);
tree->SetBranchAddress("Cath_800V_led4_up",&cath_800V_led4_up); 
tree->SetBranchAddress("Cath_800V_led4_down",&cath_800V_led4_down); 
tree->SetBranchAddress("Cath_900V_led1_up",&cath_900V_led1_up); 
tree->SetBranchAddress("Cath_900V_led1_down",&cath_900V_led1_down); 
tree->SetBranchAddress("Cath_1000V_led1_up",&cath_1000V_led1_up); 
tree->SetBranchAddress("Cath_1000V_led1_down",&cath_1000V_led1_down); 
tree->SetBranchAddress("Cath_1200V_led1_up",&cath_1200V_led1_up); 
tree->SetBranchAddress("Cath_1200V_led1_down",&cath_1200V_led1_down); 
tree->SetBranchAddress("Cath_1200V_led2_up",&cath_1200V_led2_up); 
tree->SetBranchAddress("Cath_1200V_led2_down",&cath_1200V_led2_down); 
tree->SetBranchAddress("Cath_1200V_led3_up",&cath_1200V_led3_up); 
tree->SetBranchAddress("Cath_1200V_led3_down",&cath_1200V_led3_down);
tree->SetBranchAddress("Cath_1200V_led4_up",&cath_1200V_led4_up); 
tree->SetBranchAddress("Cath_1200V_led4_down",&cath_1200V_led4_down); 
tree->SetBranchAddress("Cath_1400V_led1_up",&cath_1400V_led1_up);
tree->SetBranchAddress("Cath_1400V_led1_down",&cath_1400V_led1_down);
tree->SetBranchAddress("Cath_1600V_led1_up",&cath_1600V_led1_up); 
tree->SetBranchAddress("Cath_1600V_led1_down",&cath_1600V_led1_down); 
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

  TH2F *pmt_inv_qe;
  TH2F *pmt_inv_gain;
  TH2F *pmt_spikes;

  pmt_inv_qe =  new TH2F("Inverse_qe","inverse_qe;sector;module", 14,0,14,16,0,16);
  pmt_inv_gain =  new TH2F("Inverse_gain","inverse_gain;sector;module", 14,0,14,16,0,16);
  pmt_spikes =  new TH2F("Number_of_spikes","number_of_spikes;sector;module", 14,0,14,16,0,16);

for (int i = 0; i < tests ;i++)
{
tree->GetEvent(i);
cout<<"Measurement "<<i+1<<"; PMT code: "<<pmt<<endl;
cout<<"Begin of the measurement: "<<begin->at(0)<<"/"<<begin->at(1)<<"/"<<begin->at(2)<<" - "<<begin->at(3)<<":"<<begin->at(4)<<":"<<begin->at(5)<<endl;
cout<<"End of the measurement: "<<end->at(0)<<"/"<<end->at(1)<<"/"<<end->at(2)<<" - "<<end->at(3)<<":"<<end->at(4)<<":"<<end->at(5)<<endl;
cout<<"Number of identified and rejected spikes : "<<total_spike<<endl;
cout<<"Cathode  | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (cath_800V_led2_up > 0.0)
{
cout<<"800V      |"<<cath_800V_led1_up<<"   "<<cath_800V_led2_up<<"   "<<cath_800V_led3_up<<"   "<<cath_800V_led4_up<<endl;
cout<<"          |"<<cath_800V_led1_down<<"   "<<cath_800V_led2_down<<"   "<<cath_800V_led3_down<<"   "<<cath_800V_led4_down<<endl;
}
if (cath_800V_led2_up == 0.0 and cath_800V_led3_up == 0.0 and cath_800V_led4_up == 0.0)
{
cout<<"800V      |"<<cath_800V_led1_up<<endl;
cout<<"          |"<<cath_800V_led1_down<<endl;
}
if (cath_900V_led1_up > 0.0)
{
cout<<"900V      |"<<cath_900V_led1_up<<endl;
cout<<"          |"<<cath_900V_led1_down<<endl;
}
cout<<"1000V     |"<<cath_1000V_led1_up<<endl;
cout<<"          |"<<cath_1000V_led1_down<<endl;
cout<<"1200V     |"<<cath_1200V_led1_up<<"   "<<cath_1200V_led2_up<<"   "<<cath_1200V_led3_up<<"   "<<cath_1200V_led4_up<<endl;
cout<<"          |"<<cath_1200V_led1_down<<"   "<<cath_1200V_led2_down<<"   "<<cath_1200V_led3_down<<"   "<<cath_1200V_led4_down<<endl;
cout<<"1400V     |"<<cath_1400V_led1_up<<endl;
cout<<"          |"<<cath_1400V_led1_down<<endl;
if (cath_1600V_led1_up > 0.0)
{
cout<<"1600V     |"<<cath_1600V_led1_up<<endl;
cout<<"          |"<<cath_1600V_led1_down<<endl;
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

if(i+1 <= 16) { pmt_inv_qe->SetBinContent(1,i+1,50000.0/qe_1200V_led1); }
if(i+1 > 16) { pmt_inv_qe->SetBinContent(2,i-15,50000.0/qe_1200V_led1); }
if(i+1 <= 16) { pmt_inv_gain->SetBinContent(1,i+1,1.0/cath_1200V_led1_up); }
if(i+1 > 16) { pmt_inv_gain->SetBinContent(2,i-15,1.0/cath_1200V_led1_up); }
if(i+1 <= 16) { pmt_spikes->SetBinContent(1,i+1,total_spike); }
if(i+1 > 16) { pmt_spikes->SetBinContent(2,i-15,total_spike); }
}


TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1200,800);
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

pmt_inv_qe->Draw("colz");
pmt_inv_qe->Draw("text same");
c01->Print("Inverse_Quantum_Efficiency.png");
c01->Close();

TCanvas *c02 = new TCanvas("c02","Canvas",0,29,1200,800);
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

pmt_inv_gain->Draw("colz");
pmt_inv_gain->Draw("text same");
c02->Print("Inverse_Gain.png");
c02->Close();

TCanvas *c03 = new TCanvas("c03","Canvas",0,29,1200,800);
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
c03->Print("Number_of_Spikes.png");
c03->Close();

}
