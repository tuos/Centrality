void checkAllSys(){
  const int nBins = 20;
  double sys1[2][nBins];
  double sys2[2][nBins];
  double sys3[2][nBins];
  double sysT[2][nBins];
  double tmp;

  TH1D *hSys[2][4];
  ifstream inNpart;
  inNpart.open("npart_2018epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNpart>>tmp;
    inNpart>>tmp;
    inNpart>>tmp;
    inNpart>>sys1[0][i];
    inNpart>>sys2[0][i];
    inNpart>>sys3[0][i];
    inNpart>>sysT[0][i];
    //sysT[0][i] = sqrt(sys1[0][i]*sys1[0][i]+sys2[0][i]*sys2[0][i]+sys3[0][i]*sys3[0][i]);
  }
  ifstream inNcoll;
  inNcoll.open("ncoll_2018epos100eff.txt");
  for(int i=0; i<nBins; i++){
    inNcoll>>tmp;
    inNcoll>>tmp;
    inNcoll>>tmp;
    inNcoll>>sys1[1][i];
    inNcoll>>sys2[1][i];
    inNcoll>>sys3[1][i];
    inNcoll>>sysT[1][i];
    //sysT[1][i] = sqrt(sys1[1][i]*sys1[1][i]+sys2[1][i]*sys2[1][i]+sys3[1][i]*sys3[1][i]);
  }
  
  for(int i=0; i<4; i++){
    hSys[0][i] = new TH1D(Form("hsys_npart_%d",i),"",20,0,100);
    hSys[1][i] = new TH1D(Form("hsys_ncoll_%d",i),"",20,0,100);
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
  }  

//int rebins = 10;
//hSys[0][0]->Rebin(rebins);
//hSys[0][0]->Scale(1.0/rebins);

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

  hSys[0][3]->GetYaxis()->SetRangeUser(0,8);
  hSys[0][3]->GetXaxis()->SetTitle("Centrality (%)");
  hSys[0][3]->GetYaxis()->SetTitle("Relative uncertainty (%)");
  hSys[0][3]->GetXaxis()->SetTitleSize(0.06);
  hSys[0][3]->GetYaxis()->SetTitleSize(0.06);
  hSys[0][3]->GetYaxis()->SetTitleOffset(0.9);
  hSys[0][3]->GetXaxis()->SetLabelSize(0.05);
  hSys[0][3]->GetYaxis()->SetLabelSize(0.05);
  hSys[0][3]->GetXaxis()->CenterTitle();
  hSys[0][3]->GetYaxis()->CenterTitle();
  hSys[0][3]->GetXaxis()->SetNdivisions(506);
  hSys[0][3]->GetYaxis()->SetNdivisions(506);
  hSys[0][3]->SetLineColor(1);
  hSys[0][3]->SetLineWidth(4);
  hSys[0][3]->Draw("L");
  hSys[0][2]->SetLineColor(2);
  hSys[0][2]->SetLineWidth(3);
  hSys[0][2]->Draw("Lsame");
  hSys[0][1]->SetLineColor(4);
  hSys[0][1]->SetLineWidth(3);
  hSys[0][1]->Draw("Lsame");
  hSys[0][0]->SetLineColor(8);
  hSys[0][0]->SetLineWidth(3);
  hSys[0][0]->Draw("Lsame");

  hSys[0][3]->Draw("Lsame");
  TLegend *leg0 = new TLegend(0.55,0.605,0.9,0.905);
  leg0->SetFillColor(10);
  leg0->SetBorderSize(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.048);
  leg0->AddEntry(hSys[0][2], "Density pars.", "L");
  leg0->AddEntry(hSys[0][1], "#sigma_{NN}^{inel}", "L");
  leg0->AddEntry(hSys[0][0], "d_{node}", "L");
  leg0->AddEntry(hSys[0][3], "Total uncert.", "L");
  leg0->Draw();

  TLatex *tex1= new TLatex(12,6,"N_{part}");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.075);
  //tex1->SetTextFont(42);
  tex1->Draw();

//# ncoll
  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.16);
  gPad->SetTopMargin(0.02);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);

  hSys[1][3]->GetYaxis()->SetRangeUser(0,8);
  hSys[1][3]->GetXaxis()->SetTitle("Centrality (%)");
  hSys[1][3]->GetYaxis()->SetTitle("Relative uncertainty (%)");
  hSys[1][3]->GetXaxis()->SetTitleSize(0.06);
  hSys[1][3]->GetYaxis()->SetTitleSize(0.06);
  hSys[1][3]->GetYaxis()->SetTitleOffset(0.9);
  hSys[1][3]->GetXaxis()->SetLabelSize(0.05);
  hSys[1][3]->GetYaxis()->SetLabelSize(0.05);
  hSys[1][3]->GetXaxis()->CenterTitle();
  hSys[1][3]->GetYaxis()->CenterTitle();
  hSys[1][3]->GetXaxis()->SetNdivisions(506);
  hSys[1][3]->GetYaxis()->SetNdivisions(506);
  hSys[1][3]->SetLineColor(1);
  hSys[1][3]->SetLineWidth(4);
  hSys[1][3]->Draw("L");
  hSys[1][2]->SetLineColor(2);
  hSys[1][2]->SetLineWidth(3);
  hSys[1][2]->Draw("Lsame");
  hSys[1][1]->SetLineColor(4);
  hSys[1][1]->SetLineWidth(3);
  hSys[1][1]->Draw("Lsame");
  hSys[1][0]->SetLineColor(8);
  hSys[1][0]->SetLineWidth(3);
  hSys[1][0]->Draw("Lsame");

  hSys[1][3]->Draw("Lsame");

  TLatex *tex1= new TLatex(12,6,"N_{coll}");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.075);
  //tex1->SetTextFont(42);
  tex1->Draw();

  c1->SaveAs("plot_checkAllSys.pdf");
  c1->SaveAs("plot_checkAllSys.png");
  c1->SaveAs("plot_checkAllSys.C");

}

