void centNpartPb(){

  // Setup
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptFit(1011);

  // Open File
  TFile *infile = new TFile("./glauber_PbPb_sNN70mb_v0_dmin04_1M.root");
  infile->cd();
  TH1D *hNpart = new TH1D("hNpart","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Project("hNpart","Npart");
  TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",2000,-0.01,19.99);
  nt_Pb_Pb->Project("hB","B");


  Double_t fRunningCounts=0.;
  Int_t iBin5=0;
  Int_t iBin10=0;
  Int_t iBin15=0;
  Int_t iBin20=0;
  Int_t iBin25=0;
  Int_t iBin30=0;
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
    if(fRunningCounts>=(0.20*hB->GetEntries())&&iBin20==0) {
      iBin20=i;
      cout<<"Found 20% bin boundary="<<iBin20<<", B value = "<<hB->GetBinCenter(iBin20)<<endl;
    }
    if(fRunningCounts>=(0.25*hB->GetEntries())&&iBin25==0) {
      iBin25=i;
      cout<<"Found 25% bin boundary="<<iBin25<<", B value = "<<hB->GetBinCenter(iBin25)<<endl;
    }
    if(fRunningCounts>=(0.30*hB->GetEntries())&&iBin30==0) {
      iBin30=i;
      cout<<"Found 30% bin boundary="<<iBin30<<", B value = "<<hB->GetBinCenter(iBin30)<<endl;
    }
  }


  TH1D *hNpart05 = new TH1D("hNpart05","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart05","B<3.515");
  hNpart05->SetLineColor(2);
  hNpart05->SetLineWidth(2);
  TH1D *hNpart10 = new TH1D("hNpart10","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart10","B>=3.515&&B<4.955");
  hNpart10->SetLineColor(4);
  hNpart10->SetLineWidth(2);
  TH1D *hNpart15 = new TH1D("hNpart15","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart15","B>=4.955&&B<6.065");
  hNpart15->SetLineColor(8);
  hNpart15->SetLineWidth(2);
  TH1D *hNpart20 = new TH1D("hNpart20","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart20","B>=6.065&&B<7.005");
  hNpart20->SetLineColor(2);
  hNpart20->SetLineWidth(2);
  TH1D *hNpart25 = new TH1D("hNpart25","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart25","B>=7.005&&B<7.835");
  hNpart25->SetLineColor(4);
  hNpart25->SetLineWidth(2);
  TH1D *hNpart30 = new TH1D("hNpart30","Number of Participants Distribution;Npart;Events",500,-0.5,499.5);
  nt_Pb_Pb->Draw("Npart>>+hNpart30","B>=7.835&&B<8.585");
  hNpart30->SetLineColor(8);
  hNpart30->SetLineWidth(2);

  cout<<hNpart05->GetMean()<<"  "<<hNpart10->GetMean()<<"  "<<hNpart15->GetMean()<<endl;
  cout<<hNpart20->GetMean()<<"  "<<hNpart25->GetMean()<<"  "<<hNpart30->GetMean()<<endl;

  TCanvas *can=new TCanvas("can","can",10,10,660,510);
//can->SetTopMargin(0.02);
//can->SetRightMargin(0.02);
//can->SetBottomMargin(0.2);
//can->SetLeftMargin(0.2);

  hNpart->Draw();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  //hNpart05->Draw("same");
  //hNpart10->Draw("same");
  //hNpart15->Draw("same");
  hNpart20->Draw("same");
  hNpart25->Draw("same");
  hNpart30->Draw("same");


      tex=new TLatex(60,2.e4,"PbPb,  #sigma_{NN}=70 mb, Glauber MC");
      tex->SetTextSize(0.06);
      tex->Draw();
/*
      tex=new TLatex(100,5.e2,"10-15%, <N_{part}>=285");
      tex->SetTextColor(8);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(250,3.e3,"5-10%, <N_{part}>=333");
      tex->SetTextColor(4);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(350,2.e2,"0-5%, <N_{part}>=385");
      tex->SetTextColor(2);
      tex->SetTextSize(0.05);
      tex->Draw();
*/
      tex=new TLatex(50,5.e2,"25-30%, <N_{part}>=172");
      tex->SetTextColor(8);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(150,3.e3,"20-25%, <N_{part}>=205");
      tex->SetTextColor(4);
      tex->SetTextSize(0.05);
      tex->Draw();
      tex=new TLatex(250,2.e2,"15-20%, <N_{part}>=243");
      tex->SetTextColor(2);
      tex->SetTextSize(0.05);
      tex->Draw();

can->SaveAs("plot_pbpb_dist.png");

}


