#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
using namespace RooFit ;

void DrawEfficiencyTrigger( TH1F* h11,  TH1F* h21, int r=1, double xmax=0.25){
  // ofstream out("effout.txt");
  TH1F *h1=(TH1F*)h11->Clone();
  TH1F *h2=(TH1F*)h21->Clone();
  h1->Rebin(r);
  h2->Rebin(r);

  TH1F *f=(TH1F*)h1->Clone();
  int nBin=h1->GetNbinsX();
  double eff, s;
  for (int i=1; i<nBin; i++){
    if (h2->GetBinContent(i)!=0){
      eff=h1->GetBinContent(i)/h2->GetBinContent(i);
      s=sqrt(eff*(1-eff)/h2->GetBinContent(i));
    }
    else { eff=0; s=0;}
    
    f->SetBinContent(i, eff);
    f->SetBinError  (i, s);
  }
  RooRealVar e    ( "e"    , "efficiency", 0.0, xmax , "" );

  RooRealVar coef12( "coef12", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  RooRealVar coef22( "coef22", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  RooPolynomial pol2( "plo2", "Polynomial 2", e, RooArgList( coef12, coef22 ) );

  // RooRealVar coef11( "coef1", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  //RooPolynomial pol1( "plo1", "Polynomial 1", e, RooArgList( coef11) );

  RooRealVar coef13( "coef13", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  RooRealVar coef23( "coef23", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  RooRealVar coef33( "coef33", "Coefficicent 1"  , 0.0, -100.0, 100.0, " " );
  RooPolynomial pol3( "plo3", "Polynomial 3", e, RooArgList( coef13, coef23, coef33 ) );

//variabili per la gaussiana 
  RooRealVar ResoMean  ( "ResoMean",  "Distance Res Mean"  ,   0.0058,     0.0, 0.02, "cm" );
  RooRealVar Resolution( "Resolution","Distance Resolution", 0.0027, 0.00001,  0.1, "cm" );
  RooRealVar RBkgComb ("RBkgComb", "expo" , 0.645, 0.0, 1, "cm");
  RooGaussModel ResoGauss( "ResoGauss", "Distance Resolution Gaussian", e, ResoMean, Resolution );

  RooDecay RBkgExpo( "RBkgExpo", "Right Bk Convolved Decay",  e, RBkgComb, ResoGauss, RooDecay::SingleSided );
  // RooDecay RBkgExpopol( "RBkgExpopol", "Right Bk Convolved Decay",  e, RBkgComb,pol2 , RooDecay::SingleSided );

 RooRealVar ml("ml","mean landau",5.,-20,20) ;
  RooRealVar sl("sl","sigma landau",1,0.1,10) ;
  RooLandau landau("lx","lx",e,ml,sl) ;
  
  // RooFFTConvPdf lxg("lxg","landau (X) gauss",e,landau,RBkgExpo) ;


  RooDataHist data("data", "data", e, Import(*f));
  
  TCanvas* can = new TCanvas( "efficiency", "efficiency" , 800, 600 );
  can->SetLeftMargin( 0.15 );
  can->cd();
  
  
  e.setRange("eRange", 0.0, xmax);

  RooPlot* frame = e.frame() ;
    data.plotOn(frame, Range("eRange")) ;
 // pol2.chi2FitTo(data, Range("eRange") ); //,SumW2Error(kTRUE), Extended(kFALSE)) ;
     RBkgExpo.chi2FitTo(data, Range("eRange") ); //,SumW2Error(kTRUE), Extended(kFALSE)) ;
    // lxg.chi2FitTo(data, Range("eRange") ); //,SumW2Error(kTRUE), Extended(kFALSE)) ;
    //RBkgExpopol.chi2FitTo(data, Range("eRange") ); //,SumW2Error(kTRUE), Extended(kFALSE)) ;

  //RBkgExpo.fitTo(data, Range("eRange") ); //,SumW2Error(kTRUE), Extended(kFALSE)) ;

  //pol2.fitTo(data, Range("eRange"), Extended(kFALSE)) ;

  
 // pol2.plotOn(frame, LineColor( kRed)) ;
    RBkgExpo.plotOn(frame, LineColor( kOrange)) ;
    //RBkgExpopol.plotOn(frame, LineColor( kOrange)) ;
// lxg.plotOn(frame, LineColor( kOrange)) ;

  // pol1.fitTo(data, Range("eRange"),SumW2Error(kTRUE), Extended(kFALSE)) ;
  // pol1.plotOn(frame, LineColor( kBlue)) ;

  // pol3.fitTo(data, Range("eRange"),SumW2Error(kTRUE), Extended(kFALSE)) ;
  // pol3.plotOn(frame, LineColor( kGreen)) ;


  // pol1.paramOn(frame,Layout(0.65)) ;
 // pol2.paramOn(frame,Layout(0.65)) ;
  // pol3.paramOn(frame,Layout(0.65)) ;
  RBkgExpo.paramOn(frame,Layout(0.65)) ;
  //RBkgExpopol.paramOn(frame,Layout(0.65)) ;

  // data.statOn(frame,Layout(0.75,0.99,0.5)) ;
  frame->Draw();

  float b=coef12.getVal();
  float c=coef22.getVal();
  float a=1.0/xmax- b*xmax/2-c*xmax*xmax/3;

  cout<<1.0/xmax<<" "<< -b*xmax/2<<" "<<-c*xmax*xmax/3<<endl;

  cout<<pol2.getValV()<<endl;

  cout<<pol2.getLogVal()<<endl;
  cout<<"Termine noto:    "<<a<<endl;

  cout<<"Termine 1 grado: "<<b<<endl;
  cout<<"Termine 2 grado: "<<c<<endl;

 
  can->Print("EfficiencyFit.pdf");
  can->Print("EfficiencyFit.png");

  
}
