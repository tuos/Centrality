void sysGlauberNpartALICE(){

 const int nSys=11;
 const int nCentBin=200;
 char sysV[nSys][200]={"Glauber_Default_Para", "Glauber_Radius_down", "Glauber_Radius_up",
"Glauber_SkinDepth_down", "Glauber_SkinDepth_up", "Glauber_dmin_down",
"Glauber_dmin_up", "Glauber_SigmaNN_down", "Glauber_SigmaNN_up", "Eff_Sys_1", "Eff_Sys_3"};
 TFile *glauberFile = new TFile("histGlauber.root","read");
 TH1D *pnpartVsCent = new TH1D("pnpartvscent","pnpartvscent",nCentBin,0,nCentBin);
 TH1D *pncollVsCent = new TH1D("pncollvscent","pncollvscent",nCentBin,0,nCentBin);
 TH1D *histNpart[nSys];
 TH1D *histNcoll[nSys];
 for(int i=0; i<nSys; i++) {
  histNpart[i] = (TH1D*)glauberFile->Get(Form("%s/npartvscent",sysV[i]));
  histNcoll[i] = (TH1D*)glauberFile->Get(Form("%s/ncollvscent",sysV[i]));
 }

  const int abin=11;
  double centbin[abin];
  double npartV[abin];
  double npartE[abin];
  ifstream intxt;
  intxt.open("aliceNpart.txt");
  for(int i=0; i<abin; i++){
    intxt>>centbin[i];
    intxt>>npartV[i];
    intxt>>npartE[i];
    centbin[i]=centbin[i]*2;
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
 hist->SetYTitle("<N_{part}>");
 //hist->SetYTitle("<b> (fm)");
 hist->SetMinimum(0.001);
 hist->SetMaximum(histNpart[0]->GetMaximum()*1.2);
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
  histNpart[i]->SetLineColor(colors[i]);
  histNpart[i]->SetMarkerColor(colors[i]);
  histNpart[i]->SetMarkerStyle(markers[i]);
  histNpart[i]->SetMarkerSize(0.8);
  histNpart[i]->Draw("psame");
 }

  TGraphErrors *graph = new TGraphErrors(abin,centbin,npartV,0,npartE);
  graph->SetTitle("");
  graph->SetMarkerStyle(20);
  graph->SetMarkerColor(1);
  graph->SetLineColor(1);
  graph->SetLineWidth(2);
  graph->SetMarkerSize(1.);
  graph->Draw("psameez");

    TLegend *leg0 = new TLegend(0.45,0.405,0.74,0.925);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.048);
    leg0->AddEntry(graph,"ALICE <N_{part}>, 1512.06104","p");
    for(int i=0; i<nSys; i++)
      leg0->AddEntry(histNpart[i],Form("%s",sysV[i]),"p");
    leg0->Draw();
    TLatex *tex1= new TLatex(10,30,"PbPb \ #sqrt{s_{NN}} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.048);
    tex1->SetTextFont(42);
    tex1->Draw();

  c1->SaveAs("npartSysValueALICE.png");

}


