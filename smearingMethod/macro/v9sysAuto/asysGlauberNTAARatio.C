void asysGlauberNTAARatio(){

 const int nSys=10;
 const int nCentBin=20;
 char sysV[nSys][200]={"Glauber_Default_Para", "Glauber_Radius_down", "Glauber_Radius_up",
"Glauber_SkinDepth_down", "Glauber_SkinDepth_up", "Glauber_dmin_down",
"Glauber_dmin_up", "Glauber_SigmaNN_down", "Glauber_SigmaNN_up", 
"Eff_Sys_1"};
 TFile *glauberFile = new TFile("histGlauberHydjet5020GeV0323nbins20x.root","read");
 TH1D *pnpartVsCent = new TH1D("pnpartvscent","pnpartvscent",nCentBin,0,100);
 TH1D *pncollVsCent = new TH1D("pncollvscent","pncollvscent",nCentBin,0,100);
 TH1D *histNpart[nSys];
 TH1D *histNcoll[nSys];
 TH1D *histNxxxxR[nSys];
 for(int i=0; i<nSys; i++) {
  histNxxxxR[i]= new TH1D(Form("nxxxxvscent_%d",i),"nxxxxvscent",nCentBin,0,100);
  histNpart[i] = (TH1D*)glauberFile->Get(Form("%s/npartvscent",sysV[i]));
  histNcoll[i] = (TH1D*)glauberFile->Get(Form("%s/ncollvscent",sysV[i]));
  histNxxxxR[i]->Divide(histNcoll[i],histNcoll[0],1.,1.,"b");
 }

 TH1D *histSys[4];
 double tmp;
for(int j=0; j<4; j++){
 histSys[j] = (TH1D*)histNcoll[j]->Clone(Form("histNcoll%d",j));
 for(int i=0; i<nCentBin;i++){
   if(histNxxxxR[2*j+1]->GetBinContent(i+1)>histNxxxxR[2*j+2]->GetBinContent(i+1))
     tmp=histNxxxxR[2*j+1]->GetBinContent(i+1);
   else 
     tmp = histNxxxxR[2*j+2]->GetBinContent(i+1);
   histSys[j]->SetBinContent(i+1, tmp);
 }
}
 TFile *effFile = new TFile("effSysNcoll10Bins.root","read");
 TH1D *histNcollx;
 histNcollx = (TH1D *)effFile->Get("effSysNpart99");
 histNxxxxR[9] = (TH1D*)histNcollx->Clone("ncollvscentx");

 TH1D *histSysAll=(TH1D*)histNcollx->Clone("histSysAll");
 TH1D *histSysAll2=(TH1D*)histNcollx->Clone("histSysAll2");
 for(int i=0; i<nCentBin;i++){
  tmp=0;
  for(int j=0; j<4; j++){
    if(j==3) continue;
    tmp+=(histSys[j]->GetBinContent(i+1)-1)*(histSys[j]->GetBinContent(i+1)-1);
  }
  tmp+=(histNcollx->GetBinContent((i)/2+1)-1)*(histNcollx->GetBinContent((i)/2+1)-1);
  //tmp+=0.0001;
  histSysAll->SetBinContent(i+1, 1+sqrt(tmp));
  histSysAll2->SetBinContent(i+1, 1.0/(1+sqrt(tmp)));
 }

  TF1 *fit = new TF1("fit","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x",0,100);
  fit->SetLineColor(1);
  fit->SetLineWidth(5);
  fit->SetLineStyle(2);
  //histSysAll->Fit("fit");

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
 TH1D* hist = new TH1D("hist","",100,0,100);
 hist->SetXTitle("Centrality (%)");
 //hist->SetYTitle("<N_{part}>");
 hist->SetYTitle("<T_{AA}>/<T_{AA}^{default}>");
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
 int colors[nSys]={1,2,3,4,36,6,7,8,9,46};
 int markers[nSys]={24,2,5,25,26,27,28,30,31,32};
 for(int i=0; i<nSys; i++) {
  histNxxxxR[i]->SetLineColor(colors[i]);
  histNxxxxR[i]->SetMarkerColor(colors[i]);
  histNxxxxR[i]->SetMarkerStyle(markers[i]);
  histNxxxxR[i]->SetMarkerSize(0.9);
  if(i==7||i==8) continue;
  histNxxxxR[i]->Draw("psame");
 }
 //histSysAll->SetFillStyle(3001);
 //histSysAll->SetFillColor(2);
 //histSysAll2->SetFillColor(2);
 histSysAll->SetLineWidth(2);
 histSysAll2->SetLineWidth(2);
 //histSysAll->Draw("lsame");
 //histSysAll2->Draw("lsame");
  //fit->Draw("same");
for(int i=0; i<nCentBin; i++) cout<<i*10<<" - "<<(i+1)*10<<"%   "<<(histSysAll->GetBinContent(i+1)-1)*100<<"%   "<<(fit->Integral(i*10,(i+1)*10)/10-1)*100<<"%."<<endl;
//for(int i=0; i<nCentBin; i++) cout<<i*10<<" - "<<(i+1)*10<<"%   "<<(histSysAll->GetBinContent(i+1)-1)*100<<"%."<<endl;

    TLegend *leg0 = new TLegend(0.45,0.405,0.74,0.905);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.048);
    for(int i=0; i<nSys-1; i++){
      if(i==7||i==8) continue;
      leg0->AddEntry(histNxxxxR[i],Form("%s",sysV[i]),"p");
    }
    leg0->AddEntry(histNxxxxR[i],Form("Eff_Sys (99+/-2%)"),"p");
    //leg0->AddEntry(histSysAll,Form("Total Sys."),"l");
    leg0->Draw();
    TLatex *tex1= new TLatex(10,0.86,"PbPb \ #sqrt{s_{NN}} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.048);
    tex1->SetTextFont(42);
    tex1->Draw();
TLine *l=new TLine(0,1,100,1);
l->SetLineWidth(2);
l->SetLineStyle(2);
l->SetLineColor(4);
l->Draw();

  c1->SaveAs("nTAASysValueRatio_a.png");
  c1->SaveAs("nTAASysValueRatio_a.pdf");

}


