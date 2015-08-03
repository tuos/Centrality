{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);

  ///////////////////////////////////////////////
  //TFile *fileA = TFile::Open("/mnt/hadoop/cms/store/user/belt/HiForest_MinBias_JetRAA_v1_final/HiForest_HIMinBiasUPC_14Mar2014_v2_JetRAA_lumi8_Part95.root");
  TFile *fileA = TFile::Open("/mnt/hadoop/cms/store/user/belt/HiForest_MinBias_JetRAA_v1_final/HiForest_HIMinBiasUPC_14Mar2014_v2_JetRAA_lumi8_Part86.root");
  TTree * tree;
  tree=(TTree*)hltanalysis->Get("HltTree");
  tree->AddFriend("evttree=hiEvtAnalyzer/HiTree");
  tree->AddFriend("evttree=skimanalysis/HltTree");
  TH1D *hist_A = new TH1D("hist_A","",203,0,5203);
  hist_A->Sumw2();
  hist_A->SetLineColor(1);
  hist_A->SetLineWidth(1);
  tree->Project("hist_A","hiHF","pcollisionEventSelection&&HLT_HIMinBiasHfOrBSC_v1");

  TH1D *hist_B = new TH1D("hist_B","",203,0,5203);
  hist_B->Sumw2();
  hist_B->SetLineColor(2);
  tree->Project("hist_B","hiHF","HLT_HIJet55_v1&&pcollisionEventSelection");

  //////////////////////////////////////////////

  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->cd(1);
  c1->SetTicks(-1);
  c1->SetLogy(1);
  TH1D *hist_Ac = (TH1D*)hist_A->Clone();
  //hist_Ac->SetName("hist_Ac");
  //hist_Ac->Scale(1./hist_A->GetEntries());
  hist_Ac->SetTitle("");
  //hist_Ac->GetXaxis()->SetTitle("Centrality Bin");
  hist_Ac->GetXaxis()->SetTitle("Sum HF ET");
  hist_Ac->GetYaxis()->SetTitle("Number of Events");
  hist_Ac->GetXaxis()->SetTitleOffset(0.94);
  hist_Ac->GetYaxis()->SetTitleOffset(0.96);
  hist_Ac->GetXaxis()->SetTitleSize(0.056);
  hist_Ac->GetYaxis()->SetTitleSize(0.056);
  hist_Ac->GetYaxis()->CenterTitle(kTRUE);
  hist_Ac->GetXaxis()->CenterTitle(kTRUE);
  hist_Ac->SetMarkerStyle(25);
  hist_Ac->SetMarkerColor(1);
  hist_Ac->Draw();
  //hist_B->Scale(1./hist_B->GetEntries());
  hist_B->SetMarkerStyle(20);
  hist_B->SetMarkerColor(2);
  hist_B->Draw("same");
  TLegend *leg = new TLegend(0.19,0.76,0.4,0.92);
  leg->SetFillColor(10);
  leg->SetBorderSize(0.035);
  //leg->SetTextFont(42);
  leg->SetTextColor(1);
  leg->SetTextSize(0.04);
  leg->AddEntry(hist_Ac,"HLT_HIMinBiasHfOrBSC_v1&&pcollisionEventSelection","p");
  leg->AddEntry(hist_B,"HLT_HIJet55_v1&&pcollisionEventSelection","p");
  leg->Draw();

  c1->SaveAs("hiBin_HLT_HIJet55_v1.png");
}


