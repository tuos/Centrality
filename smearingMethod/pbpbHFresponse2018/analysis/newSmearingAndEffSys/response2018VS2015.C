void response2018VS2015(){
  const int nBins = 20;
  double sys1[2][nBins];
  double sys2[2][nBins];
  double sys3[2][nBins];
  double sysT[2][nBins];
  double tmp;
  double sys1New[2][nBins];
  double sys2New[2][nBins];
  double sys3New[2][nBins];
  double sysTNew[2][nBins];

  double oldNpart[nBins];
  double oldNcoll[nBins];
  double newNpart[nBins];
  double newNcoll[nBins];
  double errNpartL[nBins];
  double errNpartH[nBins];
  double errNcollL[nBins];
  double errNcollH[nBins];
  TH1D *hOldNpart = new TH1D("hOldNpart","",20,0,100);
  TH1D *hOldNcoll = new TH1D("hOldNcoll","",20,0,100);
  TH1D *hNewNpart = new TH1D("hNewNpart","",20,0,100);
  TH1D *hNewNcoll = new TH1D("hNewNcoll","",20,0,100);


  TH1D *hSys[2][4];
  TH1D *hSysNew[2][4];
  ifstream inNpart;
  inNpart.open("./npart_2015epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNpart>>tmp;
    inNpart>>tmp;
    inNpart>>oldNpart[i];
    inNpart>>sys1[0][i];
    inNpart>>sys2[0][i];
    inNpart>>sys3[0][i];
    inNpart>>sysT[0][i];
    //sysT[0][i] = sqrt(sys1[0][i]*sys1[0][i]+sys2[0][i]*sys2[0][i]+sys3[0][i]*sys3[0][i]);
  }
  ifstream inNcoll;
  inNcoll.open("./ncoll_2015epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNcoll>>tmp;
    inNcoll>>tmp;
    inNcoll>>oldNcoll[i];
    inNcoll>>sys1[1][i];
    inNcoll>>sys2[1][i];
    inNcoll>>sys3[1][i];
    inNcoll>>sysT[1][i];
    //sysT[1][i] = sqrt(sys1[1][i]*sys1[1][i]+sys2[1][i]*sys2[1][i]+sys3[1][i]*sys3[1][i]);
  }
 
  ifstream inNpartNew;
  inNpartNew.open("./npart_2018epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNpartNew>>tmp;
    inNpartNew>>tmp;
    inNpartNew>>newNpart[i];
    inNpartNew>>sys1New[0][i];
    inNpartNew>>sys2New[0][i];
    inNpartNew>>sys3New[0][i];
    inNpartNew>>sysTNew[0][i];
    //sysT[0][i] = sqrt(sys1[0][i]*sys1[0][i]+sys2[0][i]*sys2[0][i]+sys3[0][i]*sys3[0][i]);
  }
  ifstream inNcollNew; 
  inNcollNew.open("./ncoll_2018epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNcollNew>>tmp;
    inNcollNew>>tmp;
    inNcollNew>>newNcoll[i];
    inNcollNew>>sys1New[1][i];
    inNcollNew>>sys2New[1][i];
    inNcollNew>>sys3New[1][i];
    inNcollNew>>sysTNew[1][i];
    //sysT[1][i] = sqrt(sys1[1][i]*sys1[1][i]+sys2[1][i]*sys2[1][i]+sys3[1][i]*sys3[1][i]);
  } 

  for(int i=0; i<4; i++){
    hSys[0][i] = new TH1D(Form("hsys_npart_%d",i),"",20,0,100);
    hSys[1][i] = new TH1D(Form("hsys_ncoll_%d",i),"",20,0,100);
    hSysNew[0][i] = new TH1D(Form("hsysnew_npart_%d",i),"",20,0,100);
    hSysNew[1][i] = new TH1D(Form("hsysnew_ncoll_%d",i),"",20,0,100);
  }
  for(int i=0; i<nBins; i++){
    hSys[0][0]->SetBinContent(i+1, sys1[0][i]);
    hSys[0][1]->SetBinContent(i+1, sys2[0][i]);
    hSys[0][2]->SetBinContent(i+1, sys3[0][i]);
    hSys[0][3]->SetBinContent(i+1, sysT[0][i]);

    hSys[1][0]->SetBinContent(i+1, sys1[1][i]);
    hSys[1][1]->SetBinContent(i+1, sys2[1][i]);
    hSys[1][2]->SetBinContent(i+1, sys3[1][i]);
    hSys[1][3]->SetBinContent(i+1, sysT[1][i]);

    hSysNew[0][0]->SetBinContent(i+1, sys1New[0][i]);
    hSysNew[0][1]->SetBinContent(i+1, sys2New[0][i]);
    hSysNew[0][2]->SetBinContent(i+1, sys3New[0][i]);
    hSysNew[0][3]->SetBinContent(i+1, sysTNew[0][i]);

    hSysNew[1][0]->SetBinContent(i+1, sys1New[1][i]);
    hSysNew[1][1]->SetBinContent(i+1, sys2New[1][i]);
    hSysNew[1][2]->SetBinContent(i+1, sys3New[1][i]);
    hSysNew[1][3]->SetBinContent(i+1, sysTNew[1][i]);
  }  

//int rebins = 10;
//hSys[0][0]->Rebin(rebins);
//hSys[0][0]->Scale(1.0/rebins);

  for(int i=0; i<nBins; i++){
    hOldNpart->SetBinContent(i+1, oldNpart[i]);
    hOldNcoll->SetBinContent(i+1, oldNcoll[i]);
  }
  for(int i=0; i<nBins; i++){
    hNewNpart->SetBinContent(i+1, newNpart[i]);
    hNewNcoll->SetBinContent(i+1, newNcoll[i]);
  }
  hNewNpart->Divide(hOldNpart);
  hNewNcoll->Divide(hOldNcoll);

  double x[nBins];
  double y[nBins];
  double exl[nBins];
  double eyl[nBins];
  double exh[nBins];
  double eyh[nBins];
  for(int i=0; i<nBins; i++){
    x[i] = 5*i+2.5;
    y[i] = 1.0;
    exl[i]=0;
    exh[i]=0;
    eyl[i]= sysT[0][i]*0.01;
    eyh[i]= sysT[0][i]*0.01;
cout<<i<<"  "<<eyl[i]<<"  "<<eyh[i]<<endl;
  }
   gr = new TGraphAsymmErrors(nBins,x,y,exl,exh,eyl,eyh);
   gr->SetTitle("");
   gr->SetFillColor(kGray);
   gr->SetMarkerColor(kGray);
   //gr->SetMarkerStyle(21);

  double x2[nBins];
  double y2[nBins];
  double exl2[nBins];
  double eyl2[nBins];
  double exh2[nBins];
  double eyh2[nBins];
  for(int i=0; i<nBins; i++){
    x2[i] = 5*i+2.5;
    y2[i] = 1.0;
    exl2[i]=0;
    exh2[i]=0;
    eyl2[i]= sysT[1][i]*0.01;
    eyh2[i]= sysT[1][i]*0.01;
  }


  TCanvas* c1 = new TCanvas("c1","c1",880,500);
  c1->SetLeftMargin(0.12);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  c1->SetTicks(1);
  c1->SetGrid(1);
  c1->SetLogz();
  c1->Divide(2,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.16);
  gPad->SetTopMargin(0.02);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);

  hNewNpart->GetYaxis()->SetRangeUser(0.75,1.25);
  hNewNpart->GetXaxis()->SetTitle("Centrality (%)");
  hNewNpart->GetYaxis()->SetTitle("Ratio");
  hNewNpart->GetXaxis()->SetTitleSize(0.06);
  hNewNpart->GetYaxis()->SetTitleSize(0.06);
  hNewNpart->GetYaxis()->SetTitleOffset(0.9);
  hNewNpart->GetXaxis()->SetLabelSize(0.05);
  hNewNpart->GetYaxis()->SetLabelSize(0.05);
  hNewNpart->GetXaxis()->CenterTitle();
  hNewNpart->GetYaxis()->CenterTitle();
  hNewNpart->GetXaxis()->SetNdivisions(506);
  hNewNpart->GetYaxis()->SetNdivisions(506);
  hNewNpart->SetLineColor(2);
  hNewNpart->SetLineWidth(3);
  hNewNpart->SetMarkerStyle(20);
  hNewNpart->SetMarkerColor(2);
  hNewNpart->Draw("P");
  gr->Draw("e3same");
  hNewNpart->Draw("Psame");
  TLegend *leg0 = new TLegend(0.25,0.205,0.6,0.405);
  leg0->SetFillColor(10);
  leg0->SetBorderSize(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.048);
  leg0->AddEntry(hNewNpart, "2018/2015 HF response", "p");
  leg0->AddEntry(gr, "Uncertainty (Glauber only)", "p");
  leg0->Draw();

  TLatex *tex1= new TLatex(12,1.15,"N_{part}");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.075);
  //tex1->SetTextFont(42);
  tex1->Draw();

   TBox *box1 = new TBox(18,0.8,23,0.82);
   box1->SetFillColor(kGray);
   box1->Draw();

//# ncoll
  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.16);
  gPad->SetTopMargin(0.02);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);

   gr2 = new TGraphAsymmErrors(nBins,x2,y2,exl2,exh2,eyl2,eyh2);
   gr2->SetTitle("");
   gr2->SetFillColor(kGray);
   gr2->SetMarkerColor(kGray);

  hNewNcoll->GetYaxis()->SetRangeUser(0.75,1.25);
  hNewNcoll->GetXaxis()->SetTitle("Centrality (%)");
  hNewNcoll->GetYaxis()->SetTitle("Ratio");
  hNewNcoll->GetXaxis()->SetTitleSize(0.06);
  hNewNcoll->GetYaxis()->SetTitleSize(0.06);
  hNewNcoll->GetYaxis()->SetTitleOffset(0.9);
  hNewNcoll->GetXaxis()->SetLabelSize(0.05);
  hNewNcoll->GetYaxis()->SetLabelSize(0.05);
  hNewNcoll->GetXaxis()->CenterTitle();
  hNewNcoll->GetYaxis()->CenterTitle();
  hNewNcoll->GetXaxis()->SetNdivisions(506);
  hNewNcoll->GetYaxis()->SetNdivisions(506);
  hNewNcoll->SetLineColor(2);
  hNewNcoll->SetLineWidth(3);
  hNewNcoll->SetMarkerStyle(20);
  hNewNcoll->SetMarkerColor(2);
  hNewNcoll->Draw("P");
  gr2->Draw("e3same");
  hNewNcoll->Draw("Psame");

  TLatex *tex1= new TLatex(12,1.15,"N_{coll}");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.075);
  //tex1->SetTextFont(42);
  tex1->Draw();

  c1->SaveAs("plot_checkresponse2018VS2015.pdf");
  c1->SaveAs("plot_checkresponse2018VS2015.png");
  c1->SaveAs("plot_checkresponse2018VS2015.C");

}

