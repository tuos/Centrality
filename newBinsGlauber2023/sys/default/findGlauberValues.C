// need root at lxplus:
//cd /afs/cern.ch/user/t/tuos/work/private/CMSSW_10_1_5/src
//cmsenv
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>

bool descend(float i,float j) { return (i<j); }

void findGlauberValues(){

  const int nBins = 200;
  const char * inFileName;
  char fileDirName[251];
  sprintf(fileDirName,"/Users/shengquantuo/Desktop/soft/glauberv2/tglaubermc/newPbPb5TeV/sys/default");
  inFileName = Form("%s/glauber_PbpnrwPbpnrw_default_1M.root", fileDirName); 

  TChain * t = new TChain("nt_Pbpnrw_Pbpnrw");
  t->Add(inFileName);
  ofstream txtfile("default_output.txt");
  double binBoundaries[nBins+1];
  vector<float> values;
  float b, npart, ncoll, ecc2, ecc3, parameter;
  t->SetBranchAddress("B",&b);
  t->SetBranchAddress("Npart",&npart);
  t->SetBranchAddress("Ncoll",&ncoll);
  t->SetBranchAddress("Ecc2",&ecc2);
  t->SetBranchAddress("Ecc3",&ecc3);
  unsigned int Nevents = t->GetEntries();
  //Nevents=100000;
  //txtfile << "Number of events = " << Nevents << endl << endl;
  for(unsigned int iev = 0; iev < Nevents; iev++) {
    if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
    t->GetEntry(iev);
    parameter = b;
    values.push_back(parameter);
  }
  std::sort(values.begin(),values.end(),descend);
  int size = values.size();
  //cout<<"size="<<size<<endl;
  binBoundaries[nBins] = values[size-1];
  for(int i = 0; i < nBins; i++) {
    int entry = (int)(i*(size/nBins));
    //cout<<"entry="<<entry<<",  entry/size="<<entry*1.0/size<<endl;
    if(entry < 0 || i == 0) binBoundaries[i] = 0;
    else binBoundaries[i] = values[entry];
    //txtfile << binBoundaries[i] << ", ";
  }

  TH1D* hNpart1d[nBins];
  TH1D* hNcoll1d[nBins];
  TH1D* hEcc21d[nBins];
  TH1D* hEcc31d[nBins];
  for(int i = 0; i < nBins; i++){
    hNpart1d[i] = new TH1D(Form("hnpart1d_bin%d",i),"",450,0,450);
    hNcoll1d[i] = new TH1D(Form("hncoll1d_bin%d",i),"",2500,0,2500);
    hEcc21d[i] = new TH1D(Form("hecc21d_bin%d",i),"",1100,-0.05,1.05);
    hEcc31d[i] = new TH1D(Form("hecc31d_bin%d",i),"",1100,-0.05,1.05);
  }
  //Event loop 2
  for(unsigned int iev = 0; iev < Nevents; iev++) {
    if( iev % 50000 == 0 ) cout<<"Processing event : " << iev << endl;
    t->GetEntry(iev);
    parameter = b;
    for(int i = 0; i < nBins; i++){
      if(parameter>binBoundaries[i] && parameter<=binBoundaries[i+1]){
        hNpart1d[i]->Fill(npart);
        hNcoll1d[i]->Fill(ncoll);
        hEcc21d[i]->Fill(ecc2);
        hEcc31d[i]->Fill(ecc3);
      }
    }
  }

  TH1D *hNpartCent = new TH1D("hNpartCent","",200,0.0,200.0);
  TH1D *hNcollCent = new TH1D("hNcollCent","",200,0.0,200.0);
  TH1D *hTAACent = new TH1D("hTAACent","",200,0.0,200.0);
  TH1D *hEcc2Cent = new TH1D("hEcc2Cent","",200,0.0,200.0);
  TH1D *hEcc3Cent = new TH1D("hEcc3Cent","",200,0.0,200.0);

   for(int i = 0; i < nBins; i++){
      txtfile<<i<<"   "<<hNpart1d[i]->GetMean()<<"   "<<hNcoll1d[i]->GetMean()<<endl;
      hNpartCent->SetBinContent(i+1, hNpart1d[i]->GetMean());
      hNcollCent->SetBinContent(i+1, hNcoll1d[i]->GetMean());
      hTAACent->SetBinContent(i+1, hNcoll1d[i]->GetMean()/67.6);
      hEcc2Cent->SetBinContent(i+1, hEcc21d[i]->GetMean());
      hEcc3Cent->SetBinContent(i+1, hEcc31d[i]->GetMean());
   }
 
  TFile *ofile = new TFile("default_f.root","recreate");
  ofile->cd();
  hNpartCent->Write();
  hNcollCent->Write();
  hTAACent->Write();
  hEcc2Cent->Write();
  hEcc3Cent->Write();
  ofile->Write();

/* 
  //method with 2D histo projections
  TH2D* hNpart2d = new TH2D("hNpart2d","",nBins,binBoundaries,45000,0,450);
  TH2D* hNcoll2d = new TH2D("hNcoll2d","",nBins,binBoundaries,250000,0,2500);
  //Event loop 2
  for(unsigned int iev = 0; iev < Nevents; iev++) {
    if( iev % 50000 == 0 ) cout<<"Processing event : " << iev << endl;
    t->GetEntry(iev);
    parameter = b;
    hNpart2d->Fill(parameter,npart);
    hNcoll2d->Fill(parameter,ncoll);
  }

   for(int i = 1; i < nBins+1; i++){
      int bin = nBins - i;
      TH1D* hnpart = hNpart2d->ProjectionY(Form("%s_bin%d",hNpart2d->GetName(),bin),i,i);
      TH1D* hncoll = hNcoll2d->ProjectionY(Form("%s_bin%d",hNcoll2d->GetName(),bin),i,i);
      txtfile<<bin<<"   "<<hnpart->GetMean()<<"   "<<hncoll->GetMean()<<endl;
   }  
*/

}


