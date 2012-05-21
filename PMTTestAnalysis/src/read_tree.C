#include <stdio.h>
#include <iostream>
#include "TTree.h"
#include "TFile.h"

void read_tree(string tree_in)
{
//opening the file
TFile f(tree_in.c_str());

//declaring the tree
TTree *tree = (TTree*)f.Get("Castor_PMT_Caracterization_2012");

//declaring variables
TString pmt, begin;
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
float cath_1600V_led1_up, cath_1600V_led1_down;
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
float anode_1600V_led1_up, anode_1600V_led1_down;
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
float ref_1600V_led1_up, ref_1600V_led1_down;

float ee_800V_led1;
float ee_800V_led2;
float ee_800V_led3;
float ee_800V_led4;
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
tree->SetBranchAddress("Cath_800V_led1_up",&cath_800V_led1_up); 
tree->SetBranchAddress("Cath_800V_led1_down",&cath_800V_led1_down); 
tree->SetBranchAddress("Cath_800V_led2_up",&cath_800V_led2_up); 
tree->SetBranchAddress("Cath_800V_led2_down",&cath_800V_led2_down); 
tree->SetBranchAddress("Cath_800V_led3_up",&cath_800V_led3_up); 
tree->SetBranchAddress("Cath_800V_led3_down",&cath_800V_led3_down);
tree->SetBranchAddress("Cath_800V_led4_up",&cath_800V_led4_up); 
tree->SetBranchAddress("Cath_800V_led4_down",&cath_800V_led4_down); 
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
for (int i = 0; i < tests ;i++)
{
tree->GetEvent(i);
cout<<"Measurement "<<i+1<<" ; PMT code: "<<pmt<<" Begin of the measurement: "<<begin<<endl;
cout<<"Cathode  | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"800V      |"<<cath_800V_led1_up<<"   "<<cath_800V_led2_up<<"   "<<cath_800V_led3_up<<"   "<<cath_800V_led4_up<<endl;
cout<<"          |"<<cath_800V_led1_down<<"   "<<cath_800V_led2_down<<"   "<<cath_800V_led3_down<<"   "<<cath_800V_led4_down<<endl;
cout<<"1000V     |"<<cath_1000V_led1_up<<endl;
cout<<"          |"<<cath_1000V_led1_down<<endl;
cout<<"1200V     |"<<cath_1200V_led1_up<<"   "<<cath_1200V_led2_up<<"   "<<cath_1200V_led3_up<<"   "<<cath_1200V_led4_up<<endl;
cout<<"          |"<<cath_1200V_led1_down<<"   "<<cath_1200V_led2_down<<"   "<<cath_1200V_led3_down<<"   "<<cath_1200V_led4_down<<endl;
cout<<"1400V     |"<<cath_1400V_led1_up<<endl;
cout<<"          |"<<cath_1400V_led1_down<<endl;
cout<<"1600V     |"<<cath_1600V_led1_up<<endl;
cout<<"          |"<<cath_1600V_led1_down<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"Anode     | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"800V      |"<<anode_800V_led1_up<<"   "<<anode_800V_led2_up<<"   "<<anode_800V_led3_up<<"   "<<anode_800V_led4_up<<endl;
cout<<"          |"<<anode_800V_led1_down<<"   "<<anode_800V_led2_down<<"   "<<anode_800V_led3_down<<"   "<<anode_800V_led4_down<<endl;
cout<<"1000V     |"<<anode_1000V_led1_up<<endl;
cout<<"          |"<<anode_1000V_led1_down<<endl;
cout<<"1200V     |"<<anode_1200V_led1_up<<"   "<<anode_1200V_led2_up<<"   "<<anode_1200V_led3_up<<"   "<<anode_1200V_led4_up<<endl;
cout<<"          |"<<anode_1200V_led1_down<<"   "<<anode_1200V_led2_down<<"   "<<anode_1200V_led3_down<<"   "<<anode_1200V_led4_down<<endl;
cout<<"1400V     |"<<anode_1400V_led1_up<<endl;
cout<<"          |"<<anode_1400V_led1_down<<endl;
cout<<"1600V     |"<<anode_1600V_led1_up<<endl;
cout<<"          |"<<anode_1600V_led1_down<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"Reference | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"800V      |"<<ref_800V_led1_up<<"   "<<ref_800V_led2_up<<"   "<<ref_800V_led3_up<<"   "<<ref_800V_led4_up<<endl;
cout<<"          |"<<ref_800V_led1_down<<"   "<<ref_800V_led2_down<<"   "<<ref_800V_led3_down<<"   "<<ref_800V_led4_down<<endl;
cout<<"1000V     |"<<ref_1000V_led1_up<<endl;
cout<<"          |"<<ref_1000V_led1_down<<endl;
cout<<"1200V     |"<<ref_1200V_led1_up<<"   "<<ref_1200V_led2_up<<"   "<<ref_1200V_led3_up<<"   "<<ref_1200V_led4_up<<endl;
cout<<"          |"<<ref_1200V_led1_down<<"   "<<ref_1200V_led2_down<<"   "<<ref_1200V_led3_down<<"   "<<ref_1200V_led4_down<<endl;
cout<<"1400V     |"<<ref_1400V_led1_up<<endl;
cout<<"          |"<<ref_1400V_led1_down<<endl;
cout<<"1600V     |"<<ref_1600V_led1_up<<endl;
cout<<"          |"<<ref_1600V_led1_down<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"Efficiency| led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<"800V      |"<<ee_800V_led1<<"   "<<ee_800V_led2<<"   "<<ee_800V_led3<<"   "<<ee_800V_led4<<endl;
cout<<"          |"<<qe_800V_led1<<"   "<<qe_800V_led2<<"   "<<qe_800V_led3<<"   "<<qe_800V_led4<<endl;
cout<<"1000V     |"<<ee_1000V_led1<<endl;
cout<<"          |"<<qe_1000V_led1<<endl;
cout<<"1200V     |"<<ee_1200V_led1<<"   "<<ee_1200V_led2<<"   "<<ee_1200V_led3<<"   "<<ee_1200V_led4<<endl;
cout<<"          |"<<qe_1200V_led1<<"   "<<qe_1200V_led2<<"   "<<qe_1200V_led3<<"   "<<qe_1200V_led4<<endl;
cout<<"1400V     |"<<ee_1400V_led1<<endl;
cout<<"          |"<<qe_1400V_led1<<endl;
cout<<"1600V     |"<<ee_1600V_led1<<endl;
cout<<"          |"<<qe_1600V_led1<<endl;
cout<<"----------------------------------------------------------"<<endl;
cout<<" "<<endl;
}



}
