void getErrors(){

  const int nFiles = 100;
  const int nBins = 200;
  ifstream inFile;
  const char * inFileName;
  char fileDirName[251];
  sprintf(fileDirName,"/Users/shengquantuo/Desktop/soft/glauberv2/tglaubermc/newPbPb5TeV/sys/density");
  double tmp, npart, ncoll;
  TH1D* hNpart1d[nBins];
  TH1D* hNcoll1d[nBins];
  for(int i = 0; i < nBins; i++){
    hNpart1d[i] = new TH1D(Form("hnpart1d_bin%d",i),"",450,0,450);
    hNcoll1d[i] = new TH1D(Form("hncoll1d_bin%d",i),"",2500,0,2500);
  }
  for(int i=0; i<nFiles; i++){
    inFileName = Form("%s/jb%d/jb%d_output.txt", fileDirName,i,i);
    inFile.open(inFileName);
    //cout<<i<<"  "<<inFileName<<endl;
    for(int j=0; j<nBins; j++){
      inFile>>tmp; inFile>>npart; inFile>>ncoll;
      hNpart1d[j]->Fill(npart);
      hNcoll1d[j]->Fill(ncoll);
      //if(i==1 && j==1) cout<<tmp<<" "<<npart<<" "<<ncoll<<endl;
    }
    inFile.close();
  }


  ofstream outFile;
  outFile.open("output_err.txt");
  for(int i = 0; i < nBins; i++){
    outFile<<i<<"   "<<hNpart1d[i]->GetRMS()/hNpart1d[i]->GetMean()*100<<"   "<<hNcoll1d[i]->GetRMS()/hNcoll1d[i]->GetMean()*100<<endl;
    cout<<i<<"   "<<hNpart1d[i]->GetRMS()/hNpart1d[i]->GetMean()*100<<"   "<<hNcoll1d[i]->GetRMS()/hNcoll1d[i]->GetMean()*100<<endl;
    //cout<<i<<"   "<<hNpart1d[i]->GetMean()<<"   "<<hNcoll1d[i]->GetMean()<<endl;
  }

}


