#include <iostream>
#include <iomanip>
using namespace std;
#include "findNcoll.C"
#include "findNpart.C"
#include "findNcollAverage.C"
#include "findNpartAverage.C"
void calculateGlauber(){

  ///HIN-15-015
  //const int nBin=8;
  //double minCent[nBin]={0,10,20,60,100,140, 0,0};
  //double maxCent[nBin]={10,20,60,100,140,180,20,200};
  ///Photon RAA 
  const int nBin=2;
  double minCent[nBin]={0,60};
  double maxCent[nBin]={60,200};
  ///HIN-16-004
  //const int nBin=9;
  //double minCent[nBin]={0,20,40,60,80,100, 0,40,80};
  //double maxCent[nBin]={20,40,60,80,100,200, 40,80,200};

  //sys
  TF1 *fitSysNcoll = new TF1("fitSysNcoll","(1.06951e+00)+(3.91594e-05)*x+(-2.27580e-05)*x*x+(7.23536e-07)*x*x*x+(-3.31637e-09)*x*x*x*x",0,100);
  TF1 *fitSysNpart = new TF1("fitSysNpart","(1.00038e+00)+(1.18222e-03)*x+(-3.23105e-05)*x*x+(6.75076e-07)*x*x*x+(-2.71516e-09)*x*x*x*x",0,100);
  TF1 *fitSysTAA = new TF1("fitSysTAA","(1.01659e+00)+(-6.15535e-05)*x+(1.60963e-05)*x*x+(1.77809e-07)*x*x*x+(-1.11480e-09)*x*x*x*x",0,100);

  for(int i=0; i<nBin; i++){ 
    double ncoll=findNcollAverage(minCent[i], maxCent[i]);
    double taa=ncoll/70;
    double npart=findNpartAverage(minCent[i], maxCent[i]);
    double ncollerrp=(fitSysNcoll->Integral(minCent[i]*1.0/2, maxCent[i]*1.0/2)/(maxCent[i]*1.0/2-minCent[i]*1.0/2)-1)*100;
    double taaerrp=(fitSysTAA->Integral(minCent[i]*1.0/2, maxCent[i]*1.0/2)/(maxCent[i]*1.0/2-minCent[i]*1.0/2)-1)*100;
    double nparterrp=(fitSysNpart->Integral(minCent[i]*1.0/2, maxCent[i]*1.0/2)/(maxCent[i]*1.0/2-minCent[i]*1.0/2)-1)*100;
    double ncollerr=ncollerrp*0.01*ncoll;
    double taaerr=taaerrp*0.01*taa;
    double nparterr=nparterrp*0.01*npart;
//    cout<<setprecision(3)<<minCent[i]*1.0/2<<" - "<<maxCent[i]*1.0/2<<"%      "<<setprecision(4)<<ncoll<<"  "<<setprecision(3)<<ncollerr<<"  "<<setprecision(2)<<ncollerrp<<"%      "<<setprecision(4)<<taa<<"  "<<setprecision(3)<<taaerr<<"  "<<setprecision(2)<<taaerrp<<"%      "<<setprecision(4)<<npart<<"  "<<setprecision(3)<<nparterr<<"  "<<setprecision(2)<<nparterrp<<"%."<<endl;
    cout<<setprecision(3)<<minCent[i]*1.0/2<<" - "<<maxCent[i]*1.0/2<<"\\%   &   "<<setprecision(4)<<ncoll<<"$\\pm$"<<setprecision(3)<<ncollerr<<"("<<setprecision(2)<<ncollerrp<<"\\%)   &   "<<setprecision(4)<<taa<<"$\\pm$"<<setprecision(3)<<taaerr<<"("<<setprecision(2)<<taaerrp<<"\\%)   &   "<<setprecision(4)<<npart<<"$\\pm$"<<setprecision(3)<<nparterr<<"("<<setprecision(2)<<nparterrp<<"\\%)   \\\\   "<<endl;
    cout<<"\\hline"<<endl;

  }


}


