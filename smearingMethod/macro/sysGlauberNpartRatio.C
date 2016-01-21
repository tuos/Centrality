void sysGlauberNpartRatio(){

 const int nSys=11;
 const int nCentBin=200;
 char sysV[nSys][200]={"Glauber_Default_Para", "Glauber_Radius_down", "Glauber_Radius_up",
"Glauber_SkinDepth_down", "Glauber_SkinDepth_up", "Glauber_dmin_down",
"Glauber_dmin_up", "Glauber_SigmaNN_down", "Glauber_SigmaNN_up", 
"Eff_Sys_1", "Eff_Sys_3"};
 TFile *glauberFile = new TFile("histGlauber.root","read");
 TH1D *pnpartVsCent = new TH1D("pnpartvscent","pnpartvscent",nCentBin,0,nCentBin);
 TH1D *pncollVsCent = new TH1D("pncollvscent","pncollvscent",nCentBin,0,nCentBin);
 TH1D *histNpart[nSys];
 TH1D *histNcoll[nSys];
 TH1D *histNxxxxR[nSys];
 for(int i=0; i<nSys; i++) {
  histNxxxxR[i]= new TH1D(Form("nxxxxvscent_%d",i),"nxxxxvscent",nCentBin,0,nCentBin);
  histNpart[i] = (TH1D*)glauberFile->Get(Form("%s/npartvscent",sysV[i]));
  histNcoll[i] = (TH1D*)glauberFile->Get(Form("%s/ncollvscent",sysV[i]));
  histNxxxxR[i]->Divide(histNpart[i],histNpart[0],1.,1.,"b");
 }


  TCanvas *c1 = new TCanvas("c1","c1",1,1,550,460);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,0,200);
 hist->SetXTitle("Centrality bin");
 //hist->SetYTitle("<N_{part}>");
 hist->SetYTitle("<N_{part}>/<N_{part}^{default}>");
 //hist->SetYTitle("<b> (fm)");
 hist->SetMinimum(0.8);
 hist->SetMaximum(2);
 //hist->SetMaximum(9.99);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.3);
 hist->GetXaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleSize(0.056);
 hist->GetYaxis()->SetTitleSize(0.056);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();
 int colors[nSys]={1,2,3,4,5,6,7,8,9,36,46};
 int markers[nSys]={7,2,5,24,25,26,27,28,30,31,32};
 for(int i=0; i<nSys; i++) {
  histNxxxxR[i]->SetLineColor(colors[i]);
  histNxxxxR[i]->SetMarkerColor(colors[i]);
  histNxxxxR[i]->SetMarkerStyle(markers[i]);
  histNxxxxR[i]->SetMarkerSize(0.8);
  histNxxxxR[i]->Draw("psame");
 }

    TLegend *leg0 = new TLegend(0.45,0.405,0.74,0.905);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.048);
    for(int i=0; i<nSys; i++)
      leg0->AddEntry(histNxxxxR[i],Form("%s",sysV[i]),"p");
    leg0->Draw();
    TLatex *tex1= new TLatex(10,0.86,"PbPb \ #sqrt{s_{NN}} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.048);
    tex1->SetTextFont(42);
    tex1->Draw();

  c1->SaveAs("npartSysValueRatio.png");

}


