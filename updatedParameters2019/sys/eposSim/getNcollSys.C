#include <iomanip>
double max(double a, double b){
if (a>=b) 
  return a;
else 
  return b;
}

void getNcollSys(){

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

TH1D *hNpartValues[10];

TFile* inFile0 = new TFile("../default/default_f.root");
hNpartValues[0] = (TH1D*)inFile0->Get("hNcollCent");

TFile* inFile1 = new TFile("../dnodemax/dnodemax_f.root");
hNpartValues[1] = (TH1D*)inFile1->Get("hNcollCent");
TFile* inFile2 = new TFile("../dnodemin/dnodemin_f.root");
hNpartValues[2] = (TH1D*)inFile2->Get("hNcollCent");
TFile* inFile3 = new TFile("../sNNmax/sNNmax_f.root");
hNpartValues[3] = (TH1D*)inFile3->Get("hNcollCent");
TFile* inFile4 = new TFile("../sNNmin/sNNmin_f.root");
hNpartValues[4] = (TH1D*)inFile4->Get("hNcollCent");

TFile* inFile7 = new TFile("./default_glauber_smeared.root");
hNpartValues[7] = (TH1D*)inFile7->Get("hNcollCent");

ifstream inFileTxt;
inFileTxt.open("../density/output_cent_err.txt");
double tmp, errNpart, errNcoll;

//hNpartValues[0]->Draw();
for(int i=1; i<7; i++){
//hNpartValues[i]->Divide(hNpartValues[0]);
}
//hNpartValues[0]->Divide(hNpartValues[0]);

cout << fixed << setprecision(2);
double npart[nRange]; double sys[8][nRange];
double npartSmeared[nRange];
for(int i=0; i<nRange; i++){
    npart[i]=0;
    npartSmeared[i]=0;
    for(int k=0; k<8; k++){
      sys[k][i]=0;
    }
  for(int j=2*centL[i]; j<2*centH[i]; j++){
    npartSmeared[i]+=hNpartValues[7]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    npart[i]+=hNpartValues[0]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    sys[0][i]+=hNpartValues[1]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    sys[1][i]+=hNpartValues[2]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    sys[2][i]+=hNpartValues[3]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    sys[3][i]+=hNpartValues[4]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);

  }
    inFileTxt>>tmp;
    inFileTxt>>errNpart;
    inFileTxt>>errNcoll;
    sys[4][i]=errNcoll*npart[i]; // hNcollCent 

  double sysTotal = sqrt((sys[0][i]-sys[1][i])*(sys[0][i]-sys[1][i])*1.0/4 + (sys[2][i]-sys[3][i])*(sys[2][i]-sys[3][i])*1.0/4 + (sys[4][i]*0.01)*(sys[4][i]*0.01) );
  //double sysTotal = sqrt(max(sys[0][i]-npart[i], sys[1][i]-npart[i])*max(sys[0][i]-npart[i], sys[1][i]-npart[i]) + max(sys[2][i]-npart[i], sys[3][i]-npart[i])*max(sys[2][i]-npart[i], sys[3][i]-npart[i]) + (sys[4][i]*0.01)*(sys[4][i]*0.01) );
  //double sysTotal = sqrt(max(sys[0][i]-npart[i], sys[1][i]-npart[i])*max(sys[0][i]-npart[i], sys[1][i]-npart[i]) + max(sys[2][i]-npart[i], sys[3][i]-npart[i])*max(sys[2][i]-npart[i], sys[3][i]-npart[i]) + 0.0 );

//cout<<centL[i]<<"  "<<centH[i]<<"  "<<npart[i]<<"  "<<sysTotal<<"  "<<sysTotal*1.0/npart[i]<<endl;
printf("| %d-%d%%|  %.4g |  %.3g | %.2g | \n",centL[i],centH[i],npartSmeared[i],sysTotal,sysTotal*100.0/npartSmeared[i]);
//printf("%d %d  %.4g   %.3g  %.2g  \n",centL[i],centH[i],npartSmeared[i],sysTotal,sysTotal*100.0/npart[i]);
///printf("| %d-%d%%|  %.4g |  %.4g |  %.3g | %.2g | \n",centL[i],centH[i],npart[i],npartSmeared[i],sysTotal,sysTotal*100.0/npartSmeared[i]);

}

  cout<<endl<<"sys of each source: "<<endl<<endl;
  ifstream inFileErr200;
  inFileErr200.open("../density/output_err.txt");
  for(int j=0; j<200; j++){
    inFileErr200>>tmp;
    inFileErr200>>errNpart;
    inFileErr200>>errNcoll;
    cout<<j<<"   "<<fabs(hNpartValues[1]->GetBinContent(j+1)-hNpartValues[2]->GetBinContent(j+1))*100.0/2/hNpartValues[7]->GetBinContent(j+1)<<"   "<<fabs(hNpartValues[3]->GetBinContent(j+1)-hNpartValues[4]->GetBinContent(j+1))*100.0/2/hNpartValues[7]->GetBinContent(j+1)<<"   "<<hNpartValues[0]->GetBinContent(j+1)*1.0/hNpartValues[7]->GetBinContent(j+1)*errNcoll<<endl; // hNcollCent
  }

  for(int j=0; j<200; j++){
    //cout<<j<<"   "<<fabs(hNpartValues[1]->GetBinContent(j+1)-hNpartValues[2]->GetBinContent(j+1))*1.0/67.6<<"   "<<hNpartValues[7]->GetBinContent(j+1)*1.0/67.6<<endl;
  }

  for(int i=1; i<21; i++){
    double sysTotal = sqrt((sys[0][i]-sys[1][i])*(sys[0][i]-sys[1][i])*1.0/4 + (sys[2][i]-sys[3][i])*(sys[2][i]-sys[3][i])*1.0/4 + (sys[4][i]*0.01)*(sys[4][i]*0.01) );
    cout<<i<<"   "<<fabs(sys[0][i]-sys[1][i])*100.0/2/npartSmeared[i]<<"   "<<fabs(sys[2][i]-sys[3][i])*100.0/2/npartSmeared[i]<<"   "<<(sys[4][i]*1.0)/npartSmeared[i]<<"   "<<sysTotal*100.0/npartSmeared[i]<<endl;

  }


}


