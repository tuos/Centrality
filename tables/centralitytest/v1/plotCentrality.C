void plotCentrality(){

  
  TFile* f4 = new TFile("histogram_test_MB_AOD_10kevents.root");
  TH1D* cent  = f4->Get("demo/centhist");
  TCanvas* cd = new TCanvas("cd","",600,500);
  cd->SetLeftMargin(0.12);
  cd->SetRightMargin(0.02);
  cd->SetTopMargin(0.02);
  cd->SetBottomMargin(0.12);
  cd->SetTicks(1);
  cent->SetTitle("");
  cent->SetXTitle("Centrality (200 bins)");
  cent->SetYTitle("# of Events");
  cent->GetYaxis()->SetTitleOffset(1.2);
  cent->GetXaxis()->SetTitleOffset(1.2);
  cent->GetXaxis()->CenterTitle(1);
  cent->GetYaxis()->CenterTitle(1);
  cent->GetXaxis()->SetTitleSize(0.046);
  cent->GetYaxis()->SetTitleSize(0.046);
  cent->GetXaxis()->SetTitleFont(62);
  cent->GetYaxis()->SetTitleFont(62);
  cent->SetAxisRange(0,209,"Y");
  cent->SetAxisRange(0,203,"X");
  cent->SetMarkerStyle(20);
  cent->Sumw2();
  cent->SetMarkerSize(1);
  cent->SetMarkerColor(1);
  cent->SetLineColor(1);
  //cent->SetStats(0);
  cent->Draw("Pez");

    TLatex *tex1= new TLatex(55.5,125.060,"Hydjet 5TeV MB,  AOD");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

    TLatex *tex2= new TLatex(55.5,99.054,"CMSSW_7_5_0_pre5");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();
  cd->SaveAs("centralityDist750x2760GeV.png");

}

