#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <TApplication.h>
#include "MainAnalyzer.h"

int main(int argc, char *argv[]) {
	
  using namespace std;

  printf("argc = %d\n", argc);
  for (int i = 0; i<argc; i++){
    static int k = 0;
    printf("argv[%d] = %s\n", k, argv[k]);
    k++;
  }

  TString title = argv[1];
  cout<<"I will look in data and MC for the histo with title "<<title.Data()<<endl;

  TApplication* rootapp = new TApplication("app",&argc, argv);

  MainAnalyzer* m = new MainAnalyzer();

  m->plotHistos("../Result/","output_profile",title);
  
  delete m;
  
  return(0);
}

