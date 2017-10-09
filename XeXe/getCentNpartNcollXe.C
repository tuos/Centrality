#include <iomanip>
void getCentNpartNcollXe(){

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
  TH1D *hNcoll = new TH1D("hNcoll","Number of Binary Collision Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Project("hNcoll","Ncoll");
  TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",2000,-0.01,19.99);
  nt_Xe_Xe->Project("hB","B");

  // Extract hNpart distribution and get bin boundaries for three centralit bins

  Double_t fRunningCounts=0.;
  Int_t iBin5=0;
  Int_t iBin10=0;
  Int_t iBin15=0;
  Int_t iBin20=0;
  Int_t iBin25=0;
  Int_t iBin30=0;
  Int_t iBin40=0;
  Int_t iBin50=0;
  Int_t iBin60=0;
  Int_t iBin70=0;
  Int_t iBin80=0;
  Int_t iBin100=1;

  //for (Int_t i=hB->GetNbinsX();i>=1;i--) {
  for (Int_t i=1; i<=hB->GetNbinsX(); i++) {
    fRunningCounts=fRunningCounts+hB->GetBinContent(i);
    //    cout<<i<<": "<<fRunningCounts<<endl;
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
    if(fRunningCounts>=(0.2*hB->GetEntries())&&iBin20==0) {
      iBin20=i;
      cout<<"Found 20% bin boundary="<<iBin20<<", B value = "<<hB->GetBinCenter(iBin20)<<endl;
    }
    if(fRunningCounts>=(0.25*hB->GetEntries())&&iBin25==0) {
      iBin25=i;
      cout<<"Found 25% bin boundary="<<iBin25<<", B value = "<<hB->GetBinCenter(iBin25)<<endl;
    }
    if(fRunningCounts>=(0.3*hB->GetEntries())&&iBin30==0) {
      iBin30=i;
      cout<<"Found 30% bin boundary="<<iBin30<<", B value = "<<hB->GetBinCenter(iBin30)<<endl;
    }
    if(fRunningCounts>=(0.4*hB->GetEntries())&&iBin40==0) {
      iBin40=i;
      cout<<"Found 40% bin boundary="<<iBin40<<", B value = "<<hB->GetBinCenter(iBin40)<<endl;
    }
    if(fRunningCounts>=(0.5*hB->GetEntries())&&iBin50==0) {
      iBin50=i;
      cout<<"Found 50% bin boundary="<<iBin50<<", B value = "<<hB->GetBinCenter(iBin50)<<endl;
    }
    if(fRunningCounts>=(0.6*hB->GetEntries())&&iBin60==0) {
      iBin60=i;
      cout<<"Found 60% bin boundary="<<iBin60<<", B value = "<<hB->GetBinCenter(iBin60)<<endl;
    }
    if(fRunningCounts>=(0.7*hB->GetEntries())&&iBin70==0) {
      iBin70=i;
      cout<<"Found 70% bin boundary="<<iBin70<<", B value = "<<hB->GetBinCenter(iBin70)<<endl;
    }
    if(fRunningCounts>=(0.8*hB->GetEntries())&&iBin80==0) {
      iBin80=i;
      cout<<"Found 80% bin boundary="<<iBin80<<", B value = "<<hB->GetBinCenter(iBin80)<<endl;
    }
    if(fRunningCounts>=(1.0*hB->GetEntries())&&iBin100==0) {
      iBin100=i;
      cout<<"Found 100% bin boundary="<<iBin100<<", B value = "<<hB->GetBinCenter(iBin100)<<endl;
    }
  }
  //cout<<"By definition 100% bin boundary="<<iBin100<<", Npart Value = "<<hNpart->GetBinCenter(iBin100)<<endl;

  //hB->Draw();

  TH1D *hNpart05 = new TH1D("hNpart05","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart05","B<3.025");
//  hNpart05->SetLineColor(2);
//  hNpart05->SetLineWidth(2);
  TH1D *hNpart10 = new TH1D("hNpart10","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart10","B>=3.025&&B<4.285");
//  hNpart10->SetLineColor(4);
//  hNpart10->SetLineWidth(2);
  TH1D *hNpart15 = new TH1D("hNpart15","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart15","B>=4.285&&B<5.255");
//  hNpart15->SetLineColor(8);
//  hNpart15->SetLineWidth(2);

  //cout<<hNpart05->GetMean()<<"  "<<hNpart10->GetMean()<<"  "<<hNpart15->GetMean()<<endl;

  TH1D *hNpart20 = new TH1D("hNpart20","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart20","B>=5.255&&B<6.065");
  TH1D *hNpart25 = new TH1D("hNpart25","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart25","B>=6.065&&B<6.785");
  TH1D *hNpart30 = new TH1D("hNpart30","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart30","B>=6.785&&B<7.435");
  TH1D *hNpart40 = new TH1D("hNpart40","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart40","B>=7.435&&B<8.585");
  TH1D *hNpart50 = new TH1D("hNpart50","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart50","B>=8.585&&B<9.595");
  TH1D *hNpart60 = new TH1D("hNpart60","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart60","B>=9.595&&B<10.515");
  TH1D *hNpart70 = new TH1D("hNpart70","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart70","B>=10.515&&B<11.355");
  TH1D *hNpart80 = new TH1D("hNpart80","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart80","B>=11.355&&B<12.175");
  TH1D *hNpart100 = new TH1D("hNpart100","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart100","B>=12.175&&B<100.0");

  TH1D *hNpart0010 = new TH1D("hNpart0010","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart0010","B<4.285");
  TH1D *hNpart1030 = new TH1D("hNpart1030","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart1030","B>=4.285&&B<7.435");
  TH1D *hNpart3050 = new TH1D("hNpart3050","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart3050","B>=7.435&&B<9.595");
  TH1D *hNpart50100 = new TH1D("hNpart50100","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart50100","B>=9.595&&B<100.0");
  TH1D *hNpart0100 = new TH1D("hNpart0100","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  nt_Xe_Xe->Draw("Npart>>+hNpart0100","B>=0.0&&B<100.0");

  TH1D *hNcoll05 = new TH1D("hNcoll05","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll05","B<3.025");
  TH1D *hNcoll10 = new TH1D("hNcoll10","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll10","B>=3.025&&B<4.285");
  TH1D *hNcoll15 = new TH1D("hNcoll15","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll15","B>=4.285&&B<5.255");
  TH1D *hNcoll20 = new TH1D("hNcoll20","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll20","B>=5.255&&B<6.065");
  TH1D *hNcoll25 = new TH1D("hNcoll25","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll25","B>=6.065&&B<6.785");
  TH1D *hNcoll30 = new TH1D("hNcoll30","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll30","B>=6.785&&B<7.435");
  TH1D *hNcoll40 = new TH1D("hNcoll40","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll40","B>=7.435&&B<8.585");
  TH1D *hNcoll50 = new TH1D("hNcoll50","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll50","B>=8.585&&B<9.595");
  TH1D *hNcoll60 = new TH1D("hNcoll60","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll60","B>=9.595&&B<10.515");
  TH1D *hNcoll70 = new TH1D("hNcoll70","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll70","B>=10.515&&B<11.355");
  TH1D *hNcoll80 = new TH1D("hNcoll80","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll80","B>=11.355&&B<12.175");
  TH1D *hNcoll100 = new TH1D("hNcoll100","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll100","B>=12.175&&B<100.0");

  TH1D *hNcoll0010 = new TH1D("hNcoll0010","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll0010","B<4.285");
  TH1D *hNcoll1030 = new TH1D("hNcoll1030","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll1030","B>=4.285&&B<7.435");
  TH1D *hNcoll3050 = new TH1D("hNcoll3050","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll3050","B>=7.435&&B<9.595");
  TH1D *hNcoll50100 = new TH1D("hNcoll50100","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll50100","B>=9.595&&B<100.0");
  TH1D *hNcoll0100 = new TH1D("hNcoll0100","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  nt_Xe_Xe->Draw("Ncoll>>+hNcoll0100","B>=0.0&&B<100.0");

cout << fixed << setprecision(2);
//cout<<hNpart05->GetMean()<<"  "<<hNpart10->GetMean()<<"  "<<hNpart15->GetMean()<<endl;
//cout<<hNpart05->GetMean()<<"  "<<hNpart10->GetMean()<<"  "<<hNpart15->GetMean()<<endl;
double cent[13]={0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 100};
cout<<cent[0]<<" - "<<cent[1]<<"   "<<hNpart05->GetMean()<<"   "<<hNcoll05->GetMean()<<endl;
cout<<cent[1]<<" - "<<cent[2]<<"   "<<hNpart10->GetMean()<<"   "<<hNcoll10->GetMean()<<endl;
cout<<cent[2]<<" - "<<cent[3]<<"   "<<hNpart15->GetMean()<<"   "<<hNcoll15->GetMean()<<endl;
cout<<cent[3]<<" - "<<cent[4]<<"   "<<hNpart20->GetMean()<<"   "<<hNcoll20->GetMean()<<endl;
cout<<cent[4]<<" - "<<cent[5]<<"   "<<hNpart25->GetMean()<<"   "<<hNcoll25->GetMean()<<endl;
cout<<cent[5]<<" - "<<cent[6]<<"   "<<hNpart30->GetMean()<<"   "<<hNcoll30->GetMean()<<endl;
cout<<cent[6]<<" - "<<cent[7]<<"   "<<hNpart40->GetMean()<<"   "<<hNcoll40->GetMean()<<endl;
cout<<cent[7]<<" - "<<cent[8]<<"   "<<hNpart50->GetMean()<<"   "<<hNcoll50->GetMean()<<endl;
cout<<cent[8]<<" - "<<cent[9]<<"   "<<hNpart60->GetMean()<<"   "<<hNcoll60->GetMean()<<endl;
cout<<cent[9]<<" - "<<cent[10]<<"   "<<hNpart70->GetMean()<<"   "<<hNcoll70->GetMean()<<endl;
cout<<cent[10]<<" - "<<cent[11]<<"   "<<hNpart80->GetMean()<<"   "<<hNcoll80->GetMean()<<endl;
cout<<cent[11]<<" - "<<cent[12]<<"   "<<hNpart100->GetMean()<<"   "<<hNcoll100->GetMean()<<endl;

cout<<" 0-10%    "<<hNpart0010->GetMean()<<"   "<<hNcoll0010->GetMean()<<endl;
cout<<" 10-30%    "<<hNpart1030->GetMean()<<"   "<<hNcoll1030->GetMean()<<endl;
cout<<" 30-50%    "<<hNpart3050->GetMean()<<"   "<<hNcoll3050->GetMean()<<endl;
cout<<" 50-100%    "<<hNpart50100->GetMean()<<"   "<<hNcoll50100->GetMean()<<endl;
cout<<" 0-100%    "<<hNpart0100->GetMean()<<"   "<<hNcoll0100->GetMean()<<endl;


const int nCent=12;
double bRanges[nCent+1]={0.0, 3.025, 4.285, 5.255, 6.065, 6.785, 7.435, 8.585, 9.595, 10.515, 11.355, 12.175, 100.0};

  TH1D *hEcc2[nCent];
  TH1D *hEcc3[nCent];
  TH1D *hEcc4[nCent];
  TH1D *hEcc5[nCent];
for(int i=0; i<nCent; i++){
  hEcc2[i] = new TH1D(Form("hEcc2_%d", i),"Ecc Distribution;Ecc;Events",1100,-0.05,1.05);
  hEcc3[i] = new TH1D(Form("hEcc3_%d", i),"Ecc Distribution;Ecc;Events",1100,-0.05,1.05);
  hEcc4[i] = new TH1D(Form("hEcc4_%d", i),"Ecc Distribution;Ecc;Events",1100,-0.05,1.05);
  hEcc5[i] = new TH1D(Form("hEcc5_%d", i),"Ecc Distribution;Ecc;Events",1100,-0.05,1.05);

  nt_Xe_Xe->Draw(Form("Ecc2>>+hEcc2[%d]",i),Form("B>=%f&&B<%f", bRanges[i],bRanges[i+1]));
  nt_Xe_Xe->Draw(Form("Ecc3>>+hEcc3[%d]",i),Form("B>=%f&&B<%f", bRanges[i],bRanges[i+1]));
  nt_Xe_Xe->Draw(Form("Ecc4>>+hEcc4[%d]",i),Form("B>=%f&&B<%f", bRanges[i],bRanges[i+1]));
  nt_Xe_Xe->Draw(Form("Ecc5>>+hEcc5[%d]",i),Form("B>=%f&&B<%f", bRanges[i],bRanges[i+1]));

}



//  TCanvas *can=new TCanvas("can","can",10,10,660,510);
//hB->Draw();
//TLine *line = new TLine(hB->GetBinCenter(iBin5),0,hB->GetBinCenter(iBin5),hB->GetMaximum()*0.8)
//line->Draw();
/*
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
*/
//can->SaveAs("plot_xexe_dist.png");


}


