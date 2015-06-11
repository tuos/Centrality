void plot(){

  gROOT->SetStyle("Plain");
  TFile *infile = new TFile("/Users/tuos/Desktop/soft/glauberv2/tglaubermc/cuAu/glauberCuAu_default_1M.root","read");
  infile->cd();
  TCanvas *c1 = new TCanvas("c1","c1",100,100,610,500);
  c1->cd();
  TProfile *pEcc2Npart = new TProfile("pEcc2Npart","#epsilon_{n} vs Npart in 200 GeV CuAu Collisions from Glauber MC;Npart;#epsilon_{n}",252,-0.5,251.5);
  nt_Cu_Au->Project("pEcc2Npart","Ecc2:Npart");
  pEcc2Npart->SetMarkerSize(1);
  pEcc2Npart->SetMarkerColor(1);
  pEcc2Npart->SetMarkerStyle(20);
  pEcc2Npart->SetLineColor(1);
  pEcc2Npart->SetStats(0);
  int rebins=4;
  pEcc2Npart->Rebin(rebins);
  pEcc2Npart->Draw("p");
  TProfile *pEcc3Npart = new TProfile("pEcc3Npart","#epsilon_{n} vs Npart in 200 GeV CuAu;Npart;#epsilon_{n}",252,-0.5,251.5);
  nt_Cu_Au->Project("pEcc3Npart","Ecc3:Npart");
  pEcc3Npart->SetMarkerSize(1);
  pEcc3Npart->SetMarkerColor(2);
  pEcc3Npart->SetMarkerStyle(25);
  pEcc3Npart->SetLineColor(2);
  pEcc3Npart->SetStats(0);
  pEcc3Npart->Rebin(rebins);
  pEcc3Npart->Draw("psame");
  TLegend *leg = new TLegend(0.7,0.7,0.88,0.86);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.055);
  leg->AddEntry(pEcc2Npart,"#epsilon_{2}","p");
  leg->AddEntry(pEcc3Npart,"#epsilon_{3}","p");
  leg->Draw();
  c1->SaveAs("epsilonNvsNpart_CuAu.png");

}
