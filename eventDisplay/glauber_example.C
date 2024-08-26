#include "TRandom.h"
#include "TF1.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TLatex.h"

double nMarSiz = 2.4;

double rHard = 0.5;
TRandom * ran;
TF1 * ranR;
TF1 * ranTheta;
void wsFunc(int A, double *x, double *y, double *z);
void collide(int A, double sign, double*x1, double*y1, double*z1, double*x2, double*y2, double*z2, double*x, double*y, double*z, int&npart);
double PsiN(double order, int np, double *x, double*y);
double eccentricity(double order, double psi, int npart, double *x, double*y);
void recenter(int npart, double*x, double*y, double*z);
TH1D * hws;
TH1D * hpsi[7];
TGraph * g[7];
TGraph * g_4_2;
TGraph * g_6_2;
TGraph * g_6_3;
TGraph * g_3_2;

int colors[7]={kBlack,kCyan,kBlack,kRed, kBlue,kGreen, kMagenta};
static const int Numb = 29;
double b[29] = {0., 0.5, 1.0, 1.5, 1.8, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.1,  6.5, 7.11, 7.5, 8.0,
		8.5,9.0, 9.5, 10.0, 10.5, 11., 11.5, 12.0, 12.5, 12.83, 13.5, 14.0};
double avNpart[29];
double ecc[7][29];
double eccCnt[7][29];
double ecc_4_2[Numb];
double ecc_6_2[Numb];
double ecc_6_3[Numb];
double ecc_3_2[Numb];
double ecc_4_2_cnt[Numb];
double ecc_6_2_cnt[Numb];
double ecc_6_3_cnt[Numb];
double ecc_3_2_cnt[Numb];
Double_t bounds2(Double_t order, Double_t ang) {
  double range = TMath::Pi()/order;
  if(ang<-range) ang+=2.*range;  
  if(ang>range)  ang-=2.*range;
  return ang;
}


void glauber_example() {

  //gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  gStyle->SetTextFont(43);
  gStyle->SetLabelFont(43,"x");
  gStyle->SetLabelFont(43,"y");
  gStyle->SetLabelFont(43,"z");
  gStyle->SetTitleFont(43,"x");
  gStyle->SetTitleFont(43,"y");
  gStyle->SetTitleFont(43,"z");
  gStyle->SetEndErrorSize(0);

  double tsiz = 28;
  gStyle->SetLabelSize(28,"x");
  gStyle->SetLabelSize(28,"y");
  gStyle->SetTitleSize(28,"x");
  gStyle->SetTitleSize(28,"y");
  gStyle->SetTextSize(28);

  gStyle->SetPadTopMargin(0.02);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);

  double rxnAngle = 0. * 3.1415926 / 180.;

  cout << rxnAngle << "  " << cos(rxnAngle) << "  " << sin(rxnAngle) << endl;

  double R = 6.62;
  double a = 0.546;
  int A = 208;
  double sign = 68.0; // NN cross section for 5.36 TeV; https://arxiv.org/pdf/1710.07098v2
  //int drawb = 26;  //4 for npart400, 14 for 210, 25
  int drawb = 27;  //1 for npart=407, 15 for npart=196, 27 for npart=12
  cout<<"R: "<<R<<endl;
  cout<<"R: "<<R<<endl;
  cout<<"a: "<<a<<endl;
  TString wsDef = "4*3.1415926*x*x/(1+exp( (x - [0])/[1]))";
  ranR=new TF1("ranR",wsDef.Data(),0,2*R);
  ranR->FixParameter(0,R);
  ranR->FixParameter(1,a);
  ranTheta = new TF1("ranTheta","sin(x)",0,TMath::Pi());
  for(int i = 1; i<=6; i++) {
    hpsi[i] = new TH1D(Form("psi%d",i),Form("psi%d",i),400,-4,4);
    hpsi[i]->SetLineColor(colors[i]);
  }
  TH2D * hDum = new TH2D("Dum","Overlap",800,-2.5*R,2.5*R,800,-2.5*R,2.5*R);
  TH2D * hOverlap = new TH2D("Overlap","Overlap",800,-2.5*R,2.5*R,800,-2.5*R,2.5*R);
  TH2D * hA1 = new TH2D("A1","A1",800,-2.5*R,2.5*R,800,-2.5*R,2.5*R);
  TH2D * hA2 = new TH2D("A2","A2",800,-2.5*R,2.5*R,800,-2.5*R,2.5*R);
  TH3D * hA1_3D = new TH3D("A1_3D","A1_3D",100,-3*R,3*R,100,-3*R,3*R,100,-3*R,3*R);
  TH3D * hA2_3D = new TH3D("A2_3D","A2_3D",100,-3*R,3*R,100,-3*R,3*R,100,-3*R,3*R);
  TH3D * hCollision_3D = new TH3D("Collision_3D","Collision_3D",100,-3*R,3*R,100,-3*R,3*R,100,-3*R,3*R);
  TH1D * hWS1 = new TH1D("hWS1","hWS1",400,0,3*R);
  TH1D * hWS2 = new TH1D("hWS2","hWS2",400,0,3*R);
  hA1_3D->SetMarkerColor(kBlue);
  hA2_3D->SetMarkerColor(kRed);
  hCollision_3D->SetMarkerColor(kGreen);
  ran = new TRandom(10000);
  double x1[300],y1[300],z1[300];
  double x2[300],y2[300],z2[300];
  double x[600],y[600],z[600];
  int nEvent = 1;
  double psidraw = 0;
  double drawnpart = 0;
  for(int ib = 0; ib<Numb; ib++)  avNpart[ib] = 0;
  for(int i = 0; i<Numb; i++) {
    ecc_4_2[i]=0;
    ecc_6_2[i]=0;
    ecc_6_3[i]=0;
    ecc_3_2[i]=0;
    ecc_4_2_cnt[i]=0;
    ecc_6_2_cnt[i]=0;
    ecc_6_3_cnt[i]=0;
    ecc_3_2_cnt[i]=0;
    for(int j = 0; j<=6; j++) {
      ecc[j][i] = 0;
      eccCnt[j][i]=0;
   }
  }
  
  for(int n = 0; n<nEvent; n++) {
    wsFunc(A,x1,y1,z1);
    wsFunc(A,x2,y2,z2);
    for(int i = 0; i<A; i++) {
      double r1 = TMath::Sqrt(x1[i]*x1[i]+y1[i]*y1[i]+z1[i]*z1[i]);
      double r2 = TMath::Sqrt(x2[i]*x2[i]+y2[i]*y2[i]+z2[i]*z2[i]);
      hWS1->Fill(r1);
      hWS2->Fill(r2);
    }
    for(int ib = 0; ib<=drawb; ib++) {
      double xb = b[ib];
      double xb1[300];
      double xb2[300];
      for(int i=0; i<A; i++) {
	xb1[i]=x1[i]-xb/2.;
	xb2[i]=x2[i]+xb/2.;
      }
      int npart=0;
      collide(A, sign,xb1,y1,z1,xb2,y2,z2,x,y,z,npart);
      if( ib == drawb ) // rotate coordinates
      {
        drawnpart = npart;
        for(int i = 0; i<300; i++)
        {
          double xrot = xb1[i]*cos(rxnAngle) - y1[i]*sin(rxnAngle);
          double yrot = xb1[i]*sin(rxnAngle) + y1[i]*cos(rxnAngle);

          xb1[i] = xrot;
          y1[i] = yrot;
          xrot = xb2[i]*cos(rxnAngle) - y2[i]*sin(rxnAngle);
          yrot = xb2[i]*sin(rxnAngle) + y2[i]*cos(rxnAngle);
          xb2[i] = xrot;
          y2[i] = yrot;
        }
        for( int i = 0; i< 600; i++)
        {
          double xrot = x[i]*cos(rxnAngle) - y[i]*sin(rxnAngle);
          double yrot = x[i]*sin(rxnAngle) + y[i]*cos(rxnAngle);
          x[i] = xrot;
          y[i] = yrot;
        }
      }
      if(n==0 && ib==drawb) {
	for(int i=0;i<A; i++) {
	  hA1->Fill(xb1[i],y1[i]);
	  hA2->Fill(xb2[i],y2[i]);
	  hA1_3D->Fill(xb1[i],y1[i],z1[i]);
	  hA2_3D->Fill(xb2[i],y2[i],z2[i]);
	}
	for(int j = 0; j<npart; j++) {
	  hOverlap->Fill(x[j],y[j]);
	  hCollision_3D->Fill(x[j],y[j],z[j]);
	}
      }
      avNpart[ib]+=npart;
      recenter(npart,x,y,z);
      for(int iorder = 1; iorder<=6; iorder++) {
	double order = (double) iorder;
	double psi = PsiN(order,npart,x,y);
        if ( ib == drawb ) cout << "Order: " << iorder << " Psi: " << psi << endl;
        if ( iorder == 2 && ib == drawb ) psidraw = psi;
	hpsi[iorder]->Fill(psi);
	if(npart>5) {
	  ecc[iorder][ib] += eccentricity(order,psi,npart,x,y);
	  eccCnt[iorder][ib]+=1;
	}
      }
      if(npart>5) {
	double psi2 = PsiN(2.,npart,x,y);
	double psi3 = PsiN(3.,npart,x,y);
	ecc_4_2[ib]+=eccentricity(4.,psi2,npart,x,y);
	ecc_6_2[ib]+=eccentricity(6.,psi2,npart,x,y);
	ecc_6_3[ib]+=eccentricity(6.,psi3,npart,x,y);
	ecc_3_2[ib]+=eccentricity(3.,psi2,npart,x,y);
	++ecc_4_2_cnt[ib];
	++ecc_6_2_cnt[ib];
	++ecc_6_3_cnt[ib];
	++ecc_3_2_cnt[ib];	
      }
    }
  }
  for(int ib = 0; ib<=drawb; ib++)  {
    avNpart[ib] /= nEvent;
    for(int iorder =1; iorder<=6; iorder++) {
      ecc[iorder][ib]/=eccCnt[iorder][ib];
    }
    ecc_4_2[ib]/=ecc_4_2_cnt[ib];
    ecc_6_2[ib]/=ecc_6_2_cnt[ib];
    ecc_6_3[ib]/=ecc_6_3_cnt[ib];
    ecc_3_2[ib]/=ecc_3_2_cnt[ib];
    
  }
  for(int iorder=1; iorder<=6; iorder++) {
    g[iorder] = new TGraph(Numb,avNpart,ecc[iorder]);
    g[iorder]->SetMarkerStyle(20);
    g[iorder]->SetMarkerColor(colors[iorder]);
  }
  g_4_2 = new TGraph(Numb,avNpart,ecc_4_2);
  g_6_2 = new TGraph(Numb,avNpart,ecc_6_2);
  g_6_3 = new TGraph(Numb,avNpart,ecc_6_3);
  g_3_2 = new TGraph(Numb,avNpart,ecc_3_2);
  g_4_2->SetMarkerStyle(22);
  g_4_2->SetMarkerColor(kBlue);
  g_6_2->SetMarkerStyle(22);
  g_6_2->SetMarkerColor(kGreen);
  g_6_3->SetMarkerStyle(22);
  g_6_3->SetMarkerColor(kRed);
  g_3_2->SetMarkerStyle(22);
  g_3_2->SetMarkerColor(kCyan);


  for(int ib = 0; ib<=drawb; ib++) {

    cout<<"b:\t"<<b[ib]<<"\t <npart>\t"<<avNpart[ib]<<"\t e2,e3: \t"<<ecc[2][ib]<<"\t"<<ecc[3][ib]<<
      "\t"<<ecc[4][ib]<<"\t"<<ecc[5][ib]<<"\t"<<ecc[6][ib]<<endl;
  }
  hpsi[6]->SetXTitle("#Psi_{N}");
  hpsi[6]->SetYTitle("Counts");
  /*
  TCanvas * c1 = new TCanvas("c1","c1",800,650);
  c1->cd();
  hpsi[6]->Draw();
  hpsi[5]->Draw("same");
  hpsi[4]->Draw("same");
  hpsi[3]->Draw("same");
  hpsi[2]->Draw("same");
  hpsi[1]->Draw("same");
  TLegend * legpsi = new TLegend(0.25,0.5,0.35,0.85);
  legpsi->SetFillColor(kWhite);
  legpsi->AddEntry(hpsi[1],"#Psi_{1}","l");
  legpsi->AddEntry(hpsi[2],"#Psi_{2}","l");
  legpsi->AddEntry(hpsi[3],"#Psi_{3}","l");
  legpsi->AddEntry(hpsi[4],"#Psi_{4}","l");
  legpsi->AddEntry(hpsi[5],"#Psi_{5}","l");
  legpsi->AddEntry(hpsi[6],"#Psi_{6}","l");
  legpsi->Draw();
  TLatex * l1 = new TLatex(2.5,0.9*hpsi[6]->GetMaximum(),Form("b = %4.1f fm",b[drawb]));
  l1->Draw();
  c1->Print("glauber/PsiN.png");
  */
  TCanvas * c2 = new TCanvas("c2","c2",600,600);
  c2->cd();
gStyle->SetOptStat(0);
gPad->SetTicks(-1);
  hA1->SetMarkerStyle(24);
  hA2->SetMarkerStyle(24);
  //hA1->SetMarkerColor(kBlue-7);
  //hA2->SetMarkerColor(kRed-9);
  //hOverlap->SetMarkerColor(kGreen);
  hA1->SetMarkerColor(kBlack);
  hA2->SetMarkerColor(kBlue);
  hOverlap->SetMarkerColor(kRed);
  //hA1->SetLineWidth(3);
  //hA2->SetLineWidth(3);
  //hOverlap->SetLineWidth(2);

  hOverlap->SetMarkerStyle(20);

  hA1->SetMarkerSize(nMarSiz);
  hA2->SetMarkerSize(nMarSiz);
  hOverlap->SetMarkerSize(nMarSiz);

  hDum->SetXTitle("x (fm)");
  hDum->SetYTitle("y (fm)");
 hDum->GetXaxis()->CenterTitle(1);
 hDum->GetYaxis()->CenterTitle(1);
  hDum->GetYaxis()->SetTitleOffset(1.1); 
  hDum->SetTitle("");
  hDum->Draw();

  // calculate eps_part 
  double drawsx = 0.;
  double drawsy = 0.;
  double drawsxy = 0.;
  double draweps = 0.;

  for( int i = 0; i<drawnpart; i++)
  {
    double xp = x[i]*cos(psidraw)+y[i]*sin(psidraw);
    double yp = -x[i]*sin(psidraw)+y[i]*cos(psidraw);
    drawsx += xp*xp;
    drawsy += yp*yp;
    drawsxy += xp*yp;
  }
  drawsx /= (double)drawnpart; 
  drawsy /= (double)drawnpart; 
  drawsxy /= (double)(drawnpart-1); 

  draweps = sqrt( (drawsy-drawsx)*(drawsy-drawsx) + 4.*drawsxy ) / ( drawsx + drawsy );

  TLatex * l1 = new TLatex(-15,13.5,Form("b = %4.1f fm",b[drawb]));
  l1->Draw();
  TLatex * l2 = new TLatex(-3,13.5,Form("#varepsilon_{2} = %4.3f",draweps));
  l2->Draw();
  //TLatex * lepart3 = new TLatex(8,13.5,Form("#varepsilon_{3} = %4.3f",0.197)); //get e3 values from prints
  TLatex * lepart3 = new TLatex(8,13.5,Form("#varepsilon_{3} = %4.3f", 0.203)); //get e3 values from prints
  lepart3->Draw();
  TLatex * lx = new TLatex(-13,-14,Form("Glauber MC,   PbPb #sqrt{s_{NN}} = 5.36 TeV"));
  lx->Draw();
  //TLatex * ly = new TLatex(-15,10.5,Form("N_{part} = %d",196)); // get Npart value from prints
  TLatex * ly = new TLatex(-15,10.5,Form("N_{part} = %d",12)); // get Npart value from prints
  //TLatex * ly = new TLatex(-15,10.5,Form("N_{part} = %d",20)); // get Npart value from prints
  ly->Draw();

  //TLatex * l1 = new TLatex(-14,13.5,Form("b = %4.1f fm",b[drawb]));
  //l1->Draw();
  //TLatex * l2 = new TLatex(2,13.5,Form("#varepsilon_{part} = %4.3f",draweps));
  //l2->Draw();
  TLatex * l3 = new TLatex(2,-11.5,Form("#sigma_{x'} = %4.3f fm",sqrt(drawsx)));
  //l3->Draw();
  TLatex * l4 = new TLatex(2,-14,Form("#sigma_{y'} = %4.3f fm",sqrt(drawsy)));
  //l4->Draw();
//  TLatex * l5 = new TLatex(-10,-12.5,Form("#sigma^{2}_{x'y'} = %4.3f fm^{2}",drawsxy));
//  l5->Draw();
  TLatex * l5 = new TLatex(9.5,8.8,"x'");
  l5->SetTextAngle(psidraw*180./3.14159);
  //l5->Draw();
  TLatex * l6 = new TLatex(-9.7,8.6,"y'");
  l6->SetTextAngle(psidraw*180./3.14159);
  //l6->Draw();
  TLatex * l7 = new TLatex(11.4,1.6,"#Psi_{R}");
  //l7->SetTextAngle(rxnAngle*180./3.14159);
  l7->SetTextColor(kGray+1);
  //l7->Draw();
  
  TArrow * arrow1 = new TArrow(0,0,2.2*R*cos(rxnAngle),2.2*R*sin(rxnAngle),0.03,">");
  arrow1->SetLineWidth(2);
  arrow1->SetLineColor(kGray+1);
  //arrow1->SetLineStyle(7);
  //arrow1->Draw();    

  TArrow * arrow1a = new TArrow(0,0,2.2*R*cos(rxnAngle+3.14159),2.2*R*sin(rxnAngle+3.14159),0.03,">");
  arrow1a->SetLineWidth(2);
  arrow1a->SetLineColor(kGray+1);
  //arrow1a->Draw();    

  TLine * arrowfix = new TLine(2.14*R*cos(rxnAngle+3.14159),2.14*R*sin(rxnAngle+3.14159),
                               2.14*R*cos(rxnAngle),2.14*R*sin(rxnAngle));
  arrowfix->SetLineWidth(3);
  arrowfix->SetLineColor(kWhite);
  //arrowfix->SetLineStyle(7);
  arrowfix->Draw();

  TEllipse * e1 = new TEllipse(b[drawb]/2.*cos(rxnAngle),b[drawb]/2.*sin(rxnAngle),R,R); 
  TEllipse * e2 = new TEllipse(-b[drawb]/2.*cos(rxnAngle),-b[drawb]/2.*sin(rxnAngle),R,R); 
  e1->SetFillStyle(0);
  e2->SetFillStyle(0);
  e1->SetLineColor(kGray+1);
  e2->SetLineColor(kGray+1);
  e1->SetLineWidth(2);
  e2->SetLineWidth(2);
  hOverlap->Draw("same");
  e1->Draw();
  e2->Draw();
  hA1->Draw("same");
  hA2->Draw("same");

  TLine * arrowfix2 = new TLine(2.31*R*cos(rxnAngle+3.14159),2.31*R*sin(rxnAngle+3.14159),
                               2.31*R*cos(rxnAngle),2.31*R*sin(rxnAngle));
  arrowfix2->SetLineWidth(2);
  arrowfix2->SetLineColor(kGray+1);
  arrowfix2->SetLineStyle(7);
  arrowfix2->Draw();


  TArrow * arrow2 = new TArrow(0,0,2.2*R*cos(0.),2.2*R*sin(0.),0.03,">");
  arrow2->SetLineWidth(2);
  arrow2->SetLineColor(kGray+1);
  //arrow2->Draw();    

  TArc * arc1 = new TArc(0,0,1.7*R,0.,180.*rxnAngle/3.14159);
  arc1->SetLineWidth(2);
  arc1->SetLineColor(kGray+1);
  arc1->SetFillStyle(0);
  //arc1->Draw("only");


  TArrow * ppaxis[4];
  for(int i = 0; i<4; i++)
  {
    if(i<2) ppaxis[i] = new TArrow(0,0,2*R*cos(psidraw+(double)i*1.57079633),2*R*sin(psidraw+(double)i*1.57079633),0.03,">");
    else ppaxis[i] = new TArrow(0,0,2*R*cos(psidraw+(double)i*1.57079633),2*R*sin(psidraw+(double)i*1.57079633),0.0,">");
    ppaxis[i]->SetLineWidth(2);
    //ppaxis[i]->Draw();
  }    

  TEllipse * cfoo = new TEllipse(-10,-10,0.71,0.71);
  //cfoo->Draw();

  //c2->Print("../figures/glauber_example.pdf");
  //c2->Print("pic_glauber_exampleCent.gif");
  c2->Print("pic_glauber_Npart12_example.pdf");
  c2->Print("pic_glauber_Npart12_example.png");
  //c2->Print("pic_glauber_Npart196_example.pdf");
  //c2->Print("pic_glauber_Npart196_example.png");
  //c2->Print("pic_glauber_Npart407_example.pdf");
  //c2->Print("pic_glauber_Npart407_example.png");
  /*
  TCanvas * c3 = new TCanvas("c3","c3",800,800);
  c3->cd();
  hA1_3D->SetXTitle("x (fm)");
  hA1_3D->SetYTitle("y (fm)");
  hA1_3D->SetZTitle("z (fm)");

  hA1_3D->Draw();
  hA2_3D->Draw("same");
  hCollision_3D->Draw("same");
  c3->Print("glauber/Collision3D.png");
  TCanvas * c4 = new TCanvas("c4","c4",800,950);
  c4->cd();
  TH1D * hecc = new TH1D("hecc","hecc",500,0,450);
  hecc->SetMaximum(1.0);
  hecc->SetMinimum(-0.2);
  hecc->SetXTitle("N_{part}");
  hecc->SetYTitle("#epsilon_{N}");
  hecc->Draw();
  for(int i = 1; i<=6; i++) g[i]->Draw("p");
  g_4_2->Draw("p");
  g_6_2->Draw("p");
  g_6_3->Draw("p");
  g_3_2->Draw("p");
  gPad->SetGrid(1,1);
  TLegend * leg = new TLegend(0.6,0.4,0.75,0.88);
  leg->SetFillColor(kWhite);
  leg->AddEntry(g[1],"#epsilon_{1}","p");
  leg->AddEntry(g[2],"#epsilon_{2}","p");
  leg->AddEntry(g[3],"#epsilon_{3}","p");
  leg->AddEntry(g[4],"#epsilon_{4}","p");
  leg->AddEntry(g[5],"#epsilon_{5}","p");
  leg->AddEntry(g[6],"#epsilon_{6}","p");
  leg->AddEntry(g_4_2,"#epsilon_{4_2}","p");
  leg->AddEntry(g_6_2,"#epsilon_{6_2}","p");
  leg->AddEntry(g_6_3,"#epsilon_{6_3}","p");
  leg->AddEntry(g_3_2,"#epsilon_{3_2}","p");

  leg->Draw();
  c4->Print("glauber/Eccentricities.png");
  TCanvas * c5 = new TCanvas("c5","c5",700,550);
  c5->cd();
  hWS1->SetLineColor(kBlue);
  hWS2->SetLineColor(kRed);
  hWS1->Scale(1./nEvent);
  hWS2->Scale(1./nEvent);
  hWS1->SetXTitle("R (fm)");
  hWS1->Draw();
  hWS2->Draw("same");
  c5->Print("glauber/WS.png");
  */
}
void wsFunc(int A, double *x, double *y, double*z){
  int i = 0;
  while(i<A) {
    double R  = ranR->GetRandom();
    double th = ranTheta->GetRandom();
    double ph = ran->Uniform(0,2.*TMath::Pi());
    x[i] = R*sin(th)*cos(ph);
    y[i] = R*sin(th)*sin(ph);
    z[i] = R*cos(th);
    int sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate1 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate2 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate3 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate4 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate5 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
    if(sub>0) {
      //cout<<"sub -- relocate6 "<<sub<<endl;
      th = ranTheta->GetRandom();
      ph = ran->Uniform(0,2.*TMath::Pi());
      x[i] = R*sin(th)*cos(ph);
      y[i] = R*sin(th)*sin(ph);
      z[i] = R*cos(th);
    }
    sub = 0;
    for(int j = 0; j<i; j++) {
      if(TMath::Sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2))<rHard) sub = 1;	
    }
 
    //if(sub>0) cout<<"sub: Relocation failed"<<endl;
    i-=sub;
    i++;
     
  }
  return;
}
void collide(int A, double sign, double*x1, double*y1, double*z1, double*x2, double*y2, double*z2, double*x, double*y, double*z, int &npart){
  double rmax = TMath::Sqrt(sign/10./TMath::Pi());
  int hit1[500];
  int hit2[500];
  for(int i = 0; i< A; i++) {hit1[i]=0;hit2[i]=0;}
  for(int i = 0; i< A; i++) {
    for(int j = 0; j<A; j++) {
      double d = TMath::Sqrt( pow(x1[i]-x2[j],2) + pow(y1[i]-y2[j],2));
      if(d<rmax) {
	hit1[i] = 1;
	hit2[j] = 1;
      }
    }
  }
  npart = 0;
  for(int i = 0; i<A; i++) {
    if(hit1[i]==1) {
      x[npart] = x1[i];
      y[npart] = y1[i];
      z[npart++] = z1[i];
    }
    if(hit2[i]==1) {
      x[npart] = x2[i];
      y[npart] = y2[i];
      z[npart++] = z2[i];
    }
  }
}
void recenter(int npart, double*x, double*y, double*z) {
  double xav = 0;
  double yav = 0;
  double zav = 0;
  for(int i = 0; i< npart; i++) {
    xav+=x[i];
    yav+=y[i];
    zav+=z[i];
  }
  if( npart > 0 )
  {
    xav/=npart;
    yav/=npart;
    zav/=npart;
  }
  cout << "Average: " << xav << " " << yav << endl;
  for(int i = 0; i< npart; i++) {
    x[i]-=xav;
    y[i]-=yav;
    z[i]-=zav;
  }

}
double PsiN(double order, int np, double*x, double*y){
  double sx = 0;
  double sy = 0;
  for(int i = 0; i<np; i++) {
    double r = TMath::Sqrt(x[i]*x[i]+y[i]*y[i]);
    double rsq = r*r;
    double angp = TMath::ATan2(y[i],x[i]);
    sx+=rsq*TMath::Cos(order*angp);
    sy+=rsq*TMath::Sin(order*angp);
  }

  //angle defined from x-axis
  //cout<<"order,sx,sy: "<<order<<"\t"<<sx<<"\t"<<sy<<endl;
  double angEP = bounds2(order,(1/order)*(TMath::ATan2(sy,sx)+TMath::Pi()));
  return angEP;
  
}
double eccentricity(double order, double psi, int npart, double *x, double *y){
   double avx = 0;
   double avy = 0;
   double avr = 0;
   for(int i = 0; i<npart; i++) {
     double rsq = x[i]*x[i]+y[i]*y[i];
     double ang = TMath::ATan2(y[i],x[i]);
     avx+=rsq*TMath::Cos(order*(ang-psi));
     avy+=rsq*TMath::Sin(order*(ang-psi));
     avr+=rsq;
   }
   avx/=(double)npart;
   avy/=(double)npart;
   avr/=(double)npart;
   return  -avx/avr;
}
