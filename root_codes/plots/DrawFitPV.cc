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

void DrawFitPV( TH1F* histo, double xmin, double xmax, string title=" ", bool print=false){

  RooRealVar x    ( "x"    , "PV z difference", xmin, xmax , "cm" );

  

  RooRealVar mean ( "mean", "mean"    , 0   ,     -0.01 ,     0.01  , "." );
  RooRealVar widt1( "widt1", "Width1"   , 0.0017 , 0.00001 , 0.1, "." );
  RooRealVar widt2( "widt2", "Width2"   , 0.0044 , 0.00001 , 0.1, "." );
  //  RooRealVar widt3( "widt3", "Width3"   , 0.002 , 0.00001 , 0.1, "." );




  RooGaussian    gauss1( "gauss1", "Gaussian 1" , x, mean, widt1 );
  RooGaussian    gauss2( "gauss2", "Gaussian 2" , x, mean, widt2 );
  // RooGaussian    gauss3( "gauss3", "Gaussian 3" , x, mean, widt3 );

  RooRealVar gfrac1( "gfrac1", "fraction 1"   , 0.5 ,   0.0, 1.0  );
  //  RooRealVar gfrac2( "gfrac2", "fraction 2"   , 0.25 ,   0.0, 1.0  );

  RooDataHist data("data","data",x, Import(*histo)) ;
  
 // RooAddPdf GaussSum ( "GaussSum", "Gauss 1+2", RooArgList ( gauss1, gauss2 , gauss3),
  //                                              RooArgList ( gfrac1, gfrac2 )  );
  RooAddPdf GaussSum ( "GaussSum", "Gauss 1+2", RooArgList ( gauss1, gauss2 ), gfrac1  );

  string name=histo->GetName();
  TCanvas* can = new TCanvas( (name).c_str(), (name).c_str(), 800, 600 );
  can->SetLeftMargin( 0.15 );
  can->cd();
  //x.setBins( 30);

  RooPlot* frame = x.frame() ;
  data.plotOn(frame) ;
  GaussSum.fitTo(data) ;
  GaussSum.plotOn(frame) ;
  GaussSum.plotOn( frame, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( frame, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );
 // GaussSum.plotOn( frame, Components( "gauss3" ), LineStyle( kDashed ), LineColor( kViolet ) );

  //  RooFormulaVar Sigma ("Sigma","Total Sigma","sqrt(gfrac1*widt1*widt1+ (1-gfrac1)*widt2*widt2",
  //		       RooArgList(gfrac1,widt1,widt2)) ;
  //Sigma.evaluate();
  widt1.printScientific(kTRUE);
  RooArgSet params = RooArgList(mean, widt1, widt2) ;

  GaussSum.paramOn(frame,Layout(0.7, 0.95, 0.9), Format("NE", AutoPrecision()), Parameters(params));
  // Sigma.plotOn(frame) ;
  frame->SetYTitle("Events");
  frame->SetTitle (title.c_str());
  frame->getAttText()->SetTextSize(0.02) ;
  ofstream out ((name+"Params.txt").c_str());
  ofstream outl ((name+"Latex.txt").c_str());


//data.statOn(frame,Layout(0.75,0.99,0.5)) ;

  out <<"mean :  "  <<mean.getVal()  <<" +/- "<<mean.getError()<<endl;
  out <<"widt1 :  " <<widt1.getVal() <<" +/- "<<widt1.getError()<<endl;
  out <<"widt2 :  " <<widt2.getVal() <<" +/- "<<widt2.getError()<<endl;
  out <<"gfrac1 : " <<gfrac1.getVal()<<" +/- "<<gfrac1.getError()<<endl;

  float m=mean.getVal();
  float em=mean.getError();
  float w1=widt1.getVal();
  float w2=widt2.getVal();
  float ew1=widt1.getError();
  float ew2=widt2.getError();
  float f1=gfrac1.getVal();
  float ef1=gfrac1.getError();
  
  
  
  float Sigma= sqrt(w1*w1*f1+(1-f1)*w2*w2);
  float eSigma= sqrt(pow((w1*f1*ew1),2)+pow((w2*(1-f1)*ew2),2)+pow((w1*w1-w2*w2)*ef1,2)/2)/Sigma;
  
  outl<< setiosflags(ios::fixed) << setprecision(5) 
      <<m*100000<<" pm "<< em*100000 <<" & " 
      << setiosflags(ios::fixed) << setprecision(5) 
      <<w1*1000<<" pm "<< ew1*1000 <<" & " 
      <<w2*1000<<" pm "<< ew2*1000 <<" & " 
      <<Sigma*1000<<" pm "<<eSigma*1000<<" // ";
  
  
  frame->Draw();
  
  if(print) can->Print((name+"Fit.pdf").c_str());
  if(print) can->Print((name+"Fit.png").c_str());

  TCanvas* lcan = new TCanvas( (name+"Logy").c_str(), (name+"Logy").c_str(), 800, 600 );
  lcan->SetLeftMargin( 0.15 );
  lcan->cd();
  lcan->SetLogy();
  //x.setBins( 30);

  RooPlot* lframe = x.frame() ;
  data.plotOn(lframe) ;
  GaussSum.plotOn(lframe) ;
  GaussSum.plotOn( lframe, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( lframe, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );
  GaussSum.plotOn( lframe, Components( "gauss3" ), LineStyle( kDashed ), LineColor( kViolet ) );


  GaussSum.paramOn(lframe,Layout(0.7, 0.95, 0.9), Format("NE", AutoPrecision()), Parameters(params));
  
  lframe->getAttText()->SetTextSize(0.02) ;

  lframe->SetYTitle("Events");
  lframe->SetTitle (title.c_str());
  //GaussSum.paramOn(lframe,Layout(0.35, 0.65, 0.1)) ;
  //data.statOn(lframe,Layout(0.75,0.99,0.5)) ;

  lframe->Draw();

  if(print) lcan->Print((name+"FitLogY.pdf").c_str());
  if(print) lcan->Print((name+"FitLogy.png").c_str());

  return;
}
