{
  f = new TFile("glauberCuAu_default_1M.root","READ");
  t = (TTree*)(f->Get("nt_Cu_Au"));
 
  const int nCent = 8;

  double bRange[nCent+1]={0, 2.8095, 3.9745, 5.6275, 6.9025, 7.9685, 8.9055, 9.7575, 30};
  int centRange[nCent+1]={0, 5, 10, 20, 30, 40, 50, 60, 100}; 
  long int nEvt[nCent];
  double sumNpart[nCent], sumB[nCent], sumS[nCent];
  double sumEcc2[nCent], sumEcc22[nCent], sumEcc24[nCent];
  double sumEcc3[nCent], sumEcc32[nCent], sumEcc34[nCent];
  for(int i=0; i<nCent; i++){
    nEvt[i]=0;
    sumNpart[i]=0.; sumB[i]=0.; sumS[i]=0.;
    sumEcc2[i]=0.; sumEcc22[i]=0.; sumEcc24[i]=0.;
    sumEcc3[i]=0.; sumEcc32[i]=0.; sumEcc34[i]=0.;
  }

 Float_t npart = 0;
 Float_t nb = 0;
 Float_t ns = 0;
 Float_t ec2 = 0;
 Float_t ec3 = 0;
 t -> SetBranchAddress("Npart",&npart);
 t -> SetBranchAddress("B",&nb);
 t -> SetBranchAddress("AreaS",&ns);
 t -> SetBranchAddress("Ecc2",&ec2);
 t -> SetBranchAddress("Ecc3",&ec3);

 for ( int ient = 0; ient < t -> GetEntries(); ient++ ) {
  //for ( int ient = 0; ient < 1000; ient++ ) {
    int nbytes = t->GetEntry(ient);
    //cout<<nb<<"  "<<npart<<"  "<<ec2<<"  "<<ec3<<"  "<<ec4<<endl;
    for(int i=0; i<nCent; i++){

      if(nb>bRange[i] && nb<bRange[i+1]){

        nEvt[i]+=1;
        sumNpart[i]+=npart;
        sumB[i]+=nb;
        sumS[i]+=ns;
        sumEcc2[i]+=ec2;
        sumEcc22[i]+=ec2*ec2;
        sumEcc24[i]+=ec2*ec2*ec2*ec2;
        sumEcc3[i]+=ec3;
        sumEcc32[i]+=ec3*ec3;
        sumEcc34[i]+=ec3*ec3*ec3*ec3;

      }

    }
  }

  ofstream out;
  out.open("eccResultsCuAu.txt");

  for(int i=0; i<nCent; i++){
    //cout<<nEvt[i]<<endl;
    //cout<<centRange[i]<<"  "<<centRange[i+1]<<"   "<<sumB[i]/nEvt[i]<<"  "<<sumNpart[i]*1.0/nEvt[i]<<"  "<<sumS[i]/nEvt[i]<<"  "<<sumEcc2[i]/nEvt[i]<<"  "<<sumEcc3[i]/nEvt[i]<<"  "<<sqrt(sumEcc22[i]/nEvt[i])<<"  "<<sqrt(sumEcc32[i]/nEvt[i])<<"  "<<pow( fabs(2.0*(sumEcc22[i]/nEvt[i])*(sumEcc22[i]/nEvt[i])-sumEcc24[i]/nEvt[i]), 1.0/4)<<"  "<<pow( fabs(2.0*(sumEcc32[i]/nEvt[i])*(sumEcc32[i]/nEvt[i])-sumEcc34[i]/nEvt[i]), 1.0/4)<<endl;
    cout<<centRange[i]<<"  "<<centRange[i+1]<<"   "<<sumB[i]/nEvt[i]<<"  "<<sumNpart[i]*1.0/nEvt[i]<<"  "<<sumS[i]/nEvt[i]<<"  "<<sumEcc2[i]/nEvt[i]<<"  "<<sumEcc3[i]/nEvt[i]<<"  "<<sqrt(sumEcc22[i]/nEvt[i])<<"  "<<sqrt(sumEcc32[i]/nEvt[i])<<endl;
    out<<centRange[i]<<"  "<<centRange[i+1]<<"   "<<sumB[i]/nEvt[i]<<"  "<<sumNpart[i]*1.0/nEvt[i]<<"  "<<sumS[i]/nEvt[i]<<"  "<<sumEcc2[i]/nEvt[i]<<"  "<<sumEcc3[i]/nEvt[i]<<"  "<<sqrt(sumEcc22[i]/nEvt[i])<<"  "<<sqrt(sumEcc32[i]/nEvt[i])<<endl;
  }
  cout<<0<<"  "<<10<<"   "<<(sumB[0]+sumB[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumNpart[0]+sumNpart[1])*1.0/(nEvt[0]+nEvt[1])<<"  "<<(sumS[0]+sumS[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumEcc2[0]+sumEcc2[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumEcc3[0]+sumEcc3[1])/(nEvt[0]+nEvt[1])<<"  "<<sqrt((sumEcc22[0]+sumEcc22[1])/(nEvt[0]+nEvt[1]))<<"  "<<sqrt((sumEcc32[0]+sumEcc32[1])/(nEvt[0]+nEvt[1]))<<endl;
  out<<0<<"  "<<10<<"   "<<(sumB[0]+sumB[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumNpart[0]+sumNpart[1])*1.0/(nEvt[0]+nEvt[1])<<"  "<<(sumS[0]+sumS[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumEcc2[0]+sumEcc2[1])/(nEvt[0]+nEvt[1])<<"  "<<(sumEcc3[0]+sumEcc3[1])/(nEvt[0]+nEvt[1])<<"  "<<sqrt((sumEcc22[0]+sumEcc22[1])/(nEvt[0]+nEvt[1]))<<"  "<<sqrt((sumEcc32[0]+sumEcc32[1])/(nEvt[0]+nEvt[1]))<<endl;

out<<endl;
  for(int i=0; i<nCent; i++) out<<nEvt[i]<<endl;

}


