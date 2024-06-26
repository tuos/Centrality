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

void HFNpartPlot10Cent(){

    gROOT->Reset();
    gStyle->SetOptStat(0);

const int nC=10;
TH2D *npartvshf[nC];
  TFile *file = new TFile("/store/user/yilun/GlauberRun3/tables_Glauber2019A_ForEposLHC5020Responsenbins10x_d20190806_Smearing975Eff.root","read");

for(int i=0; i<nC; i++){
npartvshf[i] = (TH2D*)file->Get(Form("Glauber_Default_Para/HFvsNpart_%d",i));
}
int colors[nC]={1, 2, 4, 6, 46,  1, 2, 4, 6, 46};
npartvshf[0]->GetYaxis()->SetTitleOffset(1.3);
npartvshf[0]->GetYaxis()->SetRange(10,10000);
//npartvshf[0]->GetXaxis()->SetRange(0,400);
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
  //TCanvas* c1 = new TCanvas("c1","c1", 600, 600);
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

    TLatex *tex2= new TLatex(308.02,2118.001,"10-20%");
    tex2->SetTextColor(6);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(228.02,1518.001,"20-30%");
    tex3->SetTextColor(4);
    tex3->SetTextSize(0.045);
    tex3->SetTextFont(42);
    tex3->Draw();
    TLatex *tex4= new TLatex(165.02,1020.001,"30-40%");
    tex4->SetTextColor(2);
    tex4->SetTextSize(0.045);
    tex4->SetTextFont(42);
    tex4->Draw();
    TLatex *tex5= new TLatex(119.02,700.001,"40-50%");
    tex5->SetTextColor(1);
    tex5->SetTextSize(0.045);
    tex5->SetTextFont(42);
    tex5->Draw();
    TLatex *tex6= new TLatex(78.02,418.001,"50-60%");
    tex6->SetTextColor(46);
    tex6->SetTextSize(0.045);
    tex6->SetTextFont(42);
    tex6->Draw();
    TLatex *tex7= new TLatex(47.02,218.001,"60-70%");
    tex7->SetTextColor(6);
    tex7->SetTextSize(0.045);
    tex7->SetTextFont(42);
    tex7->Draw();
    TLatex *tex8= new TLatex(29.02,118.001,"70-80%");
    tex8->SetTextColor(4);
    tex8->SetTextSize(0.045);
    tex8->SetTextFont(42);
    tex8->Draw();
    TLatex *tex9= new TLatex(15.02,49.001,"80-90%");
    tex9->SetTextColor(2);
    tex9->SetTextSize(0.045);
    tex9->SetTextFont(42);
    tex9->Draw();
    TLatex *tex10= new TLatex(11.02,18.001,"90-100%");
    tex10->SetTextColor(1);
    tex10->SetTextSize(0.045);
    tex10->SetTextFont(42);
    tex10->Draw();
    TLatex *tex11= new TLatex(129.,30.075,"CMS Glauber MC Simulation");
    tex11->SetTextColor(1);
    tex11->SetTextSize(0.04);
    tex11->SetTextFont(42);
    tex11->Draw();
    TLatex *tex12= new TLatex(129.,18.0328,"HYDJET PbPb #sqrt{s_{NN}} = 5.36 TeV Smearing");
    tex12->SetTextColor(1);
    tex12->SetTextSize(0.04);
    tex12->SetTextFont(42);
    tex12->Draw();

c1->Print("hfNpart10Cent.C");
c1->Print("hfNpart10Cent.png");
c1->Print("hfNpart10Cent.pdf");



}
