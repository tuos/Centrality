#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <TF1.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <TChain.h>
#include <TFile.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TTree.h>

using namespace std;

void produceResponseHistograms(){

const int nhist = 3;
TH2D * HF_vs_Npart[nhist];
TH2D * Npix_vs_Npart[nhist];
TH2D * Npix_vs_HF;

 TFile * infile = TFile::Open("/store/user/tuos/PbPbSimulation2018/HiForest_MC_EposLHC_2018_5p02TeV_merged.root");  // EPOS
 //TFile * infile = TFile::Open("/store/user/tuos/PbPbSimulation2018/HiForest_MC_Hydjet_Drum5F_merged.root");  // HYDJET

 //TTree * tskim = (TTree *) infile->Get("skimanalysis/HltTree");
 //int selHFp;	tskim->SetBranchAddress("phfPosFilter1", &selHFp);
 //int selHFm;	tskim->SetBranchAddress("phfNegFilter1", &selHFm);
 //int selVtx;	tskim->SetBranchAddress("pprimaryvertexFilter", &selVtx);

 //TTree * thlt  = (TTree *) infile->Get("hltanalysis/HltTree");
 //int trig;	thlt->SetBranchAddress("HLT_PAZeroBiasPixel_SingleTrack_v1", &trig);

 TTree * teven = (TTree *) infile->Get("hiEvtAnalyzer/HiTree");
 float b;		teven->SetBranchAddress("b", &b);
 float npart;		teven->SetBranchAddress("Npart", &npart);
 float ncoll;		teven->SetBranchAddress("Ncoll", &ncoll);
 float nhard;		teven->SetBranchAddress("Nhard", &nhard);
 UInt_t run;		teven->SetBranchAddress("run", &run);
 UInt_t lumi;		teven->SetBranchAddress("lumi", &lumi);
 float vtxZ;		teven->SetBranchAddress("vz",&vtxZ);
 float hf;		teven->SetBranchAddress("hiHF", &hf);
 float hfplus;		teven->SetBranchAddress("hiHFplus", &hfplus);
 float hfpluseta4;	teven->SetBranchAddress("hiHFplusEta4", &hfpluseta4);
 float hfminuseta4;	teven->SetBranchAddress("hiHFminusEta4", &hfminuseta4);
 float hfminus;		teven->SetBranchAddress("hiHFminus", &hfminus);
 float hfhit;		teven->SetBranchAddress("hiHFhit", &hfhit);
 float ee;		teven->SetBranchAddress("hiEE",	&ee);
 float eb;		teven->SetBranchAddress("hiEB",	 &eb);
 int npix;		teven->SetBranchAddress("hiNpix", &npix);
 int npixtrks;		teven->SetBranchAddress("hiNpixelTracks", &npixtrks);
 int ntrks;		teven->SetBranchAddress("hiNtracks", &ntrks);

 TFile * effFile = new TFile("out/histEff_2018EPOS.root","read"); // still use EPOS eff. fun, for Hydjet
 TH1D * histEff[nhist];
 for(int i=0; i<nhist; i++) {
  histEff[i] = (TH1D*)effFile->Get(Form("effSys/effhist_%d",i));
 }

 //Create 1D and 2D histograms
 bool sel[nhist] = {0};

 for (int ih = 0; ih < nhist; ih++) {

  HF_vs_Npart[ih]= new TH2D(Form("HF_vs_Npart_%d",ih),";N_{part};#Sigma HF E_{T}",450,0,450,6000,0,6000);
  Npix_vs_Npart[ih]= new TH2D(Form("Npix_vs_Npart_%d",ih),";N_{part};hiNpix",450,0,450,45000,0,45000);

 }
  Npix_vs_HF = new TH2D(Form("Npix_vs_HF"),";#Sigma HF E_{T};hiNpix",6000,0,6000,4500,0,45000);

 TRandom3 *rnd = new TRandom3(0);
 // event loop
 int nEvents = teven->GetEntries();
 //if (nEvents != tskim->GetEntries() || nEvents != thlt->GetEntries() || nEvents != tgen->GetEntries()) cout << "Error in number of events" << endl;
 //nEvents=5000;
 for(int iev = 0; iev < nEvents; iev++) {

   for(int ih = 0; ih < nhist; ih++) sel[ih] = false;

   if(iev%2000 == 0) cout << "Processing event: " << iev << endl;
   //tskim->GetEntry(iev);
   //thlt->GetEntry(iev);
   teven->GetEntry(iev);
   //tgen->GetEntry(iev);


   for(int i=0; i<nhist; i++) {
     if (rnd->Uniform(0,1) < histEff[i]->GetBinContent(histEff[i]->FindBin(hf))) sel[i] = true;
   }

   for(int ih = 0; ih < nhist; ih++) {
    //if(sel[ih] == false) cout<<"This event is not selected"<<endl;
    if(sel[ih]) {
      HF_vs_Npart[ih]->Fill(npart,hf);
      Npix_vs_Npart[ih]->Fill(npart,npix);
    }
   }
   if(sel[0]) Npix_vs_HF->Fill(hf,npix);

 }// end of event loop

  //TFile * outfile = new TFile("out/ForSmearingHydjetDrum5F_2018Response5020_d20190805_v1.root","recreate");
  TFile * outfile = new TFile("out/ForSmearingEposLHC_2018Response5020_d20190806_v1.root","recreate");
  //TFile * outfile = new TFile("out/ForSmearingHydjetResponse5020_d20160324_v1.root","recreate");
  TDirectory * dir = outfile->mkdir("SmearingHist");
  outfile->cd();
  dir->cd();
  for(int ih = 0; ih < nhist; ih++) {
    HF_vs_Npart[ih]->Write();
    Npix_vs_Npart[ih]->Write();
  }
  Npix_vs_HF->Write();
  outfile->Write();


}

