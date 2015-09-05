void readTree(){

  TFile *f = new TFile("histogram_testMB_5020GeV.root");
  TTree *t1 = (TTree*)f->Get("demo/evttree");
  Int_t d_RunID;
  Int_t d_LumiID;
  Int_t d_EventID;
  Int_t d_centralityBin;
  Float_t d_ETHF;
  Int_t d_nTrack;

  Int_t tenCentBin;

  t1->SetBranchAddress("RunID",&d_RunID);
  t1->SetBranchAddress("LumiID",&d_LumiID);
  t1->SetBranchAddress("EventID",&d_EventID);
  t1->SetBranchAddress("centralityBin",&d_centralityBin);
  t1->SetBranchAddress("ETHF",&d_ETHF);
  t1->SetBranchAddress("nTrack",&d_nTrack);
  TH1F *hcent   = new TH1F("hcent","centrality distribution",10,0,10);
  Int_t realRunID[1000];  
  Int_t realLumiID[1000];  
  Int_t realEventID[1000];  
  Int_t realCentID[1000];  

  Int_t nentries = (Int_t)t1->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
    t1->GetEntry(i);
    for (Int_t j=0; j<10; j++){
      if(d_centralityBin>=j*20 && d_centralityBin<(j+1)*20) tenCentBin = j;
    }
    hcent->Fill(tenCentBin);
    //cout<<d_RunID<<"   "<<d_LumiID<<"   "<<d_EventID<<"   "<<tenCentBin<<endl;
    realRunID[i] = d_RunID;
    realLumiID[i] = d_LumiID;
    realEventID[i] = d_EventID;
    realCentID[i] = tenCentBin;
  }
  cout<<"Int_t realRunID[1000] = {";
  for(Int_t i=0; i<999; i++){
    cout<<realRunID[i]<<", ";
  }
  cout<<realRunID[999]<<"};"<<endl;

  cout<<"Int_t realLumiID[1000] = {";
  for(Int_t i=0; i<999; i++){
    cout<<realLumiID[i]<<", ";
  }
  cout<<realLumiID[999]<<"};"<<endl;

  cout<<"Int_t realEventID[1000] = {";
  for(Int_t i=0; i<999; i++){
    cout<<realEventID[i]<<", ";
  }
  cout<<realEventID[999]<<"};"<<endl;

  cout<<"Int_t realCentID[1000] = {";
  for(Int_t i=0; i<999; i++){
    cout<<realCentID[i]<<", ";
  }
  cout<<realCentID[999]<<"};"<<endl;

  hcent->SetMinimum(0);
  //hcent->Draw();

}

