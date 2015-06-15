void errAna(){

const int Ncent = 9;
double npart[Ncent], taa[Ncent];
double npartErr[Ncent], taaErr[Ncent];
double taaRatio[Ncent], taaRatioErr[Ncent];
ifstream insys;
insys.open("atlasSys.txt");
for(int i=0; i< Ncent; i++){
insys>>npart[i];
insys>>npartErr[i];
insys>>taa[i];
insys>>taaErr[i];
insys>>taaRatio[i];
insys>>taaRatioErr[i];
}

for(int i=0; i< Ncent; i++){
cout<<"npartErr: "<<npartErr[i]/npart[i]*100.<<"%, taaErr: "<<taaErr[i]/taa[i]*100.<<"%, taaRatio: "<<taaRatioErr[i]/taaRatio[i]*100.<<"%"<<endl;
}
//cout<<taaErr[8]<<endl;
//cout<<taaErr[0]/taa[0]<<endl;
cout<<"--------------------------------------"<<endl;
for(int i=0; i< Ncent-1; i++){
cout<<"calErr: "<<sqrt(taaErr[i]/taa[i]*taaErr[i]/taa[i]+taaErr[8]/taa[8]*taaErr[8]/taa[8])*100.<<"%, taaErr: "<<taaErr[i]/taa[i]*100.<<"%, taaRatio: "<<taaRatioErr[i]/taaRatio[i]*100.<<"%"<<endl;
}


}

