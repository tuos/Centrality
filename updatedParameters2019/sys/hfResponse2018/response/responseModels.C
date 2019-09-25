void responseModels() {

   TH2D * HF_vs_Npart;
   TH2D * HF_vs_Npart2;
   TH2D * HF_vs_NpartHydjet;

   const char* inSmearingFile = "../out/ForSmearingEposLHC_2018Response5020_d20190806_v1.root";
   TFile* inFileSmear;
   inFileSmear = new TFile(inSmearingFile);
   const char* inSmearingFile2 = "../../eposSim/ForSmearingEposResponse5020_d20160216_v1.root";
   TFile* inFileSmear2;
   inFileSmear2 = new TFile(inSmearingFile2);
   const char* inSmearingFileHydjet = "../out/ForSmearingHydjetDrum5F_2018Response5020_d20190805_v1.root";
   TFile* inFileSmearHydjet;
   inFileSmearHydjet = new TFile(inSmearingFileHydjet);

   HF_vs_Npart = (TH2D*) inFileSmear->Get(Form("SmearingHist/HF_vs_Npart_0")); // 100% eff
   //HF_vs_Npart = (TH2D*) inFileSmear->Get(Form("SmearingHist/HF_vs_Npart_2")); // 98% eff
   //Npix_vs_Npart = (TH2D*) inFileSmear->Get(Form("SmearingHist/Npix_vs_Npart_%d",ih));
   HF_vs_Npart2 = (TH2D*) inFileSmear2->Get(Form("SmearingHist/HF_vs_Npart_0")); // 100% eff
   HF_vs_NpartHydjet = (TH2D*) inFileSmearHydjet->Get(Form("SmearingHist/HF_vs_Npart_0")); // 100% eff

   //HF_vs_Npart2->Draw("colz");
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  c1->SetLeftMargin(0.14);
  c1->SetRightMargin(0.11);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  c1->SetTicks(1);
  c1->SetGrid(1);
  c1->SetLogz();
  //c1->Divide(2,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  HF_vs_Npart->GetXaxis()->SetTitle("N_{part}");
  //HF_vs_Npart->GetYaxis()->SetTitle("#sum HF E_{T}");
  HF_vs_Npart->GetXaxis()->SetTitleSize(0.05);
  HF_vs_Npart->GetYaxis()->SetTitleSize(0.05);
  HF_vs_Npart->GetYaxis()->SetTitleOffset(1.25);
  HF_vs_Npart->GetXaxis()->SetLabelSize(0.035);
  HF_vs_Npart->GetYaxis()->SetLabelSize(0.035);
  HF_vs_Npart->GetXaxis()->CenterTitle();
  HF_vs_Npart->GetYaxis()->CenterTitle();
  HF_vs_Npart->GetXaxis()->SetNdivisions(506);
  HF_vs_Npart->GetYaxis()->SetNdivisions(506);
  HF_vs_Npart->Draw("colz");
  TLatex *tex1= new TLatex(20,5000,"EPOS PbPb Simulation 2018");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.042);
  tex1->SetTextFont(42);
  tex1->Draw();
  c1->SaveAs("plot_responseEPOS2018.pdf");
  c1->SaveAs("plot_responseEPOS2018.png");
  c1->SaveAs("plot_responseEPOS2018.C");

  TCanvas* c2 = new TCanvas("c2","c2",600,600);
  c2->SetLeftMargin(0.14);
  c2->SetRightMargin(0.11);
  c2->SetTopMargin(0.02);
  c2->SetBottomMargin(0.12);
  c2->SetTicks(1);
  c2->SetGrid(1);
  c2->SetLogz();
  //c2->Divide(2,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  HF_vs_Npart2->GetXaxis()->SetTitle("N_{part}");
  //HF_vs_Npart2->GetYaxis()->SetTitle("#sum HF E_{T}");
  HF_vs_Npart2->GetXaxis()->SetTitleSize(0.05);
  HF_vs_Npart2->GetYaxis()->SetTitleSize(0.05);
  HF_vs_Npart2->GetYaxis()->SetTitleOffset(1.25);
  HF_vs_Npart2->GetXaxis()->SetLabelSize(0.035);
  HF_vs_Npart2->GetYaxis()->SetLabelSize(0.035);
  HF_vs_Npart2->GetXaxis()->CenterTitle();
  HF_vs_Npart2->GetYaxis()->CenterTitle();
  HF_vs_Npart2->GetXaxis()->SetNdivisions(506);
  HF_vs_Npart2->GetYaxis()->SetNdivisions(506);
  HF_vs_Npart2->Draw("colz");
  TLatex *tex1= new TLatex(20,5000,"EPOS PbPb Simulation 2015");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.042);
  tex1->SetTextFont(42);
  tex1->Draw();
  c2->SaveAs("plot_responseEPOS2015.pdf");
  c2->SaveAs("plot_responseEPOS2015.png");
  c2->SaveAs("plot_responseEPOS2015.C");

  TCanvas* c3 = new TCanvas("c3","c3",600,600);
  c3->SetLeftMargin(0.14);
  c3->SetRightMargin(0.11);
  c3->SetTopMargin(0.02);
  c3->SetBottomMargin(0.12);
  c3->SetTicks(1);
  c3->SetGrid(1);
  c3->SetLogz();
  //c3->Divide(2,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  HF_vs_NpartHydjet->GetXaxis()->SetTitle("N_{part}");
  //HF_vs_NpartHydjet->GetYaxis()->SetTitle("#sum HF E_{T}");
  HF_vs_NpartHydjet->GetXaxis()->SetTitleSize(0.05);
  HF_vs_NpartHydjet->GetYaxis()->SetTitleSize(0.05);
  HF_vs_NpartHydjet->GetYaxis()->SetTitleOffset(1.25);
  HF_vs_NpartHydjet->GetXaxis()->SetLabelSize(0.035);
  HF_vs_NpartHydjet->GetYaxis()->SetLabelSize(0.035);
  HF_vs_NpartHydjet->GetXaxis()->CenterTitle();
  HF_vs_NpartHydjet->GetYaxis()->CenterTitle();
  HF_vs_NpartHydjet->GetXaxis()->SetNdivisions(506);
  HF_vs_NpartHydjet->GetYaxis()->SetNdivisions(506);
  HF_vs_NpartHydjet->Draw("colz");
  TLatex *tex1= new TLatex(20,5000,"HYDJET PbPb Simulation 2018");
  tex1->SetTextColor(1);
  tex1->SetTextSize(0.042);
  tex1->SetTextFont(42);
  tex1->Draw();
  c3->SaveAs("plot_responseHydjet2018.pdf");
  c3->SaveAs("plot_responseHydjet2018.png");
  c3->SaveAs("plot_responseHydjet2018.C");

}


