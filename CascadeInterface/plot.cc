{
  TFile file("Cascade2_example_test_cff_py_GEN.root");
  TTree* tree = (TTree*) file.Get("Events");

  TFile* fout = new TFile("cascade_plot.root","RECREATE");
  fout->cd();

  TH1F* heta = new TH1F("heta","eta gen part",100,-15,15);
  TH1F* hphi = new TH1F("hphi","phi gen part",100,-3.14,3.14);
  TH1F* hpt = new TH1F("hpt","pt gen part",100,0,12);
  TH1F* henergy = new TH1F("henergy","energy gen part",100,0,3500);

  TCanvas* c = new TCanvas("c","some plots (gen particles)");
  c->Divide(2,2);

  c->cd(1);
  tree->Draw("recoGenParticles_genParticles__GEN.obj.eta()>>heta","recoGenParticles_genParticles__GEN.obj.status_==1");
  heta->Write();

  c->cd(2);
  tree->Draw("recoGenParticles_genParticles__GEN.obj.phi()>>hphi","recoGenParticles_genParticles__GEN.obj.status_==1");
  hphi->Write();

  TPad* p3 = c->cd(3);
  p3->SetLogy();
  tree->Draw("recoGenParticles_genParticles__GEN.obj.pt()>>hpt","recoGenParticles_genParticles__GEN.obj.status_==1");
  hpt->Write();

  TPad* p4 = c->cd(4);
  p4->SetLogy();
  tree->Draw("recoGenParticles_genParticles__GEN.obj.energy()>>henergy","recoGenParticles_genParticles__GEN.obj.status_==1");
  henergy->Write();

  c->Print("cascade_plot.eps");
  c->Write();

  cout<<"press enter to finish"<<endl;
  getchar();

  fout->Close();
}
