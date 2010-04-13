

#define CastorDigi_cxx
#include "CastorDigi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#define M_PI 3.14159265358979323846

void CastorDigi::Loop(int range)
{

 ////////////////////
  //  set style
  ////////////////////
  gROOT  -> SetStyle("Plain");
  gStyle -> SetMarkerStyle(20);
  gStyle -> SetMarkerSize(1);
  gStyle -> SetTextSize(1);
  //gStyle -> SetOptStat("eMR");//"iourmen");
  gStyle -> SetOptStat("");
  gStyle -> SetLineWidth(1.1);//gStyle->GetLineWidth()*1.5); // 2
  gStyle -> SetHistLineWidth(1.4);//gStyle->GetHistLineWidth()*1.5);// 2
  gStyle -> SetPadLeftMargin(0.25);
  gStyle -> SetPadRightMargin(0.1);
  gStyle -> SetPadBottomMargin(0.25);
  gStyle -> SetPadTopMargin(0.11);
  gStyle -> SetEndErrorSize(5);
  gStyle -> SetCanvasBorderSize(2);
  gStyle -> SetHistFillColor(kGray);
  gStyle -> SetHistMinimumZero(kTRUE);
  gStyle -> SetTitleOffset(2,"y");
  gStyle -> SetLegendBorderSize(0);
  gROOT  -> ForceStyle();


// declare everything...

int n900Events = 0;
int n900CaloInclusive = 0;
int n900CaloDijet = 0;
int n900PFInclusive = 0;
int n900PFDijet = 0;

int n900MCEvents = 0;
int n900MCCaloInclusive = 0;
int n900MCCaloDijet = 0;
int n900MCPFInclusive = 0;
int n900MCPFDijet = 0;

int n2360Events = 0;
int n2360CaloInclusive = 0;
int n2360CaloDijet = 0;
int n2360PFInclusive = 0;
int n2360PFDijet = 0;

int n2360MCEvents = 0;
int n2360MCCaloInclusive = 0;
int n2360MCCaloDijet = 0;
int n2360MCPFInclusive = 0;
int n2360MCPFDijet = 0;

int MCevent = 0;

TH1D * h2360SignalTot = new TH1D("h2360SignalTot","Total Signal in CASTOR for MB at 2360 GeV;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360SignalTotPFDijet = new TH1D("h2360SignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 2360 GeV;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360SignalTotPFInclusive = new TH1D("h2360SignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 2360 GeV;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360SignalTotCaloDijet = new TH1D("h2360SignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 2360 GeV;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360SignalTotCaloInclusive = new TH1D("h2360SignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 2360 GeV;Signal (ADC);Events",105,-100.,4000);

TH1D * h2360MCSignalTot = new TH1D("h2360MCSignalTot","Total Signal in CASTOR for MB at 2360 GeV MC;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360MCSignalTotPFDijet = new TH1D("h2360MCSignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 2360 GeV MC;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360MCSignalTotPFInclusive = new TH1D("h2360MCSignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 2360 GeV MC;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360MCSignalTotCaloDijet = new TH1D("h2360MCSignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 2360 GeV MC;Signal (ADC);Events",105,-100.,4000);
TH1D * h2360MCSignalTotCaloInclusive = new TH1D("h2360MCSignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 2360 GeV MC;Signal (ADC);Events",105,-100.,4000);

TH1D * h900SignalTot = new TH1D("h900SignalTot","Total Signal in CASTOR for MB at 900 GeV;Signal (ADC);Events",105,-100.,2000);
TH1D * h900SignalTotPFDijet = new TH1D("h900SignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 900 GeV;Signal (ADC);Events",105,-100.,2000);
TH1D * h900SignalTotPFInclusive = new TH1D("h900SignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 900 GeV;Signal (ADC);Events",105,-100.,2000);
TH1D * h900SignalTotCaloDijet = new TH1D("h900SignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 900 GeV;Signal (ADC);Events",105,-100.,2000);
TH1D * h900SignalTotCaloInclusive = new TH1D("h900SignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 900 GeV;Signal (ADC);Events",105,-100.,2000);

TH1D * h900MCSignalTot = new TH1D("h900MCSignalTot","Total Signal in CASTOR for MB at 900 GeV MC;Signal (ADC);Events",105,-100.,2000);
TH1D * h900MCSignalTotPFDijet = new TH1D("h900MCSignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 900 GeV MC;Signal (ADC);Events",105,-100.,2000);
TH1D * h900MCSignalTotPFInclusive = new TH1D("h900MCSignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 900 GeV MC;Signal (ADC);Events",105,-100.,2000);
TH1D * h900MCSignalTotCaloDijet = new TH1D("h900MCSignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 900 GeV MC;Signal (ADC);Events",105,-100.,2000);
TH1D * h900MCSignalTotCaloInclusive = new TH1D("h900MCSignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 900 GeV MC;Signal (ADC);Events",105,-100.,2000);



TH1D * hPFDijetPt = new TH1D("hPFDijetPt","PF Dijet Pt distribution;Pt (GeV);Events",70,0,70);
TH1D * hPFInclusivePt = new TH1D("hPFInclusivePt","PF Inclusive Pt distribution;Pt (GeV);Events",70,0,70);
TH1D * hPFDijetEta = new TH1D("hPFDijetEta","PF Dijet Eta distribution;#eta;Events",60,-3,3);
TH1D * hPFInclusiveEta = new TH1D("hPFInclusiveEta","PF Inclusive Eta distribution;#eta;Events",60,-3,3);
TH1D * hPFDijetPhi = new TH1D("hPFDijetPhi","PF Dijet Phi distribution;#phi;Events",20,-M_PI,M_PI);
TH1D * hPFInclusivePhi = new TH1D("hPFInclusivePhi","PF Inclusive Phi distribution;#phi;Events",20,-M_PI,M_PI);


// variables for manual mean calculation of distribution
double sum900 = 0;
double sum900MC = 0;
double sum2360 = 0;
double sum2360MC = 0;
double sum900PFInclusive = 0;
double sum900MCPFInclusive = 0;
double sum2360PFInclusive = 0;
double sum2360MCPFInclusive = 0;



//   In a ROOT session, you can do:
//      Root > .L CastorDigi.C
//      Root > CastorDigi t
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
      
      
      
      // select 900 GeV runs for data
      if (runNumber == 124020 || runNumber == 124022 || runNumber == 124023 || 
      runNumber == 124024 || runNumber == 124027 || runNumber == 124030) {
      
      		// calculate total numbers
      		n900Events = n900Events +1; 
      		if (isCaloInclusive == 1) n900CaloInclusive += 1;
      		if (isCaloDijet == 1) n900CaloDijet += 1;
      		if (isPFInclusive == 1) n900PFInclusive += 1;
      		if (isPFDijet == 1) n900PFDijet += 1;
      
       
       		double SignalTot = 0;
      		if (range == 15) {	
      			// calculate total signal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					SignalTot = SignalTot + signal[i];
				}
      			}
		}
		if (range == 26) {
			// calculate total signal in CASTOR
			// modules 2-6
      			for (int i=16;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<96;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[96-i];
      			}
		}
		if (range == 19) {
			// calculate total signal in CASTOR
			// modules 1-9
      			for (int i=0;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<144;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[144-i];
      			}
		}
      
      		// fill total signal histograms
      		h900SignalTot->Fill(SignalTot);
      		if (isPFDijet == 1) h900SignalTotPFDijet->Fill(SignalTot);
      		if (isPFInclusive == 1) h900SignalTotPFInclusive->Fill(SignalTot);
      		if (isCaloDijet == 1) h900SignalTotCaloDijet->Fill(SignalTot);
      		if (isCaloInclusive == 1) h900SignalTotCaloInclusive->Fill(SignalTot);
		
		sum900 = sum900 + SignalTot;
		if (isPFInclusive == 1) sum900PFInclusive = sum900PFInclusive + SignalTot;
      }
      
      // select 2360 GeV run for data
      if (runNumber == 124120 ) {
      
      		// calculate total numbers
      		n2360Events = n2360Events +1; 
      		if (isCaloInclusive == 1) n2360CaloInclusive += 1;
      		if (isCaloDijet == 1) n2360CaloDijet += 1;
      		if (isPFInclusive == 1) n2360PFInclusive += 1;
      		if (isPFDijet == 1) n2360PFDijet += 1;
      
      		
		double SignalTot = 0;
      		if (range == 15) {	
      			// calculate total signal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					SignalTot = SignalTot + signal[i];
				}
      			}
		}
		if (range == 26) {
			// calculate total signal in CASTOR
			// modules 2-6
      			for (int i=16;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<96;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[96-i];
      			}
		}
		if (range == 19) {
			// calculate total signal in CASTOR
			// modules 1-9
      			for (int i=0;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<144;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[144-i];
      			}
		}
      
      		// fill total signal histograms
      		h2360SignalTot->Fill(SignalTot);
      		if (isPFDijet == 1) h2360SignalTotPFDijet->Fill(SignalTot);
      		if (isPFInclusive == 1) h2360SignalTotPFInclusive->Fill(SignalTot);
      		if (isCaloDijet == 1) h2360SignalTotCaloDijet->Fill(SignalTot);
      		if (isCaloInclusive == 1) h2360SignalTotCaloInclusive->Fill(SignalTot);
		
		sum2360 = sum2360 + SignalTot;
		if (isPFInclusive == 1) sum2360PFInclusive = sum2360PFInclusive + SignalTot;
      }
      
      // select run for MC
      if (runNumber == 1 ) {
		
		if (MCevent < 30496) {
      
      		// calculate total numbers
      		n900MCEvents = n900MCEvents +1; 
      		if (isCaloInclusive == 1) n900MCCaloInclusive += 1;
      		if (isCaloDijet == 1) n900MCCaloDijet += 1;
      		if (isPFInclusive == 1) n900MCPFInclusive += 1;
      		if (isPFDijet == 1) n900MCPFDijet += 1;
      
      		
      		double SignalTot = 0;
      		if (range == 15) {	
      			// calculate total signal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					SignalTot = SignalTot + signal[i];
				}
      			}
		}
		if (range == 26) {
			// calculate total signal in CASTOR
			// modules 2-6
      			for (int i=16;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<96;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[96-i];
      			}
		}
		if (range == 19) {
			// calculate total signal in CASTOR
			// modules 1-9
      			for (int i=0;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<144;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[144-i];
      			}
		}
      
      		// fill total signal histograms
      		h900MCSignalTot->Fill(SignalTot);
      		if (isPFDijet == 1) h900MCSignalTotPFDijet->Fill(SignalTot);
      		if (isPFInclusive == 1) h900MCSignalTotPFInclusive->Fill(SignalTot);
      		if (isCaloDijet == 1) h900MCSignalTotCaloDijet->Fill(SignalTot);
      		if (isCaloInclusive == 1) h900MCSignalTotCaloInclusive->Fill(SignalTot);
		
		sum900MC = sum900MC + SignalTot;
		if (isPFInclusive == 1) sum900MCPFInclusive = sum900MCPFInclusive + SignalTot;
		
		} else {
		
		// calculate total numbers
      		n2360MCEvents = n2360MCEvents +1; 
      		if (isCaloInclusive == 1) n2360MCCaloInclusive += 1;
      		if (isCaloDijet == 1) n2360MCCaloDijet += 1;
      		if (isPFInclusive == 1) n2360MCPFInclusive += 1;
      		if (isPFDijet == 1) n2360MCPFDijet += 1;
      
      		
      		double SignalTot = 0;
      		if (range == 15) {	
      			// calculate total signal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					SignalTot = SignalTot + signal[i];
				}
      			}
		}
		if (range == 26) {
			// calculate total signal in CASTOR
			// modules 2-6
      			for (int i=16;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<96;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[96-i];
      			}
		}
		if (range == 19) {
			// calculate total signal in CASTOR
			// modules 1-9
      			for (int i=0;i<80;i++) {
					SignalTot = SignalTot + signal[i];
      			}
			for (int i=80;i<144;i++) {
					SignalTot = SignalTot + sumADC[i] - 4*pedestal[144-i];
      			}
		}
      
      		// fill total signal histograms
      		h2360MCSignalTot->Fill(SignalTot);
      		if (isPFDijet == 1) h2360MCSignalTotPFDijet->Fill(SignalTot);
      		if (isPFInclusive == 1) h2360MCSignalTotPFInclusive->Fill(SignalTot);
      		if (isCaloDijet == 1) h2360MCSignalTotCaloDijet->Fill(SignalTot);
      		if (isCaloInclusive == 1) h2360MCSignalTotCaloInclusive->Fill(SignalTot);
		
		sum2360MC = sum2360MC + SignalTot;
		if (isPFInclusive == 1) sum2360MCPFInclusive = sum2360MCPFInclusive + SignalTot;
		
		}
		
		MCevent = MCevent +1;
      }
   }
   
   
   ///////////////////////////
   // Cout some count numbers
   ///////////////////////////
   
   std::cout << "900 GeV results: " << std::endl;
   std::cout << "n900Events = " << n900Events << std::endl;
   std::cout << "n900CaloInclusive = " << n900CaloInclusive << std::endl;
   std::cout << "n900CaloDijet = " << n900CaloDijet << std::endl;
   std::cout << "n900PFInclusive = " << n900PFInclusive << std::endl;
   std::cout << "n900PFDijet = " << n900PFDijet << std::endl;
   
   std::cout << "2360 GeV results: " << std::endl;
   std::cout << "n2360Events = " << n2360Events << std::endl;
   std::cout << "n2360CaloInclusive = " << n2360CaloInclusive << std::endl;
   std::cout << "n2360CaloDijet = " << n2360CaloDijet << std::endl;
   std::cout << "n2360PFInclusive = " << n2360PFInclusive << std::endl;
   std::cout << "n2360PFDijet = " << n2360PFDijet << std::endl;
   
   std::cout << "900MC GeV results: " << std::endl;
   std::cout << "n900MCEvents = " << n900MCEvents << std::endl;
   std::cout << "n900MCCaloInclusive = " << n900MCCaloInclusive << std::endl;
   std::cout << "n900MCCaloDijet = " << n900MCCaloDijet << std::endl;
   std::cout << "n900MCPFInclusive = " << n900MCPFInclusive << std::endl;
   std::cout << "n900MCPFDijet = " << n900MCPFDijet << std::endl;
   
   std::cout << "2360MC GeV results: " << std::endl;
   std::cout << "n2360MCEvents = " << n2360MCEvents << std::endl;
   std::cout << "n2360MCCaloInclusive = " << n2360MCCaloInclusive << std::endl;
   std::cout << "n2360MCCaloDijet = " << n2360MCCaloDijet << std::endl;
   std::cout << "n2360MCPFInclusive = " << n2360MCPFInclusive << std::endl;
   std::cout << "n2360MCPFDijet = " << n2360MCPFDijet << std::endl;
   
   // check ratio calculation by using manual means
   
   double sumRatio900PFInclusive = (sum900PFInclusive/n900PFInclusive)/(sum900/n900Events);
   std::cout << "sumRatio900PFInclusive = " << sumRatio900PFInclusive << std::endl; 
   double sumRatio900MCPFInclusive = (sum900MCPFInclusive/n900MCPFInclusive)/(sum900MC/n900MCEvents);
   std::cout << "sumRatio900MCPFInclusive = " << sumRatio900MCPFInclusive << std::endl; 
   double sumRatio2360PFInclusive = (sum2360PFInclusive/n2360PFInclusive)/(sum2360/n2360Events);
   std::cout << "sumRatio2360PFInclusive = " << sumRatio2360PFInclusive << std::endl; 
   double sumRatio2360MCPFInclusive = (sum2360MCPFInclusive/n2360MCPFInclusive)/(sum2360MC/n2360MCEvents);
   std::cout << "sumRatio2360MCPFInclusive = " << sumRatio2360MCPFInclusive << std::endl; 
   
   //////////////////////
   // Plot CASTOR stuff
   //////////////////////
   
   TCanvas *c1_900 = new TCanvas("c1_900","Total Signal distributions in CASTOR");
   c1_900->Divide(3,2);
   c1_900->cd(1);
   
   h900MCSignalTot->SetFillColor(kGray);
   h900MCSignalTot->SetFillStyle(1001);
   h900MCSignalTot->SetMarkerStyle(0);
   h900MCSignalTot->Scale(h900SignalTot->Integral()/h900MCSignalTot->Integral());
   h900MCSignalTot->Draw("hist");
   h900SignalTot->SetFillColor(0);
   h900SignalTot->SetFillStyle(0);
   h900SignalTot->SetMarkerStyle(1);
   h900SignalTot->Draw("samee");
   c1_900->cd(2);
   h900MCSignalTotPFDijet->SetFillColor(kGray);
   h900MCSignalTotPFDijet->SetFillStyle(1001);
   h900MCSignalTotPFDijet->SetMarkerStyle(0);
   h900MCSignalTotPFDijet->Scale(h900SignalTotPFDijet->Integral()/h900MCSignalTotPFDijet->Integral());
   h900MCSignalTotPFDijet->Draw("hist");
   h900SignalTotPFDijet->SetFillColor(0);
   h900SignalTotPFDijet->SetFillStyle(0);
   h900SignalTotPFDijet->SetMarkerStyle(1);
   h900SignalTotPFDijet->Draw("samee");
   c1_900->cd(3);
   h900MCSignalTotPFInclusive->SetFillColor(kGray);
   h900MCSignalTotPFInclusive->SetFillStyle(1001);
   h900MCSignalTotPFInclusive->SetMarkerStyle(0);
   h900MCSignalTotPFInclusive->Scale(h900SignalTotPFInclusive->Integral()/h900MCSignalTotPFInclusive->Integral());
   h900MCSignalTotPFInclusive->Draw("hist");
   h900SignalTotPFInclusive->SetFillColor(0);
   h900SignalTotPFInclusive->SetFillStyle(0);
   h900SignalTotPFInclusive->SetMarkerStyle(1);
   h900SignalTotPFInclusive->Draw("samee");
   c1_900->cd(4);
   h900MCSignalTotCaloDijet->SetFillColor(kGray);
   h900MCSignalTotCaloDijet->SetFillStyle(1001);
   h900MCSignalTotCaloDijet->SetMarkerStyle(0);
   h900MCSignalTotCaloDijet->Scale(h900SignalTotCaloDijet->Integral()/h900MCSignalTotCaloDijet->Integral());
   h900MCSignalTotCaloDijet->Draw("hist");
   h900SignalTotCaloDijet->SetFillColor(0);
   h900SignalTotCaloDijet->SetFillStyle(0);
   h900SignalTotCaloDijet->SetMarkerStyle(1);
   h900SignalTotCaloDijet->Draw("samee");
   c1_900->cd(5);
   h900MCSignalTotCaloInclusive->SetFillColor(kGray);
   h900MCSignalTotCaloInclusive->SetFillStyle(1001);
   h900MCSignalTotCaloInclusive->SetMarkerStyle(0);
   h900MCSignalTotCaloInclusive->Scale(h900SignalTotCaloInclusive->Integral()/h900MCSignalTotCaloInclusive->Integral());
   h900MCSignalTotCaloInclusive->Draw("hist");
   h900SignalTotCaloInclusive->SetFillColor(0);
   h900SignalTotCaloInclusive->SetFillStyle(0);
   h900SignalTotCaloInclusive->SetMarkerStyle(1);
   h900SignalTotCaloInclusive->Draw("samee");

   
   TCanvas *c1_2360 = new TCanvas("c1_2360","Total Signal distributions in CASTOR");
   c1_2360->Divide(3,2);
   c1_2360->cd(1);
   h2360MCSignalTot->SetFillColor(kGray);
   h2360MCSignalTot->SetFillStyle(1001);
   h2360MCSignalTot->SetMarkerStyle(0);
   h2360MCSignalTot->Scale(h2360SignalTot->Integral()/h2360MCSignalTot->Integral());
   h2360MCSignalTot->Draw("hist");
   h2360SignalTot->SetFillColor(0);
   h2360SignalTot->SetFillStyle(0);
   h2360SignalTot->SetMarkerStyle(1);
   h2360SignalTot->Draw("samee");
   c1_2360->cd(2);
   h2360MCSignalTotPFDijet->SetFillColor(kGray);
   h2360MCSignalTotPFDijet->SetFillStyle(1001);
   h2360MCSignalTotPFDijet->SetMarkerStyle(0);
   h2360MCSignalTotPFDijet->Scale(h2360SignalTotPFDijet->Integral()/h2360MCSignalTotPFDijet->Integral());
   h2360MCSignalTotPFDijet->Draw("hist");
   h2360SignalTotPFDijet->SetFillColor(0);
   h2360SignalTotPFDijet->SetFillStyle(0);
   h2360SignalTotPFDijet->SetMarkerStyle(1);
   h2360SignalTotPFDijet->Draw("samee");
   c1_2360->cd(3);
   h2360MCSignalTotPFInclusive->SetFillColor(kGray);
   h2360MCSignalTotPFInclusive->SetFillStyle(1001);
   h2360MCSignalTotPFInclusive->SetMarkerStyle(0);
   h2360MCSignalTotPFInclusive->Scale(h2360SignalTotPFInclusive->Integral()/h2360MCSignalTotPFInclusive->Integral());
   h2360MCSignalTotPFInclusive->Draw("hist");
   h2360SignalTotPFInclusive->SetFillColor(0);
   h2360SignalTotPFInclusive->SetFillStyle(0);
   h2360SignalTotPFInclusive->SetMarkerStyle(1);
   h2360SignalTotPFInclusive->Draw("samee");
   c1_2360->cd(4);
   h2360MCSignalTotCaloDijet->SetFillColor(kGray);
   h2360MCSignalTotCaloDijet->SetFillStyle(1001);
   h2360MCSignalTotCaloDijet->SetMarkerStyle(0);
   h2360MCSignalTotCaloDijet->Scale(h2360SignalTotCaloDijet->Integral()/h2360MCSignalTotCaloDijet->Integral());
   h2360MCSignalTotCaloDijet->Draw("hist");
   h2360SignalTotCaloDijet->SetFillColor(0);
   h2360SignalTotCaloDijet->SetFillStyle(0);
   h2360SignalTotCaloDijet->SetMarkerStyle(1);
   h2360SignalTotCaloDijet->Draw("samee");
   c1_2360->cd(5);
   h2360MCSignalTotCaloInclusive->SetFillColor(kGray);
   h2360MCSignalTotCaloInclusive->SetFillStyle(1001);
   h2360MCSignalTotCaloInclusive->SetMarkerStyle(0);
   h2360MCSignalTotCaloInclusive->Scale(h2360SignalTotCaloInclusive->Integral()/h2360MCSignalTotCaloInclusive->Integral());
   h2360MCSignalTotCaloInclusive->Draw("hist");
   h2360SignalTotCaloInclusive->SetFillColor(0);
   h2360SignalTotCaloInclusive->SetFillStyle(0);
   h2360SignalTotCaloInclusive->SetMarkerStyle(1);
   h2360SignalTotCaloInclusive->Draw("samee");
   
   ///////////////////////
   // Plot Jet stuff
   ///////////////////////
   /*
   TCanvas *cJets = new TCanvas("cJets","Central Jet distributions");
   cJets->Divide(3,2);
   cJets->cd(1);
   hPFDijetPt->Draw();
   cJets->cd(2);
   hPFDijetEta->Draw();
   cJets->cd(3);
   hPFDijetPhi->Draw();
   cJets->cd(4);
   hPFInclusivePt->Draw();
   cJets->cd(5);
   hPFInclusiveEta->Draw();
   cJets->cd(6);
   hPFInclusivePhi->Draw();
   */
   
   //////////////////////
   // Calculate ratios
   //////////////////////
   
   double Mean900MB = h900SignalTot->GetMean();
   double Mean900MB_error = h900SignalTot->GetMeanError();
   
   double Mean900PFDijet = h900SignalTotPFDijet->GetMean();
   double Mean900PFInclusive = h900SignalTotPFInclusive->GetMean();
   
   double Mean900CaloDijet = h900SignalTotCaloDijet->GetMean();
   double Mean900CaloInclusive = h900SignalTotCaloInclusive->GetMean();
   
   double Mean900PFDijet_error = h900SignalTotPFDijet->GetMeanError();
   double Mean900PFInclusive_error = h900SignalTotPFInclusive->GetMeanError();
   
   double Mean900CaloDijet_error = h900SignalTotCaloDijet->GetMeanError();
   double Mean900CaloInclusive_error = h900SignalTotCaloInclusive->GetMeanError();
   
   double Ratio900PFDijet = Mean900PFDijet/Mean900MB;
   double Ratio900PFInclusive = Mean900PFInclusive/Mean900MB;
   
   double Ratio900CaloDijet = Mean900CaloDijet/Mean900MB;
   double Ratio900CaloInclusive = Mean900CaloInclusive/Mean900MB;
   
   double Ratio900PFDijet_error = Ratio900PFDijet*Ratio900PFDijet*((Mean900PFDijet_error*Mean900PFDijet_error)/(Mean900PFDijet*Mean900PFDijet) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900PFDijet_error = sqrt(Ratio900PFDijet_error);
   
   double Ratio900PFInclusive_error = Ratio900PFInclusive*Ratio900PFInclusive*((Mean900PFInclusive_error*Mean900PFInclusive_error)/(Mean900PFInclusive*Mean900PFInclusive) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900PFInclusive_error = sqrt(Ratio900PFInclusive_error);
   
   double Ratio900CaloDijet_error = Ratio900CaloDijet*Ratio900CaloDijet*((Mean900CaloDijet_error*Mean900CaloDijet_error)/(Mean900CaloDijet*Mean900CaloDijet) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900CaloDijet_error = sqrt(Ratio900CaloDijet_error);
   
   double Ratio900CaloInclusive_error = Ratio900CaloInclusive*Ratio900CaloInclusive*((Mean900CaloInclusive_error*Mean900CaloInclusive_error)/(Mean900CaloInclusive*Mean900CaloInclusive) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900CaloInclusive_error = sqrt(Ratio900CaloInclusive_error);
   
   std::cout << "Ratio900 PF Dijet/MB = " << Ratio900PFDijet << " +- " << Ratio900PFDijet_error << std::endl;
   std::cout << "Ratio900 PF Inclusive/MB = " << Ratio900PFInclusive << " +- " << Ratio900PFInclusive_error << std::endl;
   std::cout << "Ratio900 Calo Dijet/MB = " << Ratio900CaloDijet << " +- " << Ratio900CaloDijet_error << std::endl;
   std::cout << "Ratio900 Calo Inclusive/MB = " << Ratio900CaloInclusive << " +- " << Ratio900CaloInclusive_error << std::endl;
   
   double Mean2360MB = h2360SignalTot->GetMean();
   double Mean2360MB_error = h2360SignalTot->GetMeanError();
   
   double Mean2360PFDijet = h2360SignalTotPFDijet->GetMean();
   double Mean2360PFInclusive = h2360SignalTotPFInclusive->GetMean();
   
   double Mean2360CaloDijet = h2360SignalTotCaloDijet->GetMean();
   double Mean2360CaloInclusive = h2360SignalTotCaloInclusive->GetMean();
   
   double Mean2360PFDijet_error = h2360SignalTotPFDijet->GetMeanError();
   double Mean2360PFInclusive_error = h2360SignalTotPFInclusive->GetMeanError();
   
   double Mean2360CaloDijet_error = h2360SignalTotCaloDijet->GetMeanError();
   double Mean2360CaloInclusive_error = h2360SignalTotCaloInclusive->GetMeanError();
   
   double Ratio2360PFDijet = Mean2360PFDijet/Mean2360MB;
   double Ratio2360PFInclusive = Mean2360PFInclusive/Mean2360MB;
   
   double Ratio2360CaloDijet = Mean2360CaloDijet/Mean2360MB;
   double Ratio2360CaloInclusive = Mean2360CaloInclusive/Mean2360MB;
   
   double Ratio2360PFDijet_error = Ratio2360PFDijet*Ratio2360PFDijet*((Mean2360PFDijet_error*Mean2360PFDijet_error)/(Mean2360PFDijet*Mean2360PFDijet) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360PFDijet_error = sqrt(Ratio2360PFDijet_error);
   
   double Ratio2360PFInclusive_error = Ratio2360PFInclusive*Ratio2360PFInclusive*((Mean2360PFInclusive_error*Mean2360PFInclusive_error)/(Mean2360PFInclusive*Mean2360PFInclusive) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360PFInclusive_error = sqrt(Ratio2360PFInclusive_error);
   
   double Ratio2360CaloDijet_error = Ratio2360CaloDijet*Ratio2360CaloDijet*((Mean2360CaloDijet_error*Mean2360CaloDijet_error)/(Mean2360CaloDijet*Mean2360CaloDijet) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360CaloDijet_error = sqrt(Ratio2360CaloDijet_error);
   
   double Ratio2360CaloInclusive_error = Ratio2360CaloInclusive*Ratio2360CaloInclusive*((Mean2360CaloInclusive_error*Mean2360CaloInclusive_error)/(Mean2360CaloInclusive*Mean2360CaloInclusive) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360CaloInclusive_error = sqrt(Ratio2360CaloInclusive_error);
   
   std::cout << "Ratio2360 PF Dijet/MB = " << Ratio2360PFDijet << " +- " << Ratio2360PFDijet_error << std::endl;
   std::cout << "Ratio2360 PF Inclusive/MB = " << Ratio2360PFInclusive << " +- " << Ratio2360PFInclusive_error << std::endl;
   std::cout << "Ratio2360 Calo Dijet/MB = " << Ratio2360CaloDijet << " +- " << Ratio2360CaloDijet_error << std::endl;
   std::cout << "Ratio2360 Calo Inclusive/MB = " << Ratio2360CaloInclusive << " +- " << Ratio2360CaloInclusive_error << std::endl;
   
   // MC ratios
   
   
   double Mean900MCMB = h900MCSignalTot->GetMean();
   double Mean900MCMB_error = h900MCSignalTot->GetMeanError();
   
   double Mean900MCPFDijet = h900MCSignalTotPFDijet->GetMean();
   double Mean900MCPFInclusive = h900MCSignalTotPFInclusive->GetMean();
   
   double Mean900MCCaloDijet = h900MCSignalTotCaloDijet->GetMean();
   double Mean900MCCaloInclusive = h900MCSignalTotCaloInclusive->GetMean();
   
   double Mean900MCPFDijet_error = h900MCSignalTotPFDijet->GetMeanError();
   double Mean900MCPFInclusive_error = h900MCSignalTotPFInclusive->GetMeanError();
   
   double Mean900MCCaloDijet_error = h900MCSignalTotCaloDijet->GetMeanError();
   double Mean900MCCaloInclusive_error = h900MCSignalTotCaloInclusive->GetMeanError();
   
   double Ratio900MCPFDijet = Mean900MCPFDijet/Mean900MCMB;
   double Ratio900MCPFInclusive = Mean900MCPFInclusive/Mean900MCMB;
   
   double Ratio900MCCaloDijet = Mean900MCCaloDijet/Mean900MCMB;
   double Ratio900MCCaloInclusive = Mean900MCCaloInclusive/Mean900MCMB;
   
   double Ratio900MCPFDijet_error = Ratio900MCPFDijet*Ratio900MCPFDijet*((Mean900MCPFDijet_error*Mean900MCPFDijet_error)/(Mean900MCPFDijet*Mean900MCPFDijet) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCPFDijet_error = sqrt(Ratio900MCPFDijet_error);
   
   double Ratio900MCPFInclusive_error = Ratio900MCPFInclusive*Ratio900MCPFInclusive*((Mean900MCPFInclusive_error*Mean900MCPFInclusive_error)/(Mean900MCPFInclusive*Mean900MCPFInclusive) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCPFInclusive_error = sqrt(Ratio900MCPFInclusive_error);
   
   double Ratio900MCCaloDijet_error = Ratio900MCCaloDijet*Ratio900MCCaloDijet*((Mean900MCCaloDijet_error*Mean900MCCaloDijet_error)/(Mean900MCCaloDijet*Mean900MCCaloDijet) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCCaloDijet_error = sqrt(Ratio900MCCaloDijet_error);
   
   double Ratio900MCCaloInclusive_error = Ratio900MCCaloInclusive*Ratio900MCCaloInclusive*((Mean900MCCaloInclusive_error*Mean900MCCaloInclusive_error)/(Mean900MCCaloInclusive*Mean900MCCaloInclusive) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCCaloInclusive_error = sqrt(Ratio900MCCaloInclusive_error);
   
   std::cout << "Ratio900MC PF Dijet/MB = " << Ratio900MCPFDijet << " +- " << Ratio900MCPFDijet_error << std::endl;
   std::cout << "Ratio900MC PF Inclusive/MB = " << Ratio900MCPFInclusive << " +- " << Ratio900MCPFInclusive_error << std::endl;
   std::cout << "Ratio900MC Calo Dijet/MB = " << Ratio900MCCaloDijet << " +- " << Ratio900MCCaloDijet_error << std::endl;
   std::cout << "Ratio900MC Calo Inclusive/MB = " << Ratio900MCCaloInclusive << " +- " << Ratio900MCCaloInclusive_error << std::endl;
   
   
   double Mean2360MCMB = h2360MCSignalTot->GetMean();
   double Mean2360MCMB_error = h2360MCSignalTot->GetMeanError();
   
   double Mean2360MCPFDijet = h2360MCSignalTotPFDijet->GetMean();
   double Mean2360MCPFInclusive = h2360MCSignalTotPFInclusive->GetMean();
   
   double Mean2360MCCaloDijet = h2360MCSignalTotCaloDijet->GetMean();
   double Mean2360MCCaloInclusive = h2360MCSignalTotCaloInclusive->GetMean();
   
   double Mean2360MCPFDijet_error = h2360MCSignalTotPFDijet->GetMeanError();
   double Mean2360MCPFInclusive_error = h2360MCSignalTotPFInclusive->GetMeanError();
   
   double Mean2360MCCaloDijet_error = h2360MCSignalTotCaloDijet->GetMeanError();
   double Mean2360MCCaloInclusive_error = h2360MCSignalTotCaloInclusive->GetMeanError();
   
   double Ratio2360MCPFDijet = Mean2360MCPFDijet/Mean2360MCMB;
   double Ratio2360MCPFInclusive = Mean2360MCPFInclusive/Mean2360MCMB;
   
   double Ratio2360MCCaloDijet = Mean2360MCCaloDijet/Mean2360MCMB;
   double Ratio2360MCCaloInclusive = Mean2360MCCaloInclusive/Mean2360MCMB;
   
   double Ratio2360MCPFDijet_error = Ratio2360MCPFDijet*Ratio2360MCPFDijet*((Mean2360MCPFDijet_error*Mean2360MCPFDijet_error)/(Mean2360MCPFDijet*Mean2360MCPFDijet) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCPFDijet_error = sqrt(Ratio2360MCPFDijet_error);
   
   double Ratio2360MCPFInclusive_error = Ratio2360MCPFInclusive*Ratio2360MCPFInclusive*((Mean2360MCPFInclusive_error*Mean2360MCPFInclusive_error)/(Mean2360MCPFInclusive*Mean2360MCPFInclusive) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCPFInclusive_error = sqrt(Ratio2360MCPFInclusive_error);
   
   double Ratio2360MCCaloDijet_error = Ratio2360MCCaloDijet*Ratio2360MCCaloDijet*((Mean2360MCCaloDijet_error*Mean2360MCCaloDijet_error)/(Mean2360MCCaloDijet*Mean2360MCCaloDijet) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCCaloDijet_error = sqrt(Ratio2360MCCaloDijet_error);
   
   double Ratio2360MCCaloInclusive_error = Ratio2360MCCaloInclusive*Ratio2360MCCaloInclusive*((Mean2360MCCaloInclusive_error*Mean2360MCCaloInclusive_error)/(Mean2360MCCaloInclusive*Mean2360MCCaloInclusive) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCCaloInclusive_error = sqrt(Ratio2360MCCaloInclusive_error);
   
   std::cout << "Ratio2360MC PF Dijet/MB = " << Ratio2360MCPFDijet << " +- " << Ratio2360MCPFDijet_error << std::endl;
   std::cout << "Ratio2360MC PF Inclusive/MB = " << Ratio2360MCPFInclusive << " +- " << Ratio2360MCPFInclusive_error << std::endl;
   std::cout << "Ratio2360MC Calo Dijet/MB = " << Ratio2360MCCaloDijet << " +- " << Ratio2360MCCaloDijet_error << std::endl;
   std::cout << "Ratio2360MC Calo Inclusive/MB = " << Ratio2360MCCaloInclusive << " +- " << Ratio2360MCCaloInclusive_error << std::endl;
  
   
   /////////////////////
   // plot paper plots
   /////////////////////
   
   double cms[2] = {900,2360};
   double cms_error[2] = {0,0};
   double yRatioPFDijet[2] = {Ratio900PFDijet, Ratio2360PFDijet};
   double yRatioPFInclusive[2] = {Ratio900PFInclusive, Ratio2360PFInclusive};
   double yRatioPFDijet_error[2] = {Ratio900PFDijet_error, Ratio2360PFDijet_error};
   double yRatioPFInclusive_error[2] = {Ratio900PFInclusive_error, Ratio2360PFInclusive_error};
   
   double yRatioCaloDijet[2] = {Ratio900CaloDijet, Ratio2360CaloDijet};
   double yRatioCaloInclusive[2] = {Ratio900CaloInclusive, Ratio2360CaloInclusive};
   double yRatioCaloDijet_error[2] = {Ratio900CaloDijet_error, Ratio2360CaloDijet_error};
   double yRatioCaloInclusive_error[2] = {Ratio900CaloInclusive_error, Ratio2360CaloInclusive_error};
   
   
   TGraphErrors *gRatiosPFDijetPaper = new TGraphErrors(2,cms,yRatioPFDijet,cms_error,yRatioPFDijet_error);
   TGraphErrors *gRatiosPFInclusivePaper = new TGraphErrors(2,cms,yRatioPFInclusive,cms_error,yRatioPFInclusive_error);
   gRatiosPFDijetPaper->SetTitle("Dijet Ratios");
   gRatiosPFInclusivePaper->SetTitle("Inclusive jet Ratios");
   gRatiosPFDijetPaper->SetName("gRatiosPFDijetPaper");
   gRatiosPFInclusivePaper->SetName("gRatiosPFInclusivePaper");
   
   TGraphErrors *gRatiosCaloDijetPaper = new TGraphErrors(2,cms,yRatioCaloDijet,cms_error,yRatioCaloDijet_error);
   TGraphErrors *gRatiosCaloInclusivePaper = new TGraphErrors(2,cms,yRatioCaloInclusive,cms_error,yRatioCaloInclusive_error);
   gRatiosCaloDijetPaper->SetTitle("Dijet Ratios");
   gRatiosCaloInclusivePaper->SetTitle("Inclusive jet Ratios");
   gRatiosCaloDijetPaper->SetName("gRatiosCaloDijetPaper");
   gRatiosCaloInclusivePaper->SetName("gRatiosCaloInclusivePaper");
   
   TH1D *hRatiosPFDijetMCPaper = new TH1D("hRatiosPFDijetMCPaper","PF Dijet MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   TH1D *hRatiosPFInclusiveMCPaper = new TH1D("hRatiosPFInclusiveMCPaper","PF Inclusive MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   hRatiosPFDijetMCPaper->SetBinContent(1,0.762);
   hRatiosPFDijetMCPaper->SetBinError(1,0.0089);
   hRatiosPFDijetMCPaper->SetBinContent(2,Ratio2360MCPFDijet);
   hRatiosPFDijetMCPaper->SetBinError(2,Ratio2360MCPFDijet_error);
   hRatiosPFInclusiveMCPaper->SetBinContent(1,0.766);
   hRatiosPFInclusiveMCPaper->SetBinError(1,0.0068);
   hRatiosPFInclusiveMCPaper->SetBinContent(2,Ratio2360MCPFInclusive);
   hRatiosPFInclusiveMCPaper->SetBinError(2,Ratio2360MCPFInclusive_error);
   hRatiosPFDijetMCPaper->SetStats(0);
   hRatiosPFInclusiveMCPaper->SetStats(0);
   
   TH1D *hRatiosCaloDijetMCPaper = new TH1D("hRatiosCaloDijetMCPaper","Calo Dijet MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   TH1D *hRatiosCaloInclusiveMCPaper = new TH1D("hRatiosCaloInclusiveMCPaper","Calo Inclusive MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   hRatiosCaloDijetMCPaper->SetBinContent(1,0);
   hRatiosCaloDijetMCPaper->SetBinError(1,0.0);
   hRatiosCaloDijetMCPaper->SetBinContent(2,Ratio2360MCCaloDijet);
   hRatiosCaloDijetMCPaper->SetBinError(2,Ratio2360MCCaloDijet_error);
   hRatiosCaloInclusiveMCPaper->SetBinContent(1,0);
   hRatiosCaloInclusiveMCPaper->SetBinError(1,0);
   hRatiosCaloInclusiveMCPaper->SetBinContent(2,Ratio2360MCCaloInclusive);
   hRatiosCaloInclusiveMCPaper->SetBinError(2,Ratio2360MCCaloInclusive_error);
   hRatiosCaloDijetMCPaper->SetStats(0);
   hRatiosCaloInclusiveMCPaper->SetStats(0);
   
   TCanvas *cPFRatios = new TCanvas("cPFRatios","Forward Energy Flow Ratios in CASTOR");
   cPFRatios->Divide(1,1);
   cPFRatios->cd(1);
   // plot MC
   hRatiosPFInclusiveMCPaper->SetFillStyle(1001);
   hRatiosPFDijetMCPaper->SetFillStyle(3004);
   hRatiosPFInclusiveMCPaper->SetFillColor(kGray);
   hRatiosPFDijetMCPaper->SetFillColor(1);
   hRatiosPFInclusiveMCPaper->SetMarkerStyle(0);
   hRatiosPFDijetMCPaper->SetMarkerStyle(0);
   hRatiosPFInclusiveMCPaper->GetYaxis()->SetRangeUser(0.7,1.3);
   hRatiosPFInclusiveMCPaper->SetTitle("Forward Energy Flow Ratios in CASTOR - PF jets");
   hRatiosPFInclusiveMCPaper->Draw("hist");
   hRatiosPFDijetMCPaper->Draw("samehist");
   // plot data
   gRatiosPFInclusivePaper->Draw("sameP");
   gRatiosPFDijetPaper->Draw("sameP");
   gRatiosPFInclusivePaper->SetMarkerStyle(21);
   gRatiosPFDijetPaper->SetMarkerStyle(23);
   
   TCanvas *cCaloRatios = new TCanvas("cCaloRatios","Forward Energy Flow Ratios in CASTOR");
   cCaloRatios->Divide(1,1);
   cCaloRatios->cd(1);
   // plot MC
   hRatiosCaloInclusiveMCPaper->SetFillStyle(1001);
   hRatiosCaloDijetMCPaper->SetFillStyle(3004);
   hRatiosCaloInclusiveMCPaper->SetFillColor(kGray);
   hRatiosCaloDijetMCPaper->SetFillColor(1);
   hRatiosCaloInclusiveMCPaper->SetMarkerStyle(0);
   hRatiosCaloDijetMCPaper->SetMarkerStyle(0);
   hRatiosCaloInclusiveMCPaper->GetYaxis()->SetRangeUser(0.6,1.4);
   hRatiosCaloInclusiveMCPaper->SetTitle("Forward Energy Flow Ratios in CASTOR - Calo jets");
   hRatiosCaloInclusiveMCPaper->Draw("hist");
   hRatiosCaloDijetMCPaper->Draw("samehist");
   // plot data
   gRatiosCaloInclusivePaper->Draw("sameP");
   gRatiosCaloDijetPaper->Draw("sameP");
   gRatiosCaloInclusivePaper->SetMarkerStyle(21);
   gRatiosCaloDijetPaper->SetMarkerStyle(23);
   
   
}
