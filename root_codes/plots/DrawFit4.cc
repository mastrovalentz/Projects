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

void DrawFit4( TH1F* histo, double xmin, double xmax, string title=" ", bool print=false){

  RooRealVar x    ( "x"    , "Flight distance difference", xmin, xmax , "cm" );

  

  RooRealVar mean ( "mean", "mean"    , 0   ,     -0.01 ,     0.01  , "." );
  RooRealVar widt1( "widt1", "Width1"   , 0.0013 , 0.00001 , 0.1, "." );
  RooRealVar widt2( "widt2", "Width2"   , 0.0024 , 0.00001 , 0.1, "." );
  RooRealVar widt3( "widt3", "Width3"   , 0.0052 , 0.00001 , 0.1, "." );




  RooGaussian    gauss1( "gauss1", "Gaussian 1" , x, mean, widt1 );
  RooGaussian    gauss2( "gauss2", "Gaussian 2" , x, mean, widt2 );
  RooGaussian    gauss3( "gauss3", "Gaussian 3" , x, mean, widt3 );

  RooRealVar gfrac1( "gfrac1", "fraction 1"   , 0.25 ,   0.0, 1.0  );
  RooRealVar gfrac2( "gfrac2", "fraction 2"   , 0.25 ,   0.0, 1.0  );

  RooDataHist data("data","data",x, Import(*histo)) ;
  
  RooAddPdf GaussSum ( "GaussSum", "Gauss 1+2", RooArgList ( gauss1, gauss2 , gauss3),
                                                RooArgList ( gfrac1, gfrac2 )  );

  string name=histo->GetName();
  TCanvas* can = new TCanvas( (name).c_str(), (name).c_str(), 800, 600 );
  can->SetLeftMargin( 0.15 );
  can->cd();
  //x.setBins( 30);
  ofstream out ((name+"Params.txt").c_str());

  RooPlot* frame = x.frame() ;
  data.plotOn(frame) ;
  GaussSum.fitTo(data) ;
  GaussSum.plotOn(frame) ;
  GaussSum.plotOn( frame, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( frame, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );
  GaussSum.plotOn( frame, Components( "gauss3" ), LineStyle( kDashed ), LineColor( kViolet ) );

  widt1.printScientific(kTRUE);
  RooArgSet params = RooArgList(mean, widt1, widt2, widt3) ;

  GaussSum.paramOn(frame,Layout(0.7, 0.95, 0.9), Format("NE", AutoPrecision()), Parameters(params));
  
  frame->SetYTitle("Events");
  frame->SetTitle (title.c_str());
  frame->getAttText()->SetTextSize(0.02) ;

  out <<"mean :  "  <<mean.getVal()  <<" +/- "<<mean.getError()<<endl;
  out <<"widt1 :  " <<widt1.getVal() <<" +/- "<<widt1.getError()<<endl;
  out <<"widt2 :  " <<widt2.getVal() <<" +/- "<<widt2.getError()<<endl;
  out <<"widt3 :  " <<widt3.getVal() <<" +/- "<<widt3.getError()<<endl;
  out <<"gfrac1 : " <<gfrac1.getVal()<<" +/- "<<gfrac1.getError()<<endl;
  out <<"gfrac2 : " <<gfrac2.getVal()<<" +/- "<<gfrac2.getError()<<endl;

//data.statOn(frame,Layout(0.75,0.99,0.5)) ;


  ofstream outl ((name+"Latex.txt").c_str());
  float m=mean.getVal();
  float em=mean.getError();
  float w1=widt1.getVal();
  float w2t=widt2.getVal();
  float w3t=widt3.getVal();
  float ew1=widt1.getError();
  float ew2t=widt2.getError();
  float ew3t=widt3.getError();
  float f1=gfrac1.getVal();
  float ef1=gfrac1.getError();
  float f2=gfrac2.getVal();
  float ef2=gfrac2.getError();



  float w2=sqrt(w2t*w2t*f2+(1-f2)*w3t*w3t);
  float ew2= sqrt(pow((w2t*f2*ew2t),2)+pow((w3t*(1-f2)*ew3t),2)+pow((w2t*w2t-w3t*w3t)*ef2,2)/2)/w2;


  float Sigma= sqrt(w1*w1*f1+(1-f1)*w2*w2);
  float eSigma= sqrt(pow((w1*f1*ew1),2)+pow((w2*(1-f1)*ew2),2)+pow((w1*w1-w2*w2)*ef1,2)/2)/Sigma;
  
outl<< setiosflags(ios::fixed) << setprecision(5) 
      <<m*100000<<" pm "<< em*100000 <<" & " 
      << setiosflags(ios::fixed) << setprecision(5) 
      <<w1*1000<<" pm "<< ew1*1000 <<" & " 
      <<w2t*1000<<" pm "<< ew2t*1000 <<" & " 
      <<w3t*1000<<" pm "<< ew3t*1000 <<" & " 
      <<Sigma*1000<<" pm "<<eSigma*1000<<" // "<<endl;
  

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
