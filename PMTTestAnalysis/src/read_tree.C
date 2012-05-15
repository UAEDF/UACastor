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
TString pmt;
float cath_800V_led1_up, cath_800V_led1_down;

float cath_800V_led2_up, cath_800V_led2_down;

float cath_800V_led3_up, cath_800V_led3_down;

float cath_800V_led4_up, cath_800V_led4_down;

//setting the branches
tree->SetBranchAddress("PMT",&pmt); 
tree->SetBranchAddress("Cath_800V_led1_up",&cath_800V_led1_up); 
tree->SetBranchAddress("Cath_800V_led1_down",&cath_800V_led1_down); 
tree->SetBranchAddress("Cath_800V_led2_up",&cath_800V_led2_up); 
tree->SetBranchAddress("Cath_800V_led2_down",&cath_800V_led2_down); 
tree->SetBranchAddress("Cath_800V_led3_up",&cath_800V_led3_up); 
tree->SetBranchAddress("Cath_800V_led3_down",&cath_800V_led3_down);
tree->SetBranchAddress("Cath_800V_led4_up",&cath_800V_led4_up); 
tree->SetBranchAddress("Cath_800V_led4_down",&cath_800V_led4_down); 

//loop over the measurements
int tests = tree->GetEntries();
for (int i = 0; i < tests ;i++)
{
cout<<pmt<<endl;
tree->GetEvent(i);
cout<<"800V"<<endl;
cout<<cath_800V_led1_up<<" "<<cath_800V_led2_up<<" "<<cath_800V_led3_up<<" "<<cath_800V_led3_up<<endl;
cout<<cath_800V_led1_down<<" "<<cath_800V_led2_down<<" "<<cath_800V_led3_up<<" "<<cath_800V_led3_up<<endl;
}



}
