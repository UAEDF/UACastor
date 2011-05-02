#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include <vector> 

using namespace std;

int main(int argc, char *argv[]) {

  int debug = 0;

  if (argc != 3) {
    cout<<"This program was called with "<<argv[0]<<endl;
    cout<<""<<endl;
    cout<<"dataset = 1: Commissioning10"<<endl;
    cout<<"dataset = 2: Run210A"<<endl;
    cout<<"dataset = 3: Run210B"<<endl;
    cout<<""<<endl;
    cout<<"number of runs"<<endl;
    return(0);
  }

  int dataset = atoi(argv[1]);
  int nbrun = atoi(argv[2]);
  
  //-- open the txt files

  int nbfile = 4;
  char* filename[nbfile];

  if(dataset == 1) { 
    filename[0] = "Decision/Castor_Commissioning10_reportSummaryMap.txt";
    filename[1] = "Decision/Castor_Commissioning10_ChannelSummaryMap.txt";
    filename[2] = "Decision/Castor_Commissioning10_AllDigiValues.txt";
    filename[3] = "Decision/Info_Commissioning10_reportSummaryMap_LS.txt";
  }

  if(dataset == 2) { 
    filename[0] = "Decision/Castor_Run2010A_reportSummaryMap.txt";
    filename[1] = "Decision/Castor_Run2010A_ChannelSummaryMap.txt";
    filename[2] = "Decision/Castor_Run2010A_AllDigiValues.txt";
    filename[3] = "Decision/Info_Run2010A_reportSummaryMap_LS.txt";
  }

  if(dataset == 3) { 
    filename[0] = "Decision/Castor_Run2010B_reportSummaryMap.txt";
    filename[1] = "Decision/Castor_Run2010B_ChannelSummaryMap.txt";
    filename[2] = "Decision/Castor_Run2010B_AllDigiValues.txt";
    filename[3] = "Decision/Info_Run2010B_reportSummaryMap_LS.txt";
  }

  ifstream file[nbfile];

  for(int ifile = 0; ifile < nbfile; ++ifile) {
    file[ifile].open(filename[ifile],ios::in);
    if (ifile ==  0) cout<<""<<endl;
    if (file [ifile].is_open()) cout<<"file "<<filename[ifile]<<" is open"<<endl;
    if (ifile ==  nbfile-1) cout<<""<<endl;
    if (!file [ifile].is_open()) {
      cout<<"could not open file "<<filename[ifile]<<endl;
      return(0);
    }
  }

  //-- retrieve run, decision, nbLS, list_LS_min, list_LS_max

  int run[nbfile][nbrun];
  int decision[nbfile][nbrun];
  int nbLS[nbrun];

  int list_LS_min[nbrun][10];
  int list_LS_max[nbrun][10];
  for(int irun = 0; irun < nbrun; ++irun) {
    for(int iLS = 0; iLS < 10; ++iLS) {
      list_LS_min[irun][iLS] = 0;
      list_LS_max[irun][iLS] = 0;
    }
  }

  for (int ifile = 0; ifile < nbfile; ++ifile) {

    for(int irun = 0; irun < nbrun; ++irun) {
      
      if(ifile != 3) file[ifile] >> run[ifile][irun] >> decision[ifile][irun];
      
      if(ifile != 3) continue; //-- so the following only applies to ifile == 3 (Info_***_reportSummaryMap_LS.txt)
      
      file[ifile] >> run[ifile][irun] >> decision[ifile][irun] >> nbLS[irun];

      if(nbLS[irun] == 1) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0];

      if(nbLS[irun] == 2) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1];

      if(nbLS[irun] == 3) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2];

      if(nbLS[irun] == 4) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3];

      if(nbLS[irun] == 5) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3]
				      >> list_LS_min[irun][4] >> list_LS_max[irun][4];

      if(nbLS[irun] == 6) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3]
				      >> list_LS_min[irun][4] >> list_LS_max[irun][4]
				      >> list_LS_min[irun][5] >> list_LS_max[irun][5];
      
      if(nbLS[irun] == 7) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3]
				      >> list_LS_min[irun][4] >> list_LS_max[irun][4]
				      >> list_LS_min[irun][5] >> list_LS_max[irun][5]
				      >> list_LS_min[irun][6] >> list_LS_max[irun][6];

      if(nbLS[irun] == 8) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3]
				      >> list_LS_min[irun][4] >> list_LS_max[irun][4]
				      >> list_LS_min[irun][5] >> list_LS_max[irun][5]
				      >> list_LS_min[irun][6] >> list_LS_max[irun][6]
				      >> list_LS_min[irun][7] >> list_LS_max[irun][7];

      if(nbLS[irun] == 9) file[ifile] >> list_LS_min[irun][0] >> list_LS_max[irun][0] 
				      >> list_LS_min[irun][1] >> list_LS_max[irun][1]
				      >> list_LS_min[irun][2] >> list_LS_max[irun][2]
				      >> list_LS_min[irun][3] >> list_LS_max[irun][3]
				      >> list_LS_min[irun][4] >> list_LS_max[irun][4]
				      >> list_LS_min[irun][5] >> list_LS_max[irun][5]
				      >> list_LS_min[irun][6] >> list_LS_max[irun][6]
				      >> list_LS_min[irun][7] >> list_LS_max[irun][7]
				      >> list_LS_min[irun][8] >> list_LS_max[irun][8];

      if(nbLS[irun] > 9) cout<<"problem: there are "<<nbLS[irun]<<" blocks of LS for run "<<irun<<endl;
      if(nbLS[irun] > 9) getchar();
  	
    } //-- end loop over irun
  } //-- end loop over ifile
   
  //-- some debug 

  if(debug) {
    for (int ifile = 0; ifile < nbfile; ++ifile) {
      for(int irun = 0; irun < nbrun; ++irun) {
	if(ifile != 3) cout<<"run "<<run[ifile][irun]<<" decision for "<<filename[ifile]<<": "<<decision[ifile][irun]<<endl;
	if(ifile == 3) {
	  cout<<"run "<<run[ifile][irun]<<" decision for "<<filename[ifile]<<": "<<decision[ifile][irun]<<" nb LS: "<<nbLS[irun]<<" LS range(s): ";
	  for(int iLS = 0; iLS < nbLS[irun]; ++iLS) {
	    cout<<" "<<list_LS_min[irun][iLS]<<" - "<<list_LS_max[irun][iLS];
	    if(iLS == nbLS[irun]-1) cout<<""<<endl;
	  }
	}
	if(irun == nbrun-1) cout<<""<<endl;
	if(irun == nbrun-1) getchar(); 
      }
    }
  }

  //-- compute the final decision

  int final_decision[nbrun];
  FILE* file_Castor_final_decision;

  if(dataset == 1) file_Castor_final_decision = fopen("Decision/Castor_Commissioning10_final_decision.txt","w+");
  if(dataset == 2) file_Castor_final_decision = fopen("Decision/Castor_Run2010A_final_decision.txt","w+");
  if(dataset == 3) file_Castor_final_decision = fopen("Decision/Castor_Run2010B_final_decision.txt","w+");

  for(int irun = 0; irun < nbrun; ++irun) {

    final_decision[irun] = 1;
  
    if(decision[0][irun] == 0) final_decision[irun] = 0;
    if(debug) cout<<"run: "<<run[0][irun]<<" is at position "<<irun<<" for file "<<filename[0]<<" decision "<<decision[0][irun]<<endl;
    
    for(int ifile = 1; ifile < nbfile; ++ifile) {
      for(int jrun = 0; jrun < nbrun; ++jrun) {
	if(run[0][irun] == run[ifile][jrun]) {
	  if(decision[ifile][jrun] == 0) final_decision[irun] = 0;
	  if(debug) cout<<"run: "<<run[ifile][jrun]<<" is at position "<<jrun<<" for file "<<filename[ifile]<<" decision "<<decision[ifile][jrun]<<endl;
	}
      }
    }
    
    cout<<"run: "<<run[0][irun]<<" final decision "<<final_decision[irun]<<endl;
    fprintf(file_Castor_final_decision,"%d  %d\n",run[0][irun],final_decision[irun]);
    if(debug) cout<<""<<endl;
    if(debug) getchar();
  }
  
  fclose(file_Castor_final_decision);
  return(0);
}
