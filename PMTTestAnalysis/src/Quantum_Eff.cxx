#include <stdio.h>


void Quantum_Eff(string inf, int color, string points){
  //  FILE *f = fopen("./cpt_sf_CA3396_2012_05_07_17_02_32_mod.cpt", "r");
  FILE *f = fopen( inf.c_str() , "r");
  if(f==NULL) {
    std::cout << "can't find file\n";
    exit(1);
  };
  int imin = 0;
  int imax = 0;
  //  float time, tmp;
  float measure_time, time, hv, cath, adut, aref, led;
  float errorHV = 15.;
  float IcathInit0(0.),IcathFin0(0.), IcathLed0Init(0.), IcathLed0Fin(0.);
  float IcathInit1(0.),IcathFin1(0.), IcathLed1Init(0.), IcathLed1Fin(0.);

  bool stop = false;

  fseek(f,0,SEEK_SET);

  float setHV = 800.;

  while(!feof(f) && !stop){
    fscanf(f,"%19s %f %f %f %f %f %f", &measure_time, &time, &hv, &cath, &adut, &aref,&led);

    //    if (hv > -setHV -errorHV && hv < -setHV +errorHV && led = 0) imin++;

    if (time < 1040 && hv < 810) IcathInit0 = cath;
    if (time < 1060 && hv < 810) IcathLed0Init = cath;
    if (time < 1440 && hv < 810) IcathLed0Fin = cath;
    if (time < 1460 && hv < 810) IcathFin0 = cath;


    if (time < 1850 && hv < 810) IcathInit1 = cath;
    if (time < 1870 && hv < 810) IcathLed1Init = cath;
    if (time < 2250 && hv < 810) IcathLed1Fin = cath;
    if (time < 2280 && hv < 810) IcathFin1 = cath;
  };

  std::cout << "DeltaI0 Led0=      " << IcathLed0Init-IcathInit0 << std::endl;
  std::cout << "DeltaI1 Led0=      " << IcathLed0Fin-IcathFin0   << std::endl;
  std::cout << "Diference DeltaI=  " << (IcathLed0Fin-IcathFin0)-(IcathLed0Init-IcathInit0)   << std::endl;
  std::cout << "Average DeltaI=    " << ((IcathLed0Fin-IcathFin0)+(IcathLed0Init-IcathInit0))/2.   << std::endl;
  std::cout << "% =                " << 100*((IcathLed0Fin-IcathFin0)-(IcathLed0Init-IcathInit0))/(((IcathLed0Fin-IcathFin0)+(IcathLed0Init-IcathInit0))/2.)   << std::endl;


  std::cout << "DeltaI0 Led1=      " << IcathLed1Init-IcathInit1 << std::endl;
  std::cout << "DeltaI1 Led1=      " << IcathLed1Fin-IcathFin1   << std::endl;
  std::cout << "Diference DeltaI=  " << (IcathLed1Fin-IcathFin1)-(IcathLed1Init-IcathInit1)   << std::endl;
  std::cout << "Average DeltaI=    " << ((IcathLed1Fin-IcathFin1)+(IcathLed1Init-IcathInit1))/2.   << std::endl;
  std::cout << "% =                " << 100*((IcathLed1Fin-IcathFin1)-(IcathLed1Init-IcathInit1))/(((IcathLed1Fin-IcathFin1)+(IcathLed1Init-IcathInit1))/2.)   << std::endl;


  /*


    int count = imin;
    //  int count = imax-imin;
    std::cout << "count"  << count << "; min " << imin   << "; max " << imax << std::endl;
    if(count<1) exit(1);

    float * arrmeasure_time   = new float[count];
    float * arrtime           = new float[count];
    float * arrhv             = new float[count];
    float * arrcath           = new float[count];
    float * arradut           = new float[count];
    float * arraref           = new float[count];
    const float errcath = 0.05E-5; // 0.5 uV

    fseek(f,0,SEEK_SET);

    while(!feof(f)){
    for(i=0; i<count; i++){
    fscanf(f,"%19s %f %f %f %f %f", &measure_time, &time, &hv, &cath, &adut, &aref);
    if(hv > hv_selection - error_HV && hv < hv_selection + error_HV)
    {arrtime[i]=time; arrhv[i]=hv; arrcath[i]=cath; arradut[i]=adut; arraref[i]=aref;}
    };
    };

    /*  int i = 0;
    while(i<imin){
    fscanf(f,"%19s %f %f %f %f %f", &measure_time, &time, &hv, &cath, &adut, &aref);
    i++;
    };
    /*

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

    for(i=imin; i<imax; i++){
    int pos = i-imin;
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


    c->cd(1);
    ghv->Draw(points.c_str());
    c->cd(2);
    gcath->Draw(points.c_str());
    c->cd(3);
    gadut->Draw(points.c_str());
    c->cd(4);
    garef->Draw(points.c_str());
  */
}
