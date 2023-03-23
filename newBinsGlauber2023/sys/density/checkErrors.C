void checkErrors(){

  const int nFiles = 100;
  const int nBins = 200;
  const int nRange = 50;
  int centL[nRange] = {0,   0, 5,  10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95,  0,  10, 20, 30, 40, 50, 60, 70, 80, 90,  0,  20, 40, 60, 80,  0,  50,  0,  30, 50, 70, 70,  10, 30,  50, 40,  50, 50, 0};
  int centH[nRange] = {100, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 20, 40, 60, 80, 100, 50, 100, 30, 50, 70, 90, 100, 30, 100, 80, 100, 90, 80, 80};

  ifstream inFile;
  const char * inFileName;
  char fileDirName[251];
  sprintf(fileDirName,"/Users/shengquantuo/Desktop/soft/glauberv2/tglaubermc/newPbPb5TeV/sys/density");
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


if(1){
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
    gPad->SetBottomMargin(0.16);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    gPad->SetTicks(-1);
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
    TLatex *tex1= new TLatex(hnpart1d_bin22->GetMean()-4.*hnpart1d_bin22->GetRMS(),hnpart1d_bin22->GetMaximum()*0.9, "10-20%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.055);
    //tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(hnpart1d_bin22->GetMean()+0.8*hnpart1d_bin22->GetRMS(),hnpart1d_bin22->GetMaximum()*0.9, "Glauber PbPb");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(hnpart1d_bin22->GetMean()+0.8*hnpart1d_bin22->GetRMS(),hnpart1d_bin22->GetMaximum()*0.8, "Density para. uncert.");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(hnpart1d_bin22->GetMean()+0.8*hnpart1d_bin22->GetRMS(),hnpart1d_bin22->GetMaximum()*0.7, "from 100 files");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();

    c1->cd(2);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.16);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    gPad->SetTicks(-1);
    double means = hncoll1d_bin22->GetMean();
    double rmss = hncoll1d_bin22->GetRMS();
    hncoll1d_bin22->Rebin(10);
    //hncoll1d_bin22->GetXaxis()->SetRangeUser(hncoll1d_bin22->GetMean()-5*hncoll1d_bin22->GetRMS(), hncoll1d_bin22->GetMean()+5*hncoll1d_bin22->GetRMS());
    hncoll1d_bin22->GetXaxis()->SetRangeUser(means-5*rmss, means+5*rmss);
    hncoll1d_bin22->GetXaxis()->SetTitle("N_{coll}");
    hncoll1d_bin22->GetYaxis()->SetTitle("Entries");
    hncoll1d_bin22->GetXaxis()->SetTitleSize(0.06);
    hncoll1d_bin22->GetYaxis()->SetTitleSize(0.06);
    hncoll1d_bin22->GetXaxis()->SetLabelSize(0.05);
    hncoll1d_bin22->GetYaxis()->SetLabelSize(0.05);
    hncoll1d_bin22->GetXaxis()->CenterTitle();
    hncoll1d_bin22->GetYaxis()->CenterTitle();
    hncoll1d_bin22->GetXaxis()->SetNdivisions(506);
    hncoll1d_bin22->GetYaxis()->SetNdivisions(506);
    hncoll1d_bin22->Draw();
    TLatex *tex1= new TLatex(hncoll1d_bin22->GetMean()-4.*hncoll1d_bin22->GetRMS(),hncoll1d_bin22->GetMaximum()*0.9, "10-20%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.055);
    //tex1->SetTextFont(42);
    tex1->Draw();

    c1->cd(3);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.16);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    gPad->SetTicks(-1);
    hnpart1d_bin28->GetXaxis()->SetRangeUser(hnpart1d_bin28->GetMean()-5*hnpart1d_bin28->GetRMS(), hnpart1d_bin28->GetMean()+5*hnpart1d_bin28->GetRMS());
    hnpart1d_bin28->GetXaxis()->SetTitle("N_{part}");
    hnpart1d_bin28->GetYaxis()->SetTitle("Entries");
    hnpart1d_bin28->GetXaxis()->SetTitleSize(0.06);
    hnpart1d_bin28->GetYaxis()->SetTitleSize(0.06);
    hnpart1d_bin28->GetXaxis()->SetLabelSize(0.05);
    hnpart1d_bin28->GetYaxis()->SetLabelSize(0.05);
    hnpart1d_bin28->GetXaxis()->CenterTitle();
    hnpart1d_bin28->GetYaxis()->CenterTitle();
    hnpart1d_bin28->GetXaxis()->SetNdivisions(506);
    hnpart1d_bin28->GetYaxis()->SetNdivisions(506);
    hnpart1d_bin28->Draw();
    TLatex *tex1= new TLatex(hnpart1d_bin28->GetMean()-4.*hnpart1d_bin28->GetRMS(),hnpart1d_bin28->GetMaximum()*0.9, "70-80%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.055);
    //tex1->SetTextFont(42);
    tex1->Draw();

    c1->cd(4);
    gPad->SetLeftMargin(0.12);
    gPad->SetBottomMargin(0.16);
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.02);
    gPad->SetTicks(-1);
    hncoll1d_bin28->GetXaxis()->SetRangeUser(hncoll1d_bin28->GetMean()-5*hncoll1d_bin28->GetRMS(), hncoll1d_bin28->GetMean()+5*hncoll1d_bin28->GetRMS());
    hncoll1d_bin28->GetXaxis()->SetTitle("N_{coll}");
    hncoll1d_bin28->GetYaxis()->SetTitle("Entries");
    hncoll1d_bin28->GetXaxis()->SetTitleSize(0.06);
    hncoll1d_bin28->GetYaxis()->SetTitleSize(0.06);
    hncoll1d_bin28->GetXaxis()->SetLabelSize(0.05);
    hncoll1d_bin28->GetYaxis()->SetLabelSize(0.05);
    hncoll1d_bin28->GetXaxis()->CenterTitle();
    hncoll1d_bin28->GetYaxis()->CenterTitle();
    hncoll1d_bin28->GetXaxis()->SetNdivisions(506);
    hncoll1d_bin28->GetYaxis()->SetNdivisions(506);
    hncoll1d_bin28->Draw();
    TLatex *tex1= new TLatex(hncoll1d_bin28->GetMean()-4.*hncoll1d_bin28->GetRMS(),hncoll1d_bin28->GetMaximum()*0.9, "70-80%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.055);
    //tex1->SetTextFont(42);
    tex1->Draw();

}

  c1->SaveAs("plot_checkErrors.pdf");
  c1->SaveAs("plot_checkErrors.png");
  c1->SaveAs("plot_checkErrors.C");

}


