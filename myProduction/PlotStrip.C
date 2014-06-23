void PlotStrip(){
  gSystem->Load("libFWCoreFWLite");
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
  gSystem->Load("libAnalysisDataFormatsSUSYBSMObjects.so");
  gSystem->Load("libDataFormatsVertexReco.so");
  gSystem->Load("libDataFormatsCommon.so");
  gSystem->Load("libDataFormatsHepMCCandidate.so");
  gSystem->Load("libPhysicsToolsUtilities.so");
  gStyle->SetOptStat(0);
  cout << "Loaded stuff" << endl;

  TFile *f0 = TFile::Open("ZeroDegrees/QCD_Pt_50_80_8TeV_cfi_py_GEN_SIM_DIGI.root");
  TFile *fMin20 = TFile::Open("Minus20Degrees/QCD_Pt_50_80_8TeV_cfi_py_GEN_SIM_DIGI.root");
  TFile *fMin180 = TFile::Open("Minus180Degrees/QCD_Pt_50_80_8TeV_cfi_py_GEN_SIM_DIGI.root");

  cout<< "got files" <<endl;

  double d0Size;
  TTree *t0 = (TTree *)f0->Get("Events");
  TTree *tMin20 = (TTree *)fMin20->Get("Events");
  TTree *tMin180 = (TTree *)fMin180->Get("Events");

  TCanvas *c1 = new TCanvas();
  TH1F* H1 = new TH1F("H1","H1",260,0,260);
  TH1F* H2 = new TH1F("H2","H2",260,0,260);
  TH1F* H3 = new TH1F("H3","H3",260,0,260);

  t0->Project("H1","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.data.adc_");
  tMin20->Project("H2","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.data.adc_");
  tMin180->Project("H3","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.data.adc_");

  H1->SetTitle("Charge deposited in each strip");
  H1->Draw();
  H2->SetLineColor(kRed);
  H2->Draw("SAME");
  H3->SetLineColor(kGreen);
  H3->Draw("SAME");	
  c1->SetLogy();

  TLegend* leg = new TLegend(0.6, 0.63, .78, .80);
  leg->SetFillColor(0);
  leg->AddEntry(H1, "0C", "l");
  leg->AddEntry(H2, "-20C", "l");
  leg->AddEntry(H3, "-180C", "l");

  leg->Draw();

  c1->SaveAs("adc.png");


  TCanvas *c2 = new TCanvas();
  TH1F* H11 = new TH1F("H11","H11",260,0,260);
  TH1F* H22 = new TH1F("H22","H22",260,0,260);
  TH1F* H33 = new TH1F("H33","H33",260,0,260);

  t0->Project("H11","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.size()");
  tMin20->Project("H22","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.size()");
  tMin180->Project("H33","SiStripDigiedmDetSetVector_simSiStripDigis_ZeroSuppressed_DIGI.obj._sets.size()");

  H11->SetTitle("Cluster size");
  H11->Draw();
  H22->SetLineColor(kRed);
  H22->Draw("SAME");
  H33->SetLineColor(kGreen);
  H33->Draw("SAME");
  c2->SetLogy();
  
  TLegend* leg2 = new TLegend(0.6, 0.63, .78, .80);
  leg2->SetFillColor(0);
  leg2->AddEntry(H11, "0C", "l");
  leg2->AddEntry(H22, "-20C", "l");
  leg2->AddEntry(H33, "-180C", "l");

  leg2->Draw();

  c2->SaveAs("size.png");

}
