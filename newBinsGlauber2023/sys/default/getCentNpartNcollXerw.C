#include <iomanip>
void getCentNpartNcollXerw(){

  // Setup
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptFit(1011);

  // Open File
  TFile *infile = new TFile("./glauber_PbpnrwPbpnrw_default_1M.root");
  infile->cd();
  //TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",200000000,-0.01,19.99);
  TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",2000000,-0.01,19.99);  //200000000
  //TH1D *hB = new TH1D("hB","Number of Participants Distribution;B;Events",20000,-0.01,19.99);  //200000000
  nt_Xe2arw_Xe2arw->Project("hB","B");

  const int nBin = 200;
  Double_t fRunningCounts=0.;
  Int_t iBin[nBin];
  Double_t bValues[nBin+1];
  bValues[0] = 0.0;
  bValues[200] = 20.0;
  for(int i=0; i< nBin; i++){
    iBin[i] = 0;
  }

cout << fixed << setprecision(10);


  for (Int_t i=1; i<=hB->GetNbinsX(); i++) {
    fRunningCounts=fRunningCounts+hB->GetBinContent(i);
    //    cout<<i<<": "<<fRunningCounts<<endl;
    for(int j=1; j<nBin; j++){
      if(fRunningCounts>=(j*1.0/nBin*hB->GetEntries())&&iBin[j]==0) {
        iBin[j]=i;
        cout<<" j = "<<j<<", Found bin boundary="<<iBin[j]<<", B value = "<<hB->GetBinCenter(iBin[j])<<endl;
        bValues[j] = hB->GetBinCenter(iBin[j]);
      }      
    }

  }

  TH1D *hNpartCent = new TH1D("hNpartCent","",200,0.0,200.0);
  TH1D *hNcollCent = new TH1D("hNcollCent","",200,0.0,200.0);
  TH1D *hTAACent = new TH1D("hTAACent","",200,0.0,200.0);
  TH1D *hEcc2Cent = new TH1D("hEcc2Cent","",200,0.0,200.0);
  TH1D *hEcc3Cent = new TH1D("hEcc3Cent","",200,0.0,200.0);

  TH1D *hNpart = new TH1D("hNpart","Number of Participants Distribution;Npart;Events",300,-0.5,299.5);
  TH1D *hNcoll = new TH1D("hNcoll","Number of Participants Distribution;Ncoll;Events",1500,-0.5,1499.5);
  TH1D *hEcc2 = new TH1D("hEcc2","Ecc Distribution;Ecc;Events",1100,-0.05,1.05);
  TH1D *hEcc3 = new TH1D("hEcc3","Ecc Distribution;Ecc;Events",1100,-0.05,1.05);
  for(int i=0; i<nBin; i++){
    nt_Xe2arw_Xe2arw->Draw("Npart>>+hNpart",Form("B>=%f && B < %f", bValues[i], bValues[i+1]));
    cout<<"i = "<<i<<", <npart>= "<<hNpart->GetMean()<<endl;
    hNpartCent->SetBinContent(i+1, hNpart->GetMean());
    hNpart->Reset("ICESM");

    nt_Xe2arw_Xe2arw->Draw("Ncoll>>+hNcoll",Form("B>=%f && B < %f", bValues[i], bValues[i+1]));
    hNcollCent->SetBinContent(i+1, hNcoll->GetMean());
    hTAACent->SetBinContent(i+1, hNcoll->GetMean()/68.4);
    hNcoll->Reset("ICESM");

    nt_Xe2arw_Xe2arw->Draw("Ecc2>>+hEcc2",Form("B>=%f && B < %f", bValues[i], bValues[i+1]));
    hEcc2Cent->SetBinContent(i+1, hEcc2->GetMean());
    hEcc2->Reset("ICESM");

    nt_Xe2arw_Xe2arw->Draw("Ecc3>>+hEcc3",Form("B>=%f && B < %f", bValues[i], bValues[i+1]));
    hEcc3Cent->SetBinContent(i+1, hEcc3->GetMean());
    hEcc3->Reset("ICESM");

  }

  TFile *ofile = new TFile("default_f.root","recreate");
  ofile->cd();
  hNpartCent->Write();
  hNcollCent->Write();
  hTAACent->Write();
  hEcc2Cent->Write();
  hEcc3Cent->Write();
  ofile->Write();

}


