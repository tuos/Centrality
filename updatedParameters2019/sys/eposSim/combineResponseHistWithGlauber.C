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
#include <iomanip> 

//using namespace std;

bool descend(float i,float j) { return (i<j); }

const int nhist = 1;
TH2D * HF_vs_Npart[nhist];
TH2D * Npix_vs_Npart[nhist];
TH1D * ProjectionTmp[1000];
TH2D* hhfNpart[200];
TH1D* hNpartBin[200];

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
    if(h2->GetXaxis()->GetBinCenter(i) > mergePoint) imax = i+merge;
    h1[i] = h2->ProjectionY(Form("%s_%d",name,i),i,imax);
    double integral = h1[i]->Integral();
    if(integral > 0){
      h1[i]->Scale(1./integral);
    }
  }

}
//------------------------------------------------------------------------
float getByNpart(TH2D * hx, float Npart){  // one step smearing;

   int bin1 = hx->GetXaxis()->FindBin(Npart);
   if(bin1 > hx->GetNbinsX() ) bin1 = hx->GetNbinsX();
   if(bin1 < 1) bin1 = 1;
   if(bin1>405) bin1=405; //remove the bias of Npart(at high value) from mismatch of Hijing to Glauber;
   double hf = ProjectionTmp[bin1]->GetRandom();
   return hf;
}
//------------------------------------------------------------------------
void combineResponseHistWithGlauber(const int nbins = 200, const string label = "HFtowers", const string tags = "Glauber_Default_Para", int eff = 0) {

   bool PbPb2760 = false;
   bool PbPb5020 = true;
   //const char* outFileName = "out/tables_Glauber2016A_ForEposResponsebin05_d20160216_SmearingEff.root";
   const char* outFileName = "./out/tables_Glauber2018B_ForEPOS5020Responsenbins200x_d20180717_SmearingEff.root";
   const char* inSmearingFile = "./ForSmearingEposResponse5020_d20160216_v1.root";
   //const char* inSmearingFile = "../out/ForSmearingEposResponse5020_d20160216_v1.root";
   TFile* inFileSmear;
   inFileSmear = new TFile(inSmearingFile);
  for (int ih = 0; ih < nhist; ih++) {

   HF_vs_Npart[ih] = (TH2D*) inFileSmear->Get(Form("SmearingHist/HF_vs_Npart_0"));
   //Npix_vs_Npart[ih] = (TH2D*) inFileSmear->Get(Form("SmearingHist/Npix_vs_Npart_%d",ih));

  } 

  for (int ibin = 0; ibin < nbins; ibin++) {
   hhfNpart[ibin] = new TH2D(Form("HFvsNpart_%d",ibin),";N_{part};#Sigma HF E_{T}",300,0,300,6000,0,6000);
   hNpartBin[ibin] = new TH1D(Form("NpartBin_%d",ibin),"",450,0,450);
  }
 

 //input Glauber ntuple
bool SysGlauberStandard = tags.compare("Glauber_Default_Para") == 0;
bool SysGlauberRlow = tags.compare("Glauber_Radius_down") == 0;
bool SysGlauberRhigh = tags.compare("Glauber_Radius_up") == 0;
bool SysGlauberDlow = tags.compare("Glauber_SkinDepth_down") == 0;
bool SysGlauberDhigh = tags.compare("Glauber_SkinDepth_up") == 0;
bool SysGlauberdminlow = tags.compare("Glauber_dmin_down") == 0;
bool SysGlauberdminhigh = tags.compare("Glauber_dmin_up") == 0;
bool SysGlaubersigmalow = tags.compare("Glauber_SigmaNN_down") == 0;
bool SysGlaubersigmahigh = tags.compare("Glauber_SigmaNN_up") == 0;
bool SysEff1 = tags.compare("Eff_Sys_1") == 0;

const char * infilename;
char fdirname[200];

if(PbPb2760){
sprintf(fdirname,"/Users/shengquantuo/Desktop/soft/glauberv2/tglaubermc/Xe/sys/deformationdata");
if(SysGlauberStandard){ infilename = Form("%s/glauberPbPb_Default_1M.root",fdirname); eff=0; }
if(SysGlauberDlow){  infilename = Form("%s/glauberPbPb_SD4914_1M.root",fdirname); eff=0; }
if(SysGlauberDhigh){  infilename = Form("%s/glauberPbPb_SD6006_1M.root",fdirname); eff=0; }
if(SysGlauberdminlow){  infilename = Form("%s/glauberPbPb_dmin00_1M.root",fdirname); eff=0; }
if(SysGlauberdminhigh){  infilename = Form("%s/glauberPbPb_dmin08_1M.root",fdirname); eff=0; }
if(SysGlauberRlow){  infilename = Form("%s/glauberPbPb_R649_1M.root",fdirname); eff=0; }
if(SysGlauberRhigh){  infilename = Form("%s/glauberPbPb_R675_1M.root",fdirname); eff=0; }
if(SysGlaubersigmalow){  infilename = Form("%s/glauberPbPb_SigmaNN59_1M.root",fdirname); eff=0; }
if(SysGlaubersigmahigh){  infilename = Form("%s/glauberPbPb_SigmaNN69_1M.root",fdirname); eff=0; }
if(SysEff1){ infilename = Form("%s/glauberPbPb_Default_1M.root",fdirname); eff=0; }
}
if(PbPb5020){
sprintf(fdirname,"/Users/shengquantuo/Desktop/soft/glauberv2/tglaubermc/newPbPb5TeV/sys/default/");
if(SysGlauberStandard){ infilename = Form("%s/glauber_PbpnrwPbpnrw_default_1M.root",fdirname); eff=0; }
if(SysGlauberDlow){  infilename = Form("%s/glauberPbPb_SkinDepth536fm_1M.root",fdirname); eff=0; }
if(SysGlauberDhigh){  infilename = Form("%s/glauberPbPb_SkinDepth556fm_1M.root",fdirname); eff=0; }
if(SysGlauberdminlow){  infilename = Form("%s/glauberPbPb_dMin00fm_1M.root",fdirname); eff=0; }
if(SysGlauberdminhigh){  infilename = Form("%s/glauberPbPb_dMin08fm_1M.root",fdirname); eff=0; }
if(SysGlauberRlow){  infilename = Form("%s/glauberPbPb_NuclearRadius656fm_1M.root",fdirname); eff=0; }
if(SysGlauberRhigh){  infilename = Form("%s/glauberPbPb_NuclearRadius668fm_1M.root",fdirname); eff=0; }
if(SysGlaubersigmalow){  infilename = Form("%s/glauberPbPb_SigmaInelNN65mb_1M.root",fdirname); eff=0; }
if(SysGlaubersigmahigh){  infilename = Form("%s/glauberPbPb_SigmaInelNN75mb_1M.root",fdirname); eff=0; }
if(SysEff1){ infilename = Form("%s/glauberPbPb_Default_1M.root",fdirname); eff=0; }
}

 TChain * t = new TChain("nt_Pbpnrw_Pbpnrw");
 t->Add(infilename);

 bool binHF = label.compare("HFtowers") == 0;
 bool binNpix = label.compare("Npix") == 0;
 bool binNpart = label.compare("Npart") == 0;
 bool binB = label.compare("b") == 0;

 if (binHF) {
   getProjections(HF_vs_Npart[eff],ProjectionTmp,"ProjectionTmp",1,405);
 }
 else if (binNpix) {
   getProjections(Npix_vs_Npart[eff],ProjectionTmp,"ProjectionTmp",1,405);
 }

 //output
 const char *tag = tags.c_str();
 TFile * outf = new TFile(outFileName,"update");
 outf->cd();
 TDirectory* dir = outf->mkdir(tag);
 dir->cd();
 TNtuple* nt = new TNtuple("nt","","HFbyNpart:Bin:b:Npart:Ncoll:Nhard");

 ofstream txtfile("out/output.txt");
 txtfile << "Input Glauber tree: " << infilename << endl << "Input MC HiForest HYDJET" << endl << "Input Glauber/sys file: " << tag << endl;

 //Setting up variables and branches
 double binboundaries[nbins+1];
 vector<float> values;

 float b, npart, ncoll, nhard, parameter, ecc2, ecc3;

 t->SetBranchAddress("B",&b);
 t->SetBranchAddress("Npart",&npart);
 t->SetBranchAddress("Ncoll",&ncoll);
 t->SetBranchAddress("Ecc2",&ecc2);
 t->SetBranchAddress("Ecc3",&ecc3);
 nhard = 0;

// TFile * effFile = new TFile("out/histEff.root","read");
// TH1D * histEff[nhist];
// for(int i=0; i<nhist; i++) {
//  histEff[i] = (TH1D*)effFile->Get(Form("effSys/effhist_%d",i));
// }
// TRandom3 *rnd = new TRandom3(0);
 //Event loop 1
 unsigned int Nevents = t->GetEntries();
 //Nevents=100000;
 txtfile << "Number of events = " << Nevents << endl << endl;
 for(unsigned int iev = 0; iev < Nevents; iev++) {
   if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
   t->GetEntry(iev);

   if (binHF) parameter = getByNpart(HF_vs_Npart[eff],npart);
   if (binNpix) parameter = getByNpart(Npix_vs_Npart[eff],npart);
   if (binNpart) parameter = npart;
   if (binB) parameter = b;

   //if (rnd->Uniform(0,1) < histEff[eff]->GetBinContent(histEff[eff]->FindBin(parameter)))
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
 TH2D* hNpart = new TH2D("hNpart","",nbins,binboundaries,45000,0,450); 
 //the bug related to larger <npart> is fixed here, need to use large #bins for npart;
 //bin size matters since after ProjectionY, getMean() will get value at middle of the bin, not the value you set;
 //if use 40 bins for npart, 0.5 difference for <npart> will be introduced. with 40000 bins, it will be 0.0005;
 TH2D* hNcoll = new TH2D("hNcoll","",nbins,binboundaries,50000,0,2500);
 TH2D* hNhard = new TH2D("hNhard","",nbins,binboundaries,50000,0,2500);
 TH2D* hb = new TH2D("hb","",nbins,binboundaries,30000,0,30);

 TH2D* hEcc2 = new TH2D("hEcc2","",nbins,binboundaries,11000,-0.05,1.05);
 TH2D* hEcc3 = new TH2D("hEcc3","",nbins,binboundaries,11000,-0.05,1.05);


 TH2D* hNpartAll = new TH2D("hNpartAll","",6000,0,6000,4500,0,450);
 TH2D* hNcollAll = new TH2D("hNcollAll","",6000,0,6000,10000,0,2500);
 TH2D* hbAll = new TH2D("hbAll","",6000,0,6000,3000,0,30);

 //Event loop 2
 for(unsigned int iev = 0; iev < Nevents; iev++) {
   if( iev % 50000 == 0 ) cout<<"Processing event : " << iev << endl;
   t->GetEntry(iev);

   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,nhist);
   //if (binHFplusTrunc) parameter = getHFplusByPt(npart,eff);
   //if (binHFplusTrunc) parameter = getByNpart(Npart_vs_HFplusEta4[eff],npart);
//cout<<"a"<<endl;

   if (binHF) parameter = getByNpart(HF_vs_Npart[eff],npart);
   if (binNpix) parameter = getByNpart(Npix_vs_Npart[eff],npart);
   //parameter=npart;
//cout<<"parameter = "<<parameter<<endl;

   hNpartAll->Fill(parameter,npart);
   hNcollAll->Fill(parameter,ncoll);
   hbAll->Fill(parameter,b);

   //if (rnd->Uniform(0,1) < histEff[eff]->GetBinContent(histEff[eff]->FindBin(parameter))){
    hNpart->Fill(parameter,npart);
    hNcoll->Fill(parameter,ncoll);
    hNhard->Fill(parameter,nhard);
    hb->Fill(parameter,b);
    hEcc2->Fill(parameter,ecc2);
    hEcc3->Fill(parameter,ecc3);
    int bin = hNpart->GetXaxis()->FindBin(parameter) - 1;
    if(bin < 0) bin = 0;
    if(bin >= nbins) bin = nbins - 1;
    //nt->Fill(parameter, et, bin, b, npart, ncoll, nhard);
    nt->Fill(parameter, bin, b, npart, ncoll, nhard);
   
    hhfNpart[bin]->Fill(npart,parameter);
    hNpartBin[bin]->Fill(npart);
   //}
//cout<<"b"<<endl;

 }

 TF1* fGaus = new TF1("fb","gaus(0)",0,2);
 fitSlices(hNpart,fGaus);
 fitSlices(hNcoll,fGaus);
 fitSlices(hNhard,fGaus);
 fitSlices(hb,fGaus);
 fitSlices(hEcc2,fGaus);
 fitSlices(hEcc3,fGaus);

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

   txtfile << i << "  " << hNpartMean->GetBinContent(ii) << " " << hNpartSigma->GetBinContent(ii) << " " << hNcollMean->GetBinContent(ii) << " " << hNcollSigma->GetBinContent(ii) << " " << hbMean->GetBinContent(ii) << " " <<hbSigma->GetBinContent(ii) << " " << binboundaries[ii-1] << " " <<endl;
   //sumnpart+=hNpartMean->GetBinContent(ii);
 }
 //cout<<"<npart>="<<sumnpart/nbins<<endl;
 txtfile<<"-------------------------------------"<<endl;
 for(int i = 0; i < nbins; i++){
    int ii = nbins-i;
    txtfile << i*100.0/nbins<<"-"<<(i+1)*100.0/nbins << "   " <<std::setprecision(4)<< hNpartMean->GetBinContent(ii)<<"   "<<std::setprecision(4)<<hNcollMean->GetBinContent(ii)<<endl;
 }
 txtfile<<"-------------------------------------"<<endl;
 for(int i = 0; i < nbins; i++){
    int ii = nbins-i;
    txtfile << i << "   " <<std::setprecision(4)<< hNpartMean->GetBinContent(ii)<<"   "<<std::setprecision(4)<<hNcollMean->GetBinContent(ii)<<endl;
 }
 txtfile.close();

 outf->cd();
 dir->cd();
 nt->Write();

  for (int ih = 0; ih < nhist; ih++) {
   //HF_vs_Npart[ih]->Write();
   //Npix_vs_Npart[ih]->Write();
  }

  for (int ibin = 0; ibin < nbins; ibin++) {
   hhfNpart[ibin]->Write(); 
   hNpartBin[ibin]->Write(); 
  }
   hNpart->Write();
   hNcoll->Write();
   hb->Write();
   hNpartAll->Write();
   hNcollAll->Write();
   hbAll->Write();
   outf->Write();
   outf->Close();

/*
   TFile * outfile = new TFile("out/histGlauberEPOS5440GeV01nbins1x.root","recreate");
   outfile->cd();
   TDirectory *dir2 = outfile->mkdir(tag);
   dir2->cd();
   TH1D *npartVsCent = new TH1D("npartvscent","npartvscent",nbins,0,100);
   TH1D *ncollVsCent = new TH1D("ncollvscent","ncollvscent",nbins,0,100);
   TH1D *bVsCent = new TH1D("bvscent","bvscent",nbins,0,100);
   for(int i = 0; i < nbins; i++){
      int ii = nbins-i;
      npartVsCent->SetBinContent(i+1, hNpartMean->GetBinContent(ii));
      ncollVsCent->SetBinContent(i+1, hNcollMean->GetBinContent(ii));
      bVsCent->SetBinContent(i+1, hbMean->GetBinContent(ii));
   }
   npartVsCent->Write();
   ncollVsCent->Write();
   bVsCent->Write();
   outfile->Write();
   outfile->Close();

*/

}


