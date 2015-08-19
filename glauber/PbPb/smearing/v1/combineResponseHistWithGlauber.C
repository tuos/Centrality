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

bool descend(float i,float j) { return (i<j); }

const int nhist = 6;
TH2D * Npart_vs_PtGenPlusEta4[nhist+1];
TH2D * PtGenPlusEta4_vs_HFplusEta4[nhist+1];
TH2D * Npart_vs_PtGenMinusEta4[nhist+1];
TH2D * PtGenMinusEta4_vs_HFminusEta4[nhist+1];
TH2D * Npart_vs_Ngentrk[nhist+1];
TH2D * Ngentrk_vs_Ntracks[nhist+1];
TH2D * Npart_vs_HFplusEta4[nhist+1];
TH2D * Npart_vs_HFminusEta4[nhist+1];
TH2D * Npart_vs_Ntracks[nhist+1];
TH1D * Proj1[1000];
TH1D * Proj2[1000];
TH1D * Projs[1000];
TH2D* hNparthf[6];
//TH2D* hNpartpt[6];
//TH2D* hpthf[6];
TH1D* hNpart1[6];
TH1D* hNpart00;

float et = 0;

//------------------------------------------------------------------------
void fitSlices(TH2* hCorr, TF1* func){

   int nBins = hCorr->GetNbinsX();

   TH1D* hMean = new TH1D(Form("%s_1",hCorr->GetName()),"",nBins,hCorr->GetXaxis()->GetXmin(),hCorr->GetXaxis()->GetXmax());
   TH1D* hSigma = new TH1D(Form("%s_2",hCorr->GetName()),"",nBins,hCorr->GetXaxis()->GetXmin(),hCorr->GetXaxis()->GetXmax());
   for(int i = 1; i < nBins+1; i++){
      int bin = nBins - i;
      TH1D* h = hCorr->ProjectionY(Form("%s_bin%d",hCorr->GetName(),bin),i,i);
      func->SetParameter(0,h->GetMaximum());

      hMean->SetBinContent(i,h->GetMean());
      hSigma->SetBinContent(i,h->GetRMS());
      hMean->SetBinError(i,h->GetMeanError());
      hSigma->SetBinError(i,h->GetRMSError());

   }

}
//------------------------------------------------------------------------
void getProjections(TH2D * h2, TH1D ** h1, const char* name, double merge, double mergePoint){
  
  if(!h2) return;
  for(int i = 0; i < h2->GetNbinsX()+1; i++){
    int imax = i;
    if(h2->GetBinCenter(i) > mergePoint) imax = i+merge;
    h1[i] = h2->ProjectionY(Form("%s_%d",name,i),i,imax);
    double integral = h1[i]->Integral();
    if(integral > 0){
      h1[i]->Scale(1./integral);
    }
  }

}
//------------------------------------------------------------------------
float getHFplusByPt(float Npart, int eff){
   
   int bin1 = Npart_vs_PtGenPlusEta4[eff]->GetXaxis()->FindBin(Npart);
   if(bin1 > Npart_vs_PtGenPlusEta4[eff]->GetNbinsX() ) bin1 = Npart_vs_PtGenPlusEta4[eff]->GetNbinsX();
   if(bin1 < 1) bin1 = 1; 
   if(bin1>23) bin1=23; //remove the bias of Npart(at high value) from mismatch of Hijing to Glauber;
   et = Proj1[bin1]->GetRandom();

   int bin2 = PtGenPlusEta4_vs_HFplusEta4[eff]->GetXaxis()->FindBin(et);
   if(bin2 > PtGenPlusEta4_vs_HFplusEta4[eff]->GetNbinsX()) bin2 = PtGenPlusEta4_vs_HFplusEta4[eff]->GetNbinsX();
   if(bin2 < 1) bin2 = 1;
   double hf = Proj2[bin2]->GetRandom();
   return hf;

}
//------------------------------------------------------------------------
float getByNpart(TH2D * hx, float Npart){  // one step smearing;

   int bin1 = hx->GetXaxis()->FindBin(Npart);
   if(bin1 > hx->GetNbinsX() ) bin1 = hx->GetNbinsX();
   if(bin1 < 1) bin1 = 1;
   if(bin1>23) bin1=23; //remove the bias of Npart(at high value) from mismatch of Hijing to Glauber;
   double hf = Projs[bin1]->GetRandom();
   return hf;
}
//------------------------------------------------------------------------
float getHFminusByPt(float Npart){
   
   int bin1 = Npart_vs_PtGenMinusEta4[0]->GetXaxis()->FindBin(Npart);
   if(bin1 > Npart_vs_PtGenMinusEta4[0]->GetNbinsX() ) bin1 = Npart_vs_PtGenMinusEta4[0]->GetNbinsX();
   if(bin1 < 1) bin1 = 1;
   et = Proj1[bin1]->GetRandom();

   int bin2 = PtGenMinusEta4_vs_HFminusEta4[0]->GetXaxis()->FindBin(et);
   if(bin2 > PtGenMinusEta4_vs_HFminusEta4[0]->GetNbinsX()) bin2 = PtGenMinusEta4_vs_HFminusEta4[0]->GetNbinsX();
   if(bin2 < 1) bin2 = 1;
   double hf = Proj2[bin2]->GetRandom();
   return hf;

}
//------------------------------------------------------------------------
float getTracksByGen(float Npart){
   
   int bin1 = Npart_vs_Ngentrk[0]->GetXaxis()->FindBin(Npart);
   if(bin1 > Npart_vs_Ngentrk[0]->GetNbinsX() ) bin1 = Npart_vs_Ngentrk[0]->GetNbinsX();
   if(bin1 < 1) bin1 = 1;
   et = Proj1[bin1]->GetRandom();

   int bin2 = Ngentrk_vs_Ntracks[0]->GetXaxis()->FindBin(et);
   if(bin2 > Ngentrk_vs_Ntracks[0]->GetNbinsX()) bin2 = Ngentrk_vs_Ntracks[0]->GetNbinsX();
   if(bin2 < 1) bin2 = 1;
   double hf = Proj2[bin2]->GetRandom();
   return hf;

}
//------------------------------------------------------------------------
void combineResponseHistWithGlauber(const int nbins = 5, const string label = "HFtowersPlusTrunc", const string tags = "Glauber_Default_Para", int eff = 0) {

   //const char* outfilename = "out/tables_Glauber2013B_EposResponse_d20130307_v5DoubleSmearingEff.root";
   //const char* outfilename = "out/tables_Glauber2013B_EposResponse_d20130307_v5SingleSmearingEff5.root";
   //const char* outfilename = "out/tables_Glauber2013B_EposResponse_d20130307_v5SingleSmearingNoEff.root";
   //const char* outfilename = "out/tables_Glauber2013B_EposResponse_d20130307_v5DoubleSmearingNoEff.root";
   //const char* outfilename = "out/tables_Glauber2013B_EposResponse_d20130307_v5DoubleSmearingNpart.root";
   //const char* outfilename = "out/tables_Glauber2013B_HijingResponse_d20130307_v5SingleSmearingEff.root";
   const char* outfilename = "out/tables_Glauber2013B_ForHijingResponse_d20130820_v5SingleSmearingEff.root";
   //const char* outfilename = "out/tables_Glauber2013B_QGSJetIIResponse_d20130307_v5SingleSmearingEff.root";
   //const char* inSmear = "out/Smear_HijingResponse_d20130306_v2.root";
   //const char* inSmear = "out/Smear_EposResponse_d20130306_v2.root";
   //const char* inSmear = "out/Smear_EposResponse_d20130306mit_v2.root";
   //const char* inSmear = "out/Smear_QGSJetIIResponse_d20130306_v2.root";
   //const char* inSmear = "out/Smear_HijingResponse_d20130306mit_v2.root";
   const char* inSmear = "out/ForSmear_HijingResponse_d20130820_v2.root";
   TFile* infSmear;
   infSmear = new TFile(inSmear);
  for (int ih = 0; ih < nhist+1; ih++) {
   Npart_vs_PtGenPlusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_PtGenPlusEta4_%d",ih));
   PtGenPlusEta4_vs_HFplusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/PtGenPlusEta4_vs_HFplusEta4_%d",ih));
   Npart_vs_PtGenMinusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_PtGenMinusEta4_%d",ih));
   PtGenMinusEta4_vs_HFminusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/PtGenMinusEta4_vs_HFminusEta4_%d",ih));
   Npart_vs_Ngentrk[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_Ngentrk_%d",ih));
   Ngentrk_vs_Ntracks[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Ngentrk_vs_Ntracks_%d",ih));
   Npart_vs_HFplusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_HFplusEta4_%d",ih));
   Npart_vs_HFminusEta4[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_HFminusEta4_%d",ih));
   Npart_vs_Ntracks[ih] = (TH2D*) infSmear->Get(Form("SmearingHist/Npart_vs_Ntracks_%d",ih));

   hNparthf[ih] = new TH2D(Form("NpartvsHFplusEta4_%d",ih),";N_{part};#Sigma HF E_{T} in #eta > 4",40,0,40,80,0,80);
   //hNpartpt[ih] = new TH2D(Form("NpartvsPtGenPlusEta4_%d",ih),";N_{part};#Sigma gen p_{T} in #eta > 4",400,0,40,400,0,60);
   //hpthf[ih] = new TH2D(Form("PtGenPlusEta4vsHFplusEta4_%d",ih),";#Sigma gen p_{T} in #eta > 4;#Sigma HF E_{T} in #eta > 4",400,0,60,400,0,80);
   hNpart1[ih] = new TH1D(Form("Npart1_%d",ih),"",40,0,40);
  }  
   hNpart00 = new TH1D("Npart00","",40,0,40);

//cout<<"???"<<endl;
 //input Glauber ntuple
bool SysGlauberStandard = tags.compare("Glauber_Default_Para") == 0;
bool SysGlauberRlow = tags.compare("Glauber_Radius_649") == 0;
bool SysGlauberRhigh = tags.compare("Glauber_Radius_675") == 0;
bool SysGlauberDlow = tags.compare("Glauber_SkinDepth_4914") == 0;
bool SysGlauberDhigh = tags.compare("Glauber_SkinDepth_6006") == 0;
bool SysGlauberdminlow = tags.compare("Glauber_dmin_00") == 0;
bool SysGlauberdminhigh = tags.compare("Glauber_dmin_08") == 0;
bool SysGlaubersigmalow = tags.compare("Glauber_SigmaNN_65") == 0;
bool SysGlaubersigmahigh = tags.compare("Glauber_SigmaNN_75") == 0;
bool SysEff1 = tags.compare("Eff_Sys_1") == 0;
bool SysEff2 = tags.compare("Eff_Sys_2") == 0;
bool SysEff3 = tags.compare("Eff_Sys_3") == 0;
bool SysEff4 = tags.compare("Eff_Sys_4") == 0;
bool SysEff5 = tags.compare("Eff_Sys_5") == 0;
bool SysEff6 = tags.compare("Eff_Sys_6") == 0;

const char * infilename;
char fdirname[200];
sprintf(fdirname,"/Users/tuos/Analysis/Vpac/Model/Code/CMSGlauber/Sep09/testMar2012/Mar17/May30/ForpPb/5020GeV/1M");
if(SysGlauberStandard){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=0; }
if(SysGlauberDlow){  infilename = Form("%s/D/D04914/Phob_Glau_pPb_sNN70mb_v15_1M_D04914.root",fdirname); eff=0; }
if(SysGlauberDhigh){  infilename = Form("%s/D/D06006/Phob_Glau_pPb_sNN70mb_v15_1M_D06006.root",fdirname); eff=0; }
if(SysGlauberdminlow){  infilename = Form("%s/dmin/dmin00/Phob_Glau_pPb_sNN70mb_v15_1M_dmin00.root",fdirname); eff=0; }
if(SysGlauberdminhigh){  infilename = Form("%s/dmin/dmin08/Phob_Glau_pPb_sNN70mb_v15_1M_dmin08.root",fdirname); eff=0; }
if(SysGlauberRlow){  infilename = Form("%s/R/R649/Phob_Glau_pPb_sNN70mb_v15_1M_R649.root",fdirname); eff=0; }
if(SysGlauberRhigh){  infilename = Form("%s/R/R675/Phob_Glau_pPb_sNN70mb_v15_1M_R675.root",fdirname); eff=0; }
if(SysGlaubersigmalow){  infilename = Form("%s/sigma/sigma66/Phob_Glau_pPb_sNN66mb_v15_1M_dmin04.root",fdirname); eff=0; }
if(SysGlaubersigmahigh){  infilename = Form("%s/sigma/sigma74/Phob_Glau_pPb_sNN74mb_v15_1M_dmin04.root",fdirname); eff=0; }
if(SysEff1){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=0; }
if(SysEff2){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=1; }
if(SysEff3){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=2; }
if(SysEff4){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=3; }
if(SysEff5){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=4; }
if(SysEff6){ infilename = Form("%s/Standard/Phob_Glau_pPb_sNN70mb_v15_1M_dmin04.root",fdirname); eff=5; }

 TChain * t = new TChain("nt_p_Pb");
 t->Add(infilename);

 bool binHFplusTrunc = label.compare("HFtowersPlusTrunc") == 0;
 bool binHFminusTrunc = label.compare("HFtowersMinusTrunc") == 0;
 bool binTracks = label.compare("Tracks") == 0;

 if (binHFplusTrunc) {
   //getProjections(Npart_vs_PtGenPlusEta4[eff],Proj1,"Proj1",1,30);
   //getProjections(PtGenPlusEta4_vs_HFplusEta4[eff],Proj2,"Proj2",1,140);
   //getProjections(Npart_vs_HFplusEta4[eff],Projs,"Projs",1,20);
   getProjections(Npart_vs_HFminusEta4[eff],Projs,"Projs",1,20);
 }
 else if (binHFminusTrunc) {
   getProjections(Npart_vs_PtGenMinusEta4[0],Proj1,"Proj1",1,30);
   getProjections(PtGenMinusEta4_vs_HFminusEta4[0],Proj2,"Proj2",1,140);
 }
 else if (binTracks) {
   getProjections(Npart_vs_Ngentrk[0],Proj1,"Proj1",1,30);
   getProjections(Ngentrk_vs_Ntracks[0],Proj2,"Proj2",1,200);
 }

 //output
 const char *tag = tags.c_str();
 TFile * outf = new TFile(outfilename,"update");
 outf->cd();
 TDirectory* dir = outf->mkdir(tag);
 dir->cd();
 TNtuple* nt = new TNtuple("nt","","HFbyPt:genPt:Bin:b:Npart:Ncoll:Nhard");
 CentralityBins * outputTable = new CentralityBins(Form("run%d",1), tag, nbins);
 outputTable->table_.reserve(nbins);

 ofstream txtfile("out/output.txt");
 txtfile << "Input Glauber tree: " << infilename << endl << "Input MC HiForest HIJING" << endl;

 //Setting up variables and branches
 double binboundaries[nbins+1];
 vector<float> values;

 float b, npart, ncoll, nhard, parameter;

 t->SetBranchAddress("B",&b);
 t->SetBranchAddress("Npart",&npart);
 t->SetBranchAddress("Ncoll",&ncoll);
 nhard = 0;

 TFile * effFile = new TFile("out/EffNewV0.root","read");
 TF1 * fitEff[nhist];
 for(int i=0; i<nhist; i++) {
  fitEff[i] = (TF1*)effFile->Get(Form("HFtowersPlusTrunc/fitEff%d",i));
 }
 TRandom3 *rnd = new TRandom3(0);
 //Event loop 1
 unsigned int Nevents = t->GetEntries();
 //Nevents=100000;
 txtfile << "Number of events = " << Nevents << endl << endl;
 for(unsigned int iev = 0; iev < Nevents; iev++) {
   if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
   t->GetEntry(iev);

   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,nhist);
   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,eff);
   //if (binHFplusTrunc) parameter = getByNpart(Npart_vs_HFplusEta4[eff],npart);
   if (binHFplusTrunc) parameter = getByNpart(Npart_vs_HFminusEta4[eff],npart);
   if (binHFminusTrunc) parameter = getHFminusByPt(npart);
   if (binTracks) parameter = getTracksByGen(npart);
   //parameter=npart;

   //if(eff==nhist) values.push_back(parameter);
   if(rnd->Uniform(0,1) < fitEff[eff]->Eval(parameter))
     values.push_back(parameter);
 }

 if(label.compare("b") == 0) sort(values.begin(),values.end(),descend);
 else sort(values.begin(),values.end());

 //Finding the bin boundaries
 txtfile << "-------------------------------------" << endl;
 txtfile << label.data() << " based cuts are: " << endl;
 txtfile << "(";
//for(unsigned int iev = 0; iev < Nevents; iev++) txtfile<<values[iev]<<endl;
//txtfile<<endl<<endl<<endl;

 int size = values.size(); 
 //cout<<"size="<<size<<endl;
 binboundaries[nbins] = values[size-1];

 for(int i = 0; i < nbins; i++) {
   int entry = (int)(i*(size/nbins));
   //cout<<"entry="<<entry<<",  entry/size="<<entry*1.0/size<<endl;
   if(entry < 0 || i == 0) binboundaries[i] = 0;
   else binboundaries[i] = values[entry];
   txtfile << binboundaries[i] << ", ";
 }
 txtfile << binboundaries[nbins] << ")" << endl << "-------------------------------------" << endl;

 // Determining Glauber results in various bins
 TH2D* hNpart = new TH2D("hNpart","",nbins,binboundaries,40000,0,40); 
 //the bug related to larger <npart> is fixed here, need to use large #bins for npart;
 //bin size matters since after ProjectionY, getMean() will get value at middle of the bin, not the value you set;
 //if use 40 bins for npart, 0.5 difference for <npart> will be introduced. with 40000 bins, it will be 0.0005;
 TH2D* hNcoll = new TH2D("hNcoll","",nbins,binboundaries,40000,0,40);
 TH2D* hNhard = new TH2D("hNhard","",nbins,binboundaries,50000,0,50);
 TH2D* hb = new TH2D("hb","",nbins,binboundaries,30000,0,30);

 //Event loop 2
 for(unsigned int iev = 0; iev < Nevents; iev++) {
   if( iev % 50000 == 0 ) cout<<"Processing event : " << iev << endl;
   t->GetEntry(iev);

   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,nhist);
   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,eff);
   //if (binHFplusTrunc) parameter = getByNpart(Npart_vs_HFplusEta4[eff],npart);
//cout<<"a"<<endl;
   if (binHFplusTrunc) parameter = getByNpart(Npart_vs_HFminusEta4[eff],npart);
   if (binHFminusTrunc) parameter = getHFminusByPt(npart);
   if (binTracks) parameter = getTracksByGen(npart);
   //parameter=npart;
//cout<<"parameter = "<<parameter<<endl;

   if(rnd->Uniform(0,1) < fitEff[eff]->Eval(parameter)){
    hNpart->Fill(parameter,npart);
    hNcoll->Fill(parameter,ncoll);
    hNhard->Fill(parameter,nhard);
    hb->Fill(parameter,b);
    int bin = hNpart->GetXaxis()->FindBin(parameter) - 1;
    if(bin < 0) bin = 0;
    if(bin >= nbins) bin = nbins - 1;
    nt->Fill(parameter, et, bin, b, npart, ncoll, nhard);
   
    hNparthf[bin]->Fill(npart,parameter);
    hNpart1[bin]->Fill(npart);
    if(bin==0) hNpart00->Fill(npart);
    hNparthf[5]->Fill(npart,parameter);
   }
//cout<<"b"<<endl;

 }

 TF1* fGaus = new TF1("fb","gaus(0)",0,2);
 fitSlices(hNpart,fGaus);
 fitSlices(hNcoll,fGaus);
 fitSlices(hNhard,fGaus);
 fitSlices(hb,fGaus);

 TH1D* hNpartMean = (TH1D*)gDirectory->Get("hNpart_1");
 TH1D* hNpartSigma = (TH1D*)gDirectory->Get("hNpart_2");
 TH1D* hNcollMean = (TH1D*)gDirectory->Get("hNcoll_1");
 TH1D* hNcollSigma = (TH1D*)gDirectory->Get("hNcoll_2");
 TH1D* hNhardMean = (TH1D*)gDirectory->Get("hNhard_1");
 TH1D* hNhardSigma = (TH1D*)gDirectory->Get("hNhard_2");
 TH1D* hbMean = (TH1D*)gDirectory->Get("hb_1");
 TH1D* hbSigma = (TH1D*)gDirectory->Get("hb_2");

 txtfile<<"-------------------------------------"<<endl;
 txtfile<<"# Bin NpartMean NpartSigma NcollMean NcollSigma bMean bSigma BinEdge"<<endl;
 //double sumnpart=0;
 for(int i = 0; i < nbins; i++){ 
   //TH1D *meanpart = hNpart->ProjectionY("meanpart", i+1, i+1);
   //cout<<"meanpart="<<meanpart->GetMean()<<" entries="<<meanpart->GetEntries()<<endl;
   //cout<<"hNpartMean= "<<hNpartMean->GetBinContent(i+1)<<endl;
   int ii = nbins-i;  
   outputTable->table_[i].n_part_mean = hNpartMean->GetBinContent(ii);
   outputTable->table_[i].n_part_var = hNpartSigma->GetBinContent(ii);
   outputTable->table_[i].n_coll_mean = hNcollMean->GetBinContent(ii);
   outputTable->table_[i].n_coll_var = hNcollSigma->GetBinContent(ii);
   outputTable->table_[i].b_mean = hbMean->GetBinContent(ii);
   outputTable->table_[i].b_var = hbSigma->GetBinContent(ii);
   outputTable->table_[i].n_hard_mean = hNhardMean->GetBinContent(ii);
   outputTable->table_[i].n_hard_var = hNhardSigma->GetBinContent(ii);
   outputTable->table_[i].bin_edge = binboundaries[ii-1];

   txtfile << i << " " << hNpartMean->GetBinContent(ii) << " " << hNpartSigma->GetBinContent(ii) << " " << hNcollMean->GetBinContent(ii) << " " << hNcollSigma->GetBinContent(ii) << " " << hbMean->GetBinContent(ii) << " " <<hbSigma->GetBinContent(ii) << " " << binboundaries[ii-1] << " " <<endl;
   //sumnpart+=hNpartMean->GetBinContent(ii);
 }
 //cout<<"<npart>="<<sumnpart/nbins<<endl;
 txtfile<<"-------------------------------------"<<endl;
 outf->cd();
 dir->cd();
 outputTable->Write();
 nt->Write();
 for(int ih = 0; ih < nhist+1; ih++) {
  if(ih==0){
   Npart_vs_PtGenPlusEta4[ih]->Write();
   PtGenPlusEta4_vs_HFplusEta4[ih]->Write();
   Npart_vs_PtGenMinusEta4[ih]->Write();
   PtGenMinusEta4_vs_HFminusEta4[ih]->Write();
   Npart_vs_Ngentrk[ih]->Write();
   Ngentrk_vs_Ntracks[ih]->Write();
   Npart_vs_HFplusEta4[ih]->Write();
   Npart_vs_HFminusEta4[ih]->Write();
   Npart_vs_Ntracks[ih]->Write();
  }
   hNparthf[ih]->Write();
   hNpart1[ih]->Write();
 }
   hNpart00->Write();
   hNpart->Write();
   hNcoll->Write();
   hNpartMean->Write();
   hNpartSigma->Write();
   hNcollMean->Write();
   hNcollSigma->Write();
   hNhardMean->Write();
   hNhardSigma->Write();
   hbMean->Write();
   hbSigma->Write();
 outf->Write();
 txtfile.close();



}
