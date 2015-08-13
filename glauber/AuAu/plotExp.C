{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TFile f("glauberAuAu_default_1M.root");

  TH1D* hb4 = new TH1D("hb4","",25000,0.,25);
  nt_Au_Au->Project("hb4","B");
  //tree4->Draw("b>>b4","","GOFF");

  long int nCounts=0;
  int iBin05=0;
  int iBin10=0;
  int iBin20=0;
  int iBin30=0;
  int iBin40=0;
  int iBin50=0;
  int iBin60=0;
  int iBin100=1;

  for(int i=1; i<=hb4->GetNbinsX(); i++){
    nCounts=nCounts+hb4->GetBinContent(i);
    if(nCounts>=(0.05*hb4->GetEntries())&&iBin05==0){
      iBin05=i;
      cout<<"5  "<<hb4->GetBinCenter(iBin05)<<endl;
    }
    if(nCounts>=(0.1*hb4->GetEntries())&&iBin10==0){
      iBin10=i;
      cout<<"10  "<<hb4->GetBinCenter(iBin10)<<endl;
    }
    if(nCounts>=(0.2*hb4->GetEntries())&&iBin20==0){
      iBin20=i;
      cout<<"20  "<<hb4->GetBinCenter(iBin20)<<endl;
    }
    if(nCounts>=(0.3*hb4->GetEntries())&&iBin30==0){
      iBin30=i;
      cout<<"30  "<<hb4->GetBinCenter(iBin30)<<endl;
    }
    if(nCounts>=(0.4*hb4->GetEntries())&&iBin40==0){
      iBin40=i;
      cout<<"40  "<<hb4->GetBinCenter(iBin40)<<endl;
    }
    if(nCounts>=(0.5*hb4->GetEntries())&&iBin50==0){
      iBin50=i;
      cout<<"50  "<<hb4->GetBinCenter(iBin50)<<endl;
    }
    if(nCounts>=(0.6*hb4->GetEntries())&&iBin60==0){
      iBin60=i;
      cout<<"60  "<<hb4->GetBinCenter(iBin60)<<endl;
    }
  }  
    cout<<"100  "<<30<<endl;

  TCanvas* cd = new TCanvas("cd","",600,500);
  cd->SetLeftMargin(0.12);
  cd->SetRightMargin(0.02);
  cd->SetTopMargin(0.02);
  cd->SetBottomMargin(0.12);
  cd->SetTicks(1);
   
  hb4->Draw("pez");
    TLatex *tex1= new TLatex(-1.6,1000.305,"AMPT, 5TeV PbPb, b=0fm");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(62);
    tex1->Draw();

 //cd->SaveAs("dNdetab0PbPb5TeV.png");

}
