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

//------------------------------------------------------------------------
void readGlauberFile() {

const char* outFileName = "./hist_Glauber2025_OO.root";

//input Glauber ntuple
const char * infilePbPbname;
char PbPbdirname[200];
sprintf(PbPbdirname,"/store/user/tuos/GlauberMC/PbPb5360GeV/default");
infilePbPbname = Form("%s/glauber_PbpnrwPbpnrw_default_1M.root",PbPbdirname); 

const char * infileOOname;
char OOdirname[200];
sprintf(OOdirname,"/nobackup/user/tuos/run2025/oopo/glauber");
infileOOname = Form("%s/glauber_OO_default_1M.root",OOdirname);

 TChain * tPbPb = new TChain("nt_Pbpnrw_Pbpnrw");
 tPbPb->Add(infilePbPbname);
 TChain * tOO = new TChain("nt_O_O");
 tOO->Add(infileOOname);


 float b, npart, ncoll, nhard, parameter, ecc2, ecc3;
 tPbPb->SetBranchAddress("B",&b);
 tPbPb->SetBranchAddress("Npart",&npart);
 tPbPb->SetBranchAddress("Ncoll",&ncoll);
 tPbPb->SetBranchAddress("Ecc2",&ecc2);
 tPbPb->SetBranchAddress("Ecc3",&ecc3);

 float bOO, npartOO, ncollOO, ecc2OO, ecc3OO;
 tOO->SetBranchAddress("B",&bOO);
 tOO->SetBranchAddress("Npart",&npartOO);
 tOO->SetBranchAddress("Ncoll",&ncollOO);
 tOO->SetBranchAddress("Ecc2",&ecc2OO);
 tOO->SetBranchAddress("Ecc3",&ecc3OO);

TH1D* hBPbPb = new TH1D("hBPbPb", "", 300, 0, 30);
TH1D* hnpartPbPb = new TH1D("hnpartPbPb", "", 450, 0, 450);
TH1D* hncollPbPb = new TH1D("hncollPbPb", "", 2500, 0, 2500);
TH2D* hnpartvsbPbPb = new TH2D("hnpartvsbPbPb", "", 300, 0, 30, 450,0,450);
TH1D* hBOO = new TH1D("hBOO", "", 150, 0, 15);
TH1D* hnpartOO = new TH1D("hnpartOO", "", 40, 0, 40);
TH1D* hncollOO = new TH1D("hncollOO", "", 200, 0, 200);
TH2D* hnpartvsbOO = new TH2D("hnpartvsbOO", "", 150, 0, 15, 40,0,40);

 unsigned int Nevents = tPbPb->GetEntries();
 cout << "Number of events for PbPb = " << Nevents << endl << endl;
 for(unsigned int iev = 0; iev < Nevents; iev++) {
 //for(unsigned int iev = 0; iev < 10; iev++) {
   if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
   tPbPb->GetEntry(iev);
   //cout<<b<<"  "<<npart<<"  "<<ncoll<<endl;
   hBPbPb->Fill(b);
   hnpartPbPb->Fill(npart);
   hncollPbPb->Fill(ncoll);
   hnpartvsbPbPb->Fill(b, npart);
 }
 unsigned int NeventsOO = tOO->GetEntries();
 cout << "Number of events for OO = " << NeventsOO << endl << endl;
 for(unsigned int iev = 0; iev < NeventsOO; iev++) {
 //for(unsigned int iev = 0; iev < 10; iev++) {
   if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
   tOO->GetEntry(iev);
   //cout<<bOO<<"  "<<npartOO<<"  "<<ncollOO<<endl;
   hBOO->Fill(bOO);
   hnpartOO->Fill(npartOO);
   hncollOO->Fill(ncollOO);
   hnpartvsbOO->Fill(bOO, npartOO);
 }

 TFile * outf = new TFile(outFileName, "update");
 outf->cd();
 
   hBPbPb->Write();
   hnpartPbPb->Write();
   hncollPbPb->Write();
   hnpartvsbPbPb->Write();
   hBOO->Write();
   hnpartOO->Write();
   hncollOO->Write();
   hnpartvsbOO->Write();
   outf->Write();
   outf->Close();


}


