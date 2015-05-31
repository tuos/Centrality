

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <TF1.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <TChain.h>
#include <TFile.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TGraphErrors.h>

#define BIGNUMBER 1000
#define MIDNUMBER 100

#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
//#include "CentralityBins.h"

using namespace std;

double addQuad(double *x,int n){
   
   double sum = 0;
   for(int i = 0; i < n; ++i){
      sum+= x[i]*x[i];
   }
   return sqrt(sum);
 
}

double printError(double *var0,double uncSmear = 0.002,int uncEff = 2, double nom = 1);

vector<string> analyzeVariable(int mode, bool RCP = 0){

   int nTable = 22;
   int nBins = 40;

   bool doNpart = 0;
   bool doNcoll = 0;
   bool doTAB = 0;
   bool doEcc = 0;
   bool doB = 0;
   bool doS = 0;

   if(mode==0)doNpart=1;
   if(mode==1)doNcoll=1;
   if(mode==2)doTAB=1;
   if(mode==3)doEcc=1;
   if(mode==4)doB=1;
   if(mode==5)doS=1;

   bool forwardBins = 0;
   bool zBins = 0;
   bool flowBins = 0;
   bool jetBins = 0;
   bool dNdetaBins = 0;
   bool spectraBinsA = 0 && 0 && 0;
   bool spectraBinsB = 1;
   bool photonBins = 0;
   bool quarkoniaBins = 0;
   bool jpsiBins = 0;
   bool jpsiBins5 = 0;
   bool jpsiBins10 = 0;
   bool castorBins11 = 0;
   bool bjetBins3 = 0;
   bool newBins4 = 0;

   double sigmaNN = 64;

   // Analysis bins defined by the PInG
   vector<vector<int> > bins;
   vector<int> b0, b1, b2, b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14;

   double errors[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   double errorsRMS[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   vector<string> txtNcoll;

   if(quarkoniaBins){
      for(int i = 0; i < 4; ++i) b0.push_back(i);
      for(int i = 4; i < 8; ++i) b1.push_back(i);
      for(int i = 8; i < 12; ++i) b2.push_back(i);
      for(int i = 12; i < 16; ++i) b3.push_back(i);
      for(int i = 16; i < 20; ++i) b4.push_back(i);
      for(int i = 20; i < 40; ++i) b5.push_back(i);
      for(int i = 0; i < 8; ++i) b6.push_back(i);
      for(int i = 8; i < 40; ++i) b7.push_back(i);
      for(int i = 0; i < 40; ++i) b8.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);

   }else if(forwardBins){


      for(int i = 0; i < 1; ++i) b0.push_back(i);
      for(int i = 1; i < 2; ++i) b1.push_back(i);
      for(int i = 2; i < 3; ++i) b2.push_back(i);
      for(int i = 3; i < 4; ++i) b3.push_back(i);

      for(int i = 4; i < 8; ++i) b4.push_back(i);
      for(int i = 8; i < 12; ++i) b5.push_back(i);
      for(int i = 12; i < 16; ++i) b6.push_back(i);
      for(int i = 16; i < 20; ++i) b7.push_back(i);
      for(int i = 20; i < 24; ++i) b8.push_back(i);
      for(int i = 24; i < 28; ++i) b9.push_back(i);
      for(int i = 28; i < 32; ++i) b10.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);
      bins.push_back(b9);
      bins.push_back(b10);


   }else if(zBins){
      for(int i = 0; i < 4; ++i) b0.push_back(i);
      for(int i = 4; i < 12; ++i) b1.push_back(i);
      for(int i = 12; i < 40; ++i) b2.push_back(i);
      for(int i = 0; i < 40; ++i) b3.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);

   }else if(flowBins){
      for(int i = 0; i < 2; ++i) b0.push_back(i);
      for(int i = 2; i < 4; ++i) b1.push_back(i);
      for(int i = 4; i < 6; ++i) b2.push_back(i);
      for(int i = 6; i < 8; ++i) b3.push_back(i);
      for(int i = 8; i < 10; ++i) b4.push_back(i);
      for(int i = 10; i < 12; ++i) b5.push_back(i);
      for(int i = 12; i < 14; ++i) b6.push_back(i);
      for(int i = 14; i < 16; ++i) b7.push_back(i);
      for(int i = 16; i < 20; ++i) b8.push_back(i);
      for(int i = 20; i < 24; ++i) b9.push_back(i);
      for(int i = 24; i < 28; ++i) b10.push_back(i);
      for(int i = 28; i < 32; ++i) b11.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);
      bins.push_back(b9);
      bins.push_back(b10);
      bins.push_back(b11);

   }else if(jetBins){

      for(int i = 0; i < 4; ++i) b0.push_back(i);
      for(int i = 4; i < 8; ++i) b1.push_back(i);
      for(int i = 8; i < 12; ++i) b2.push_back(i);
      for(int i = 12; i < 20; ++i) b3.push_back(i);
      for(int i = 20; i < 28; ++i) b4.push_back(i);
      for(int i = 28; i < 40; ++i) b5.push_back(i);
      for(int i = 0; i < 8; ++i) b6.push_back(i);
      for(int i = 0; i < 12; ++i) b7.push_back(i);
      for(int i = 12; i < 40; ++i) b8.push_back(i);
      for(int i = 0; i < 40; ++i) b9.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);
      bins.push_back(b9);

   }else if(dNdetaBins){
      for(int j = 0; j < 20; ++j){
	 vector<int> bh;
	 for(int k = 0; k < 2; ++k){
	    bh.push_back(j*2+k);
	 }
	 bins.push_back(bh);
      }

   }else if(spectraBinsA){
      for(int i = 0; i < 2; ++i) b0.push_back(i);
      for(int i = 2; i < 4; ++i) b1.push_back(i);
      for(int i = 4; i < 12; ++i) b2.push_back(i);
      for(int i = 12; i < 20; ++i) b3.push_back(i);
      for(int i = 20; i < 36; ++i) b4.push_back(i);
      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);

   }else if(spectraBinsB){
      for(int i = 0; i < 2; ++i) b0.push_back(i);
      for(int i = 2; i < 4; ++i) b1.push_back(i);
      for(int i = 4; i < 12; ++i) b2.push_back(i);
      for(int i = 12; i < 20; ++i) b3.push_back(i);
      for(int i = 20; i < 28; ++i) b4.push_back(i);
      for(int i = 28; i < 36; ++i) b5.push_back(i);
      for(int i = 20; i < 36; ++i) b6.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);



   }else if(photonBins){

      for(int i = 0; i < 4; ++i) b0.push_back(i);
      for(int i = 4; i < 12; ++i) b1.push_back(i);
      for(int i = 12; i < 40; ++i) b2.push_back(i);
      for(int i = 0; i < 40; ++i) b3.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);

   }else if(jpsiBins){
      for(int i = 0; i < 40; ++i) b0.push_back(i);
      for(int i = 0; i < 2; ++i) b1.push_back(i);
      for(int i = 2; i < 4; ++i) b2.push_back(i);
      for(int i = 4; i < 8; ++i) b3.push_back(i);
      for(int i = 8; i < 12; ++i) b4.push_back(i);
      for(int i = 12; i < 16; ++i) b5.push_back(i);
      for(int i = 16; i < 20; ++i) b6.push_back(i);
      for(int i = 20; i < 40; ++i) b7.push_back(i);
      for(int i = 20; i < 24; ++i) b8.push_back(i);
      for(int i = 24; i < 40; ++i) b9.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);
      bins.push_back(b9);

   }else if(jpsiBins5){
      for(int i = 0; i < 2; ++i) b0.push_back(i);
      for(int i = 2; i < 4; ++i) b1.push_back(i);
      for(int i = 4; i < 6; ++i) b2.push_back(i);
      for(int i = 6; i < 8; ++i) b3.push_back(i);
      for(int i = 8; i < 10; ++i) b4.push_back(i);
      for(int i = 10; i < 12; ++i) b5.push_back(i);
      for(int i = 12; i < 14; ++i) b6.push_back(i);
      for(int i = 14; i < 16; ++i) b7.push_back(i);
      for(int i = 16; i < 18; ++i) b8.push_back(i);
      for(int i = 18; i < 20; ++i) b9.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);
      bins.push_back(b8);
      bins.push_back(b9);

   }else if(jpsiBins10){
   for(int i = 0; i < 4; ++i) b0.push_back(i);
   for(int i = 4; i < 8; ++i) b1.push_back(i);
   for(int i = 8; i < 12; ++i) b2.push_back(i);
   for(int i = 12; i < 16; ++i) b3.push_back(i);
   for(int i = 16; i < 20; ++i) b4.push_back(i);
   for(int i = 20; i < 24; ++i) b5.push_back(i);
   for(int i = 24; i < 28; ++i) b6.push_back(i);
   for(int i = 28; i < 40; ++i) b7.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);
      bins.push_back(b4);
      bins.push_back(b5);
      bins.push_back(b6);
      bins.push_back(b7);

   }else if(castorBins11){
   for(int i = 0; i < 1; ++i) b0.push_back(i);
   for(int i = 1; i < 2; ++i) b1.push_back(i);
   for(int i = 2; i < 3; ++i) b2.push_back(i);
   for(int i = 3; i < 4; ++i) b3.push_back(i);
   for(int i = 4; i < 8; ++i) b4.push_back(i);
   for(int i = 8; i < 12; ++i) b5.push_back(i);
   for(int i = 12; i < 16; ++i) b6.push_back(i);
   for(int i = 16; i < 20; ++i) b7.push_back(i);
   for(int i = 20; i < 24; ++i) b8.push_back(i);
   for(int i = 24; i < 28; ++i) b9.push_back(i);
   for(int i = 28; i < 32; ++i) b10.push_back(i);
      
      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3); 
      bins.push_back(b4); 
      bins.push_back(b5); 
      bins.push_back(b6); 
      bins.push_back(b7); 
      bins.push_back(b8); 
      bins.push_back(b9); 
      bins.push_back(b10); 

   }else if(bjetBins3){

      for(int i = 0; i < 12; ++i) b0.push_back(i);
      for(int i = 12; i < 36; ++i) b1.push_back(i);
      for(int i = 0; i < 36; ++i) b2.push_back(i);
   
      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2); 
   
   }else if(newBins4){

      for(int i = 0; i < 8; ++i) b0.push_back(i);
      for(int i = 8; i < 40; ++i) b1.push_back(i);
      for(int i = 8; i < 20; ++i) b2.push_back(i);
      for(int i = 12; i < 20; ++i) b3.push_back(i);

      bins.push_back(b0);
      bins.push_back(b1);
      bins.push_back(b2);
      bins.push_back(b3);

   }else{

   for(int i = 0; i < 4; ++i) b0.push_back(i);
   for(int i = 4; i < 8; ++i) b1.push_back(i);
   for(int i = 8; i < 12; ++i) b2.push_back(i);
   for(int i = 12; i < 16; ++i) b3.push_back(i);
   for(int i = 16; i < 20; ++i) b4.push_back(i);
   for(int i = 20; i < 24; ++i) b5.push_back(i);
   for(int i = 24; i < 28; ++i) b6.push_back(i);
   for(int i = 28; i < 32; ++i) b7.push_back(i);
   for(int i = 32; i < 36; ++i) b8.push_back(i);
   for(int i = 36; i < 40; ++i) b9.push_back(i);

   bins.push_back(b0);
   bins.push_back(b1);
   bins.push_back(b2);
   bins.push_back(b3);
   bins.push_back(b4);
   bins.push_back(b5);
   bins.push_back(b6);
   bins.push_back(b7);
   bins.push_back(b8);
   bins.push_back(b9);
   }


   CentralityBins* table[20];

   string tags[200] = {

      "Eff103_sim00_g0",
      "Eff102_sim00_g0",
      "Eff101_sim00_g0",

      "Eff100_sim00_g0",
      "Eff099_sim00_g0",
      "Eff098_sim00_g0",
      "Eff097_sim00_g0",
      "Eff096_sim00_g0",
      "Eff095_sim00_g0",

      "Eff100_sim01_g0",
      "Eff100_sim10_g0",
      "Eff100_sim11_g0",

      "Eff100_sim00_g1a",
      "Eff100_sim00_g1b",

      "Eff100_sim00_g2a",
      "Eff100_sim00_g2b",

      "Eff100_sim00_g3a",
      "Eff100_sim00_g3b",

      "Eff100_sim00_g4a",
      "Eff100_sim00_g4b",

      "Eff100_sim00_g5a",
      "Eff100_sim00_g5b"

   };


   string names[100] = {

      "Eff 103","Eff 102","Eff 101","Eff 100","Eff 99", "Eff 98", "Eff 97", "Eff 96", "Eff 95", // 9
      "Changing SIM","Changing GEN","Changing GEN+SIM", // 3
      "Nuclear Radius","Nuclear Radius",   // 2
      "Skin Depth %2","Skin Depth %2", // 2
      "Skin Depth %10","Skin Depth %10", //2
      "d Min","d Min", //2
      "Sigma NN","Sigma NN"  //2
   };


   TFile* inf = new TFile("./glaubertest_40bins_d0317.root");

   CentralityBins* standardTable = (CentralityBins*)inf->Get("Eff100_sim00_g0/run1");
   double Ncoll[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
   double Npart[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
   double RmsSq[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
   double MSq[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
   double Rms[20] ={0,0,0,0,0,0,0,0,0,0,0,0};

   double NpartCP2 = 0;
   double NcollCP2 = 0;

   double var0[100], var1[100],var2[100],varcp2[100];
   double var[40][100];
   double varms[40][100];
   double varcp[40][100];

   for(int t = 0; t < bins.size(); ++t){
      for(int j = 0; j < bins[t].size(); ++j){
      double r = 0;
      double m = 0;
      if(doNcoll){
	 Ncoll[t] += standardTable->NcollMeanOfBin((bins[t])[j]);
	 r = standardTable->NcollSigmaOfBin((bins[t])[j]);
	 m = standardTable->NcollMeanOfBin((bins[t])[j]);
      }
      if(doNpart){
	 Ncoll[t] += standardTable->NpartMeanOfBin((bins[t])[j]);
	 r = standardTable->NpartSigmaOfBin((bins[t])[j]);
	 m = standardTable->NpartMeanOfBin((bins[t])[j]);
      }
      if(doTAB){
	 Ncoll[t] += standardTable->NcollMeanOfBin((bins[t])[j])/sigmaNN;
	 r = standardTable->NcollSigmaOfBin((bins[t])[j])/sigmaNN;
	 m = standardTable->NcollMeanOfBin((bins[t])[j])/sigmaNN;
      }
      if(doEcc){
	 Ncoll[t] += standardTable->eccentricityMeanOfBin((bins[t])[j]);
	 r = standardTable->eccentricitySigmaOfBin((bins[t])[j]);
	 m = standardTable->eccentricityMeanOfBin((bins[t])[j]);
      }
      if(doB){
         Ncoll[t] += standardTable->bMeanOfBin((bins[t])[j]);
         r = standardTable->bSigmaOfBin((bins[t])[j]);
         m = standardTable->bMeanOfBin((bins[t])[j]);
      }
      if(doS){
         Ncoll[t] += standardTable->areaMeanOfBin((bins[t])[j]);
         r = standardTable->areaSigmaOfBin((bins[t])[j]);
         m = standardTable->areaMeanOfBin((bins[t])[j]);
      }

      RmsSq[t] += r*r;
      MSq[t] += m*m;
      }
      
      Ncoll[t] /= bins[t].size();
      RmsSq[t] /= bins[t].size();
      MSq[t] /= bins[t].size();
      
      Rms[t] = sqrt(RmsSq[t] + MSq[t] - Ncoll[t]*Ncoll[t]);
   }

   NpartCP2 = (Npart[0])/(Npart[2]);
   NcollCP2 = (Ncoll[0])/(Ncoll[2]);

   for(int i = 0; i < nTable; ++i){

      if(i == 14 || i == 15) continue;

      sigmaNN = 64;
      if(i == 20) sigmaNN = 59;
      if(i == 21) sigmaNN = 69;

      cout<<"Analyzing variation : "<<names[i].data()<<endl;
      table[i] = (CentralityBins*)inf->Get(Form("%s/run1",tags[i].data()));
      
      double ncoll[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
      double rmsSq[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
      double mSq[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
      double rms[20] ={0,0,0,0,0,0,0,0,0,0,0,0};
      double rcp[20] = {0,0,0,0,0,0,0,0,0,0,0,0};

      for(int t = 0; t < bins.size(); ++t){
	 for(int j = 0; j < bins[t].size(); ++j){
	    double r = 0;
            double m = 0;
	    if(doNcoll){
	       ncoll[t] += table[i]->NcollMeanOfBin((bins[t])[j]);
	       r = table[i]->NcollSigmaOfBin((bins[t])[j]);
	       m = table[i]->NcollMeanOfBin((bins[t])[j]);
	    }
	    if(doNpart){
	       ncoll[t] += table[i]->NpartMeanOfBin((bins[t])[j]);
               r = table[i]->NpartSigmaOfBin((bins[t])[j]);
	       m = table[i]->NpartMeanOfBin((bins[t])[j]);
	    }
	    if(doTAB){
	       ncoll[t] += table[i]->NcollMeanOfBin((bins[t])[j])/sigmaNN;
               r = table[i]->NcollSigmaOfBin((bins[t])[j])/sigmaNN;
	       m = table[i]->NcollMeanOfBin((bins[t])[j])/sigmaNN;
	    }
	    if(doEcc){
	       ncoll[t] += table[i]->eccentricityMeanOfBin((bins[t])[j]);
               r = table[i]->eccentricitySigmaOfBin((bins[t])[j]);
	       m = table[i]->eccentricityMeanOfBin((bins[t])[j]);
	    }
	    if(doB){
               ncoll[t] += table[i]->bMeanOfBin((bins[t])[j]);
               r = table[i]->bSigmaOfBin((bins[t])[j]);
               m = table[i]->bMeanOfBin((bins[t])[j]);
            }
	    if(doS){
               ncoll[t] += table[i]->areaMeanOfBin((bins[t])[j]);
               r = table[i]->areaSigmaOfBin((bins[t])[j]);
               m = table[i]->areaMeanOfBin((bins[t])[j]);
            }

	    rmsSq[t] += r*r;
            mSq[t] += m*m;
	 }
	 rmsSq[t] /= bins[t].size();
	 ncoll[t] /= bins[t].size();
         rmsSq[t] /= bins[t].size();
	 mSq[t] /= bins[t].size();

	 rms[t] = sqrt(rmsSq[t] + mSq[t] - ncoll[t]*ncoll[t]);
      }
  
        cout<<"Results : "<<ncoll[0]<<endl;

	for(int t = 0; t < bins.size(); ++t){
	   var[t][i] = ((ncoll[t])-(Ncoll[t]))/Ncoll[t];
	   varms[t][i] = ((rms[t])-(Rms[t]))/Rms[t];
	   varcp[t][i] = (ncoll[t]/ncoll[bins.size()-1] - Ncoll[t]/Ncoll[bins.size()-1])/(Ncoll[t]/Ncoll[bins.size()-1]);
	}
   }


   for(int t = 0; t < bins.size(); ++t){
      cout<<"Large Bin : "<<t<<endl;

      if(RCP) errors[t] = printError(varcp[t],0.0005);
      else errors[t] = printError(var[t],0.0005);

      errorsRMS[t] = printError(varms[t],0.0005);

      cout<<Ncoll[t]<<"$\\pm$ "<<errors[t]*Ncoll[t]<<" &"<<endl;
      if(mode==3) txtNcoll.push_back(Form("%0.4f$\\pm$%0.4f(%0.1f\\%%) & %0.4f &",Ncoll[t],errors[t]*Ncoll[t],errors[t]*100.,Rms[t]));
      else{
	 //if(mode < 30) txtNcoll.push_back(Form("%0.2f$\\pm$%0.2f(%0.1f\\%%) & %0.2f &",Ncoll[t],errors[t]*Ncoll[t],errors[t]*100.,Rms[t]));
         if(mode < 30) txtNcoll.push_back(Form("%0.2f +/- %0.2f  %0.1f\%%  %0.2f ",Ncoll[t],errors[t]*Ncoll[t],errors[t]*100.,Rms[t]));
	 else txtNcoll.push_back(Form("%0.4f$\\pm$%0.4f(%0.1f \\%%) & %0.2f$\\pm$%0.2f \\\\",Ncoll[t],errors[t]*Ncoll[t],errors[t]*100.,Rms[t],errorsRMS[t]*Rms[t]));
      }
  }

   cout<<"0 - 10% / 30 -100%"<<endl;
   printError(varcp2);

   cout<<"Custom Calculations : "<<endl;
   if(0){
      double a[100] = {0.2,   7.4,   0.36,   2.7,   3 };
      cout<<addQuad(a,5)<<endl;
      
      double b[100] = {3,5.7,0.17,8.4,1.2};
      cout<<addQuad(b,5)<<endl;
      
      double c[100] = {3,1.8,0.5,6,2};
      cout<<addQuad(c,5)<<endl;
   }
   
   return txtNcoll;

}

double printError(double *var0, double uncSmear, int uncEff, double nom){
   
   int offset = 3;

   double errorR = (fabs(var0[12])+fabs(var0[13]))/2;
   double errorSkin = (fabs(var0[16])+fabs(var0[17]))/2;
   double errorDmin =  (fabs(var0[18])+fabs(var0[19]))/2;
   double errorSigmaNN = (fabs(var0[20])+fabs(var0[21]))/2;

   if(0){
   cout<<"Error SigmaNN : "<<errorSigmaNN/nom*100<<endl;
   cout<<"Error Radius : "<<errorR/nom*100<<endl;
   cout<<"Error Skin Depth : "<<errorSkin/nom*100<<endl;
   cout<<"Error dMin : "<<errorDmin/nom*100<<endl;
   }
 
   double glauberArray0[20] = {
      errorR,
      errorSkin,
      errorDmin,
      errorSigmaNN
   };
   
   double glauberError0 = addQuad(glauberArray0,4);

   double effError = (fabs(var0[offset - uncEff]) + fabs(var0[ offset + uncEff]))/2;
   double finalArray0[20] = {
      effError,
      //      fabs(var0[offset + uncEff]),
      glauberError0,
      uncSmear
   };
   double error0 = addQuad(finalArray0,3);

   if(0){
      cout<<"Glauber Error : "<<glauberError0/nom*100<<endl;
      cout<<"Efficiency Error : "<<effError/nom*100<<endl;
      cout<<"Final Error   : "<<error0/nom*100<<endl;
   }

   cout<<Form("%0.2f\\%% & %0.2f\\%% &%0.2f\\%% &%0.2f\\%% &%0.2f\\%% &%0.2f\\%% &%0.2f\\%% \\\\",errorSigmaNN/nom*100,errorR/nom*100,errorSkin/nom*100,errorDmin/nom*100,glauberError0/nom*100,effError/nom*100,error0/nom*100)<<endl;

   //   return effError;
   //   return glauberError0;
   return error0;
  
}   


void analyze_systematics(){


   string cLabelqq[40] = {
      "0 - 10\\% & ",
      "10 - 20\\% & ",
      "20 - 30\\% & ",
      "30 - 40\\% & ",
      "40 - 50\\% & ",
      "50 - 100\\% & ",
      "0 - 20\\% & ",
      "20 - 100\\% & ",
      "0 - 100\\% & "
   };


   string cLabelz[40] = {
      "0 - 10\\% & ",
      "10 - 30\\% & ",
      "30 - 100\\% & ",
      "0 - 100\\% &"
   };
   
   string cLabelphoton[40] = {
      "0 - 10\\% & ",
      "10 - 30\\% & ",
      "30 - 100\\% & ",
      "0 - 100\\% &"
   };

   string cLabeljet[40] = {

      "0 - 10\\% & ",
      "10 - 20\\% & ",
      "20 - 30\\% & ",
      "30 - 50\\% & ",
      "50 - 70\\% & ",
      "70 - 100\\% & ",
      "0 - 30\\% & ",
      "30 - 100\\% & ",
      "0 - 100\\% & "

   };

   string cLabelflow[40] = {
      "0 - 5\\% & ",
      "5 - 10\\% & ",
      "10 - 15\\% & ",
      "15 - 20\\% &",
      "20 - 25\\% &",
      "25 - 30\\% & ",
      "30 - 35\\% &",
      "35 - 40\\% & ",
      "40 - 50\\% & ",
      "50 - 60\\% &",
      "60 - 70\\% & ",
      "70 - 80\\% & "
   };

   string cLabelforward[40] = {
      "0 - 2.5\\% & ",
      "2.5 - 5\\% & ",
      "5 - 7.5\\% & ",
      "7.5 - 10\\% & ",
      "10 - 20\\% &",
      "20 - 30\\% & ",
      "30 - 40\\% & ",
      "40 - 50\\% & ",
      "50 - 60\\% &",
      "60 - 70\\% & ",
      "70 - 80\\% & "
   };


   string cLabelmult[40] = {
      "0 - 5\\% & ",
      "5 - 10\\% & ",
      "10 - 15\\% & ",
      "15 - 20\\% &",
      "20 - 25\\% & ",
      "25 - 30\\% & ",
      "30 - 35\\% & ",
      "35 - 40\\% &",
      "40 - 45\\% & ",
      "45 - 50\\% & ",
      "50 - 55\\% & ",
      "55 - 60\\% & ",
      "60 - 65\\% & ",
      "65 - 70\\% & ",
      "70 - 75\\% & ",
      "75 - 80\\% & ",
      "80 - 85\\% & ",
      "85 - 90\\% & ",
      "90 - 95\\% & ",
      "95 - 100\\% & "

   };

   string cLabelSpectraA[40] = {
      "0 - 5\\% & ",
      "5 - 10\\% & ",
      "10 - 30\\% & ",
      "30 - 50\\% &",
      "50 - 90\\% & "
   };

   string cLabelSpectraB[40] = {
      "0 - 5  \\% &",
      "5 - 10 \\% &",
      "10 - 30\\% &",
      "30 - 50\\% &",
      "50 - 70\\% &",
      "70 - 90\\% &",
      "50 - 90\\% &"
   };

   string cLabeljpsi[40] = {
      "0 - 100\\% & ",
      "0 - 5\\% & ",
      "5 - 10\\% & ",
      "10 - 20\\% &",
      "20 - 30\\% &",
      "30 - 40\\% & ",
      "40 - 50\\% &",
      "50 - 100\\% & ",
      "50 - 60\\% &",
      "60 - 100\\% & "
   };

   string cLabeljpsi5[40] = {
      "0 - 5\\% & ",
      "5 - 10\\% & ",
      "10 - 15\\% & ",
      "15 - 20\\% &",
      "20 - 25\\% & ",
      "25 - 30\\% & ",
      "30 - 35\\% & ",
      "35 - 40\\% &",
      "40 - 45\\% & ",
      "45 - 50\\% & "
   };

   string cLabeljpsi10[40] = {
      "0 - 10\\% & ",
      "10 - 20\\% & ",
      "20 - 30\\% & ",
      "30 - 40\\% & ",
      "40 - 50\\% & ",
      "50 - 60\\% & ",
      "60 - 70\\% & ",
      "70 - 100\\% & "
   };

   string cLabelcastor11[40] = {
      "0 - 2.5\\% & ",
      "2.5 - 5\\% & ",
      "5 - 7.5\\% & ",
      "7.5 - 10\\% & ",
      "10 - 20\\% & ",
      "20 - 30\\% & ",
      "30 - 40\\% & ",
      "40 - 50\\% & ",
      "50 - 60\\% & ",
      "60 - 70\\% & ",
      "70 - 80\\% & "
   }; 

   string cLabelbjet3[40] = {
      "0 - 30\\% & ",
      "30 - 90\\% & ",
      "0 - 90\\% &"
   }; 

//   string cLabelnew4[40] = {
//      "0 - 20\\% & ",
//      "20 - 100\\% & ",
//      "20 - 50\\% & ",
//      "30 - 50\\% &"
//   };

   string cLabelnew4[40] = {
      "0 - 20\%  ",
      "20 - 100\%  ",
      "20 - 50\%  ",
      "30 - 50\%  "
   };


   vector<string> st0,st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11;

   //bool RCP = 0;
   bool RCP = 1;

   st0 = analyzeVariable(0,RCP); // Npart
   if(1){
      st1 = analyzeVariable(1,RCP); // Ncoll
      st2 = analyzeVariable(2,RCP); // TAB
      st3 = analyzeVariable(3,RCP); // Ecc
      st4 = analyzeVariable(4,RCP); // b
      st5 = analyzeVariable(5,RCP); // S
   }

   bool a = 0;
   bool b = 0;
   bool c = 0;
   bool d = 0;
   bool e = 0;
   bool f = 0;

   bool jp = 0;
   bool jp5 = 0;
   bool jp10 = 0;
   bool ca11 = 0;
   bool bjet3 = 0;
   bool new4 = 0;
   bool speB = 1;
   

   if(a) cout<<"b Mean "<<"b RMS "<<"Npart Mean "<<"Npart RMS "<<"Ncoll Mean "<<"Ncoll RMS"<<endl;
   if(b) cout<<"Npart Sigma "<<"Eccentricity Sigma "<<"S Sigma "<<endl;
   if(c) cout<<"Npart Mean "<<"Npart RMS "<<"Ncoll Mean "<<"Ncoll RMS "<<"T_AB Mean "<<"T_AB RMS"<<endl;
   if(f) cout<<"Npart "<<" Npart RMS "<<endl;
   if(d) cout<<"Ncoll "<<" Ncoll RMS "<<endl;
   if(e) cout<<"Ncoll "<<" Ncoll RMS "<<endl;
   if(jp) cout<<"Npart_Mean "<<"Npart_RMS "<<"T_AB_Mean "<<"T_AB_RMS"<<endl;
   if(jp) cout<<"Npart_Mean "<<"Npart_RMS "<<"Ncoll_Mean "<<"Ncoll_RMS "<<endl;
   if(ca11) cout<<"Npart_Mean "<<"Npart_RMS "<<"T_AB_Mean "<<"T_AB_RMS"<<endl;
   if(ca11) cout<<"Npart_Mean "<<"Npart_RMS "<<"Ncoll_Mean "<<"Ncoll_RMS "<<endl;
   if(bjet3) cout<<"Npart_Mean "<<"Npart_RMS "<<"T_AB_Mean "<<"T_AB_RMS"<<endl;
   if(bjet3) cout<<"Npart_Mean "<<"Npart_RMS "<<"Ncoll_Mean "<<"Ncoll_RMS "<<endl;
   if(new4) cout<<"Npart_Mean "<<"Npart_RMS "<<"T_AB_Mean "<<"T_AB_RMS"<<endl;
   if(new4) cout<<"Npart_Mean "<<"Npart_RMS "<<"Ncoll_Mean "<<"Ncoll_RMS "<<endl;
   //if(speB) cout<<"Npart_Mean "<<"Npart_RMS "<<"b_Mean "<<"b_RMS"<<endl;
   if(speB) cout<<"Centrality range  ||   <Ncoll> "<<" RMSncoll "<<" ||  <T_AB> "<<"RMStaa "<<" ||   <Npart>   RMSnpart"<<endl;

      for(int i = 0; i < st0.size(); ++i){
//	 cout<<"\\hline"<<endl;
	 
	 if(a) cout<<cLabeljet[i]<<st4[i]<<st0[i]<<st1[i]<<endl;
	 if(b) cout<<cLabelflow[i]<<st0[i]<<st3[i]<<st5[i]<<endl;

	 //	 if(c) cout<<cLabelqq[i]<<st0[i]<<st1[i]<<st2[i]<<endl;
	 //	 if(c) cout<<cLabelSpectraB[i]<<st0[i]<<st1[i]<<st2[i]<<endl;

	 if(c) cout<<cLabeljet[i]<<st0[i]<<st1[i]<<endl;
         if(f) cout<<cLabelforward[i]<<st0[i]<<endl;

	 if(jp) cout<<cLabeljpsi[i]<<st0[i]<<st2[i]<<endl;
	 if(jp5) cout<<cLabeljpsi5[i]<<st0[i]<<st2[i]<<endl;
	 if(jp10) cout<<cLabeljpsi10[i]<<st0[i]<<st2[i]<<endl;
	 if(ca11) cout<<cLabelcastor11[i]<<st0[i]<<st2[i]<<endl;
         if(bjet3) cout<<cLabelbjet3[i]<<st0[i]<<st2[i]<<endl;
         //if(new4) cout<<cLabelnew4[i]<<st0[i]<<st2[i]<<endl;
         if(new4) cout<<cLabelnew4[i]<<"\t"<<st0[i]<<"\t"<<st4[i]<<endl;
         if(speB) cout<<cLabelSpectraB[i]<<"  ||  "<<st1[i]<<"  ||  "<<st2[i]<<"  ||  "<<st0[i]<<endl;
      }
      for(int i = 0; i < st0.size(); ++i){
//         cout<<"\\hline"<<endl;
         if(jp) cout<<cLabeljpsi[i]<<st4[i]<<st1[i]<<endl;
         if(jp5) cout<<cLabeljpsi5[i]<<st4[i]<<st1[i]<<endl;
         if(jp10) cout<<cLabeljpsi10[i]<<st4[i]<<st1[i]<<endl;
         if(ca11) cout<<cLabelcastor11[i]<<st4[i]<<st1[i]<<endl;
         if(bjet3) cout<<cLabelbjet3[i]<<st4[i]<<st1[i]<<endl;
         //if(new4) cout<<cLabelnew4[i]<<st4[i]<<st1[i]<<endl;
         if(new4) cout<<cLabelnew4[i]<<"\t"<<st1[i]<<"\t"<<st2[i]<<endl;
         //if(speB) cout<<cLabelSpectraB[i]<<"\t"<<st1[i]<<"\t"<<st2[i]<<endl;
      }

}


