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

void NpartDist10Cent(){

    gROOT->Reset();
    gStyle->SetOptStat(0);

TH2D *npartpt;
TH2D *pthf;
TH2D *nparthf;
const int nC=10;
TH2D *npartvshf[nC];
TH1D *npart[nC];

  TFile *file = new TFile("tables_Glauber2015A_ForHydjetResponsebin10_d20150826_SmearingEff.root","read");
if(1){
for(int i=0; i<nC; i++){
npart[i] = (TH1D*)file->Get(Form("Glauber_Default_Para/NpartBin_%d",i));
}

 TH2D * histHFNpart;
 histHFNpart = (TH2D*)file->Get(Form("Glauber_Default_Para/HF_vs_Npart_%d",1));
 TH1D *hNpart = histHFNpart->ProjectionX("hNpart", 0, 6001);

int colors[nC]={1, 2, 4, 6, 46,  1, 2, 4, 6, 46};
npart[0]->GetYaxis()->SetTitleOffset(1.3);
//npart[0]->GetYaxis()->SetRange(0,70);
npart[0]->GetYaxis()->SetTitle("Normalized");
npart[0]->GetXaxis()->SetTitle("N_{part}");
npart[0]->GetXaxis()->SetRange(0,450);
 npart[0]->GetXaxis()->CenterTitle(1);
 npart[0]->GetYaxis()->CenterTitle(1);
 npart[0]->GetYaxis()->SetTitleOffset(1.1);
 npart[0]->GetXaxis()->SetTitleOffset(0.9);
 npart[0]->GetXaxis()->SetTitleSize(0.056);
 npart[0]->GetYaxis()->SetTitleSize(0.056);
 npart[0]->GetXaxis()->SetLabelSize(0.05);
 npart[0]->GetYaxis()->SetLabelSize(0.05);
for(int j=0;j<nC;j++)
//npart[j]->Scale(1.0/npart[j]->GetEntries());
for(int i=0;i<450;i++){
     npart[j]->SetBinContent(i+1,npart[j]->GetBinContent(i+1)*1.0/1000000);
     //npart[j]->SetBinError(i+1,npart[j]->GetBinError(i+1)*1.0/1000000);
}
  vandyStyle();
  TCanvas* c1 = makeMultiCanvas("c1","c1", true, true);
  SetHistStyle();
  fixedFontHist1D(npart[0], 1.1, 1.1);

npart[0]->SetLineColor(1);
npart[0]->SetFillColor(1);
npart[0]->SetFillStyle(3350);
npart[0]->Draw();

/*
npart[1]->SetFillColor(2);
npart[1]->SetFillStyle(3001);
npart[1]->Draw("same");
npart[2]->SetFillColor(4);
npart[2]->SetFillStyle(3001);
npart[2]->Draw("same");
npart[3]->SetFillColor(6);
npart[3]->SetFillStyle(3001);
npart[3]->Draw("same");
npart[4]->SetFillColor(8);
npart[4]->SetFillStyle(3001);
npart[4]->Draw("same");
*/
int fills[nC]={3350, 3351, 3352, 3353, 3354, 3345, 3356, 3357, 3358, 3359};
for(int i=1; i<nC; i++){
npart[i]->SetLineColor(colors[i]);
npart[i]->SetFillColor(colors[i]);
npart[i]->SetFillStyle(fills[i]);
//npart[i]->SetFillStyle(4100);
npart[i]->Draw("same");
}
//hNpart->Scale(1.0/hNpart->GetEntries()/0.8);
//hNpart->Scale(1.0/1000000);
//hNpart->Draw("same");

    TLatex *tex1= new TLatex(342.02,0.0014,"0-10%");
    tex1->SetTextColor(46);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(238.02,0.0016,"10-20%");
    tex1->SetTextColor(6);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(161.02,0.0019,"20-30%");
    tex1->SetTextColor(4);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(165.02,1020.001,"30-40%");
    tex1->SetTextColor(2);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    //tex1->Draw();
    TLatex *tex1= new TLatex(65.02,0.0032,"40-50%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(78.02,418.001,"50-60%");
    tex1->SetTextColor(46);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    //tex1->Draw();
    TLatex *tex1= new TLatex(24.02,0.0062,"60-70%");
    tex1->SetTextColor(6);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(14.02,0.0092,"70-80%");
    tex1->SetTextColor(4);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    //tex1->Draw();
    TLatex *tex1= new TLatex(15.02,49.001,"80-90%");
    tex1->SetTextColor(2);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    //tex1->Draw();
    TLatex *tex1= new TLatex(8.02,0.03,"90-100%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();

    TLatex *tex1= new TLatex(113.42,0.035,"CMS Glauber MC Simulation");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.04);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(113.42,0.0178,"HYDJET PbPb \ #sqrt{s_{NN}} = 5.05 TeV Smearing");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.04);
    tex1->SetTextFont(42);
    tex1->Draw();

c1->Print("npart1D10Cent.C");
c1->Print("npart1D10Cent.png");
c1->Print("npart1D10Cent.pdf");
}


}

