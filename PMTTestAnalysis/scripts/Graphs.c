void Graphs()
{
gROOT -> Reset();

gStyle->SetMarkerSize(.2);
gStyle->SetMarkerStyle(2);

gROOT -> ProcessLine(".L Plot_All.cxx");
gROOT -> ProcessLine(".L Plot_New.cxx");
gROOT -> ProcessLine(".L Plot_New2.cxx");
gROOT -> ProcessLine(".L Quantum_Eff.cxx");

string file, points;
int color;

  TCanvas *c = new TCanvas("c","c",800,800);
  c->Divide(2,2);

file = "cpt_sf_CA1579_2012_05_12_15_32_59_mod.cpt";
color = 1; points = "AP";
//Plot_All(file, color, points);
//Plot_New(file, color, points);
Plot_New2(file, color, points);
//Quantum_Eff(file, color, points);

file = "cpt_sf_CA1579_2012_05_13_09_56_20_mod.cpt";
color = 2; points = "P";
//Plot_All(file, color, points);
//Plot_New(file, color, points);
Plot_New2(file, color, points);
//Plot_New2(file, color, points);

}
