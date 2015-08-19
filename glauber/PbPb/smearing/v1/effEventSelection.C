//#include "TH1D.h"
#include "hfHistPbPb5TeVMC.h"
void effEventSelection(){

   TFile * outfile = new TFile("out/histEff.root","recreate");
   TDirectory *dir = outfile->mkdir("effSys");
   
   TH1D *effHist[3];
   effHist[0] = new TH1D("effhist_0","effhist_0",60000,0,6000);
   effHist[1] = new TH1D("effhist_1","effhist_1",60000,0,6000);
   effHist[2] = new TH1D("effhist_2","effhist_2",60000,0,6000);
   TH1D *tmp = new TH1D("tmp","tmp",60000,0,6000);
   TH1D *tmp2 = new TH1D("tmp2","tmp2",60000,0,6000);
   for(int i = 1; i <= 60000; i++){
     effHist[0]->SetBinContent(i, 1);
     effHist[1]->SetBinContent(i, 1);
     effHist[2]->SetBinContent(i, 1);
   }

if(1){
   // for 99% eff   
   TF1 *expfun99 = new TF1("expfun99", "1-exp(-0.335*x*x-0.1)", 0, 100);
   for(int i = 1; i <= 50; i++){
     effHist[0]->SetBinContent(i, expfun99->Eval(effHist[0]->GetBinCenter(i)));
   }   
   tmp->Multiply(hfHistPbPb5TeVMC(),effHist[0]);
   cout<<"eff in percent = "<<tmp->Integral(1, 60000)/hfHistPbPb5TeVMC()->Integral(1, 60000)*100.<<"%"<<endl;
}

if(1){
   // for 98% eff   
   TF1 *expfun98 = new TF1("expfun98", "1-exp(-0.079*x*x-0.1)", 0, 100);
   for(int i = 1; i <= 100; i++){
     effHist[1]->SetBinContent(i, expfun98->Eval(effHist[1]->GetBinCenter(i)));
   }
   tmp2->Multiply(hfHistPbPb5TeVMC(),effHist[1]);
   cout<<"eff in percent = "<<tmp2->Integral(1, 60000)/hfHistPbPb5TeVMC()->Integral(1, 60000)*100.<<"%"<<endl;
}

  // effHist[2] is for 100% eff.

   outfile->cd();
   dir->cd();
   for(int i=0; i<3; i++) effHist[i]->Write();
   outfile->Write();

}
