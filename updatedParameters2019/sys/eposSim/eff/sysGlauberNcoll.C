void sysGlauberNcoll(){

 const int nSys=3;
 const int nCentBin=200;
 int sysV[nSys]={99, 97, 101};
 TFile *glauberFile; 
 TH1D *pnpartVsCent = new TH1D("pnpartvscent","pnpartvscent",nCentBin,0,nCentBin);
 TH1D *pncollVsCent = new TH1D("pncollvscent","pncollvscent",nCentBin,0,nCentBin);
 TH1D *pbVsCent = new TH1D("pbvscent","pbvscent",nCentBin,0,nCentBin);
 TH1D *histNpart[nSys];
 TH1D *histNcoll[nSys];
 TH1D *histB[nSys];
 for(int i=0; i<nSys; i++) {
  glauberFile = new TFile(Form("./out/default_glauber_eff%dsmeared0808.root",sysV[i]),"read");
  histNpart[i] = (TH1D*)glauberFile->Get("hNpartCent");
  histNcoll[i] = (TH1D*)glauberFile->Get("hNcollCent");
  histNpart[i]->SetDirectory(0);
  histNcoll[i]->SetDirectory(0);
  glauberFile->Close();
  if(i>0)
    histNcoll[i]->Divide(histNcoll[0]);
 }
 histNcoll[0]->Divide(histNcoll[0]);
//histNcoll[0]->Draw();
for(int j=0; j<nCentBin; j++) { 
  cout<<histNcoll[2]->GetBinContent(j+1)<<", "<<histNcoll[1]->GetBinContent(j+1)<<endl;
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
 hist->SetXTitle("Centrality bins");
 //hist->SetYTitle("<N_{part}>");
 hist->SetYTitle("<N_{coll}> over <N_{coll}> with Eff=99%");
 //hist->SetYTitle("<b> (fm)");
 hist->SetMinimum(0.50);
 //hist->SetMaximum(histNcoll[0]->GetMaximum()*1.2);
 hist->SetMaximum(1.50);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.3);
 hist->GetXaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleSize(0.056);
 hist->GetYaxis()->SetTitleSize(0.056);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();
 int colors[nSys]={1,2,4};
 int markers[nSys]={24,20,25};
 for(int i=0; i<nSys; i++) {
  histNcoll[i]->Rebin(5);
  histNcoll[i]->Scale(1.0/5);
  histNcoll[i]->SetLineWidth(3);
  histNcoll[i]->SetLineColor(colors[i]);
  histNcoll[i]->SetMarkerColor(colors[i]);
  histNcoll[i]->SetMarkerStyle(markers[i]);
  histNcoll[i]->SetMarkerSize(0.8);
  histNcoll[i]->Draw("Lsame");
 }

    TLegend *leg0 = new TLegend(0.25,0.705,0.44,0.905);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.048);
    for(int i=0; i<nSys; i++)
      leg0->AddEntry(histNcoll[i],Form("Eff%d",sysV[i]),"L");
    leg0->Draw();
    TLatex *tex1= new TLatex(5,70,"PbPb  #sqrt{s_{NN}} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.048);
    tex1->SetTextFont(42);
    tex1->Draw();

  c1->SaveAs("ncollGlauberSysValue.png");
  c1->SaveAs("ncollGlauberSysValue.pdf");

}

