// for sys. of normal <Npart> see: /Users/tuos/Analysis/CMS/cmsswReleases/CMSSW_5_3_8_HI_patch2/src/pbpb/v10findFinalAuto/calculateGlauber.C
// Shengquan Tuo, 07/01/16
void sysNpartWithNcollWeight(){

const int nBin = 4;
double lowV[nBin]={358.8,226.7,131.4,42.22};
double lowVs[nBin]={0.54,1.6,2.7,6.7};

double highV[nBin]={384.3,264.2,109.2,46.81};
double highVs[nBin]={0.31,1.3,3.3,7.0};

double objV[nBin]={363.4,239.9,118.8,45.37};
double objVs[nBin];

for(int i=0; i<nBin; i++){
objVs[i]=(highVs[i]-lowVs[i])/(highV[i]-lowV[i])*objV[i] +(highV[i]*lowVs[i]-lowV[i]*highVs[i])/(highV[i]-lowV[i]);
cout<<objV[i]<<"   "<<objVs[i]<<"   "<<objV[i]*objVs[i]*0.01<<endl;
}



}


