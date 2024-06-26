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

#include "./vandyStyle.h"

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

  TFile *file = new TFile("/store/user/yilun/GlauberRun3/tables_Glauber2019A_ForEposLHC5020Responsenbins10x_d20190806_Smearing975Eff.root","read");
if(1){
for(int i=0; i<nC; i++){
npart[i] = (TH1D*)file->Get(Form("Glauber_Default_Para/NpartBin_%d",i));
}

 TH2D * histHFNpart;
 histHFNpart = (TH2D*)file->Get(Form("Glauber_Default_Para/HFvsNpart_%d",1));
 //TH1D *hNpart = histHFNpart->ProjectionX("hNpart", 0, 6001);

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
    TLatex *tex2= new TLatex(238.02,0.0016,"10-20%");
    tex2->SetTextColor(6);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(161.02,0.0019,"20-30%");
    tex3->SetTextColor(4);
    tex3->SetTextSize(0.045);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(165.02,1020.001,"30-40%");
    tex4->SetTextColor(2);
    tex4->SetTextSize(0.045);
    tex4->SetTextFont(42);
    //tex4->Draw();
    TLatex *tex5= new TLatex(65.02,0.0032,"40-50%");
    tex5->SetTextColor(1);
    tex5->SetTextSize(0.045);
    tex5->SetTextFont(42);
    tex5->Draw();
    TLatex *tex6= new TLatex(78.02,418.001,"50-60%");
    tex6->SetTextColor(46);
    tex6->SetTextSize(0.045);
    tex6->SetTextFont(42);
    //tex6->Draw();
    TLatex *tex7= new TLatex(24.02,0.0062,"60-70%");
    tex7->SetTextColor(6);
    tex7->SetTextSize(0.045);
    tex7->SetTextFont(42);
    tex7->Draw();
    TLatex *tex8= new TLatex(14.02,0.0092,"70-80%");
    tex8->SetTextColor(4);
    tex8->SetTextSize(0.045);
    tex8->SetTextFont(42);
    //tex8->Draw();
    TLatex *tex9= new TLatex(15.02,49.001,"80-90%");
    tex9->SetTextColor(2);
    tex9->SetTextSize(0.045);
    tex9->SetTextFont(42);
    //tex9->Draw();
    TLatex *tex10= new TLatex(8.02,0.03,"90-100%");
    tex10->SetTextColor(1);
    tex10->SetTextSize(0.045);
    tex10->SetTextFont(42);
    tex10->Draw();

    TLatex *tex11= new TLatex(113.42,0.035,"CMS Glauber MC Simulation");
    tex11->SetTextColor(1);
    tex11->SetTextSize(0.04);
    tex11->SetTextFont(42);
    tex11->Draw();
    TLatex *tex12= new TLatex(113.42,0.0178,"HYDJET PbPb #sqrt{s_{NN}} = 5.36 TeV Smearing");
    tex12->SetTextColor(1);
    tex12->SetTextSize(0.04);
    tex12->SetTextFont(42);
    tex12->Draw();

c1->Print("npart1D10Cent.C");
c1->Print("npart1D10Cent.png");
c1->Print("npart1D10Cent.pdf");
}


}

