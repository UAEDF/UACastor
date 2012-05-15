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
float cath_800V_led1_up;

//setting the branches
TBranch *cath_800V_led1_up = tree.GetBranch("Cath_800V_led1_up");

//loop over the measurements
int tests = tree->GetEntries();
for (int i = 0; i < tests ;i++)
{
cout<<i+1<<endl;

}



}
