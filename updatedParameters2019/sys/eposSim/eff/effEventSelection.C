//#include "TH1D.h"
#include "hfHistPbPb5TeVGlauber.h"
void effEventSelection(){

   TFile * outfile = new TFile("out/histEff.root","recreate");
   TDirectory *dir = outfile->mkdir("effSys");
   
   TH1D *effHist[4];
   effHist[0] = new TH1D("effhist_0","effhist_0",60000,0,6000);
   effHist[1] = new TH1D("effhist_1","effhist_1",60000,0,6000);
   effHist[2] = new TH1D("effhist_2","effhist_2",60000,0,6000);
   effHist[3] = new TH1D("effhist_3","effhist_3",60000,0,6000);
   TH1D *tmp = new TH1D("tmp","tmp",60000,0,6000);
   TH1D *tmp2 = new TH1D("tmp2","tmp2",60000,0,6000);
   TH1D *tmp3 = new TH1D("tmp3","tmp3",60000,0,6000);
   for(int i = 1; i <= 60000; i++){
     effHist[0]->SetBinContent(i, 1);
     effHist[1]->SetBinContent(i, 1);
     effHist[2]->SetBinContent(i, 1);
     effHist[3]->SetBinContent(i, 1);
   }

   TH1D *hfhist;
   hfhist = (TH1D*)hfHistPbPb5TeVGlauber();

if(1){
   // for 99% eff   
   TF1 *expfun99 = new TF1("expfun99", "1-exp(-0.06261*x*x-0.1)", 0, 100);
   for(int i = 1; i <= 50; i++){
     effHist[1]->SetBinContent(i, expfun99->Eval(effHist[1]->GetBinCenter(i)));
   }   
   tmp->Multiply(hfhist,effHist[1]);
   cout<<"eff in percent = "<<tmp->Integral(1, 60000)/hfhist->Integral(1, 60000)*100.<<"%"<<endl;
}

if(1){
   // for 97% eff   
   TF1 *expfun97 = new TF1("expfun97", "1-exp(-0.014208*x*x-0.1)", 0, 100);
   for(int i = 1; i <= 100; i++){
     effHist[2]->SetBinContent(i, expfun97->Eval(effHist[2]->GetBinCenter(i)));
   }
   tmp2->Multiply(hfhist,effHist[2]);
   cout<<"eff in percent = "<<tmp2->Integral(1, 60000)/hfhist->Integral(1, 60000)*100.<<"%"<<endl;
}

if(1){
   // for 101% eff   
   TF1 *expfun101 = new TF1("expfun101", "1+exp(-0.0727*x*x-0.1)", 0, 100);
   for(int i = 1; i <= 100; i++){
     effHist[3]->SetBinContent(i, expfun101->Eval(effHist[3]->GetBinCenter(i)));
   }
   tmp3->Multiply(hfhist,effHist[3]);
   cout<<"eff in percent = "<<tmp3->Integral(1, 60000)/hfhist->Integral(1, 60000)*100.<<"%"<<endl;
}

  // effHist[0] is for 100% eff.

   outfile->cd();
   dir->cd();
   for(int i=0; i<4; i++) effHist[i]->Write();
   outfile->Write();

}
