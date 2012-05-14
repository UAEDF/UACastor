#include <stdio.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <TAttFill.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
using namespace std;

void Plot_All(string filename="ExampleFiles/cpt_sf_CA1579_2012_05_13_09_56_20.cpt", int color=kBlue, string points="p"){
  FILE *f = fopen(filename.c_str(), "r");
  if(f==NULL) {
    std::cout << "can't find file\n";
    exit(1);
  };
  int imin = 0;
  int imax = 0;
//  float time, tmp;
  float measure_time, time, hv, cath, adut, aref;
    bool stop = false;
  while(!feof(f) && !stop){
//    fscanf(f, "%f %E %E %E", &time, &tmp, &tmp, &tmp);
    fscanf(f,"%19s %f %f %f %f %f", &measure_time, &time, &hv, &cath, &adut, &aref);
    if(time > 0){imin++;}
//    if(time > 1000){stop = true;}
    imax++;
   };
   imax-=2;

  int count = imin;
//  int count = imax-imin;
  std::cout << "count"  << count 
	    << "; min " << imin 
	    << "; max " << imax << std::endl;
  if(count<1) exit(1);

  float * arrmeasure_time   = new float[count];
  float * arrtime           = new float[count];
  float * arrhv             = new float[count];
  float * arrcath           = new float[count];
  float * arradut           = new float[count];
  float * arraref           = new float[count];
  const float errcath = 0.05E-5; // 0.5 uV  
  fseek(f,0,SEEK_SET);

/*  int i = 0;
  while(i<imin){
    fscanf(f,"%19s %f %f %f %f %f", &measure_time, &time, &hv, &cath, &adut, &aref);
    i++;
  };


  TH1F         * h = new TH1F("h","h", 500, 0.70e-3, 0.74e-3);

  for(i=imin; i<imax; i++){
    int pos = i-imin;
    if ( pos < count ){
      fscanf(f, "%f %E %E %E", arrtime+pos, arranode+pos, arrref+pos, arrcath+pos);
      if(*(arrcath+pos)>1.0) *(arrcath+pos)=0; 
      if(*(arrcath+pos)<-1.0) *(arrcath+pos)=0; 
      arrcatherr[pos] = errcath;
      h->Fill(*(arrcath+pos));
    };
  };
*/
  for(int i=0; i<imax; i++){
    int pos = i;
   fscanf(f,"%19s %f %f %f %f %f", arrmeasure_time+pos, arrtime+pos, arrhv+pos, arrcath+pos, arradut+pos, arraref+pos);
  };

  fclose(f);
  
  TGraphErrors * ghv = new TGraphErrors(count, arrtime, arrhv,  0, 0);
  ghv->SetTitle("High voltage"); ghv->SetMarkerColor(color);
  TGraphErrors * gcath = new TGraphErrors(count, arrtime, arrcath, 0, 0);
  gcath->SetTitle("Cathode"); gcath->SetMarkerColor(color);
  TGraphErrors * gadut = new TGraphErrors(count, arrtime, arradut,   0, 0);
  gadut->SetTitle("Current DUT"); gadut->SetMarkerColor(color);
  TGraphErrors * garef = new TGraphErrors(count, arrtime, arraref,   0, 0);
  garef->SetTitle("Current REF"); garef->SetMarkerColor(color);

  TCanvas * c = NULL;
  c = new TCanvas("c","",800,600);
  c->cd(1);
  ghv->Draw(points.c_str());
  c->cd(2);
  gcath->Draw(points.c_str());
  c->cd(3);
  gadut->Draw(points.c_str());
  c->cd(4);
  garef->Draw(points.c_str());
}
