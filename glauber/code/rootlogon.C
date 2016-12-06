// regular style
/*
{   gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111);
  //  gStyle->SetOptTitle(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetCanvasBorderSize(0);
//  gStyle->SetErrorX(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineWidth(2.0);  
  gStyle->SetCanvasColor(0); 
  gStyle->SetCanvasBorderMode(0); 
  gStyle->SetPadColor(0);   
  gStyle->SetPadBorderMode(0);
  //  gStyle->SetOptFit(0001);   
  gStyle->SetPadTickX(1); 
  gStyle->SetPadTickY(1);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetErrorX(0.001);
}
*/

// AN-10-394 Style

{
cout << endl << "Welcome to rootlogon.C" << endl;
cout << "To use this style use gROOT->SetStyle(\"MyStyle\");"
<< endl << endl;

//..My style from RooLogon.C in workdir
TStyle *MyStyle= new TStyle("MyStyle","MyStyle");

// use plain black on white colors
MyStyle->SetFrameBorderMode(0);
MyStyle->SetCanvasBorderMode(0);
MyStyle->SetPadBorderMode(0);
MyStyle->SetPadColor(0);
MyStyle->SetCanvasColor(0);
MyStyle->SetStatColor(0);
MyStyle->SetFillStyle(0);
MyStyle->SetFillColor(0);
MyStyle->SetLegendBorderSize(0);

// set the paper & margin sizes
//MyStyle->SetPaperSize(20,26);
MyStyle->SetPadTopMargin(0.2);
MyStyle->SetPadRightMargin(0.2);
MyStyle->SetPadBottomMargin(0.2);
MyStyle->SetPadLeftMargin(0.2);
//MyStyle->SetHistTopMargin(0.12);
int fs=132;
// use large Times-Roman fonts
MyStyle->SetTextFont(fs);
MyStyle->SetTextSize(0.08);
MyStyle->SetLabelFont(fs,"x");
MyStyle->SetLabelFont(fs,"y");
MyStyle->SetLabelFont(fs,"z");
MyStyle->SetLabelSize(0.08,"x");
MyStyle->SetLabelSize(0.08,"y");
MyStyle->SetLabelOffset(0.01,"x");
MyStyle->SetLabelOffset(0.01,"y");
MyStyle->SetLabelSize(0.08,"z");
MyStyle->SetTitleBorderSize(0);
MyStyle->SetTitleX(0.2);
MyStyle->SetTitleY(0.9);
MyStyle->SetTitleFont(fs,"x");
MyStyle->SetTitleFont(fs,"y");
MyStyle->SetTitleFont(fs,"z");
MyStyle->SetTitleSize(0.08,"x");
MyStyle->SetTitleSize(0.08,"y");
MyStyle->SetTitleSize(0.08,"z");
MyStyle->SetTitleFontSize(0.08);
MyStyle->SetTitleOffset(1.2,"x");
MyStyle->SetTitleOffset(1.3,"y");

// use bold lines and markers
MyStyle->SetMarkerStyle(20);
MyStyle->SetHistLineWidth(1.85);
MyStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
MyStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
MyStyle->SetOptTitle(0);
MyStyle->SetOptStat(0);
MyStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
MyStyle->SetPadTickX(1);
MyStyle->SetPadTickY(1);

MyStyle->cd();
//gROOT->SetStyle("Plain");
//gStyle->SetOptStat(1111111);
//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);
}

