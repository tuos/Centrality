void weightedNpart(){

const char * infilename;
infilename = Form("tables_Glauber2016A_ForHydjet5020Responsenbins200x_d20160609_SmearingEff.root");

 TChain * t = new TChain("Glauber_Default_Para/nt");
 t->Add(infilename);
 float hf, b, Npart, Ncoll;
 Float_t Bin;

 
 t->SetBranchAddress("HFbyNpart",&hf);
 t->SetBranchAddress("Bin",&Bin);
 t->SetBranchAddress("b",&b);
 t->SetBranchAddress("Npart",&Npart);
 t->SetBranchAddress("Ncoll",&Ncoll);

 TH2D *NcollNpart1030 = new TH2D("NcollNpart1030","NcollNpart1030",450,0,450, 2500,0,2500);
 const int nBin=6;
 double sumN[nBin], sumNpart[nBin];
 double sumNcoll[nBin], sumNcollNpart[nBin];
 double aveNpart[nBin], weightedNpart[nBin];
 for(int i=0; i<nBin; i++){
   sumN[i]=0; sumNpart[i]=0;
   sumNcoll[i]=0; sumNcollNpart[i]=0;
   aveNpart[i]=0; weightedNpart[i]=0;
 }

 unsigned int Nevents = t->GetEntries();
 for(unsigned int iev = 0; iev < Nevents; iev++) {
   if(iev%50000 == 0) cout<<"Processing event: " << iev << endl;
   t->GetEntry(iev);

   if(Bin>=20 && Bin<60)
     NcollNpart1030->Fill(Npart, Ncoll);

   if(Bin>=0&&Bin<20){
     sumN[0]+= 1; sumNpart[0]+= Npart;
     sumNcoll[0]+= Ncoll; sumNcollNpart[0]+= Ncoll*Npart;
   }
   if(Bin>=20&&Bin<60){
     sumN[1]+= 1; sumNpart[1]+= Npart;
     sumNcoll[1]+= Ncoll; sumNcollNpart[1]+= Ncoll*Npart;
   }
   if(Bin>=60&&Bin<100){
     sumN[2]+= 1; sumNpart[2]+= Npart;
     sumNcoll[2]+= Ncoll; sumNcollNpart[2]+= Ncoll*Npart;
   }
   if(Bin>=100&&Bin<160){
     sumN[3]+= 1; sumNpart[3]+= Npart;
     sumNcoll[3]+= Ncoll; sumNcollNpart[3]+= Ncoll*Npart;
   }
   if(Bin>=160&&Bin<200){
     sumN[4]+= 1; sumNpart[4]+= Npart;
     sumNcoll[4]+= Ncoll; sumNcollNpart[4]+= Ncoll*Npart;
   }
   if(Bin>=100&&Bin<200){
     sumN[5]+= 1; sumNpart[5]+= Npart;
     sumNcoll[5]+= Ncoll; sumNcollNpart[5]+= Ncoll*Npart;
   }
 }
 for(int i=0; i<nBin; i++){
  aveNpart[i]=sumNpart[i]/sumN[i];
  weightedNpart[i]=sumNcollNpart[i]/sumNcoll[i];
  cout<<aveNpart[i]<<"   "<<weightedNpart[i]<<endl;
 }

  TCanvas* cd = new TCanvas("cd","",500,500);
  cd->SetLeftMargin(0.12);
  cd->SetRightMargin(0.12);
  cd->SetTopMargin(0.02);
  cd->SetBottomMargin(0.12);
  cd->SetTicks(1);
  //cd->SetLogy();
  gStyle->SetOptStat(0);
  NcollNpart1030->SetTitle("");
  NcollNpart1030->SetXTitle("N_{part}");
  NcollNpart1030->SetYTitle("N_{coll}");
  NcollNpart1030->GetYaxis()->SetTitleOffset(1.2);
  NcollNpart1030->GetXaxis()->SetTitleOffset(1.2);
  NcollNpart1030->GetXaxis()->CenterTitle(1);
  NcollNpart1030->GetYaxis()->CenterTitle(1);
  NcollNpart1030->GetXaxis()->SetTitleSize(0.046);
  NcollNpart1030->GetYaxis()->SetTitleSize(0.046);
  NcollNpart1030->GetXaxis()->SetTitleFont(62);
  NcollNpart1030->GetYaxis()->SetTitleFont(62);
  NcollNpart1030->SetAxisRange(0,2500,"Y");
  NcollNpart1030->SetAxisRange(0,450,"X");
  NcollNpart1030->Draw("colz");

    TLatex *tex1= new TLatex(30,2200,"CMS Glauber MC, PbPb 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex1= new TLatex(30,2000,"Centrality: 10-30%");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();

  cd->SaveAs("NcollVsNpartCent1030.png");  
  cd->SaveAs("NcollVsNpartCent1030.pdf");  
}

