#define SimHits_cxx
#include "SimHits.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVirtualPad.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <iostream>




double SimHits::CalculateRatioError(double ratio,double nominator, double denominator, double error_nominator,double error_denominator) {

double RatioError = 0;

RatioError = ratio*ratio*((error_nominator*error_nominator)/(nominator*nominator) + (error_denominator*error_denominator)/(denominator*denominator));
RatioError = sqrt(RatioError);
return RatioError;

}

void SimHits::CalculateScaling() {

int energies = 11;

//TH1D *hEnergy = new TH1D("hEnergy","Energy distribution of hits",100,0,1.);
//TH1D *hTotalEnergy = new TH1D("hTotalEnergy","Total Energy distribution of hits",100,0,1.);
//TH1D *hWeightedModules = new TH1D("hWeightedModules","Weighted module distribution of simhits",14,1,15);
//TH1D *hWeightedSectors = new TH1D("hWeightedSectors","Weighted sector distribution of simhits",16,1,17);

TH1D *hEnergy[energies];
TH1D *hTotalEnergy[energies];
Char_t htitleEnergy[100];
Char_t hnameEnergy[100];
Char_t htitleTotalEnergy[100];
Char_t hnameTotalEnergy[100];

TH1D *hWeightedModules[energies];
TH1D *hWeightedSectors[energies];
Char_t htitleWeightedModules[100];
Char_t hnameWeightedModules[100];
Char_t htitleWeightedSectors[100];
Char_t hnameWeightedSectors[100];

for (int i=0;i<energies;i++) {
	sprintf(hnameEnergy,"hEnergy_%d",i);
	sprintf(htitleEnergy,"Energy of simhits at %d GeV",(i+1)*5);
	sprintf(hnameTotalEnergy,"hTotalenergy_%d",i);
	sprintf(htitleTotalEnergy,"Total energy of simhits at %d GeV",(i+1)*5);
	hEnergy[i] = new TH1D(hnameEnergy,htitleEnergy,100,0,1.);
	hTotalEnergy[i] = new TH1D(hnameTotalEnergy,htitleTotalEnergy,100,0,1.);
	
	sprintf(hnameWeightedModules,"hWeightedModules_%d",i);
	sprintf(htitleWeightedModules,"Energy weighted module distribution of simhits at %d GeV",(i+1)*5);
	hWeightedModules[i] = new TH1D(hnameWeightedModules,htitleWeightedModules,14,1,15);
}
for (int i=0;i<energies;i++) {
	sprintf(hnameWeightedSectors,"hWeightedSectors_%d",i);
	sprintf(htitleWeightedSectors,"Energy weighted sector distribution of simhits at %d GeV",(i+1)*5);
	hWeightedSectors[i] = new TH1D(hnameWeightedSectors,htitleWeightedSectors,16,1,17);
}

//TH1D *hRatiosModules = new TH1D("hRatiosModules","FS/SL ratio in modules",14,1,15);
//TH1D *hRatiosSectors = new TH1D("hRatiosSectors","FS/SL ratio in sectors",16,1,17);
//TH1D *hRatiosModules2 = new TH1D("hRatiosModules2","FS/SL ratio in modules",14,1,15);
//TH1D *hRatiosSectors2 = new TH1D("hRatiosSectors2","FS/SL ratio in sectors",16,1,17);   

TH1D *hMod[14];
Char_t htitleMod[100];
Char_t hnameMod[100];

for (int i=0;i<14;i++) {
	sprintf(hnameMod,"hMod_%d",i);
	sprintf(htitleMod,"Energy of simhits in module %d",i+1);
	hMod[i] = new TH1D(hnameMod,htitleMod,energies,1,50);
}


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   
   int nEntries[energies];
   for (int i=0;i<energies;i++) {
   	nEntries[i] = 0;
   }

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      int energybin = 0;
      for (int k=0;k<energies;k++) {
      	if (jentry >= k*10000 && jentry < (k+1)*10000) energybin = k; 
      }
      //std::cout << " energybin = " << energybin << std::endl;
      
      nEntries[energybin] = nEntries[energybin] + 1;
      for (size_t i=0;i<simhit_energy->size();i++) {
		hWeightedModules[energybin]->Fill((*simhit_module)[i],(*simhit_energy)[i]);
		hWeightedSectors[energybin]->Fill((*simhit_sector)[i],(*simhit_energy)[i]);
		hEnergy[energybin]->Fill((*simhit_energy)[i]);
      }
      hTotalEnergy[energybin]->Fill(simhit_etot);
      
   }
   
   for (int i=0;i<energies;i++) {
   	std::cout << "There are " << nEntries[i] << " entries for bin " << i << std::endl;
   }
   
   TCanvas *c1 = new TCanvas("c1","Canvas");
   c1->Divide(3,2);
   c1->cd(1);
   double max = hWeightedModules[energies-1]->GetBinContent(hWeightedModules[energies-1]->GetMaximumBin());
   hWeightedModules[0]->GetYaxis()->SetRangeUser(0.1,max+10);
   for (int i=0;i<energies;i++) {
   	if (i==0) hWeightedModules[i]->Draw();
   	if (i > 0) hWeightedModules[i]->SetLineColor(40-i);
   	if (i > 0) hWeightedModules[i]->Draw("same");
   }
   c1->cd(2);
   max = hWeightedSectors[energies-1]->GetBinContent(hWeightedSectors[energies-1]->GetMaximumBin());
   hWeightedSectors[0]->GetYaxis()->SetRangeUser(0.1,max+10);
   for (int i=0;i<energies;i++) {
   	if (i==0) hWeightedSectors[i]->Draw();
   	if (i > 0) hWeightedSectors[i]->SetLineColor(40-i);
   	if (i > 0) hWeightedSectors[i]->Draw("same");
   }
   TVirtualPad* c1_3 = c1->cd(3);
   c1_3->SetLogy();
   max = hEnergy[0]->GetBinContent(hEnergy[0]->GetMaximumBin());
   hEnergy[0]->GetYaxis()->SetRangeUser(0.1,max+100000);
   for (int i=0;i<energies;i++) {
   	if (i==0) hEnergy[i]->Draw();
   	if (i > 0) hEnergy[i]->SetLineColor(40-i);
   	if (i > 0) hEnergy[i]->Draw("same");
   }
   TVirtualPad* c1_4 = c1->cd(4);
   c1_4->SetLogy();
   max = hTotalEnergy[0]->GetBinContent(hTotalEnergy[0]->GetMaximumBin());
   hTotalEnergy[0]->GetYaxis()->SetRangeUser(0.1,max+1000);
   for (int i=0;i<energies;i++) {
   	if (i==0) hTotalEnergy[i]->Draw();
   	if (i > 0) hTotalEnergy[i]->SetLineColor(40-i);
   	if (i > 0) hTotalEnergy[i]->Draw("same");
   }
   TVirtualPad* c1_5 = c1->cd(5);
   c1_5->SetLogy();
   max = hWeightedModules[energies-1]->GetBinContent(hWeightedModules[energies-1]->GetMaximumBin());
   hWeightedModules[0]->GetYaxis()->SetRangeUser(0.1,max+100);
   for (int i=0;i<energies;i++) {
   	if (i==0) hWeightedModules[i]->Draw();
   	if (i > 0) hWeightedModules[i]->SetLineColor(40-i);
   	if (i > 0) hWeightedModules[i]->Draw("same");
   }
   TVirtualPad* c1_6 = c1->cd(6);
   c1_6->SetLogy();
   max = hWeightedSectors[energies-1]->GetBinContent(hWeightedSectors[energies-1]->GetMaximumBin());
   hWeightedSectors[0]->GetYaxis()->SetRangeUser(0.1,max+100);
   for (int i=0;i<energies;i++) {
   	if (i==0) hWeightedSectors[i]->Draw();
   	if (i > 0) hWeightedSectors[i]->SetLineColor(40-i);
   	if (i > 0) hWeightedSectors[i]->Draw("same");
   }
   
   
   // construct fit function
   TF1 *logfunction = new TF1("logfunction","[0] + [1]*x",5,50);
   logfunction->SetParameter(0, 0.615);
   logfunction->SetParameter(1, 1);
   double a[14], b[14], chi2ndf[14];
   for (int k=0;k<14;k++) {
   	a[k] = 0;
	b[k] = 0;
	chi2ndf[k] = 0;
   }

   TCanvas *c2 = new TCanvas("c2","canvas 2");
   c2->Divide(4,4);
   for (int i=0;i<14;i++) {
   	c2->cd(i+1);
	for (int j=0;j<energies;j++) {
		hMod[i]->SetBinContent(j+1,hWeightedModules[j]->GetBinContent(i+1));
	}
	hMod[i]->Draw();
	for (int k=0;k<5;k++) {
		hMod[i]->Fit("logfunction","","",5,50);
	}
	TF1 *fit = hMod[i]->GetFunction("logfunction");
	a[i] = fit->GetParameter(0);	
	b[i] = fit->GetParameter(1);
	chi2ndf[i] = fit->GetChisquare()/fit->GetNDF();
	
   }
   
   for (int k=0;k<14;k++) {
   	std::cout << " parameter a[" << k << "] = " << a[k] <<std::endl;
	std::cout << " parameter b[" << k << "] = " << b[k] << std::endl;
	std::cout << " Chi2/NDF[" << k << "] = " << chi2ndf[k] << std::endl;
   	//std::cout << " slope (b/a) = " << b[k]/a[k] << std::endl;
   } 
   
   for (int k=0;k<14;k++) {
   	std::cout << " 50 bin / 5 bin for module " << k << " = " << hMod[k]->GetBinContent(energies)/hMod[k]->GetBinContent(2) << std::endl;
   }
   
   
   
   TCanvas *c3 = new TCanvas("c3","canvas 3");
   c3->Divide(1,1);
   c3->cd(1);
   max = hMod[2]->GetBinContent(hMod[2]->GetMaximumBin());
   hMod[0]->GetYaxis()->SetRangeUser(0.1,max+300);
   for (int i=0;i<14;i++) {
	for (int j=0;j<energies;j++) {
		hMod[i]->SetBinContent(j+1,hWeightedModules[j]->GetBinContent(i+1));
	}
	if (i==0) hMod[i]->Draw();
	if (i>0) hMod[i]->SetLineColor(40-i);
	if (i>0) hMod[i]->Draw("same");	
   }
   
   TCanvas *c4 = new TCanvas("c4","canvas 4");
   c4->Divide(1,1);
   c4->cd(1);
   hWeightedModules[4]->Draw(); // draw original 50 GeV shower
   TH1D *scaled20to50GeVshower = new TH1D("scaled20to50GeVshower","20 GeV upscaled to 50 GeV",14,1,15);
   for (int i=0;i<14;i++) {
   	scaled20to50GeVshower->SetBinContent(i+1,hWeightedModules[10]->GetBinContent(i+1)*0.4); // get bincontents of 20 GeV shower and scale each bin by 2.5 (50/20)
   }
   scaled20to50GeVshower->Draw("same"); // draw the upscaled 20GeV shower with original 50GeV shower
   hWeightedModules[10]->Draw("same"); // draw original 20 GeV shower to compare
   
   for (int i=0;i<14;i++) {
   	std::cout << "20/50 in module " << i << " = " << (hWeightedModules[4]->GetBinContent(i+1)/hWeightedModules[10]->GetBinContent(i+1))/0.4 << std::endl;
   }
}

void SimHits::Loop()
{

gStyle->SetPaintTextFormat("2.2f");
gROOT->ForceStyle();


int energies = 9;

TH1D *hEnergyFS[energies];
TH1D *hTotalEnergyFS[energies];
Char_t htitleEnergyFS[100];
Char_t hnameEnergyFS[100];
Char_t htitleTotalEnergyFS[100];
Char_t hnameTotalEnergyFS[100];

TH1D *hWeightedModulesFS[energies];
TH1D *hWeightedSectorsFS[energies];
Char_t htitleWeightedModulesFS[100];
Char_t hnameWeightedModulesFS[100];
Char_t htitleWeightedSectorsFS[100];
Char_t hnameWeightedSectorsFS[100];

TH1D *hEnergySL[energies];
TH1D *hTotalEnergySL[energies];
Char_t htitleEnergySL[100];
Char_t hnameEnergySL[100];
Char_t htitleTotalEnergySL[100];
Char_t hnameTotalEnergySL[100];

TH1D *hWeightedModulesSL[energies];
TH1D *hWeightedSectorsSL[energies];
Char_t htitleWeightedModulesSL[100];
Char_t hnameWeightedModulesSL[100];
Char_t htitleWeightedSectorsSL[100];
Char_t hnameWeightedSectorsSL[100];

TH2D *hMapFS[energies];
Char_t htitleMapFS[100];
Char_t hnameMapFS[100];
TH2D *hMapSL[energies];
Char_t htitleMapSL[100];
Char_t hnameMapSL[100];

for (int i=0;i<energies;i++) {
	sprintf(hnameEnergyFS,"hEnergyFS_%d",i);
	sprintf(htitleEnergyFS,"Energy of simhits at %d GeV",(i+1)*5);
	sprintf(hnameTotalEnergyFS,"hTotalenergyFS_%d",i);
	sprintf(htitleTotalEnergyFS,"Total energy of simhits at %d GeV",(i+1)*5);
	hEnergyFS[i] = new TH1D(hnameEnergyFS,htitleEnergyFS,100,0,1.);
	hTotalEnergyFS[i] = new TH1D(hnameTotalEnergyFS,htitleTotalEnergyFS,100,0,1.);
	
	sprintf(hnameWeightedModulesFS,"hWeightedModulesFS_%d",i);
	sprintf(htitleWeightedModulesFS,"Energy weighted module distribution of simhits at %d GeV",(i+1)*5);
	hWeightedModulesFS[i] = new TH1D(hnameWeightedModulesFS,htitleWeightedModulesFS,14,1,15);
	sprintf(hnameWeightedSectorsFS,"hWeightedSectorsFS_%d",i);
	sprintf(htitleWeightedSectorsFS,"Energy weighted sector distribution of simhits at %d GeV",(i+1)*5);
	hWeightedSectorsFS[i] = new TH1D(hnameWeightedSectorsFS,htitleWeightedSectorsFS,16,1,17);
	
	sprintf(hnameEnergySL,"hEnergySL_%d",i);
	sprintf(htitleEnergySL,"Energy of simhits at %d GeV",(i+1)*5);
	sprintf(hnameTotalEnergySL,"hTotalenergySL_%d",i);
	sprintf(htitleTotalEnergySL,"Total energy of simhits at %d GeV",(i+1)*5);
	hEnergySL[i] = new TH1D(hnameEnergySL,htitleEnergySL,100,0,1.);
	hTotalEnergySL[i] = new TH1D(hnameTotalEnergySL,htitleTotalEnergySL,100,0,1.);
	
	sprintf(hnameWeightedModulesSL,"hWeightedModulesSL_%d",i);
	sprintf(htitleWeightedModulesSL,"Energy weighted module distribution of simhits at %d GeV",(i+1)*5);
	hWeightedModulesSL[i] = new TH1D(hnameWeightedModulesSL,htitleWeightedModulesSL,14,1,15);
	sprintf(hnameWeightedSectorsSL,"hWeightedSectorsSL_%d",i);
	sprintf(htitleWeightedSectorsSL,"Energy weighted sector distribution of simhits at %d GeV",(i+1)*5);
	hWeightedSectorsSL[i] = new TH1D(hnameWeightedSectorsSL,htitleWeightedSectorsSL,16,1,17);
	
	sprintf(hnameMapFS,"hMapFS_%d",i);
	sprintf(htitleMapFS,"Mapping of simhits at %d GeV",(i+1)*5);
	hMapFS[i] = new TH2D(hnameMapFS,htitleMapFS,16,1,17,14,1,15);
	sprintf(hnameMapSL,"hMapSL_%d",i);
	sprintf(htitleMapSL,"Mapping of simhits at %d GeV",(i+1)*5);
	hMapSL[i] = new TH2D(hnameMapSL,htitleMapSL,16,1,17,14,1,15);
	
}

TH1D *hRatios = new TH1D("hRatios","SL/FS ratios",energies,5,45);
TH1D *hResolutionFS = new TH1D("hResolutionFS","Resolutions of FS and SL",energies,5,50);
TH1D *hResolutionSL = new TH1D("hResolutionSL","Resolution of FS and SL",energies,5,50);
//TH1D *hEoverPi = new TH1D("hEoverPi","e/pi ratios of FS and SL",energies,5,50);

int nEntries[2*energies];
   for (int i=0;i<2*energies;i++) {
   	nEntries[i] = 0;
   }

//   In a ROOT session, you can do:
//      Root > .L SimHits.C
//      Root > SimHits t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     
      
      int energybin = 0;
      for (int k=0;k<2*energies;k++) {
      	if (jentry >= k*10000 && jentry < (k+1)*10000) energybin = k; 
      }
      //std::cout << " energybin = " << energybin << std::endl;
      
      nEntries[energybin] = nEntries[energybin] + 1;
      
      if (energybin+1 > energies) {
      		for (size_t i=0;i<simhit_energy->size();i++) {
			hWeightedModulesSL[energybin-energies]->Fill((*simhit_module)[i],(*simhit_energy)[i]);
			hWeightedSectorsSL[energybin-energies]->Fill((*simhit_sector)[i],(*simhit_energy)[i]);
			hEnergySL[energybin-energies]->Fill((*simhit_energy)[i]);
			hMapSL[energybin-energies]->Fill((*simhit_sector)[i],(*simhit_module)[i],(*simhit_energy)[i]);
      		}
      		hTotalEnergySL[energybin-energies]->Fill(simhit_etot);
      
      } else {
      		for (size_t i=0;i<simhit_energy->size();i++) {
			hWeightedModulesFS[energybin]->Fill((*simhit_module)[i],(*simhit_energy)[i]);
			hWeightedSectorsFS[energybin]->Fill((*simhit_sector)[i],(*simhit_energy)[i]);
			hEnergyFS[energybin]->Fill((*simhit_energy)[i]);
			hMapFS[energybin]->Fill((*simhit_sector)[i],(*simhit_module)[i],(*simhit_energy)[i]);
      		}
      		hTotalEnergyFS[energybin]->Fill(simhit_etot);
      
      }
   }
   
   for (int i=0;i<2*energies;i++) {
   	std::cout << "There are " << nEntries[i] << " entries for bin " << i << std::endl;
   }
   
   /*
   // scale all with nEntries
   hWeightedModulesFS->Scale(1./nFSEntries);
   hWeightedModulesSL->Scale(1./nSLEntries);
   hWeightedModulesNewSL->Scale(1./nNewSLEntries);
   
   hWeightedSectorsFS->Scale(1./nFSEntries);
   hWeightedSectorsSL->Scale(1./nSLEntries);
   hWeightedSectorsNewSL->Scale(1./nNewSLEntries);
   
   hEnergyFS->Scale(1./nFSEntries);
   hEnergySL->Scale(1./nSLEntries);
   hEnergyNewSL->Scale(1./nNewSLEntries);
   
   hTotalEnergyFS->Scale(1./nFSEntries);
   hTotalEnergySL->Scale(1./nSLEntries);
   hTotalEnergyNewSL->Scale(1./nNewSLEntries);
   */
   
   
   TCanvas *cCanvas[energies];
   Char_t ctitle[100];
   Char_t cname[100];
   
   for (int i=0;i<energies;i++) {
        sprintf(cname,"cCanvas_%d",i);
	sprintf(ctitle,"Distributions of energy %d GeV",(i+1)*5);
	cCanvas[i] = new TCanvas(cname,ctitle);
	cCanvas[i]->Divide(3,2);
        cCanvas[i]->cd(1);
	hWeightedModulesFS[i]->GetXaxis()->SetTitle("Modules");
	hWeightedModulesFS[i]->GetYaxis()->SetTitle("Energy");
        hWeightedModulesFS[i]->Draw();
        hWeightedModulesSL[i]->SetLineColor(2);
        hWeightedModulesSL[i]->Draw("same");
 
   	cCanvas[i]->cd(2);
	hWeightedSectorsFS[i]->GetXaxis()->SetTitle("Sectors");
	hWeightedSectorsFS[i]->GetYaxis()->SetTitle("Energy");
        hWeightedSectorsFS[i]->Draw();
        hWeightedSectorsSL[i]->SetLineColor(2);
        hWeightedSectorsSL[i]->Draw("same");

        TVirtualPad* c1_3 = cCanvas[i]->cd(3);
        c1_3->SetLogy();
	hEnergyFS[i]->GetXaxis()->SetTitle("Energy");
	hEnergyFS[i]->GetYaxis()->SetTitle("Number of hits");
        hEnergyFS[i]->Draw();
        hEnergySL[i]->SetLineColor(2);
        hEnergySL[i]->Draw("same");

        TVirtualPad* c1_4 = cCanvas[i]->cd(4);
        c1_4->SetLogy();
	hTotalEnergyFS[i]->GetXaxis()->SetTitle("Energy");
	hTotalEnergyFS[i]->GetYaxis()->SetTitle("Number of events");
        hTotalEnergyFS[i]->Draw();
        hTotalEnergySL[i]->SetLineColor(2);
        hTotalEnergySL[i]->Draw("same"); 
 
        TVirtualPad* c1_5 = cCanvas[i]->cd(5);
        c1_5->SetLogy();
	hWeightedModulesFS[i]->GetXaxis()->SetTitle("Modules");
	hWeightedModulesFS[i]->GetYaxis()->SetTitle("Energy");
        hWeightedModulesFS[i]->Draw();
        hWeightedModulesSL[i]->SetLineColor(2);
        hWeightedModulesSL[i]->Draw("same");

        TVirtualPad* c1_6 = cCanvas[i]->cd(6);
        c1_6->SetLogy();
	hWeightedSectorsFS[i]->GetXaxis()->SetTitle("Sectors");
	hWeightedSectorsFS[i]->GetYaxis()->SetTitle("Energy");
        hWeightedSectorsFS[i]->Draw();
        hWeightedSectorsSL[i]->SetLineColor(2);
        hWeightedSectorsSL[i]->Draw("same");

   }	
   
   for (int i=0;i<energies;i++) {
   	hRatios->SetBinContent(i+1,hTotalEnergySL[i]->GetMean()/hTotalEnergyFS[i]->GetMean());
	hRatios->SetBinError(i+1,CalculateRatioError(hTotalEnergySL[i]->GetMean()/hTotalEnergyFS[i]->GetMean(),hTotalEnergySL[i]->GetMean(),hTotalEnergyFS[i]->GetMean(),hTotalEnergySL[i]->GetMeanError(),hTotalEnergyFS[i]->GetMeanError()));
	hResolutionFS->SetBinContent(i+1,hTotalEnergyFS[i]->GetRMS()/hTotalEnergyFS[i]->GetMean());
	hResolutionSL->SetBinContent(i+1,hTotalEnergySL[i]->GetRMS()/hTotalEnergySL[i]->GetMean());
        hResolutionFS->SetBinError(i+1,CalculateRatioError(hTotalEnergyFS[i]->GetRMS()/hTotalEnergyFS[i]->GetMean(),hTotalEnergyFS[i]->GetRMS(),hTotalEnergyFS[i]->GetMean(),hTotalEnergyFS[i]->GetRMSError(),hTotalEnergyFS[i]->GetMeanError()));
	hResolutionSL->SetBinError(i+1,CalculateRatioError(hTotalEnergySL[i]->GetRMS()/hTotalEnergySL[i]->GetMean(),hTotalEnergySL[i]->GetRMS(),hTotalEnergySL[i]->GetMean(),hTotalEnergySL[i]->GetRMSError(),hTotalEnergySL[i]->GetMeanError()));
   }
   
   TCanvas *cMaps[energies];
   Char_t ctitleMaps[100];
   Char_t cnameMaps[100];
   
   for (int i=0;i<energies;i++) {
   	sprintf(cnameMaps,"cMaps_%d",i);
	sprintf(ctitleMaps,"Ratio SL/FS of all channels at %d GeV",(i+1)*5);
	cMaps[i] = new TCanvas(cnameMaps,ctitleMaps);
   	cMaps[i]->cd(1);
	hMapSL[i]->Divide(hMapFS[i]);
	hMapSL[i]->Draw("coltext");
   }
   
   
   TCanvas *cCanvas2 = new TCanvas("cCanvas2","Ratios and resolutions");
   cCanvas2->Divide(2,1);
   cCanvas2->cd(1);
   hRatios->GetXaxis()->SetTitle("Energies");
   hRatios->GetYaxis()->SetTitle("SL/FS ratio");
   hRatios->Draw();
   cCanvas2->cd(2);
   hResolutionFS->GetXaxis()->SetTitle("Energies");
   hResolutionFS->GetYaxis()->SetTitle("Resolution (RMS/Mean)");
   hResolutionFS->Draw();
   hResolutionSL->SetLineColor(2);
   hResolutionSL->Draw("same");
	
   
   
   
}
