void PlotDrift(){
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

  TFile *f0 = TFile::Open("ZeroDegrees/StripVars.root");
  TFile *fMin20 = TFile::Open("Minus20Degrees/StripVars.root");
  TFile *fMin180 = TFile::Open("Minus180Degrees/StripVars.root");

  cout<< "got files" <<endl;

  TTree *t0 = (TTree *)f0->Get("EventVars");
  TTree *tMin20 = (TTree *)fMin20->Get("EventVars");
  TTree *tMin180 = (TTree *)fMin180->Get("EventVars");

  TCanvas *c1 = new TCanvas();
  TH1F* H1 = new TH1F("H1","H1",100,0,30e-09);
  TH1F* H2 = new TH1F("H2","H2",100,0,30e-09);
  TH1F* H3 = new TH1F("H3","H3",100,0,30e-09);

  t0->Project("H1","driftTime");
  tMin20->Project("H2","driftTime");
  tMin180->Project("H3","driftTime");

  H1->SetTitle("Drift Time");
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

  c1->SaveAs("driftTime.png");

/*
  TCanvas *c2 = new TCanvas();
  TH1F* H11 = new TH1F("H11","H11",100,0,0.7e-03);
  TH1F* H22 = new TH1F("H22","H22",100,0,0.7e-03);
  TH1F* H33 = new TH1F("H33","H33",100,0,0.7e-03);

  t0->Project("H11","sigmaCS");
  tMin20->Project("H22","sigmaCS");
  tMin180->Project("H33","sigmaCS");

  H11->SetTitle("Charge Spread");
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

  c2->SaveAs("ChargeSpreadSigma.png");
*/
  cout<<"END"<<endl;
}
