#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

# define debug 1

void ReadFile(vector<int>& run_list, char fname[200]) {

  ifstream file;
  file.open(fname,ios::in);

  if(file.is_open()) {
    int temp;
    while (file>>temp) {
      run_list.push_back(temp);
    }
  }

  return;
}

int main(int argc, char *argv[]) {
    
  if (argc != 2) {
    cout<<"This program was called with "<<argv[0]<<endl;
    cout<<""<<endl;
    cout<<"dataset = 1: Commissioning10"<<endl;
    cout<<"dataset = 2: Run210A"<<endl;
    cout<<"dataset = 3: Run210B"<<endl;
    cout<<""<<endl;
    return(0);
  }
  
  int dataset = atoi(argv[1]);

  //-- initialization

  char fname_ana[200];
  char fname_json[200];

  if(dataset == 1) {
    sprintf(fname_ana,"Analyse/Castor_Commissioning10_final_decision_good.txt");
    sprintf(fname_json,"JSON/Cert_Castor_Commissioning10_all_energy_Express_Collisions10_RunList.txt");
  }

  if(dataset == 2) {
    sprintf(fname_ana,"Analyse/Castor_Run2010A_final_decision_good.txt");
    sprintf(fname_json,"JSON/Cert_Castor_Run2010A_all_energy_Express_Collisions10_RunList.txt");
  }
  
  if(dataset == 3) {
    sprintf(fname_ana,"Analyse/Castor_Run2010B_final_decision_good.txt");
    sprintf(fname_json,"JSON/Cert_Castor_Run2010B_all_energy_Express_Collisions10_RunList.txt");
  }
  
  //-- retrieve list of runs

  vector<int> run_ana, run_json;

  ReadFile(run_ana,fname_ana);
  ReadFile(run_json,fname_json);

  if(debug) {
    cout<<"number of runs selected by ana: "<<run_ana.size()<<endl<<"\n";
    for (int i=0;i<run_ana.size();i++) cout<<"run ana "<<i+1<<": "<< run_ana.at(i)<<endl;
    cout<<"\n";

    cout<<"number of runs selected by json: "<<run_json.size()<<endl<<"\n";
    for (int i=0;i<run_json.size();i++) cout<<"run json "<<i+1<<": "<< run_json.at(i)<<endl;
    cout<<"\n";
  }
  
  //-- comparison
 
  FILE* fout_common;
  FILE* fout_ana_only;
  FILE* fout_json_only;

  if(dataset == 1) {
    fout_common = fopen("Result/run_Commissioning10_common.txt","w+");
    fout_ana_only = fopen("Result/run_Commissioning10_ana_only.txt","w+");
    fout_json_only = fopen("Result/run_Commissioning10_json_only.txt","w+");
  }

  if(dataset == 2) {
    fout_common = fopen("Result/run_Run2010A_common.txt","w+");
    fout_ana_only = fopen("Result/run_Run2010A_ana_only.txt","w+");
    fout_json_only = fopen("Result/run_Run2010A_json_only.txt","w+");
  }

  if(dataset == 3) {
    fout_common = fopen("Result/run_Run2010B_common.txt","w+");
    fout_ana_only = fopen("Result/run_Run2010B_ana_only.txt","w+");
    fout_json_only = fopen("Result/run_Run2010B_json_only.txt","w+");
  }

  cout<<"number of runs selected by ana: "<<run_ana.size()<<endl<<"\n";
  cout<<"number of runs selected by json: "<<run_json.size()<<endl<<"\n";

  int n_common = 0, n_ana_only = 0, n_json_only = 0;
  bool is_common = false;

  //-- loop on ana
  for (int ana = 0; ana < run_ana.size(); ana++) {

    is_common = false;

    //-- loop on json
    for (int json = 0; json < run_json.size(); json++) {
      
      if(run_ana[ana] != run_json[json]) continue;

      n_common++;
      is_common = true;
      fprintf(fout_common," %d \n",run_ana[ana]);
      run_json.erase(run_json.begin()+json);      
    } //-- end loop on json
     
    if(is_common == false) {
      n_ana_only++;
      fprintf(fout_ana_only," %d \n",run_ana[ana]);
    }

  } //-- end loop on ana

  n_json_only =  run_json.size();
  for (int json = 0; json < run_json.size(); json++) fprintf(fout_json_only," %d \n",run_json[json]);

  cout<<"number of runs common: "<<n_common<<endl<<"\n";
  cout<<"number of runs ana only: "<<n_ana_only<<endl<<"\n";
  cout<<"number of runs json only: "<<n_json_only<<endl<<"\n";

  fclose(fout_common);
  fclose(fout_ana_only);
  fclose(fout_json_only);

  return 0;
}
