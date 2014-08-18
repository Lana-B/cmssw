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
  double driftTime0;
  double driftTimeMin20;
  double driftTimeMin180;



  TTree *t0 = (TTree *)f0->Get("EventVars");
  TTree *tMin20 = (TTree *)fMin20->Get("EventVars");
  TTree *tMin180 = (TTree *)fMin180->Get("EventVars");
  t0->SetBranchAddress("driftTime", &driftTime0);
  tMin20->SetBranchAddress("driftTime", &driftTimeMin20);
  tMin180->SetBranchAddress("driftTime", &driftTimeMin180);
cout<<"got trees..set branch address"<<endl;
/*
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
  H2->Scale(1.1);
  H2->Draw("same");
  H3->SetLineColor(kGreen);
  //H3->Draw("SAME");	
  c1->SetLogy();

  TLegend* leg = new TLegend(0.6, 0.63, .78, .80);
  leg->SetFillColor(0);
  leg->AddEntry(H1, "0C", "l");
  leg->AddEntry(H2, "-20C", "l");
  leg->AddEntry(H3, "-180C", "l");

  leg->Draw();

  c1->SaveAs("driftTime.png");


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
  H22->Scale(H11->Integral()/H22->Integral());
  H22->Draw("SAME");
  H33->Scale(H11->Integral()/H33->Integral());
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

  TCanvas *c3 = new TCanvas();
  //TH2F* HModT = new TH2F("HModT","HModT", 100, 0.028, 0.048, 100, .05e-03, 0.4e-03);
  TH2F* HModT = new TH2F("HModT","HModT",100, .0e-03, 0.7e-03, 100, 0.02, 0.05);

  int nEntries180 = tMin180->GetEntries();
  double dSCS;
  double dModT;
  tMin180->SetBranchAddress("sigmaCS", &dSCS);
  tMin180->SetBranchAddress("modThick", &dModT);

  for (int i = 0; i<nEntries180; i++){
    tMin180->GetEntry(i);
    HModT->Fill(dSCS, dModT);
  }

  HModT->SetTitle("");
  HModT->GetXaxis()->SetTitle("Charge Spread");
  HModT->GetYaxis()->SetTitle("module Thickness");
  HModT->Draw("colz");
  c3->SetLogy();
  c3->SaveAs("modTvSig.png");
*/

  TH1F * hMod28 = new TH1F("hMod28", "hMod28", 100, 0, 0.7e-03);
  TH1F * hMod48 = new TH1F("hMod48", "hMod28", 100, 0, 0.7e-03);
  double dSCS0, dModT0;
  t0->SetBranchAddress("sigmaCS", &dSCS0);
  t0->SetBranchAddress("modThick", &dModT0);
  hMod28->SetFillColor(kBlue-9);
  hMod48->SetFillColor(kBlue+3);
  cout<<"Start loop"<<endl;
  int nEntries0 = t0->GetEntries();
  for (int i = 0; i<nEntries0; i++){
    t0->GetEntry(i);
    if(dModT0 <0.03){
      hMod28->Fill(dSCS0);
    }
    else{
      hMod48->Fill(dSCS0);
    }
  }
  hMod48->GetXaxis()->SetTitle("Charge Spread");
  cout<<"mod histo filled"<<endl;
  THStack *stackmod = new THStack("stackmod", "Zero degrees");
  stackmod->Add(hMod48);
  stackmod->Add(hMod28);
  TCanvas* cStack = new TCanvas();
  TLegend* legS = new TLegend(0.6, 0.63, .86, .80);
  legS->SetFillColor(0);
  legS->AddEntry(hMod28, "modThick = 0.028" , "f");
  legS->AddEntry(hMod48, "modThick = 0.048" , "f");

  legS->SetTextSize(.03);
  stackmod->Draw();
  stackmod->GetHistogram()->GetXaxis()->SetTitle("Charge Spread");

  legS->Draw();
  cStack->SaveAs("sigmaStack.png");
  ///////Minus 20/////Stack///////
  TH1F * hMod28M20 = new TH1F("hMod28M20", "hMod28M20", 100, 0, 0.7e-03);
  TH1F * hMod48M20 = new TH1F("hMod48M20", "hMod28M20", 100, 0, 0.7e-03);
  double dSCSM20, dModTM20;
  tMin20->SetBranchAddress("sigmaCS", &dSCSM20);
  tMin20->SetBranchAddress("modThick", &dModTM20);
  hMod28M20->SetFillColor(kBlue-9);
  hMod48M20->SetFillColor(kBlue+3);
  int nEntriesMin20 = tMin20->GetEntries();
  for (int i = 0; i<nEntriesMin20; i++){
    tMin20->GetEntry(i);
    if(dModTM20 <0.03){
      hMod28M20->Fill(dSCSM20);
    }
    else{
      hMod48M20->Fill(dSCSM20);
    }
  }
  hMod48M20->GetXaxis()->SetTitle("Charge Spread");

  THStack *stackmodM20 = new THStack("stackmodM20", "Minus 20 degrees");
  stackmodM20->Add(hMod48M20);
  stackmodM20->Add(hMod28M20);
  TCanvas* cStackM20 = new TCanvas();
  TLegend* legSM20 = new TLegend(0.6, 0.63, .86, .80);
  legSM20->SetFillColor(0);
  legSM20->AddEntry(hMod28M20, "modThick = 0.028" , "f");
  legSM20->AddEntry(hMod48M20, "modThick = 0.048" , "f");

  legSM20->SetTextSize(.03);
  stackmodM20->Draw();
  stackmodM20->GetHistogram()->GetXaxis()->SetTitle("Charge Spread");

  legSM20->Draw();
  cStackM20->SaveAs("sigmaStackMinus20.png");

  cout<<"END"<<endl;
}
