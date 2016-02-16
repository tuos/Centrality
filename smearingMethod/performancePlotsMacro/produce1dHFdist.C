#include "/Users/tuos/Dropbox/RUN2015/rpPb/pPbSpectra/hin12017/plotStyle/vandyStyle.h"

void SetHistStyle(){
    gPad->SetTicks();
    gPad->SetLeftMargin(0.14);
    gPad->SetBottomMargin(0.16);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    //gPad->SetLogx(1);
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
}

void produce1dHFdist(){

 TH1::SetDefaultSumw2();
 TFile * histFile = new TFile("./out/dHistHydjet5020b_d20150828_v1.root","read");
 //TFile * histFile = new TFile("./ForSmearingEposResponse5020_d20160216_v1.root","read");
 TH2D * histHFNpart;
 histHFNpart = (TH2D*)histFile->Get(Form("SmearingHist/HF_vs_Npart_%d",1));
 //histHFNpart->Draw("colz");
 TH1D *hNpart20 = histHFNpart->ProjectionY("hNpart20", 21, 21);
 TH1D *hNpart100 = histHFNpart->ProjectionY("hNpart100", 101, 101);
 TH1D *hNpart200 = histHFNpart->ProjectionY("hNpart200", 201, 201);
 TH1D *hNpart400 = histHFNpart->ProjectionY("hNpart400", 401, 401);

  int rebin[4]={20, 40, 40, 40};
  hNpart20->Rebin(rebin[0]);
  hNpart100->Rebin(rebin[1]);
  hNpart200->Rebin(rebin[2]);
  hNpart400->Rebin(rebin[3]);
  hNpart20->Scale(1.0/hNpart20->GetEntries());
  hNpart100->Scale(1.0/hNpart100->GetEntries());
  hNpart200->Scale(1.0/hNpart200->GetEntries());
  hNpart400->Scale(1.0/hNpart400->GetEntries());
  hNpart20->SetMarkerStyle(20);
  hNpart20->SetMarkerColor(1);
  hNpart20->SetMarkerSize(1.0);
  hNpart100->SetMarkerStyle(21);
  hNpart100->SetMarkerColor(2);
  hNpart100->SetMarkerSize(1.0);
  hNpart200->SetMarkerStyle(24);
  hNpart200->SetMarkerColor(4);
  hNpart200->SetMarkerSize(1.0);
  hNpart400->SetMarkerStyle(25);
  hNpart400->SetMarkerColor(6);
  hNpart400->SetMarkerSize(1.0);
  hNpart20->SetAxisRange(0.01,hNpart20->GetMaximum()*2.8,"Y");
  hNpart20->SetAxisRange(0,5900,"X");
  //TCanvas* c1 = makeMultiCanvas("c1","c1", true, true);
  vandyStyle();
  TCanvas* c1 = makeMultiCanvas("c1","c1", true, true);
  SetHistStyle();
  fixedFontHist1D(hNpart20, 1.1, 1.1);
  hNpart20->GetYaxis()->SetTitle("Event Faction");
  hNpart20->GetXaxis()->SetTitle("#Sigma HF E_{T} (GeV)");
  hNpart20->Draw("PE");
  hNpart100->Draw("PEsame");
  hNpart200->Draw("PEsame");
  hNpart400->Draw("PEsame");

    TLegend *leg0 = new TLegend(0.75,0.66,0.91,0.865);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.035);
    leg0->SetTextFont(42);
    leg0->SetTextSize(0.048);
    leg0->AddEntry(hNpart20,"N_{part} = 20","pl");
    leg0->AddEntry(hNpart100,"N_{part} = 100","pl");
    leg0->AddEntry(hNpart200,"N_{part} = 200","pl");
    leg0->AddEntry(hNpart400,"N_{part} = 400","pl");
    leg0->Draw();
    TLatex *tex1= new TLatex(400.5,0.6,"PbPb 5.02 TeV HYDJET Smearing");
    //TLatex *tex1= new TLatex(400.5,0.6,"PbPb 5.02 TeV EPOS Smearing");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

c1->SaveAs("smearing1dNpartHydjet5020GeV.C");
c1->SaveAs("smearing1dNpartHydjet5020GeV.png");
c1->SaveAs("smearing1dNpartHydjet5020GeV.pdf");
//c1->SaveAs("smearing1dNpartEpos5020GeV.C");
//c1->SaveAs("smearing1dNpartEpos5020GeV.png");
//c1->SaveAs("smearing1dNpartEpos5020GeV.pdf");

}
