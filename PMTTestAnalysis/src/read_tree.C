//to do : 	finish the plots
//		read a chain instead of a root file


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

//root libs
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TLegend.h"

struct measurement {
	int points;
	int spikes;
	float cath_value;
	float cath_error;
	float anode_value;
	float anode_error;
	float ref_value;
	float ref_error;
	float gain_value;
	float gain_error;
	float qe_value;
	float qe_error;
};


TGraphErrors *read_newgain(int sec, int hv)
{
// By Samantha Dooling
// Changed by Pedro Cipriano
//==============
//    get the root files
//==============
TGraphErrors *s_gain;
char strRootFile[255]; char * RootFile = NULL;
sprintf(strRootFile,"sec%d_%d.root",sec,hv );
RootFile = strRootFile;

TString filesdir("../data_new/");

const int n = 4 ;
TFile *f[n];
f[0] = new TFile(filesdir + RootFile);

//TGraphErrors *_s_gain[n];
//TGraphErrors *_s_gain;

//_s_gain[0] = (TGraphErrors*) f[0]->Get("gr_g;1");
s_gain = (TGraphErrors*) f[0]->Get("gr_g;1");
return s_gain;
}

TGraphErrors *get_gain_sector(double *gain, double *egain, int sec)
{
TGraphErrors *graph;
int n = 14;
double x[n], y[n], ex[n], ey[n];

for (int i=0; i < 14; i++)
{
x[i] = i + 1;
ex[i] = 0;
y[i] = gain[(i)*14 + (sec-1)];
ey[i] = egain[(i)*14 + (sec-1)];
//cout << "Sector : " << sec << " Module : " << i << "  Gain = " << y[i] << " (" << ey[i] << ")" << endl;
}

graph = new TGraphErrors(n,x,y,ex,ey);
return graph;
}

void set_inst_code(string pmt, int& module, int& sector, double& gain1200, double& qe1200)
{
if ( pmt == "BA0393" ) { sector = 1;  module = 1; }
if ( pmt == "BA0392" ) { sector = 2;  module = 1; gain1200 = 28916; qe1200 = 22.2e-6; }
if ( pmt == "BA0398" ) { sector = 3;  module = 1; }
if ( pmt == "BA0433" ) { sector = 4;  module = 1; }
if ( pmt == "BA0322" ) { sector = 5;  module = 1; }
if ( pmt == "BA0336" ) { sector = 6;  module = 1; }
if ( pmt == "BA0314" ) { sector = 7;  module = 1; }
if ( pmt == "BA0359" ) { sector = 8;  module = 1; }
if ( pmt == "BA0297" ) { sector = 9;  module = 1; }
if ( pmt == "BA0337" ) { sector = 10; module = 1; }
if ( pmt == "BA0342" ) { sector = 11; module = 1; }
if ( pmt == "BA0353" ) { sector = 12; module = 1; }
if ( pmt == "BA0404" ) { sector = 13; module = 1; }
if ( pmt == "BA0413" ) { sector = 14; module = 1; }
if ( pmt == "BA0446" ) { sector = 15; module = 1; }
if ( pmt == "BA0451" ) { sector = 16; module = 1; }
if ( pmt == "BA0388" ) { sector = 1;  module = 2; }
if ( pmt == "BA0408" ) { sector = 2;  module = 2; }
if ( pmt == "BA0411" ) { sector = 3;  module = 2; }
if ( pmt == "BA0452" ) { sector = 4;  module = 2; gain1200 = 30056.0; qe1200 = 24.2e-6; }
if ( pmt == "BA0287" ) { sector = 5;  module = 2; }
if ( pmt == "BA0317" ) { sector = 6;  module = 2; }
if ( pmt == "BA0263" ) { sector = 7;  module = 2; }
if ( pmt == "BA0321" ) { sector = 8;  module = 2; }
if ( pmt == "BA0291" ) { sector = 9;  module = 2; }
if ( pmt == "BA0303" ) { sector = 10; module = 2; }
if ( pmt == "BA0361" ) { sector = 11; module = 2; }
if ( pmt == "BA0304" ) { sector = 12; module = 2; }
if ( pmt == "BA0456" ) { sector = 13; module = 2; }
if ( pmt == "BA0387" ) { sector = 14; module = 2; }
if ( pmt == "BA0381" ) { sector = 15; module = 2; }
if ( pmt == "BA0460" ) { sector = 16; module = 2; }
if ( pmt == "BA0457" ) { sector = 1;  module = 3; }
if ( pmt == "BA0379" ) { sector = 2;  module = 3; }
if ( pmt == "BA0461" ) { sector = 3;  module = 3; }
if ( pmt == "BA0384" ) { sector = 4;  module = 3; }
if ( pmt == "BA0305" ) { sector = 5;  module = 3; }
if ( pmt == "BA0349" ) { sector = 6;  module = 3; }
if ( pmt == "BA0274" ) { sector = 7;  module = 3; }
if ( pmt == "BA0327" ) { sector = 8;  module = 3; }
if ( pmt == "BA0169" ) { sector = 9;  module = 3; }
if ( pmt == "BA0329" ) { sector = 10; module = 3; }
if ( pmt == "BA0300" ) { sector = 11; module = 3; }
if ( pmt == "BA0352" ) { sector = 12; module = 3; gain1200 = 18680.0;}
if ( pmt == "BA0443" ) { sector = 13; module = 3; }
if ( pmt == "BA0407" ) { sector = 14; module = 3; }
if ( pmt == "BA0396" ) { sector = 15; module = 3; }
if ( pmt == "BA0444" ) { sector = 16; module = 3; }
if ( pmt == "BA0401" ) { sector = 1;  module = 4; }
if ( pmt == "BA0425" ) { sector = 2;  module = 4; gain1200 = 38943.0; qe1200 = 22.9e-6; }
if ( pmt == "BA0458" ) { sector = 3;  module = 4; }
if ( pmt == "BA0449" ) { sector = 4;  module = 4; }
if ( pmt == "BA0364" ) { sector = 5;  module = 4; }
if ( pmt == "BA0264" ) { sector = 6;  module = 4; }
if ( pmt == "BA0360" ) { sector = 7;  module = 4; }
if ( pmt == "BA0288" ) { sector = 8;  module = 4; }
if ( pmt == "BA0403" ) { sector = 9;  module = 4; }
if ( pmt == "BA0339" ) { sector = 10; module = 4; }
if ( pmt == "BA0355" ) { sector = 11; module = 4; }
if ( pmt == "BA0265" ) { sector = 12; module = 4; }
if ( pmt == "BA0447" ) { sector = 13; module = 4; }
if ( pmt == "BA0367" ) { sector = 14; module = 4; }
if ( pmt == "BA0430" ) { sector = 15; module = 4; }
if ( pmt == "BA0409" ) { sector = 16; module = 4; }
if ( pmt == "BA0376" ) { sector = 1;  module = 5; }
if ( pmt == "BA0453" ) { sector = 2;  module = 5; }
if ( pmt == "BA0440" ) { sector = 3;  module = 5; gain1200 = 19701.0; qe1200 = 20.1e-6; }
if ( pmt == "BA0326" ) { sector = 4;  module = 5; }
if ( pmt == "BA0311" ) { sector = 5;  module = 5; }
if ( pmt == "BA0373" ) { sector = 6;  module = 5; }
if ( pmt == "BA0374" ) { sector = 7;  module = 5; }
if ( pmt == "BA0324" ) { sector = 8;  module = 5; }
if ( pmt == "BA0279" ) { sector = 9;  module = 5; }
if ( pmt == "BA0307" ) { sector = 10; module = 5; }
if ( pmt == "BA0318" ) { sector = 11; module = 5; }
if ( pmt == "BA0170" ) { sector = 12; module = 5; }
if ( pmt == "BA0455" ) { sector = 13; module = 5; }
if ( pmt == "BA0402" ) { sector = 14; module = 5; }
if ( pmt == "BA0439" ) { sector = 15; module = 5; gain1200 = 21506.0; qe1200 = 17.7e-6; }
if ( pmt == "BA0377" ) { sector = 16; module = 5; }
if ( pmt == "BA0441" ) { sector = 1;  module = 6; qe1200 = 19.1e-6;}
if ( pmt == "BA0472" ) { sector = 2;  module = 6; }
if ( pmt == "BA0386" ) { sector = 3;  module = 6; }
if ( pmt == "BA0454" ) { sector = 4;  module = 6; }
if ( pmt == "BA0184" ) { sector = 5;  module = 6; }
if ( pmt == "BA0182" ) { sector = 6;  module = 6; }
if ( pmt == "BA0390" ) { sector = 7;  module = 6; }
if ( pmt == "BA0405" ) { sector = 8;  module = 6; }
if ( pmt == "BA0437" ) { sector = 9;  module = 6; }
if ( pmt == "BA0435" ) { sector = 10; module = 6; }
if ( pmt == "BA0354" ) { sector = 11; module = 6; }
if ( pmt == "BA0428" ) { sector = 12; module = 6; }
if ( pmt == "BA0372" ) { sector = 13; module = 6; gain1200 = 9427; }
if ( pmt == "BA0438" ) { sector = 14; module = 6; gain1200 = 9345; }
if ( pmt == "BA0351" ) { sector = 15; module = 6; gain1200 = 8840; }
if ( pmt == "BA0434" ) { sector = 16; module = 6; gain1200 = 12941; }
if ( pmt == "CA1387" ) { sector = 1;  module = 7; }
if ( pmt == "CA0292" ) { sector = 2;  module = 7; }
if ( pmt == "CA1490" ) { sector = 3;  module = 7; }
if ( pmt == "CA0400" ) { sector = 4;  module = 7; }
if ( pmt == "CA1010" ) { sector = 5;  module = 7; }
if ( pmt == "CA0656" ) { sector = 6;  module = 7; }
if ( pmt == "CA0948" ) { sector = 7;  module = 7; }
if ( pmt == "CA1509" ) { sector = 8;  module = 7; }
if ( pmt == "CA2044" ) { sector = 9;  module = 7; }
if ( pmt == "CA1953" ) { sector = 10; module = 7; }
if ( pmt == "CA0932" ) { sector = 11; module = 7; }
if ( pmt == "CA1884" ) { sector = 12; module = 7; }
if ( pmt == "CA1450" ) { sector = 13; module = 7; }
if ( pmt == "CA0977" ) { sector = 14; module = 7; }
if ( pmt == "CA1434" ) { sector = 15; module = 7; }
if ( pmt == "CA1576" ) { sector = 16; module = 7; }
if ( pmt == "CA1620" ) { sector = 1;  module = 8; }
if ( pmt == "CA1229" ) { sector = 2;  module = 8; }
if ( pmt == "CA0930" ) { sector = 3;  module = 8; }
if ( pmt == "CA1300" ) { sector = 4;  module = 8; }
if ( pmt == "CA0045" ) { sector = 5;  module = 8; }
if ( pmt == "CA1881" ) { sector = 6;  module = 8; }
if ( pmt == "CA2060" ) { sector = 7;  module = 8; }
if ( pmt == "CA1363" ) { sector = 8;  module = 8; }
if ( pmt == "CA1501" ) { sector = 9;  module = 8; }
if ( pmt == "CA1530" ) { sector = 10; module = 8; }
if ( pmt == "CA0979" ) { sector = 11; module = 8; }
if ( pmt == "CA1143" ) { sector = 12; module = 8; }
if ( pmt == "CA0847" ) { sector = 13; module = 8; }
if ( pmt == "CA1680" ) { sector = 14; module = 8; }
if ( pmt == "CA1844" ) { sector = 15; module = 8; }
if ( pmt == "CA0811" ) { sector = 16; module = 8; }
if ( pmt == "CA1095" ) { sector = 1;  module = 9; }
if ( pmt == "CA1760" ) { sector = 2;  module = 9; }
if ( pmt == "CA0422" ) { sector = 3;  module = 9; }
if ( pmt == "CA2123" ) { sector = 4;  module = 9; }
if ( pmt == "CA1410" ) { sector = 5;  module = 9; }
if ( pmt == "CA0354" ) { sector = 6;  module = 9; }
if ( pmt == "CA0299" ) { sector = 7;  module = 9; }
if ( pmt == "CA1759" ) { sector = 8;  module = 9; }
if ( pmt == "CA2022" ) { sector = 9;  module = 9; }
if ( pmt == "CA1377" ) { sector = 10; module = 9; }
if ( pmt == "CA1951" ) { sector = 11; module = 9; }
if ( pmt == "CA1966" ) { sector = 12; module = 9; }
if ( pmt == "CA0808" ) { sector = 13; module = 9; }
if ( pmt == "CA0907" ) { sector = 14; module = 9; }
if ( pmt == "CA1325" ) { sector = 15; module = 9; }
if ( pmt == "CA1316" ) { sector = 16; module = 9; }
if ( pmt == "CA1691" ) { sector = 1;  module = 10; }
if ( pmt == "CA0055" ) { sector = 2;  module = 10; }
if ( pmt == "CA1979" ) { sector = 3;  module = 10; }
if ( pmt == "CA1495" ) { sector = 4;  module = 10; }
if ( pmt == "CA2034" ) { sector = 5;  module = 10; }
if ( pmt == "CA1808" ) { sector = 6;  module = 10; }
if ( pmt == "CA1432" ) { sector = 7;  module = 10; }
if ( pmt == "CA1469" ) { sector = 8;  module = 10; }
if ( pmt == "CA0084" ) { sector = 9;  module = 10; }
if ( pmt == "CA1655" ) { sector = 10; module = 10; }
if ( pmt == "CA1931" ) { sector = 11; module = 10; }
if ( pmt == "CA1577" ) { sector = 12; module = 10; }
if ( pmt == "CA2623" ) { sector = 13; module = 10; }
if ( pmt == "CA1634" ) { sector = 14; module = 10; }
if ( pmt == "CA0584" ) { sector = 15; module = 10; }
if ( pmt == "CA2046" ) { sector = 16; module = 10; }
if ( pmt == "CA0749" ) { sector = 2;  module = 11; }
if ( pmt == "CA1527" ) { sector = 4;  module = 11; }
if ( pmt == "CA1444" ) { sector = 5;  module = 11; }
if ( pmt == "CA0043" ) { sector = 7;  module = 11; }
}

void set_code(int module, int sector, int set, string& pmt)
{
//old pmts
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
if (sector == 4  and module == 3  and set == 1) { pmt = "CA0723"; }
if (sector == 3  and module == 3  and set == 1) { pmt = "CA1438"; }
if (sector == 2  and module == 3  and set == 1) { pmt = "CA0640"; }
if (sector == 1  and module == 3  and set == 1) { pmt = "CA0126"; }
if (sector == 4  and module == 4  and set == 1) { pmt = "CA1524"; }
if (sector == 3  and module == 4  and set == 1) { pmt = "CA1434"; }
if (sector == 2  and module == 4  and set == 1) { pmt = "CA0885"; }
if (sector == 1  and module == 4  and set == 1) { pmt = "CA1410"; }
if (sector == 4  and module == 5  and set == 1) { pmt = "CA1387"; }
if (sector == 3  and module == 5  and set == 1) { pmt = "CA1228"; }
if (sector == 2  and module == 5  and set == 1) { pmt = "CA2044"; }
if (sector == 1  and module == 5  and set == 1) { pmt = "CA0315"; }
if (sector == 4  and module == 6  and set == 1) { pmt = "CA2623"; }
if (sector == 3  and module == 6  and set == 1) { pmt = "CA0354"; }
if (sector == 2  and module == 6  and set == 1) { pmt = "CA0979"; }
if (sector == 1  and module == 6  and set == 1) { pmt = "CA0811"; }
if (sector == 16 and module == 3  and set == 1) { pmt = "CA1984"; }
if (sector == 15 and module == 3  and set == 1) { pmt = "CA1316"; }
if (sector == 14 and module == 3  and set == 1) { pmt = "CA1634"; }
if (sector == 13 and module == 3  and set == 1) { pmt = "CA0535"; }
if (sector == 16 and module == 4  and set == 1) { pmt = "CA1141"; }
if (sector == 15 and module == 4  and set == 1) { pmt = "CA0793"; }
if (sector == 14 and module == 4  and set == 1) { pmt = "CA3184"; }
if (sector == 13 and module == 4  and set == 1) { pmt = "CA1327"; }
if (sector == 16 and module == 5  and set == 1) { pmt = "CA1759"; }
if (sector == 15 and module == 5  and set == 1) { pmt = "CA1161"; }
if (sector == 14 and module == 5  and set == 1) { pmt = "CA1131"; }
if (sector == 13 and module == 5  and set == 1) { pmt = "CA0792"; }
if (sector == 16 and module == 6  and set == 1) { pmt = "CA1495"; }
if (sector == 15 and module == 6  and set == 1) { pmt = "CA1538"; }
if (sector == 14 and module == 6  and set == 1) { pmt = "CA1844"; }
if (sector == 13 and module == 6  and set == 1) { pmt = "CA0292"; }
if (sector == 5  and module == 3  and set == 1) { pmt = "CA0045"; }
if (sector == 6  and module == 3  and set == 1) { pmt = "CA0018"; }
if (sector == 7  and module == 3  and set == 1) { pmt = "CA1350"; }
if (sector == 8  and module == 3  and set == 1) { pmt = "CA1170"; }
if (sector == 9  and module == 3  and set == 1) { pmt = "CA0326"; }
if (sector == 10 and module == 3  and set == 1) { pmt = "CA1931"; }
if (sector == 11 and module == 3  and set == 1) { pmt = "CA1795"; }
if (sector == 12 and module == 3  and set == 1) { pmt = "CA0843"; }
if (sector == 5  and module == 4  and set == 1) { pmt = "CA1328"; }
if (sector == 6  and module == 4  and set == 1) { pmt = "CA1442"; }
if (sector == 7  and module == 4  and set == 1) { pmt = "CA2023"; }
if (sector == 8  and module == 4  and set == 1) { pmt = "CA2022"; }
if (sector == 9  and module == 4  and set == 1) { pmt = "CA0790"; }
if (sector == 10 and module == 4  and set == 1) { pmt = "CA0143"; }
if (sector == 11 and module == 4  and set == 1) { pmt = "CA2034"; }
if (sector == 12 and module == 4  and set == 1) { pmt = "CA2018"; }
if (sector == 5  and module == 5  and set == 1) { pmt = "CA0977"; }
if (sector == 6  and module == 5  and set == 1) { pmt = "CA0708"; }
if (sector == 7  and module == 5  and set == 1) { pmt = "CA0072"; }
if (sector == 8  and module == 5  and set == 1) { pmt = "CA1513"; }
if (sector == 9  and module == 5  and set == 1) { pmt = "CA0299"; }
if (sector == 10 and module == 5  and set == 1) { pmt = "CA0584"; }
if (sector == 11 and module == 5  and set == 1) { pmt = "CA1325"; }
if (sector == 12 and module == 5  and set == 1) { pmt = "CA1450"; }
if (sector == 5  and module == 6  and set == 1) { pmt = "CA1870"; }
if (sector == 6  and module == 6  and set == 1) { pmt = "CA2060"; }
if (sector == 7  and module == 6  and set == 1) { pmt = "CA1509"; }
if (sector == 8  and module == 6  and set == 1) { pmt = "CA0796"; }
if (sector == 9  and module == 6  and set == 1) { pmt = "CA1655"; }
if (sector == 10 and module == 6  and set == 1) { pmt = "CA1525"; }
if (sector == 11 and module == 6  and set == 1) { pmt = "CA1966"; }
if (sector == 12 and module == 6  and set == 1) { pmt = "CA2046"; }
if (sector == 5  and module == 7  and set == 1) { pmt = "CA1530"; }
if (sector == 6  and module == 7  and set == 1) { pmt = "CA1501"; }
if (sector == 7  and module == 7  and set == 1) { pmt = "CA1979"; }
if (sector == 8  and module == 7  and set == 1) { pmt = "CA1808"; }
if (sector == 9  and module == 7  and set == 1) { pmt = "CA1760"; }
if (sector == 10 and module == 7  and set == 1) { pmt = "CA1691"; }
if (sector == 11 and module == 7  and set == 1) { pmt = "CA0696"; }
if (sector == 12 and module == 7  and set == 1) { pmt = "CA1377"; }
if (sector == 5  and module == 8  and set == 1) { pmt = "CA0084"; }
if (sector == 6  and module == 8  and set == 1) { pmt = "CA1992"; }
if (sector == 7  and module == 8  and set == 1) { pmt = "CA1432"; }
if (sector == 8  and module == 8  and set == 1) { pmt = "CA1577"; }
if (sector == 9  and module == 8  and set == 1) { pmt = "CA1657"; }
if (sector == 10 and module == 8  and set == 1) { pmt = "CA0787"; }
if (sector == 11 and module == 8  and set == 1) { pmt = "CA1591"; }
if (sector == 12 and module == 8  and set == 1) { pmt = "CA0847"; }
if (sector == 5  and module == 9  and set == 1) { pmt = "CA1300"; }
if (sector == 6  and module == 9  and set == 1) { pmt = "CA1884"; }
if (sector == 7  and module == 9  and set == 1) { pmt = "CA0930"; }
if (sector == 9  and module == 9  and set == 1) { pmt = "CA0656"; }
if (sector == 10 and module == 9  and set == 1) { pmt = "CA1273"; }
if (sector == 11 and module == 9  and set == 1) { pmt = "CA1828"; }
if (sector == 3  and module == 10 and set == 1) { pmt = "CA1601"; }
if (sector == 4  and module == 7  and set == 1) { pmt = "CA0040"; }
if (sector == 15 and module == 9  and set == 1) { pmt = "CA2123"; }
if (sector == 16 and module == 9  and set == 1) { pmt = "CA1095"; }
if (sector == 14 and module == 10 and set == 1) { pmt = "CA0808"; }
if (sector == 14 and module == 8  and set == 1) { pmt = "CA1469"; }
if (sector == 13 and module == 10 and set == 1) { pmt = "CA1951"; }
if (sector == 4  and module == 8  and set == 1) { pmt = "CA0791"; }
if (sector == 15 and module == 7  and set == 1) { pmt = "CA0055"; }
if (sector == 16 and module == 10 and set == 1) { pmt = "CA2045"; }
if (sector == 2  and module == 8  and set == 1) { pmt = "CA1636"; }
if (sector == 13 and module == 9  and set == 1) { pmt = "CA1576"; }
if (sector == 3  and module == 7  and set == 1) { pmt = "CA2020"; }
if (sector == 13 and module == 7  and set == 1) { pmt = "CA0745"; }
if (sector == 14 and module == 9  and set == 1) { pmt = "CA0675"; }
if (sector == 1  and module == 7  and set == 1) { pmt = "CA1229"; }
if (sector == 2  and module == 11 and set == 1) { pmt = "CA0749"; }
if (sector == 1  and module == 9  and set == 1) { pmt = "CA0422"; }
if (sector == 2  and module == 10 and set == 1) { pmt = "CA2057"; }
if (sector == 3  and module == 9  and set == 1) { pmt = "CA3400"; }
if (sector == 4  and module == 11 and set == 1) { pmt = "CA1527"; }
if (sector == 13 and module == 7  and set == 1) { pmt = "CA0400"; }
if (sector == 1  and module == 8  and set == 1) { pmt = "CA1016"; }
if (sector == 4  and module == 10 and set == 1) { pmt = "CA1548"; }
if (sector == 2  and module == 9  and set == 1) { pmt = "CA1852"; }
if (sector == 6  and module == 8  and set == 1) { pmt = "CA0267"; }
if (sector == 14 and module == 7  and set == 1) { pmt = "CA2115"; }
if (sector == 16 and module == 7  and set == 1) { pmt = "CA1881"; }
if (sector == 4  and module == 9  and set == 1) { pmt = "CA1363"; }
if (sector == 1  and module == 10 and set == 1) { pmt = "CA1468"; }
if (sector == 15 and module == 8  and set == 1) { pmt = "CA1866"; }
if (sector == 2  and module == 7  and set == 1) { pmt = "CA1143"; }
if (sector == 16 and module == 8  and set == 1) { pmt = "CA2051"; }
if (sector == 15 and module == 10 and set == 1) { pmt = "CA0907"; }
if (sector == 12 and module == 9  and set == 1) { pmt = "CA1953"; }
if (sector == 10 and module == 10 and set == 1) { pmt = "CA0780"; }
if (sector == 6  and module == 10 and set == 1) { pmt = "CA0932"; }
if (sector == 9  and module == 10 and set == 1) { pmt = "CA1010"; }
if (sector == 5  and module == 10 and set == 1) { pmt = "CA0031"; }
if (sector == 12 and module == 8  and set == 1) { pmt = "CA1594"; }
if (sector == 7  and module == 11 and set == 1) { pmt = "CA0043"; }
if (sector == 5  and module == 11 and set == 1) { pmt = "CA1444"; }
if (sector == 11 and module == 10 and set == 1) { pmt = "CA1490"; }
if (sector == 12 and module == 10 and set == 1) { pmt = "CA1790"; }
if (sector == 5  and module == 12 and set == 1) { pmt = "CA1676"; }

//testpmt
if (sector == 1  and module == 1  and set == 3) { pmt = "CA2000"; }

//newpmts
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
if (sector == 10 and module == 1  and set == 2) { pmt = "BA0169"; }
if (sector == 10 and module == 2  and set == 2) { pmt = "BA0170"; }
if (sector == 10 and module == 3  and set == 2) { pmt = "BA0314"; }
if (sector == 10 and module == 4  and set == 2) { pmt = "BA0316"; }
if (sector == 10 and module == 5  and set == 2) { pmt = "BA0317"; }
if (sector == 9  and module == 1  and set == 2) { pmt = "BA0318"; }
if (sector == 9  and module == 2  and set == 2) { pmt = "BA0319"; }
if (sector == 9  and module == 3  and set == 2) { pmt = "BA0321"; }
if (sector == 9  and module == 4  and set == 2) { pmt = "BA0322"; }
if (sector == 9  and module == 5  and set == 2) { pmt = "BA0324"; }
if (sector == 8  and module == 1  and set == 2) { pmt = "BA0172"; }
if (sector == 8  and module == 2  and set == 2) { pmt = "BA0326"; }
if (sector == 8  and module == 3  and set == 2) { pmt = "BA0327"; }
if (sector == 8  and module == 4  and set == 2) { pmt = "BA0329"; }
if (sector == 8  and module == 5  and set == 2) { pmt = "BA0336"; }
if (sector == 7  and module == 1  and set == 2) { pmt = "BA0337"; }
if (sector == 7  and module == 2  and set == 2) { pmt = "BA0339"; }
if (sector == 7  and module == 3  and set == 2) { pmt = "BA0342"; }
if (sector == 7  and module == 4  and set == 2) { pmt = "BA0349"; }
if (sector == 7  and module == 5  and set == 2) { pmt = "BA0351"; }
if (sector == 6  and module == 1  and set == 2) { pmt = "BA0352"; }
if (sector == 6  and module == 2  and set == 2) { pmt = "BA0353"; }
if (sector == 6  and module == 3  and set == 2) { pmt = "BA0354"; }
if (sector == 6  and module == 4  and set == 2) { pmt = "BA0355"; }
if (sector == 6  and module == 5  and set == 2) { pmt = "BA0359"; }
if (sector == 5  and module == 1  and set == 2) { pmt = "BA0360"; }
if (sector == 5  and module == 2  and set == 2) { pmt = "BA0361"; }
if (sector == 5  and module == 3  and set == 2) { pmt = "BA0364"; }
if (sector == 5  and module == 4  and set == 2) { pmt = "BA0373"; }
if (sector == 5  and module == 5  and set == 2) { pmt = "BA0374"; }
if (sector == 14 and module == 1  and set == 2) { pmt = "BA0182"; }
if (sector == 14 and module == 2  and set == 2) { pmt = "BA0184"; }
if (sector == 14 and module == 3  and set == 2) { pmt = "BA0367"; }
if (sector == 14 and module == 4  and set == 2) { pmt = "BA0372"; }
if (sector == 14 and module == 5  and set == 2) { pmt = "BA0377"; }
if (sector == 13 and module == 1  and set == 2) { pmt = "BA0379"; }
if (sector == 13 and module == 2  and set == 2) { pmt = "BA0381"; }
if (sector == 13 and module == 3  and set == 2) { pmt = "BA0384"; }
if (sector == 13 and module == 4  and set == 2) { pmt = "BA0386"; }
if (sector == 13 and module == 5  and set == 2) { pmt = "BA0387"; }
if (sector == 12 and module == 1  and set == 2) { pmt = "BA0388"; }
if (sector == 12 and module == 2  and set == 2) { pmt = "BA0390"; }
if (sector == 12 and module == 3  and set == 2) { pmt = "BA0391"; }
if (sector == 12 and module == 4  and set == 2) { pmt = "BA0392"; }
if (sector == 12 and module == 5  and set == 2) { pmt = "BA0393"; }
if (sector == 11 and module == 1  and set == 2) { pmt = "BA0396"; }
if (sector == 11 and module == 2  and set == 2) { pmt = "BA0397"; }
if (sector == 11 and module == 3  and set == 2) { pmt = "BA0398"; }
if (sector == 11 and module == 4  and set == 2) { pmt = "BA0400"; }
if (sector == 11 and module == 5  and set == 2) { pmt = "BA0401"; }
if (sector == 15 and module == 1  and set == 2) { pmt = "BA0376"; }
if (sector == 15 and module == 2  and set == 2) { pmt = "BA0402"; }
if (sector == 15 and module == 3  and set == 2) { pmt = "BA0403"; }
if (sector == 15 and module == 4  and set == 2) { pmt = "BA0404"; }
if (sector == 15 and module == 5  and set == 2) { pmt = "BA0405"; }
if (sector == 16 and module == 1  and set == 2) { pmt = "BA0407"; }
if (sector == 16 and module == 2  and set == 2) { pmt = "BA0408"; }
if (sector == 16 and module == 3  and set == 2) { pmt = "BA0409"; }
if (sector == 16 and module == 4  and set == 2) { pmt = "BA0411"; }
if (sector == 16 and module == 5  and set == 2) { pmt = "BA0413"; }
if (sector == 17 and module == 1  and set == 2) { pmt = "BA0422"; }
if (sector == 17 and module == 2  and set == 2) { pmt = "BA0425"; }
if (sector == 17 and module == 3  and set == 2) { pmt = "BA0426"; }
if (sector == 17 and module == 4  and set == 2) { pmt = "BA0427"; }
if (sector == 17 and module == 5  and set == 2) { pmt = "BA0428"; }
if (sector == 18 and module == 1  and set == 2) { pmt = "BA0431"; }
if (sector == 18 and module == 2  and set == 2) { pmt = "BA0433"; }
if (sector == 18 and module == 3  and set == 2) { pmt = "BA0435"; }
if (sector == 18 and module == 4  and set == 2) { pmt = "BA0437"; }
if (sector == 18 and module == 5  and set == 2) { pmt = "BA0438"; }
if (sector == 19 and module == 1  and set == 2) { pmt = "BA0420"; }
if (sector == 19 and module == 2  and set == 2) { pmt = "BA0430"; }
if (sector == 19 and module == 3  and set == 2) { pmt = "BA0434"; }
if (sector == 19 and module == 4  and set == 2) { pmt = "BA0439"; }
if (sector == 19 and module == 5  and set == 2) { pmt = "BA0440"; }
if (sector == 20 and module == 1  and set == 2) { pmt = "BA0441"; }
if (sector == 20 and module == 2  and set == 2) { pmt = "BA0443"; }
if (sector == 20 and module == 3  and set == 2) { pmt = "BA0444"; }
if (sector == 20 and module == 4  and set == 2) { pmt = "BA0445"; }
if (sector == 20 and module == 5  and set == 2) { pmt = "BA0446"; }
if (sector == 21 and module == 1  and set == 2) { pmt = "BA0447"; }
if (sector == 21 and module == 2  and set == 2) { pmt = "BA0448"; }
if (sector == 21 and module == 3  and set == 2) { pmt = "BA0449"; }
if (sector == 21 and module == 4  and set == 2) { pmt = "BA0451"; }
if (sector == 21 and module == 5  and set == 2) { pmt = "BA0452"; }
if (sector == 22 and module == 1  and set == 2) { pmt = "BA0453"; }
if (sector == 22 and module == 2  and set == 2) { pmt = "BA0454"; }
if (sector == 22 and module == 3  and set == 2) { pmt = "BA0455"; }
if (sector == 22 and module == 4  and set == 2) { pmt = "BA0456"; }
if (sector == 22 and module == 5  and set == 2) { pmt = "BA0457"; }
if (sector == 23 and module == 1  and set == 2) { pmt = "BA0458"; }
if (sector == 23 and module == 2  and set == 2) { pmt = "BA0460"; }
if (sector == 23 and module == 3  and set == 2) { pmt = "BA0461"; }
if (sector == 23 and module == 4  and set == 2) { pmt = "BA0466"; }
if (sector == 23 and module == 5  and set == 2) { pmt = "BA0472"; }

if (pmt == "") { cout<<"Unknown PMT"<<endl; }

}


void read_tree(string *trees_in, int ini_file, int end_file)
{
//cout << "load tree"<<endl;
//opening the file

  TH2F *pmt_qe_800_old;
  TH2F *pmt_gain_800_old;
  TH2F *pmt_qe_1200_old;
  TH2F *pmt_gain_1200_old;
  TH2F *pmt_ratio_old;
  TH2F *pmt_spikes_old;
  TH2F *pmt_bad_fits_old;
  TH2F *measurements_old;
  TH2F *pmt_gain_1200_qe_old;

  pmt_qe_800_old =  new TH2F("QE_800V_old","QE_800V_old;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_800_old =  new TH2F("Gain_800V_old","Gain_800V_old;Module;Sector", 14,0,14,16,0,16);
  pmt_qe_1200_old =  new TH2F("QE_1200V_old","QE_1200V_old;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_1200_old =  new TH2F("Gain_1200V_old","Gain_1200V_old;Module;Sector", 14,0,14,16,0,16);
  pmt_ratio_old =  new TH2F("Ratio_old","Ratio_old;Module;Sector", 14,0,14,16,0,16);
  pmt_spikes_old =  new TH2F("Number_of_spikes_old","number_of_spikes_old;Module;Sector", 14,0,14,16,0,16);
  pmt_bad_fits_old =  new TH2F("Number_of_bad_fits_old","number_of_bad_fits_old;Module;Sector", 14,0,14,16,0,16);
  measurements_old =  new TH2F("Number_of_measurements_old","number_of_measurements_old;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_1200_qe_old =  new TH2F("PMT_gain_1200V_times_QE_old","PMT_gain_1200V_times_QE_old;Module;Sector", 14,0,14,16,0,16);

  TH2F *pmt_qe_800_new;
  TH2F *pmt_gain_800_new;
  TH2F *pmt_qe_1200_new;
  TH2F *pmt_gain_1200_new;
  TH2F *pmt_ratio_new;
  TH2F *pmt_spikes_new;
  TH2F *pmt_bad_fits_new;
  TH2F *measurements_new;
  TH2F *pmt_gain_1200_qe_new;

  pmt_qe_800_new =  new TH2F("QE_800V_new","QE_800V_new;Row;Line", 5,0,5,23,0,23);
  pmt_gain_800_new =  new TH2F("Gain_800V_new","Gain_800V_new;Row;Line", 5,0,5,23,0,23);
  pmt_qe_1200_new =  new TH2F("QE_1200V_new","QE_1200V_new;Row;Line", 5,0,5,23,0,23);
  pmt_gain_1200_new =  new TH2F("Gain_1200V_new","Gain_1200V_new;Row;Line", 5,0,5,23,0,23);
  pmt_ratio_new =  new TH2F("Ratio_new","Ratio_new;Row;Line", 5,0,5,23,0,23);
  pmt_spikes_new =  new TH2F("Number_of_spikes_new","number_of_spikes_new1;Row;Line", 5,0,5,23,0,23);
  pmt_bad_fits_new =  new TH2F("Number_of_bad_fits_new","number_of_bad_fits_new1;Row;Line", 5,0,5,23,0,23);
  measurements_new =  new TH2F("Number_of_measurements_new","number_of_measurements_new1;Row;Line", 5,0,5,23,0,23);
  pmt_gain_1200_qe_new =  new TH2F("PMT_gain_1200V_times_QE_new","PMT_gain_1200V_times_QE_new;Row;Line", 5,0,5,23,0,23);
  
  TH2F *pmt_qe_800_inst;
  TH2F *pmt_gain_800_inst;
  TH2F *pmt_qe_1200_inst;
  TH2F *pmt_gain_1200_inst;
  TH2F *pmt_ratio_inst;
  TH2F *pmt_spikes_inst;
  TH2F *pmt_bad_fits_inst;
  TH2F *measurements_inst;
  TH2F *pmt_gain_1200_qe_inst;

  pmt_qe_800_inst =  new TH2F("QE_800V_inst","QE_800V_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_800_inst =  new TH2F("Gain_800V_inst","Gain_800V_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_qe_1200_inst =  new TH2F("QE_1200V_inst","QE_1200V_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_1200_inst =  new TH2F("Gain_1200V_inst","Gain_1200V_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_ratio_inst =  new TH2F("Ratio_inst","Ratio_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_spikes_inst =  new TH2F("Number_of_spikes_inst","number_of_spikes_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_bad_fits_inst =  new TH2F("Number_of_bad_fits_inst","number_of_bad_fits_inst;Module;Sector", 14,0,14,16,0,16);
  measurements_inst =  new TH2F("Number_of_measurements_inst","number_of_measurements_inst;Module;Sector", 14,0,14,16,0,16);
  pmt_gain_1200_qe_inst =  new TH2F("PMT_gain_1200V_times_QE_inst","PMT_gain_1200V_times_QE_inst;Module;Sector", 14,0,14,16,0,16);

//variables for the comparison
    int array_size = 14 * 16;
    double gain_1200[array_size];
    double egain_1200[array_size];
    
    for (int i = 0; i < array_size-1; i++)
    {
    gain_1200[i] = 0.0;
    egain_1200[i] = 0.0;
    }

for (int z=ini_file-1; z < end_file; z++)
{

//open the cpt file
  string file = trees_in[z];
  cout<<"File "<<z+1<<"/"<<end_file<<" -> "<<file<<endl;
  TFile f(file.c_str());
  //if(f==NULL) {
  //  std::cout << "can't find file\n";
  //  exit(1);
  //}


//cout << "declare the tree" << endl;
//declaring the tree
TTree *tree = (TTree*)f.Get("Castor_PMT_Caracterization_2012");

//tree->Show(0);

//cout << "variables" << endl;
//declaring variables
std::vector<int> *begin, *end;
std::vector<float> *cath, *cath_ori, *anode, *ref, *led, *hv, *time;

int total_spikes, bad_fits, entries, module, sector, set;

int inst_module, inst_sector;
double inst_gain1200, inst_qe1200;

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

float ratio_800V, ratio_1200V, error_800V, error_1200V;

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

for (int i = 0; i < tests ;i++)
{

//cout << "getting the event : "<< i << endl;
tree->GetEvent(i);
//cout << "empty string" << endl;
string pmt = "";
inst_module = 0;
inst_sector = 0;
inst_gain1200 = 0.0;
inst_qe1200 = 0.0;
//cout << "set code" << endl;
set_code(module, sector, set, pmt);
set_inst_code(pmt, inst_module, inst_sector, inst_gain1200, inst_qe1200);
//cout << "output" << endl;

ratio_800V = 0.0;
ratio_1200V = 0.0;
error_800V = 0.0;
error_1200V = 0.0;

if (m_1200V_led3.qe_value > 0.0)
{
ratio_1200V = m_1200V_led1.qe_value / m_1200V_led3.qe_value;
error_1200V = ratio_1200V * sqrt( (m_1200V_led1.qe_error/m_1200V_led1.qe_value) * (m_1200V_led1.qe_error/m_1200V_led1.qe_value) + (m_1200V_led3.qe_error/m_1200V_led3.qe_value) * (m_1200V_led3.qe_error/m_1200V_led3.qe_value));
}

if (m_800V_led3.qe_value > 0.0)
{
ratio_800V = m_800V_led1.qe_value / m_800V_led3.qe_value;
error_800V = ratio_800V * sqrt( (m_800V_led1.qe_error/m_800V_led1.qe_value) * (m_800V_led1.qe_error/m_800V_led1.qe_value) + (m_800V_led3.qe_error/m_800V_led3.qe_value) * (m_800V_led3.qe_error/m_800V_led3.qe_value));
}

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
cout<<"          |Number of Spikes |"<<m_800V_led1.spikes<<"   "<<m_800V_led2.spikes<<"   "<<m_800V_led3.spikes<<"   "<<m_800V_led4.spikes<<endl;
cout<<"          |Points used      |"<<m_800V_led1.points<<"   "<<m_800V_led2.points<<"   "<<m_800V_led3.points<<"   "<<m_800V_led4.points<<endl;
}
if (m_800V_led2.cath_value == 0.0 and m_800V_led3.cath_value == 0.0 and m_800V_led4.cath_value == 0.0)
{
cout<<"800V      |Current          |"<<m_800V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_800V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_800V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_800V_led1.points<<endl;
}
if (m_900V_led1.cath_value > 0.0)
{
cout<<"900V      |Current          |"<<m_900V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_900V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_900V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_900V_led1.points<<endl;
}
cout<<"1000V     |Current          |"<<m_1000V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1000V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1000V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_1000V_led1.points<<endl;
if (m_1200V_led2.cath_value > 0.0)
{
cout<<"1200V     |Current          |"<<m_1200V_led1.cath_value<<"   "<<m_1200V_led2.cath_value<<"   "<<m_1200V_led3.cath_value<<"   "<<m_1200V_led4.cath_value<<endl;
cout<<"          |Error            |"<<m_1200V_led1.cath_error<<"   "<<m_1200V_led2.cath_error<<"   "<<m_1200V_led3.cath_error<<"   "<<m_1200V_led4.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1200V_led1.spikes<<"   "<<m_1200V_led2.spikes<<"   "<<m_1200V_led3.spikes<<"   "<<m_1200V_led4.spikes<<endl;
cout<<"          |Points used      |"<<m_1200V_led1.points<<"   "<<m_1200V_led2.points<<"   "<<m_1200V_led3.points<<"   "<<m_1200V_led4.points<<endl;
}
if (m_1200V_led2.cath_value == 0.0 and m_1200V_led3.cath_value == 0.0 and m_1200V_led4.cath_value == 0.0)
{
cout<<"1200V     |Current          |"<<m_1200V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1200V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1200V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_1200V_led1.points<<endl;
}
cout<<"1400V     |Current          |"<<m_1400V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1400V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1400V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_1400V_led1.points<<endl;
if (m_1600V_led1.cath_value > 0.0)
{
cout<<"1600V     |Current          |"<<m_1600V_led1.cath_value<<endl;
cout<<"          |Error            |"<<m_1600V_led1.cath_error<<endl;
cout<<"          |Number of Spikes |"<<m_1600V_led1.spikes<<endl;
cout<<"          |Points used      |"<<m_1600V_led1.points<<endl;
}
if (m_1800V_led4.cath_value > 0.0)
{
cout<<"1800V     |Current          |                                    "<<m_1800V_led4.cath_value<<endl;
cout<<"          |Error            |                                    "<<m_1800V_led4.cath_error<<endl;
cout<<"          |Number of Spikes |                                    "<<m_1800V_led4.spikes<<endl;
cout<<"          |Points used      |                                    "<<m_1800V_led4.points<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Anode     |        | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.anode_value > 0.0)
{
cout<<"800V      |Current |"<<m_800V_led1.anode_value<<"   "<<m_800V_led2.anode_value<<"   "<<m_800V_led3.anode_value<<"   "<<m_800V_led4.anode_value<<endl;
cout<<"          |Error   |"<<m_800V_led1.anode_error<<"   "<<m_800V_led2.anode_error<<"   "<<m_800V_led3.anode_error<<"   "<<m_800V_led4.anode_error<<endl;
}
if (m_800V_led2.anode_value == 0.0 and m_800V_led3.anode_value == 0.0 and m_800V_led4.anode_value == 0.0)
{
cout<<"800V      |Current |"<<m_800V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_800V_led1.anode_error<<endl;
}
if (m_900V_led1.anode_value > 0.0)
{
cout<<"900V      |Current |"<<m_900V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_900V_led1.anode_error<<endl;
}
cout<<"1000V     |Current |"<<m_1000V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_1000V_led1.anode_error<<endl;
if (m_1200V_led2.anode_value > 0.0)
{
cout<<"1200V     |Current |"<<m_1200V_led1.anode_value<<"   "<<m_1200V_led2.anode_value<<"   "<<m_1200V_led3.anode_value<<"   "<<m_1200V_led4.anode_value<<endl;
cout<<"          |Error   |"<<m_1200V_led1.anode_error<<"   "<<m_1200V_led2.anode_error<<"   "<<m_1200V_led3.anode_error<<"   "<<m_1200V_led4.anode_error<<endl;
}
if (m_1200V_led2.anode_value == 0.0 and m_1200V_led3.anode_value == 0.0 and m_1200V_led4.anode_value == 0.0)
{
cout<<"1200V     |Current |"<<m_1200V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_1200V_led1.anode_error<<endl;
}
cout<<"1400V     |Current |"<<m_1400V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_1400V_led1.anode_error<<endl;
if (m_1600V_led1.anode_value > 0.0)
{
cout<<"1600V     |Current |"<<m_1600V_led1.anode_value<<endl;
cout<<"          |Error   |"<<m_1600V_led1.anode_error<<endl;
}
if (m_1800V_led4.anode_value > 0.0)
{
cout<<"1800V     |Current |                                          "<<m_1800V_led4.anode_value<<endl;
cout<<"          |Error   |                                          "<<m_1800V_led4.anode_error<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Reference |        | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.ref_value > 0.0)
{
cout<<"800V      |Current |"<<m_800V_led1.ref_value<<"   "<<m_800V_led2.ref_value<<"   "<<m_800V_led3.ref_value<<"   "<<m_800V_led4.ref_value<<endl;
cout<<"          |Error   |"<<m_800V_led1.ref_error<<"   "<<m_800V_led2.ref_error<<"   "<<m_800V_led3.ref_error<<"   "<<m_800V_led4.ref_error<<endl;
}
if (m_800V_led2.ref_value == 0.0 and m_800V_led3.ref_value == 0.0 and m_800V_led4.ref_value == 0.0)
{
cout<<"800V      |Current |"<<m_800V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_800V_led1.ref_error<<endl;
}
if (m_900V_led1.ref_value > 0.0)
{
cout<<"900V      |Current |"<<m_900V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_900V_led1.ref_error<<endl;
}
cout<<"1000V     |Current |"<<m_1000V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_1000V_led1.ref_error<<endl;
if (m_1200V_led2.ref_value > 0.0)
{
cout<<"1200V     |Current |"<<m_1200V_led1.ref_value<<"   "<<m_1200V_led2.ref_value<<"   "<<m_1200V_led3.ref_value<<"   "<<m_1200V_led4.ref_value<<endl;
cout<<"          |Error   |"<<m_1200V_led1.ref_error<<"   "<<m_1200V_led2.ref_error<<"   "<<m_1200V_led3.ref_error<<"   "<<m_1200V_led4.ref_error<<endl;
}
if (m_1200V_led2.ref_value == 0.0 and m_1200V_led3.ref_value == 0.0 and m_1200V_led4.ref_value == 0.0)
{
cout<<"1200V     |Current |"<<m_1200V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_1200V_led1.ref_error<<endl;
}
cout<<"1400V     |Current |"<<m_1400V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_1400V_led1.ref_error<<endl;
if (m_1600V_led1.ref_error > 0.0)
{
cout<<"1600V     |Current |"<<m_1600V_led1.ref_value<<endl;
cout<<"          |Error   |"<<m_1600V_led1.ref_error<<endl;
}
if (m_1800V_led4.ref_value > 0.0)
{
cout<<"1800V     |Current |                                      "<<m_1800V_led4.ref_value<<endl;
cout<<"          |Error   |                                      "<<m_1800V_led4.ref_error<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Gain                |      | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.gain_value > 0.0)
{
cout<<"800V                |Value |"<<m_800V_led1.gain_value<<"   "<<m_800V_led2.gain_value<<"   "<<m_800V_led3.gain_value<<"   "<<m_800V_led4.gain_value<<endl;
cout<<"                    |Error |"<<m_800V_led1.gain_error<<"   "<<m_800V_led2.gain_error<<"   "<<m_800V_led3.gain_error<<"   "<<m_800V_led4.gain_error<<endl;
}
if (m_800V_led2.gain_value == 0.0 and m_800V_led3.gain_value == 0.0 and m_800V_led4.gain_value == 0.0)
{
cout<<"800V                |Value |"<<m_800V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_800V_led1.gain_error<<endl;
}
if (m_900V_led1.gain_value > 0.0)
{
cout<<"900V                |Value |"<<m_900V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_900V_led1.gain_error<<endl;
}
cout<<"1000V               |Value |"<<m_1000V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_1000V_led1.gain_error<<endl;
if (m_1200V_led2.gain_value > 0.0)
{
cout<<"1200V               |Value |"<<m_1200V_led1.gain_value<<"   "<<m_1200V_led2.gain_value<<"   "<<m_1200V_led3.gain_value<<"   "<<m_1200V_led4.gain_value<<endl;
cout<<"                    |Error |"<<m_1200V_led1.gain_error<<"   "<<m_1200V_led2.gain_error<<"   "<<m_1200V_led3.gain_error<<"   "<<m_1200V_led4.gain_error<<endl;
}
if (m_1200V_led2.gain_value == 0.0 and m_1200V_led3.gain_value == 0.0 and m_1200V_led4.gain_value == 0.0)
{
cout<<"1200V               |Value |"<<m_1200V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_1200V_led1.gain_error<<endl;
}
cout<<"1400V               |Value |"<<m_1400V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_1400V_led1.gain_error<<endl;
if (m_1600V_led1.gain_value > 0.0)
{
cout<<"1600V               |Value |"<<m_1600V_led1.gain_value<<endl;
cout<<"                    |Error |"<<m_1600V_led1.gain_error<<endl;
}
if (m_1800V_led4.gain_value > 0.0)
{
cout<<"1800V               |Value |                                    "<<m_1800V_led4.gain_value<<endl;
cout<<"                    |Error |                                    "<<m_1800V_led4.gain_error<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"Quantum Efficiency  |      | led1         led2          led3          led4"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (m_800V_led2.qe_value > 0.0)
{
cout<<"800V                |Value |"<<m_800V_led1.qe_value<<"   "<<m_800V_led2.qe_value<<"   "<<m_800V_led3.qe_value<<"   "<<m_800V_led4.qe_value<<endl;
cout<<"                    |Error |"<<m_800V_led1.qe_error<<"   "<<m_800V_led2.qe_error<<"   "<<m_800V_led3.qe_error<<"   "<<m_800V_led4.qe_error<<endl;
}
if (m_800V_led2.qe_value == 0.0 and m_800V_led3.qe_value == 0.0 and m_800V_led4.qe_value == 0.0)
{
cout<<"800V                |Value |"<<m_800V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_800V_led1.qe_error<<endl;
}
if (m_900V_led1.qe_value > 0.0)
{
cout<<"900V                |Value |"<<m_900V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_900V_led1.qe_error<<endl;
}
cout<<"1000V               |Value |"<<m_1000V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_1000V_led1.qe_error<<endl;
if (m_1200V_led2.qe_value > 0.0)
{
cout<<"1200V               |Value |"<<m_1200V_led1.qe_value<<"   "<<m_1200V_led2.qe_value<<"   "<<m_1200V_led3.qe_value<<"   "<<m_1200V_led4.qe_value<<endl;
cout<<"                    |Error |"<<m_1200V_led1.qe_error<<"   "<<m_1200V_led2.qe_error<<"   "<<m_1200V_led3.qe_error<<"   "<<m_1200V_led4.qe_error<<endl;
}
if (m_1200V_led2.qe_value == 0.0 and m_1200V_led3.qe_value == 0.0 and m_1200V_led4.qe_value == 0.0)
{
cout<<"1200V               |Value |"<<m_1200V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_1200V_led1.qe_error<<endl;
}
cout<<"1400V               |Value |"<<m_1400V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_1400V_led1.qe_error<<endl;
if (m_1600V_led1.qe_value > 0.0)
{
cout<<"1600V               |Value |"<<m_1600V_led1.qe_value<<endl;
cout<<"                    |Error |"<<m_1600V_led1.qe_error<<endl;
}
if (m_1800V_led4.qe_value > 0.0)
{
cout<<"1800V               |Value |                                    "<<m_1800V_led4.qe_value<<endl;
cout<<"                    |Error |                                    "<<m_1800V_led4.qe_error<<endl;
}
cout<<"----------------------------------------------------------"<<endl;
cout<<"QE Ratio            |Value         Error"<<endl;
cout<<"----------------------------------------------------------"<<endl;
if (ratio_800V > 0.0)
{
cout<<"800V                |"<<ratio_800V<<"  "<<error_800V<<endl;
}
if (ratio_1200V > 0.0)
{
cout<<"1200V               |"<<ratio_1200V<<"  "<<error_1200V<<endl;
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
pmt_gain_800_old->SetBinContent(module,sector,m_800V_led1.gain_value);
pmt_gain_1200_old->SetBinContent(module,sector,m_1200V_led1.gain_value);
pmt_qe_800_old->SetBinContent(module,sector,m_800V_led1.qe_value);
pmt_qe_1200_old->SetBinContent(module,sector,m_1200V_led1.qe_value);
if (ratio_800V > 0.0) { pmt_ratio_old->SetBinContent(module,sector,ratio_800V); }
if (ratio_1200V > 0.0) { pmt_ratio_old->SetBinContent(module,sector,ratio_1200V); }
pmt_spikes_old->SetBinContent(module,sector,total_spikes);
pmt_bad_fits_old->SetBinContent(module,sector,bad_fits);
measurements_old->Fill(module-0.5,sector-0.5);
pmt_gain_1200_qe_old->SetBinContent(module,sector,m_1200V_led1.gain_value*m_1200V_led1.qe_value);
}

if (set == 2)
{
pmt_gain_800_new->SetBinContent(module,sector,m_800V_led1.gain_value);
pmt_gain_1200_new->SetBinContent(module,sector,m_1200V_led1.gain_value);
pmt_qe_800_new->SetBinContent(module,sector,m_800V_led1.qe_value);
pmt_qe_1200_new->SetBinContent(module,sector,m_1200V_led1.qe_value);
if (ratio_800V > 0.0) { pmt_ratio_new->SetBinContent(module,sector,ratio_800V); }
if (ratio_1200V > 0.0) { pmt_ratio_new->SetBinContent(module,sector,ratio_1200V); }
pmt_spikes_new->SetBinContent(module,sector,total_spikes);
pmt_bad_fits_new->SetBinContent(module,sector,bad_fits);
measurements_new->Fill(module-0.5,sector-0.5);
pmt_gain_1200_qe_new->SetBinContent(module,sector,m_1200V_led1.gain_value*m_1200V_led1.qe_value);
}

if (inst_module > 0 and inst_sector > 0)
{
pmt_gain_800_inst->SetBinContent(inst_module,inst_sector,m_800V_led1.gain_value);
egain_1200[(inst_module-1)*14 + (inst_sector-1)] = m_1200V_led1.gain_error;
if (inst_gain1200 > 0.0)
{
pmt_gain_1200_inst->SetBinContent(inst_module,inst_sector,inst_gain1200);
gain_1200[(inst_module-1)*14 + (inst_sector-1)] = inst_gain1200;
}
else
{
pmt_gain_1200_inst->SetBinContent(inst_module,inst_sector,m_1200V_led1.gain_value);
gain_1200[(inst_module-1)*14 + (inst_sector-1)] = m_1200V_led1.gain_value;
}
pmt_qe_800_inst->SetBinContent(inst_module,inst_sector,m_800V_led1.qe_value);
if (inst_qe1200 > 0.0)
{
pmt_qe_1200_inst->SetBinContent(inst_module,inst_sector,inst_qe1200);
}
else
{
pmt_qe_1200_inst->SetBinContent(inst_module,inst_sector,m_1200V_led1.qe_value);
}
if (ratio_800V > 0.0) { pmt_ratio_inst->SetBinContent(inst_module,inst_sector,ratio_800V); }
if (ratio_1200V > 0.0) { pmt_ratio_inst->SetBinContent(inst_module,inst_sector,ratio_1200V); }
pmt_spikes_inst->SetBinContent(inst_module,inst_sector,total_spikes);
pmt_bad_fits_inst->SetBinContent(inst_module,inst_sector,bad_fits);
measurements_inst->Fill(inst_module-0.5,inst_sector-0.5);
if (inst_gain1200 > 0 and inst_qe1200 > 0)
{
pmt_gain_1200_qe_inst->SetBinContent(inst_module,inst_sector,inst_gain1200*inst_qe1200);
}
if (inst_gain1200 == 0.0 and inst_qe1200 == 0.0)
{
pmt_gain_1200_qe_inst->SetBinContent(inst_module,inst_sector,m_1200V_led1.gain_value*m_1200V_led1.qe_value);
}
if (inst_gain1200 > 0.0 and inst_qe1200 == 0.0)
{
pmt_gain_1200_qe_inst->SetBinContent(inst_module,inst_sector,inst_gain1200*m_1200V_led1.qe_value);
}
if (inst_gain1200 == 0.0 and inst_qe1200 > 0.0)
{
pmt_gain_1200_qe_inst->SetBinContent(inst_module,inst_sector,m_1200V_led1.gain_value*inst_qe1200);
}
}
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

pmt_qe_800_old->Draw("colz");
pmt_qe_800_old->Draw("text same");
c01->Print("Quantum_Efficiency_800V_old.png");
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

pmt_qe_1200_old->Draw("colz");
pmt_qe_1200_old->Draw("text same");
c02->Print("Quantum_Efficiency_1200V_old.png");
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

pmt_gain_800_old->Draw("colz");
pmt_gain_800_old->Draw("text same");
c03->Print("Gain_800V_old.png");
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

pmt_gain_1200_old->Draw("colz");
pmt_gain_1200_old->Draw("text same");
c04->Print("Gain_1200V_old.png");
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

pmt_gain_1200_qe_old->Draw("colz");
pmt_gain_1200_qe_old->Draw("text same");
c07->Print("Gain_1200_qe_old.png");
c07->Close();

/*TCanvas *c08 = new TCanvas("c08","Canvas",0,29,1200,800);
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
c08->Close();*/

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

pmt_ratio_old->Draw("colz");
pmt_ratio_old->Draw("text same");
c09->Print("Ratio_of_qe_between_led1_and_led3_old.png");
c09->Close(); 

TCanvas *c10 = new TCanvas("c10","Canvas",0,29,1200,800);
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

pmt_bad_fits_old->Draw("colz");
pmt_bad_fits_old->Draw("text same");
c10->Print("Bad_fits_old.png");
c10->Close();

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

pmt_qe_800_new->Draw("colz");
pmt_qe_800_new->Draw("text same");
c11->Print("Quantum_Efficiency_800V_new.png");
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

pmt_qe_1200_new->Draw("colz");
pmt_qe_1200_new->Draw("text same");
c12->Print("Quantum_Efficiency_1200V_new.png");
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

pmt_gain_800_new->Draw("colz");
pmt_gain_800_new->Draw("text same");
c13->Print("Gain_800V_new.png");
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

pmt_gain_1200_new->Draw("colz");
pmt_gain_1200_new->Draw("text same");
c14->Print("Gain_1200V_new.png");
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

pmt_spikes_new->Draw("colz");
pmt_spikes_new->Draw("text same");
c15->Print("Number_of_Spikes_new.png");
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

measurements_new->Draw("colz");
measurements_new->Draw("text same");
c16->Print("Number_of_Measurements_new.png");
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

pmt_gain_1200_qe_new->Draw("colz");
pmt_gain_1200_qe_new->Draw("text same");
c17->Print("Gain_1200_qe_new.png");
c17->Close();

/* TCanvas *c18 = new TCanvas("c18","Canvas",0,29,1200,800);
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
c18->Close(); */


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

pmt_ratio_new->Draw("colz");
pmt_ratio_new->Draw("text same");
c19->Print("Ratio_of_qe_between_led1_and_led3_new.png");
c19->Close();

TCanvas *c20 = new TCanvas("c20","Canvas",0,29,1200,800);
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

pmt_bad_fits_new->Draw("colz");
pmt_bad_fits_new->Draw("text same");
c20->Print("Bad_fits_new.png");
c20->Close();

TCanvas *c21 = new TCanvas("c21","Canvas",0,29,1200,800);
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

pmt_qe_800_inst->Draw("colz");
pmt_qe_800_inst->Draw("text same");
c21->Print("Quantum_Efficiency_800V_inst.png");
c21->Close();

TCanvas *c22 = new TCanvas("c22","Canvas",0,29,1200,800);
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

pmt_qe_1200_inst->Draw("colz");
pmt_qe_1200_inst->Draw("text same");
c22->Print("Quantum_Efficiency_1200V_inst.png");
c22->Close();

TCanvas *c23 = new TCanvas("c23","Canvas",0,29,1200,800);
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

pmt_gain_800_inst->Draw("colz");
pmt_gain_800_inst->Draw("text same");
c23->Print("Gain_800V_inst.png");
c23->Close();

TCanvas *c24 = new TCanvas("c24","Canvas",0,29,1200,800);
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

pmt_gain_1200_inst->Draw("colz");
pmt_gain_1200_inst->Draw("text same");
c24->Print("Gain_1200V_inst.png");
c24->Close();

TCanvas *c25 = new TCanvas("c25","Canvas",0,29,1200,800);
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

pmt_spikes_inst->Draw("colz");
pmt_spikes_inst->Draw("text same");
c25->Print("Number_of_Spikes_inst.png");
c25->Close();

TCanvas *c26 = new TCanvas("c26","Canvas",0,29,1200,800);
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

measurements_inst->Draw("colz");
measurements_inst->Draw("text same");
c26->Print("Number_of_Measurements_inst.png");
c26->Close();

TCanvas *c27 = new TCanvas("c27","Canvas",0,29,1200,800);
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

pmt_gain_1200_qe_inst->Draw("colz");
pmt_gain_1200_qe_inst->Draw("text same");
c27->Print("Gain_1200_qe_inst.png");
c27->Close();

/*TCanvas *c28 = new TCanvas("c28","Canvas",0,29,1200,800);
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
c28->Print("Inverse_Eletrical_Efficiency_1200V_new1.png");
c28->Close(); */


TCanvas *c29 = new TCanvas("c29","Canvas",0,29,1200,800);
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

pmt_ratio_inst->Draw("colz");
pmt_ratio_inst->Draw("text same");
c29->Print("Ratio_of_qe_between_led1_and_led3_inst.png");
c29->Close();

TCanvas *c30 = new TCanvas("c30","Canvas",0,29,1200,800);
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

pmt_bad_fits_inst->Draw("colz");
pmt_bad_fits_inst->Draw("text same");
c30->Print("Bad_fits_inst.png");
c30->Close();


double x = 0.0,y = 0.0;

TH2F *pmt_gain_1200_com;
pmt_gain_1200_com =  new TH2F("Gain_1200V_com","Gain_1200V_inst;Module;Sector", 14,0,14,16,0,16);

for (int i=1; i<= 16; i++)
{

cout << "Reading new gain files for sector " << i << "..." << endl;
TGraphErrors *new_gain = read_newgain(i , 1200);
cout << "Reading old gain array for sector " << i << "..." << endl;
TGraphErrors *old_gain = get_gain_sector(gain_1200, egain_1200, i);

TCanvas *c31 = new TCanvas("c31","Canvas",0,29,1200,800);
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

//cout << "output new_gain" << endl;
//new_gain->Print();
//cout << "output old_gain" << endl;
//old_gain->Print();
for (int j=1; j <= 14; j++)
{
new_gain->GetPoint(j,x,y);
pmt_gain_1200_com->SetBinContent(j,i,y);
}
cout << "Drawning new values for sector " << i << "..." << endl;
new_gain->SetTitle("Commisioning Gain for 1200V;Module;Gain");
new_gain->SetMarkerColor(2);
new_gain->SetMarkerStyle(21);
new_gain->SetMinimum(0);
new_gain->Draw("AP");
cout << "Drawning old values for sector " << i << "..." << endl;
old_gain->SetTitle("PMT test Gain for 1200V");
old_gain->SetMarkerColor(4);
old_gain->SetMarkerStyle(21);
old_gain->Draw("P");

TLegend *leg01 = new TLegend(0.13, 0.98, 0.50, .88);
leg01->AddEntry(new_gain,"Commissioning Gain for 1200V","p");
leg01->AddEntry(old_gain,"PMT test Gain for 1200V","p");
leg01->SetFillColor(0);
leg01->SetLineWidth(1);
leg01->SetLineColor(0);
leg01->SetFillStyle(1001);
leg01->Draw();

std::stringstream ss;
ss << i;
TString fileout = "sector_comparison_" + ss.str() + ".png";
c31->Print(fileout);
c31->Close();
}

TCanvas *c32 = new TCanvas("c32","Canvas",0,29,1200,800);
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

pmt_gain_1200_com->Draw("colz");
pmt_gain_1200_com->Draw("text same");
c32->Print("Gain_1200_commissioning.png");
c32->Close();
}
