void getCentErrors(){

  const int nFiles = 100;
  const int nBins = 200;
  const int nRange = 49;
int centL[nRange] = {0,   0,   0,   0,   0,   0,   0,   5,   10,  10,
                     10,  15,  20,  20,  20,  25,  30,  30,  30,  30,
                     35,  40,  40,  40,  40,  45,  50,  50,  50,  50,
                     50,  50,  55,  60,  60,  60,  65,  70,  70,  70,
                     70,  75,  80,  80,  80,  85,  90,  90,  95};
int centH[nRange] = {5,   10,  20,  30,  50,  80,  100, 10,  15,  20,
                     30,  20,  25,  30,  40,  30,  35,  40,  50,  100,
                     40,  45,  50,  60,  100, 50,  55,  60,  70,  80,
                     90,  100, 60,  65,  70,  80,  70,  75,  80,  90,
                     100, 80,  85,  90,  100, 90,  95,  100, 100};


  ifstream inFile;
  const char * inFileName;
  char fileDirName[251];
  sprintf(fileDirName,"/Users/shengquantuo/Desktop/SDM/backfiles/glauberv2/tglaubermc/newPbPb5TeV/sys/density");
  double tmp;
  double npart[nBins], ncoll[nBins];
  double npartAve[nRange], ncollAve[nRange];
  TH1D* hNpart1d[nRange];
  TH1D* hNcoll1d[nRange];
  for(int i = 0; i < nRange; i++){
    hNpart1d[i] = new TH1D(Form("hnpart1d_bin%d",i),"",4500,0,450);
    hNcoll1d[i] = new TH1D(Form("hncoll1d_bin%d",i),"",25000,0,2500);
  }
  for(int i=0; i<nFiles; i++){
    inFileName = Form("%s/jb%d/jb%d_output.txt", fileDirName,i,i);
    inFile.open(inFileName);
    for(int j=0; j<nBins; j++){
      inFile>>tmp; inFile>>npart[j]; inFile>>ncoll[j];
    }
    for(int k=0; k<nRange; k++){
      npartAve[k]=0.0; 
      ncollAve[k]=0.0;
      for(int m=2*centL[k]; m<2*centH[k]; m++){
        npartAve[k]+=npart[m+1]*1.0/(2*centH[k] - 2*centL[k]);
        ncollAve[k]+=ncoll[m+1]*1.0/(2*centH[k] - 2*centL[k]);
      }
      hNpart1d[k]->Fill(npartAve[k]);
      hNcoll1d[k]->Fill(ncollAve[k]);      
    }
    inFile.close();
  }


  ofstream outFile;
  outFile.open("output_cent_err.txt");
  for(int i = 0; i < nRange; i++){
    outFile<<i<<"   "<<hNpart1d[i]->GetRMS()/hNpart1d[i]->GetMean()*100<<"   "<<hNcoll1d[i]->GetRMS()/hNcoll1d[i]->GetMean()*100<<endl;
    cout<<i<<"  "<<centL[i]<<" "<<centH[i]<<"   "<<hNpart1d[i]->GetRMS()/hNpart1d[i]->GetMean()*100<<"   "<<hNcoll1d[i]->GetRMS()/hNcoll1d[i]->GetMean()*100<<endl;
    //cout<<i<<"   "<<hNpart1d[i]->GetMean()<<"   "<<hNcoll1d[i]->GetMean()<<endl;
  }

if(0){
  TCanvas* c1 = new TCanvas("c1","c1",880,800);
  c1->SetLeftMargin(0.12);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  c1->SetTicks(1);
  c1->SetGrid(1);
  c1->SetLogz();
  c1->Divide(2,2);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

    c1->cd(1);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.12);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    hnpart1d_bin22->GetXaxis()->SetRangeUser(hnpart1d_bin22->GetMean()-5*hnpart1d_bin22->GetRMS(), hnpart1d_bin22->GetMean()+5*hnpart1d_bin22->GetRMS());
    hnpart1d_bin22->GetXaxis()->SetTitle("N_{part}");
    hnpart1d_bin22->GetYaxis()->SetTitle("Entries");
    hnpart1d_bin22->GetXaxis()->SetTitleSize(0.06);
    hnpart1d_bin22->GetYaxis()->SetTitleSize(0.06);
    hnpart1d_bin22->GetXaxis()->SetLabelSize(0.05);
    hnpart1d_bin22->GetYaxis()->SetLabelSize(0.05);
    hnpart1d_bin22->GetXaxis()->CenterTitle();
    hnpart1d_bin22->GetYaxis()->CenterTitle();
    hnpart1d_bin22->GetXaxis()->SetNdivisions(506);
    hnpart1d_bin22->GetYaxis()->SetNdivisions(506);
    hnpart1d_bin22->Draw();

    c1->cd(2);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.12);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    //hncoll1d_bin22->Rebin(2);
    //hncoll1d_bin22->Scale(1.0/2);
    hncoll1d_bin22->GetXaxis()->SetRangeUser(hncoll1d_bin22->GetMean()-5*hncoll1d_bin22->GetRMS(), hncoll1d_bin22->GetMean()+5*hncoll1d_bin22->GetRMS());
    hncoll1d_bin22->Draw();

    c1->cd(3);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.12);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    hnpart1d_bin28->GetXaxis()->SetRangeUser(hnpart1d_bin28->GetMean()-5*hnpart1d_bin28->GetRMS(), hnpart1d_bin28->GetMean()+5*hnpart1d_bin28->GetRMS());
    hnpart1d_bin28->Draw();

    c1->cd(4);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.12);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    hncoll1d_bin28->GetXaxis()->SetRangeUser(hncoll1d_bin28->GetMean()-5*hncoll1d_bin28->GetRMS(), hncoll1d_bin28->GetMean()+5*hncoll1d_bin28->GetRMS());
    hncoll1d_bin28->Draw();

}


}


