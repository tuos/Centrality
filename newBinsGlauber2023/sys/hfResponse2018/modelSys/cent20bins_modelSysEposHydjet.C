#include <iomanip>
double max(double a, double b){
if (a>=b) 
  return a;
else 
  return b;
}

void cent20bins_modelSysEposHydjet(){

const int nRange = 20;
int centL[nRange] = {0, 5,  10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95};
int centH[nRange] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};

TH1D *hNpartValues[10];

//TFile* inFile1 = new TFile("../../eposSim/default_glauber_smeared.root");
TFile* inFile1 = new TFile("../default_glauber_smeared_2018hf.root");
TFile* inFile2 = new TFile("../default_glauber_smeared_2018hf_hydjet.root");
//TFile* inFile1 = new TFile("../default_glauber_smeared_2018hf_98eff.root");

hNpartValues[0] = (TH1D*)inFile1->Get("hNpartCent");
hNpartValues[1] = (TH1D*)inFile2->Get("hNpartCent");
hNpartValues[2] = (TH1D*)inFile1->Get("hNcollCent");
hNpartValues[3] = (TH1D*)inFile2->Get("hNcollCent");
hNpartValues[4] = (TH1D*)inFile1->Get("hTAACent");
hNpartValues[5] = (TH1D*)inFile2->Get("hTAACent");

ofstream outFileTxt;
outFileTxt.open("./output_cent_err_model_20bins.txt");

//cout << fixed << setprecision(2);
double npartSmeared[nRange]; double npartSmearedHydjet[nRange];
double ncollSmeared[nRange]; double ncollSmearedHydjet[nRange];
double taaSmeared[nRange]; double taaSmearedHydjet[nRange];


for(int i=0; i<nRange; i++){
    npartSmeared[i]=0; npartSmearedHydjet[i]=0;
    ncollSmeared[i]=0; ncollSmearedHydjet[i]=0;
    taaSmeared[i]=0; taaSmearedHydjet[i]=0;
  for(int j=2*centL[i]; j<2*centH[i]; j++){
    npartSmeared[i]+=hNpartValues[0]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    npartSmearedHydjet[i]+=hNpartValues[1]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    ncollSmeared[i]+=hNpartValues[2]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    ncollSmearedHydjet[i]+=hNpartValues[3]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    taaSmeared[i]+=hNpartValues[4]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);
    taaSmearedHydjet[i]+=hNpartValues[5]->GetBinContent(j+1)*1.0/(2*centH[i] - 2*centL[i]);

  }

  cout<<i<<"   "<<fabs(npartSmeared[i] - npartSmearedHydjet[i])/npartSmearedHydjet[i]<<"   "<<fabs(ncollSmeared[i] - ncollSmearedHydjet[i])/ncollSmearedHydjet[i]<<"   "<<fabs(taaSmeared[i] - taaSmearedHydjet[i])/taaSmearedHydjet[i]<<endl;
  //outFileTxt<<i<<"   "<<fabs(npartSmeared[i] - npartSmearedHydjet[i])/npartSmearedHydjet[i]<<"   "<<fabs(ncollSmeared[i] - ncollSmearedHydjet[i])/ncollSmearedHydjet[i]<<"   "<<fabs(taaSmeared[i] - taaSmearedHydjet[i])/taaSmearedHydjet[i]<<endl;
  // the same for TAA and Ncoll, don't need it
  outFileTxt<<i<<"   "<<fabs(npartSmeared[i] - npartSmearedHydjet[i])*100.0/npartSmearedHydjet[i]<<"   "<<fabs(ncollSmeared[i] - ncollSmearedHydjet[i])*100.0/ncollSmearedHydjet[i]<<endl;

}





}


