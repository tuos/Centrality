#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TRandom.h>

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

void HFNpartPlot10Cent(){

    gROOT->Reset();
    gStyle->SetOptStat(0);

const int nC=10;
TH2D *npartvshf[nC];
  TFile *file = new TFile("tables_Glauber2015A_ForHydjetResponsebin10_d20150826_SmearingEff.root","read");

for(int i=0; i<nC; i++){
npartvshf[i] = (TH2D*)file->Get(Form("Glauber_Default_Para/HFvsNpart_%d",i));
}
int colors[nC]={1, 2, 4, 6, 46,  1, 2, 4, 6, 46};
npartvshf[0]->GetYaxis()->SetTitleOffset(1.3);
npartvshf[0]->GetYaxis()->SetRange(10,6000);
//npartvshf[0]->GetZaxis()->SetRangeUser(-1e12, 1e15);
npartvshf[0]->GetYaxis()->SetTitle("#Sigma HF E_{T} from Glauber (GeV)");
npartvshf[0]->GetXaxis()->SetTitle("N_{part}");
 npartvshf[0]->GetXaxis()->CenterTitle(1);
 npartvshf[0]->GetYaxis()->CenterTitle(1);
 npartvshf[0]->GetYaxis()->SetTitleOffset(0.9);
 npartvshf[0]->GetXaxis()->SetTitleOffset(0.9);
 npartvshf[0]->GetXaxis()->SetTitleSize(0.056);
 npartvshf[0]->GetYaxis()->SetTitleSize(0.056);
 npartvshf[0]->GetXaxis()->SetLabelSize(0.05);
 npartvshf[0]->GetYaxis()->SetLabelSize(0.05);

  vandyStyle();
  TCanvas* c1 = makeMultiCanvas("c1","c1", true, true);
  SetHistStyle();
  fixedFontHist1D(npartvshf[0], 1.1, 1.1);

npartvshf[0]->SetFillColor(1);
npartvshf[0]->SetFillStyle(1001);
npartvshf[0]->Draw("box");
for(int i=1; i<nC; i++){
npartvshf[i]->SetFillColor(colors[i]);
npartvshf[i]->SetFillStyle(1001);
npartvshf[i]->Draw("box same");
}
    TLatex *tex1= new TLatex(382.02,2700,"0-10%");
    tex1->SetTextColor(46);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(308.02,2118.001,"10-20%");
    tex1->SetTextColor(6);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(228.02,1518.001,"20-30%");
    tex1->SetTextColor(4);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(165.02,1020.001,"30-40%");
    tex1->SetTextColor(2);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(119.02,700.001,"40-50%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(78.02,418.001,"50-60%");
    tex1->SetTextColor(46);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(47.02,218.001,"60-70%");
    tex1->SetTextColor(6);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(29.02,118.001,"70-80%");
    tex1->SetTextColor(4);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(15.02,49.001,"80-90%");
    tex1->SetTextColor(2);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(11.02,18.001,"90-100%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(129.,30.075,"CMS Glauber MC Simulation");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.04);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(129.,18.0328,"HYDJET PbPb \ #sqrt{s_{NN}} = 5.02 TeV Smearing");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.04);
    tex1->SetTextFont(42);
    tex1->Draw();
c1->Print("hfNpart10Cent.C");
c1->Print("hfNpart10Cent.png");
c1->Print("hfNpart10Cent.pdf");



}
