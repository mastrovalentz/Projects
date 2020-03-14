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

void DrawFit2( TH1F* histo, double xmin, double xmax, bool print=false){

  RooRealVar x    ( "x"    , "distance diff", xmin, xmax , "." );

  RooRealVar mean ( "mean", "mean"    , 0   ,     -0.01 ,     0.01  , "." );
  RooRealVar widt1( "widt1", "Widt1"   , 0.002 , 0.001 , 0.1, "." );
  RooRealVar widt2( "widt2", "Widt2"   , 0.002 , 0.001 , 0.1, "." );

  RooGaussian    gauss1( "gauss1", "Gaussian 1" , x, mean, widt1 );
  RooGaussian    gauss2( "gauss2", "Gaussian 2" , x, mean, widt2 );
 
  RooRealVar gfrac( "gfrac", "fraction"   , 0.5 ,   0.0, 1.0  );

  RooDataHist data("data","data",x, Import(*histo)) ;
  
  RooAddPdf GaussSum ( "GaussSum", "Gauss 1+2", RooArgList( gauss1, gauss2 ), gfrac  );

  string name=histo->GetName();
  TCanvas* can = new TCanvas( (name+"Logy").c_str(), (name+"Logy").c_str(), 800, 600 );
  can->SetLeftMargin( 0.15 );
  can->cd();
  //x.setBins( 30);

  RooPlot* frame = x.frame() ;
  data.plotOn(frame) ;
  GaussSum.fitTo(data) ;
  GaussSum.plotOn(frame) ;
  GaussSum.plotOn( frame, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( frame, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );


GaussSum.paramOn(frame,Layout(0.75)) ;
data.statOn(frame,Layout(0.75,0.99,0.5)) ;



  frame->Draw();
  
  if(print) can->Print((name+"Fit.pdf").c_str());
  if(print) can->Print((name+"Fit.png").c_str());

  TCanvas* lcan = new TCanvas( name.c_str(), name.c_str(), 800, 600 );
  lcan->SetLeftMargin( 0.15 );
  lcan->cd();
  lcan->SetLogy();
  //x.setBins( 30);

  RooPlot* lframe = x.frame() ;
  data.plotOn(lframe) ;
  GaussSum.plotOn(lframe) ;
  GaussSum.plotOn( lframe, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( lframe, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );
  //GaussSum.paramOn(lframe,Layout(0.75)) ;
  //data.statOn(lframe,Layout(0.75,0.99,0.5)) ;

  lframe->Draw();

  if(print) lcan->Print((name+"FitLogY.pdf").c_str());
  if(print) lcan->Print((name+"FitLogy.png").c_str());

  return;
}
