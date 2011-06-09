{

  TH1F* heta = new TH1F("heta","eta gen part",100,-15,15);
  TH1F* hphi = new TH1F("hphi","phi gen part",100,-3.14,3.14);
  TH1F* hpt = new TH1F("hpt","pt gen part",100,0,12);
  TH1F* henergy = new TH1F("henergy","energy gen part",100,0,3500);

  TFile file("Cascade2_example_test_cff_py_GEN.root");
  TTree* tree = (TTree*) file.Get("Events");
  
  TCanvas* c = new TCanvas("c","some plots (gen particles)");
  c->Divide(2,2);

  c->cd(1);
  Events->Draw("recoGenParticles_genParticles__GEN.obj.eta()>>heta","recoGenParticles_genParticles__GEN.obj.status_==1");
  c->cd(2);
  Events->Draw("recoGenParticles_genParticles__GEN.obj.phi()>>hphi","recoGenParticles_genParticles__GEN.obj.status_==1");
  TPad* p3 = c->cd(3);
  p3->SetLogy();
  Events->Draw("recoGenParticles_genParticles__GEN.obj.pt()>>hpt","recoGenParticles_genParticles__GEN.obj.status_==1");
  TPad* p4 = c->cd(4);
  p4->SetLogy();
  Events->Draw("recoGenParticles_genParticles__GEN.obj.energy()>>henergy","recoGenParticles_genParticles__GEN.obj.status_==1");

  c->Print("cascade_plot.eps");

  TFile* fout = new TFile("cascade_plot.root","RECREATE");
  fout->cd();

  heta->Write();
  hphi->Write();
  hpt->Write();
  henergy->Write();
  c->Write();

  fout->Close();
}
