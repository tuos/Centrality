void centNpartXe(){

  // Setup
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptFit(1011);

  // Open File
  TFile *infile = new TFile("./glauber_XeXe_sNN70mb_v0_dmin04_1M.root");
  infile->cd();
  TH1D *hNpart = new TH1D("hNpart","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Project("hNpart","Npart");
  TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",2000,-0.01,19.99);
  nt_Xe_Xe->Project("hB","B");


  Double_t fRunningCounts=0.;
  Int_t iBin5=0;
  Int_t iBin10=0;
  Int_t iBin15=0;
  Int_t iBin100=1;

  for (Int_t i=1; i<=hB->GetNbinsX(); i++) {
    fRunningCounts=fRunningCounts+hB->GetBinContent(i);
    if(fRunningCounts>=(0.05*hB->GetEntries())&&iBin5==0) {
      iBin5=i;
      cout<<"Found 5% bin boundary="<<iBin5<<", B value = "<<hB->GetBinCenter(iBin5)<<endl;
    }
    if(fRunningCounts>=(0.1*hB->GetEntries())&&iBin10==0) {
      iBin10=i;
      cout<<"Found 10% bin boundary="<<iBin10<<", B value = "<<hB->GetBinCenter(iBin10)<<endl;
    }
    if(fRunningCounts>=(0.15*hB->GetEntries())&&iBin15==0) {
      iBin15=i;
      cout<<"Found 15% bin boundary="<<iBin15<<", B value = "<<hB->GetBinCenter(iBin15)<<endl;
    }
  }
  //cout<<"By definition 100% bin boundary="<<iBin100<<", Npart Value = "<<hNpart->GetBinCenter(iBin100)<<endl;


  TH1D *hNpart05 = new TH1D("hNpart05","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart05","B<3.025");
  hNpart05->SetLineColor(2);
  hNpart05->SetLineWidth(2);
  TH1D *hNpart10 = new TH1D("hNpart10","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart10","B>=3.025&&B<4.285");
  hNpart10->SetLineColor(4);
  hNpart10->SetLineWidth(2);
  TH1D *hNpart15 = new TH1D("hNpart15","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart15","B>=4.285&&B<5.255");
  hNpart15->SetLineColor(8);
  hNpart15->SetLineWidth(2);

  cout<<hNpart05->GetMean()<<"  "<<hNpart10->GetMean()<<"  "<<hNpart15->GetMean()<<endl;

  TCanvas *can=new TCanvas("can","can",10,10,660,510);

  hNpart->Draw();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  hNpart05->Draw("same");
  hNpart10->Draw("same");
  hNpart15->Draw("same");


      tex=new TLatex(60,2.e4,"XeXe,  #sigma_{NN}=70 mb, Glauber MC");
      tex->SetTextSize(0.06);
      tex->Draw();
      tex=new TLatex(80,5.e2,"10-15%, <N_{part}>=178");
      tex->SetTextColor(8);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(150,3.e3,"5-10%, <N_{part}>=207");
      tex->SetTextColor(4);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(200,2.e2,"0-5%, <N_{part}>=237");
      tex->SetTextColor(2);
      tex->SetTextSize(0.05);
      tex->Draw();

can->SaveAs("plot_xexe_dist.png");


}


