void npartForJavier(){

  const int nCent=13;
  char centNames[nCent][200]={"_0_5", "_5_10", "_10_20", "_20_30", "_30_40", "_40_50", "_50_70", "_70_100", "_0_10", "_10_30", "_30_50", "_50_100", "_0_100",};
  int binNamesA[nCent]={39, 37, 33, 29, 25, 21, 13, 1,  37, 29, 21, 1,  1};
  int binNamesB[nCent]={40, 38, 36, 32, 28, 24, 20, 12, 40, 36, 28, 20, 40};
  TH2D *Npart_vs_Cent;
  TH2D *Ncoll_vs_Cent;
  TH1D *NpartCent[nCent];
  TH1D *NcollCent[nCent];
  for (int i = 0; i < nCent; i++) {
   NpartCent[i]= new TH1D(Form("NpartCent%s",centNames[i]), "Npart distribution", 500, 0, 500);
   NcollCent[i]= new TH1D(Form("NcollCent%s",centNames[i]), "Ncoll distribution", 2000, 0, 2000);
  }
  TFile* inFile = new TFile("./glaubertest_40bins_d0317.root");
  Npart_vs_Cent = (TH2D*)inFile->Get(Form("Eff100_sim00_g0/hNpart")); 
  Ncoll_vs_Cent = (TH2D*)inFile->Get(Form("Eff100_sim00_g0/hNcoll")); 
  for (int i = 0; i < nCent; i++) {
   NpartCent[i] = Npart_vs_Cent->ProjectionY(Form("NpartCent%s",centNames[i]), binNamesA[i], binNamesB[i]);
   NcollCent[i] = Ncoll_vs_Cent->ProjectionY(Form("NcollCent%s",centNames[i]), binNamesA[i], binNamesB[i]);
   cout<<centNames[i]<<"  "<<NpartCent[i]->GetMean()<<"  "<<NcollCent[i]->GetMean()<<endl;
  }
 
  TFile * outFile = new TFile("./hNpartNcollCentralityForJavier.root","recreate");
  outFile->cd();
  for (int i = 0; i < nCent; i++) {
   NpartCent[i]->Write();
   NcollCent[i]->Write();
  } 

}

