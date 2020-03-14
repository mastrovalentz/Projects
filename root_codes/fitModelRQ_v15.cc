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

using namespace RooFit ;

//.x fitGauss2Exp2D.cc ("SubSim/try.txt", "tryout", 100, 5, 6, 0.5, 0.5, 5.37, 0.01, 0.02,-3.0, 0.5)

//.x fitGauss2Exp2D_v5.cc ("alldata.txt", "5m", 100, 5, 6, 0.5, 0.5, 5.37, 0.01, 0.02,-3.0, 0.5)



EColor csig = kBlue;
EColor csi2 = kViolet;
EColor cbkg = kGreen;
EColor cmis = kRed;

/*
void fitGauss2ExpE2D( const string& head,
                      const string& name,
                      const string& pset, int year,
                      const string& dset, float lumi,
                      const string& ptit,
                      const string& atit,
                      const vector<const InfoLabel*>& lv, const string& misrl,
                      int nbin, double xmin, double xmax,
                      float xfac, float yfac, float xfct, float yfct,
                      double mass, double sig1, double sig2,
                      double expc, double mbkg, double sbkg, double fbkg,
                      double fsig,
                      bool pbkg = true, bool psig = false ) {
  string nfit = name + pset + to_string( year ) + dset;
  string file = head + nfit;
  const char* list = file.c_str();


*/
/*
.x fitModelRQ_v15.cc ("../../PK12/30kAllNoBs.txt", "AllNoBs", 100, 5, 6, 0.5, 0.5, 5.37, 0.01, 0.02,-3.0, 0.5, 3.05459, -1.63214, 2.15937)

.x fitModelRQ_v15.cc  ("../data/30k/LD30kAllNoBs.txt", "AllNoBs", 100, 5, 6, 0.5, 0.5, 5.37, 0.01, 0.02,-3.0, 0.5, 3.05459, -1.63214, 2.15937, 0, false, true, false)

*/

void fitModelRQ_v15  (const string& file, const string& outname,
		     int nbin, double xmin, double xmax,
		     double xfac, double yfac,
		     double mass, double sigma1, double sigma2, 
		     double expc, double signalFrac,
			   double ap, double bp, double cp, double norm,
         int tr , bool setReso, bool setMean, bool setFrac ) 
         //tr indica il trigger in uso 0 nessuno 1 il primo 2 entrambi
          //i boolenai impostano le cose da fissare
{

	   

  if( tr!=0 && tr!=1 && tr!=2 )
  {
    cout<<"errore selezione trigger"<<endl;
    return;
  }
  ofstream oo ((outname+"outParams.txt").c_str());

  const char* list = file.c_str(); //lista dei dati
  // define the data variables and fit model parameters
  float dmin = -0.03;
  float dbkg= 0.02;
  float dmax =  0.20;
  //int dbin=60;
  int dbin =int((dmax-dmin)*400) ;
 

  RooRealVar m( "m", "Reconstructed Mass",    xmin, xmax, "GeV" );
  RooRealVar d( "d",    "Flight Distance",    dmin, dmax,  "cm" );
  RooRealVar e( "e",     "Distance Error", 0.00001,  0.2,  "cm" );

  RooRealVar rmass (  "rmass",   "Resonance  Mass",   mass,   xmin,  xmax, "GeV" );
  RooRealVar widt1( "widt1", "Resonance Widt1", sigma1,  0.001, sigma1*10, "GeV" );
  RooRealVar widt2( "widt2", "Resonance Widt2", sigma2,  0.001, sigma2*10, "GeV" ); 
  RooRealVar gfrac    ( "gfrac", "signal fraction1", signalFrac , 0.0, 1.0 );
  
// create the fit model components: Gaussian and exponential PDFs
  RooGaussian    gauss1( "gauss1",     "Signal Distribution1", m, rmass, widt1 );
  RooGaussian    gauss2( "gauss2",     "Signal Distribution2", m, rmass, widt2 );
 
  RooRealVar coef1( "coef1", "Coefficicent 1"  , -0.3, -100.0, 100.0, "GeV^-1" );
  RooRealVar coef2( "coef2", "Coefficicent 2"  , 0.03,  -10.0,  10.0, "GeV^-2" );
 
  RooPolynomial polyn( "polyn", "Polynomial Distribution", m, RooArgList( coef1, coef2 ) );
  // RooChebychev  polyc( "polyc", "Chebychev Polynomial Distribution", m, RooArgList( coef1, coef2) );

  RooAddPdf GaussSum ( "GaussSum", "Signal"  , RooArgList( gauss1, gauss2   ), gfrac   );
 
// read values of ’m d e’ from a text file
  RooDataSet*       data = RooDataSet::read( list, RooArgList( m, d, e) );
   
  //calculate weight with pol2 values
  
  RooRealVar a( "a",     "a"  , ap,  ap-0.1, ap+0.1 );
  RooRealVar b( "b",     "b"  , bp,  bp-0.1, bp+0.1 );
  RooRealVar c( "c",     "c"  , cp,  cp-0.1, cp+0.1 );
  RooRealVar normm( "normm",     "normm"  ,norm ,norm  -0.1,norm +0.1 );
  a.setConstant( kTRUE );
  b.setConstant( kTRUE );
  c.setConstant( kTRUE );

  RooRealVar ae( "a",     "a"  , ap/ap,  -100, 100   );
  RooRealVar be( "b",     "b"  , bp/ap,  -100, 100   );
  RooRealVar ce( "c",     "c"  , cp/ap,  -100, 100   );
  ae.setConstant( kTRUE );
  be.setConstant( kTRUE );
  ce.setConstant( kTRUE );
  normm.setConstant( kTRUE );
 
  RooFormulaVar wFunc ("w","event weight","1/(normm*(a+b*sqrt(d*d)+c*d*d))",RooArgList(d,a,b,c, normm)) ;
  RooRealVar*   w = (RooRealVar*) data->addColumn(wFunc) ;
  data->Print() ;
  RooDataSet wdata(data->GetName(),data->GetTitle(),data,*data->get(),0,w->GetName()) ;
  wdata.Print() ;

  int          TotEvents = wdata.numEntries();
  float        SigEvents = TotEvents * signalFrac;
  float        BkgEvents = TotEvents * ( 1.0 - signalFrac );
  

  RooRealVar   SigNum ( "SigNum", "Signal number", SigEvents,  SigEvents/10.0, SigEvents*10.0 );
  RooRealVar   BkgNum ( "BkgNum", "Backgr number", BkgEvents,  BkgEvents/10.0, BkgEvents*10.0 );
 
  RooExtendPdf ExtendedSignal  ( "ExtendedSignal", "ExtendedSignal", GaussSum, SigNum );
  RooExtendPdf ExtendedBackCP  ( "ExtendedBackCP", "ExtendedBackCP",  polyn , BkgNum );

  RooAddPdf  model12  ( "modell2", "Signal + Background 12", RooArgList(ExtendedBackCP ,ExtendedSignal) );
 


 //taglio un pezzo dei dati per fittare il fondo
  TString Cut = "m<5.3||m>5.5";
//  TString Cut = "m>5.5";

 // RooAbsData* CutData = wdata.reduce( Cut );
  RooAbsData* CutData = data->reduce( Cut );

  RooAbsData* TempMass = CutData;

  m.setRange("lowMass" ,   5, 5.3);
  m.setRange("highMass", 5.50, 6.0);

  m.setRange("signal", 5.3, 5.5);

 
  polyn.fitTo( *CutData , Range("lowMass,highMass"), Extended (kFALSE));

  //polyn.fitTo( *CutData , Extended (kFALSE) );

  TCanvas* tbg = new TCanvas( "tbg",outname.c_str(), 800, 600 );
  tbg->SetLeftMargin( 0.15 );
  tbg->cd();
  m.setBins( nbin );
  RooPlot* mfrtbg = m.frame();
  CutData->plotOn( mfrtbg );
  
  polyn.plotOn( mfrtbg,LineColor( cbkg )  );
  mfrtbg->SetTitle("");
  mfrtbg->Draw();


  cout << "dframe objects:\n";
  for (int i=0; i<mfrtbg->numItems(); i++) {
    TString obj_name=mfrtbg->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());
  }

//questi sono tutti insieme
  TString names1[] = {
    "h_dataset",
    "polyn_Norm[m]_Range[fit_nll_polyn_dataset_lowMass,fit_nll_polyn_dataset_highMass]_NormRange[fit_nll_polyn_dataset_lowMass,fit_nll_polyn_dataset_highMass]",
    ""
  };

  TString signs1[] = {
    "data",
    "Background"
  };

  
  TLegend* leg1 = new TLegend(0.6,0.65,0.80,0.80);
  // TLegend* leg1 = new TLegend(0.3, 0.2);
Int_t ib=-1;
  while ( names1[++ib] != "" ) {
    TObject *obj =mfrtbg ->findObject(names1[ib].Data());
    if (!obj) {
      //Warning("fitBi4",Form("Can't find item='%s' in the frame2!\n",names[i].Data()));
      cout<<"non trovato\n";
      continue;
    }
    if (signs1[ib]=="data")    leg1->AddEntry(obj,signs1[ib],"pe");
    else leg1->AddEntry(obj,signs1[ib],"l");
  }
  leg1->Draw("same");



  tbg->Print( ( outname + "MassBkg.pdf" ).c_str() );
  tbg->Print( ( outname + "MassBkg.png" ).c_str() );

  cout << "coef1: " << coef1.getVal() << " +/- " << coef1.getError() << endl;
  cout << "coef2: " << coef2.getVal() << " +/- " << coef2.getError() << endl;
  cout << "BkgNum: " << BkgNum.getVal() << " +/- " << BkgNum.getError() << endl;
//  return;

  coef1.setConstant( kTRUE );
  coef2.setConstant( kTRUE );

  // model12.fitTo( wdata, Extended( kTRUE ),SumW2Error(kTRUE)  );
  model12.fitTo( *data, Extended( kTRUE )); 

  // print results
  cout << "results" << endl;
  cout << "rmass: " << rmass.getVal() << " +/- " << rmass.getError() << endl;
  cout << "widt1: " << widt1.getVal() << " +/- " << widt1.getError() << endl;
  cout << "widt2: " << widt2.getVal() << " +/- " << widt2.getError() << endl;
  cout << "gfrac: " << gfrac.getVal() << " +/- " << gfrac.getError() << endl;
 

  float f1 = gfrac.getVal();
  float sigma = sqrt( ( pow( widt1.getVal(), 2 ) *         signalFrac ) +
                      ( pow( widt2.getVal(), 2 ) * ( 1.0 - signalFrac ) ) );
  cout << " sigma = " << sigma << endl;


  TCanvas* tmp = new TCanvas( "tmp",outname.c_str(), 800, 600 );
  tmp->SetLeftMargin( 0.15 );
  tmp->cd();
  m.setBins( nbin );
  RooPlot* mfrtmp = m.frame();
  //  mfrtmp->SetTitle( ptit.c_str() );
  // mfrtmp->SetXTitle( atit.c_str() );
 // wdata.plotOn( mfrtmp );
  data->plotOn( mfrtmp );
  
  model12.plotOn( mfrtmp, Components( "polyn" ),LineStyle( kDashed ), LineColor( cbkg ) );
  model12.plotOn( mfrtmp, Components( "GaussSum"),LineStyle( kDashed ), LineColor( csig ) );
  //model12.plotOn( mfrtmp, Components( "gauss1"),LineStyle( kDashed ), LineColor( kOrange ) );
  //model12.plotOn( mfrtmp, Components( "gauss2"),LineStyle( kDashed ), LineColor( kGreen ) );
  model12.plotOn( mfrtmp, LineColor( cmis ) );
  mfrtmp->SetTitle("");
  mfrtmp->Draw();
 

  cout << "dframe objects:\n";
  for (int i=0; i<mfrtmp->numItems(); i++) {
    TString obj_name=mfrtmp->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());
  }

TString mnames[] = {
    "h_dataset",
    "modell2_Norm[m]_Comp[polyn]",
    "modell2_Norm[m]_Comp[GaussSum]",
    "modell2_Norm[m]",
    ""
  };

  TString msigns[] = {
    "data",
    "Background",
    "Signal",
    "Total"
  };

  TLegend* mleg = new TLegend(0.6,0.7,0.90,0.90);
  Int_t im=-1;
  while ( mnames[++im] != "" ) {
    TObject *obj = mfrtmp->findObject(mnames[im].Data());
    if (!obj) {
     // Warning("fitBi4",Form("Can't find item='%s' in the frame2!\n",names[i].Data()));
      cout<<"non trovato\n";
      continue;
    }
    if (msigns[im]=="data")    mleg->AddEntry(obj,msigns[im],"pe");
    else mleg->AddEntry(obj,msigns[im],"l");
  }
  mleg->Draw("same");

  tmp->Print( ( outname + "Mass.pdf" ).c_str() );
  tmp->Print( ( outname + "Mass.png" ).c_str() );


//per i dati sarebbe da mettere "lep"


  /* *****************************
     FIT DELLE DISTANZE
     ***************************** */

//fisso costanti le variabili già fittate
  rmass.setConstant( kTRUE );
  widt1.setConstant( kTRUE );
  widt2.setConstant( kTRUE );
  gfrac.setConstant( kTRUE );
  //  SigNum.setConstant( kTRUE );
  //  BkgNum.setConstant( kTRUE );

//variabili per i bkg, decadimenti a destra->R e Q e a sinistra -> L

  RooRealVar RBkgComb ("RBkgComb", "combinatorial Bkg life, Right side" , 0.031, 0.0, 0.5, "cm");
  RooRealVar LBkgComb ("LBkgComb", "combinatorial Bkg life, Left side"  , 0.001 , 0.0, 0.5, "cm");
  RooRealVar QBkgComb ("QBkgComb", "combinatorial Bkg life, Q tail side", 0.002, 0.0, 0.5, "cm");

  //vita del segnale
  RooRealVar SigLife( "SigLife", "Signal Life" , 0.044, 0.0, 0.1, "cm" );

  //variabili per la gaussiana della risoluzione
  RooRealVar ResoMean  ( "ResoMean",  "Distance Res Mean"  ,   0.0,     0.0, 0.01, "cm" );
  RooRealVar Resolution( "Resolution","Distance Resolution", 0.00161, 0.00001,  0.1, "cm" );
  ResoMean.setConstant( kTRUE );
  
  //variabili per il Prompt bkg
  RooRealVar PMean  ( "PMean",  "Prompt Mean" ,   0.0,     0.0, 0.005, "cm" );
  RooRealVar PWidth ( "PWidth", "Prompt width", 0.005, 0.00001, 0.005, "cm" );
  RooRealVar PFrac  ( "PFrac",  "Prompt Core Fraction", 0.5, 0.0, 1.0, "." );
  if( setMean ) PMean.setConstant( kTRUE );

  //frazioni del bkg R e Q sono quelle degli esponenziali B e' quella del prompt
  RooRealVar BFrac( "BFrac", "Bkg fraction"       , 0.5, 0.0, 1.0, "." );
  RooRealVar QFrac( "QFrac", "Bkg fraction q tail", 0.5, 0.0, 1.0, "." );
  RooRealVar RFrac( "RFrac", "Bkg fraction right ", 0.5, 0.0, 1.0, "." );

  RooRealVar Trig1Mean ( "Trig1Mean",  "Trig1 Res Mean"  ,  0.0059802,     0.0, 0.02, "cm" );
  RooRealVar Trig1Reso ( "Trig1Reso",  "Trig1 Resolution",  0.0027234, 0.00001,  0.1, "cm" );
  RooRealVar Trig1Comb ( "Trig1Comb",  "Trig1 expo"      ,     0.6691,     0.0,    1, "cm");
  RooRealVar Trig12Mean ( "Trig12Mean",  "Trig12 Res Mean"  ,  0.0055209,     0.0, 0.02, "cm" );
  RooRealVar Trig12Reso ( "Trig12Reso",  "Trig12 Resolution",  0.0032537, 0.00001,  0.1, "cm" );
  RooRealVar Trig12Comb ( "Trig12Comb",  "Trig12 expo"      ,     0.6678,     0.0,    1, "cm");

  Trig1Mean.setConstant( kTRUE );
  Trig1Reso.setConstant( kTRUE );
  Trig1Comb.setConstant( kTRUE );
  Trig12Mean.setConstant( kTRUE );
  Trig12Reso.setConstant( kTRUE );
  Trig12Comb.setConstant( kTRUE );

  //distribuzione gaussiana della risoluzione per la convoluzione
  RooGaussModel ResoGauss( "ResoGauss", "Distance Resolution Gaussian", d, ResoMean, Resolution );

  //distribuzioni dei decadimenti con convoluzione della gaussiana
  
  // distribuzione decadimento del segnale e sua efficienza
  RooDecay SigExpo ( "SigExpo",  "Signal Convolved Decay",    d, SigLife , ResoGauss, RooDecay::SingleSided );
  //efficienza senza trigger
  RooPolynomial EffPol( "EffPol", "Efficiency Distribution",  d, RooArgList( be, ce ) );
  //efficienza con i trigger
  RooGaussModel Trig1Gauss( "Trig1Gauss", "Trig1 Resolution Gaussian", d, Trig1Mean, Trig1Reso );
  RooDecay      Trig1Expo ( "Trig1Expo", "Trig 1 Efficiency",  d, Trig1Comb, Trig1Gauss, RooDecay::SingleSided );
  RooGaussModel Trig12Gauss( "Trig12Gauss", "Trig12 Resolution Gaussian", d, Trig12Mean, Trig12Reso );
  RooDecay      Trig12Expo ( "Trig12Expo" , "Trig 12 Efficiency",  d, Trig12Comb, Trig12Gauss, RooDecay::SingleSided );



 //distribuzioni dei decadimenti esponenziali di fondo con convoluzione della gaussiana
  RooDecay RBkgExpo( "RBkgExpo", "Right Bk Convolved Decay",  d, RBkgComb, ResoGauss, RooDecay::SingleSided );
  RooDecay LBkgExpo( "LBkgExpo", "Left Bk Convolved Decay",   d, LBkgComb, ResoGauss, RooDecay::Flipped     );
  RooDecay QBkgExpo( "QBkgExpo", "Q tail Bk Convolved Decay", d, QBkgComb, ResoGauss, RooDecay::SingleSided );

  //prompt distribution
  RooGaussian CoreGauss( "CoreGauss", "Prompt Core Distribution", d, PMean , Resolution ); 
  RooGaussian TailGauss( "TailGauss", "Prompt Tail Distribution", d, PMean , PWidth     );
  RooAddPdf PromptGauss( "PromptGauss", "Convolved Tails sum", RooArgList( CoreGauss, TailGauss ), PFrac );

  //sommo i decadimenti tra loro per i modelli
  RooAddPdf RLBkgExpo  ("RLBkgExpo", "Convolved Right and left Bkg"  , RooArgList( RBkgExpo  , LBkgExpo), RFrac );
  RooAddPdf R2BkgExpo  ("R2BkgExpo", "Convolved Right 2 Bkg"         , RooArgList( RBkgExpo  , QBkgExpo), RFrac );
  RooAddPdf RQBkgExpo  ("RQBkgExpo", "Convolved Right 2 and left Bkg", RooArgList( RBkgExpo , QBkgExpo,  LBkgExpo), 
                                                                       RooArgList( RFrac , QFrac));
  //unisco al bkg il prompt gaussiano
  RooAddPdf RLTotDecay ("RLTotDecay", "Combin Total Decay right left"  , RooArgList( RLBkgExpo ,  CoreGauss ), BFrac );
//RooAddPdf RLTotDecay ("RLTotDecay", "Combin Total Decay right left"  , RooArgList( RLBkgExpo , PromptGauss), BFrac );

  RooAddPdf RQTotDecay ("RQTotDecay", "Combin Total Decay 2 right left", RooArgList( RQBkgExpo ,  CoreGauss  ), BFrac );
//RooAddPdf RQTotDecay ("RQTotDecay", "Combin Total Decay 2 right left", RooArgList( RQBkgExpo ,  PromptGauss), BFrac );

  RooAddPdf R2TotDecay ("R2TotDecay", "Combin Total Decay right 2     ", RooArgList( R2BkgExpo ,  CoreGauss   ), BFrac );
//RooAddPdf R2TotDecay ("R2TotDecay", "Combin Total Decay right 2     ", RooArgList( R2BkgExpo , PromptGauss  ), BFrac );

  //costruisco il modello per fit 2d
  //prodotto di segnale con efficienza e gaussiane di massa
  
  RooProdPdf Signalt0( "Signalt0", "Signal 2D", RooArgSet( GaussSum, SigExpo, EffPol    ) );
  RooProdPdf Signalt1( "Signalt1", "Signal 2D", RooArgSet( GaussSum, SigExpo, Trig1Expo ) );
  RooProdPdf Signalt2( "Signalt2", "Signal 2D", RooArgSet( GaussSum, SigExpo, Trig12Expo) );

  RooProdPdf* SigPtr;
  if (tr==0) SigPtr=&Signalt0;
  if (tr==1) SigPtr=&Signalt1;
  if (tr==2) SigPtr=&Signalt2;

  //RooProdPdf Signal *SigPtr;
  //RooProdPdf Signal( "Signal", "Signal 2D", RooArgSet( GaussSum, SigExpo, *SigPtr ) );
   RooProdPdf Signal( "Signal", "Signal 2D", RooArgSet( GaussSum, SigExpo, EffPol ) );
  //prodotto di modello del fondo e polinomio delle masse
  RooProdPdf RLBkg ( "RLBkg", "2D bkg right left"  , RooArgSet( polyn  , RLTotDecay ) );
  RooProdPdf RQBkg ( "RQBkg", "2D bkg right 2 left", RooArgSet( polyn  , RQTotDecay ) );
  RooProdPdf R2Bkg ( "R2Bkg", "2D bkg right 2"     , RooArgSet( polyn  , R2TotDecay ) );

  
  RooExtendPdf ExtendedSignal2D ( "ExtendedSignal2D", "ExtendedSignal2D", Signal, SigNum);
  RooExtendPdf RLExtendedBackgr ( "RLExtendedBackgr", "RLExtendedBackgr", RLBkg , BkgNum);
  RooExtendPdf RQExtendedBackgr ( "RQExtendedBackgr", "RQExtendedBackgr", RQBkg , BkgNum);
  RooExtendPdf R2ExtendedBackgr ( "R2ExtendedBackgr", "R2ExtendedBackgr", R2Bkg , BkgNum);

  RooAddPdf ModelRL ("ModelRL", "Signal + bkg right left"  , RooArgList( ExtendedSignal2D , RLExtendedBackgr ));
  RooAddPdf ModelRQ ("ModelRQ", "Signal + 2 right left "   , RooArgList( ExtendedSignal2D , RQExtendedBackgr ));
  RooAddPdf ModelR2 ("ModelR2", "Signal + right 2 "        , RooArgList( ExtendedSignal2D , R2ExtendedBackgr ));

  //taglio un pezzo dei dati per fittare il fondo
  TString MassCut = "m>5.5||m<5.3";
  TString DistCut = "d>-0.005";

  d.setRange("central", dmin, dbkg );
  d.setRange("lowDist", dmin, -0.01 );

// RooAbsData* SideData = wdata.reduce( MassCut );
  RooAbsData* SideData = data->reduce( MassCut );
  RooAbsData* SideData2 =SideData ->reduce( DistCut );

  RooAbsData* TempDist = SideData;
  RooAbsData* TempDist2 = SideData2;
  Bool_t Ext = kFALSE;

//prima di fittare il modello con due a destra e uno a sinistra faccio un fit 
//sul modello con due a destra
//condividono gli stessi parametri quindi in questo modo ottengo dei buoni valori iniziali
//e posso anche bloccare il valore dell'efficienza
 

/* ***************

   FIT DEL FONDO 

   ************** */

 oo<<"************ PRIMA DEI FIT ************"<<std::endl;
   oo<<"SigLife: "<<SigLife.getVal() <<std::endl;
   oo<<"ResoMean : "<<ResoMean.getVal() <<' '<<"Resolution : "<<Resolution.getVal() <<std::endl;
   oo<<"PMean : "<<PMean.getVal() <<' '<<"PWidth : "<<PWidth.getVal() <<std::endl;

   oo<<"RFrac : "<<RFrac.getVal() <<' '<<"QFrac : "<<QFrac.getVal() <<std::endl;
   oo<<"BFrac : "<<BFrac.getVal() <<' '<<"PFrac : "<<PFrac.getVal() <<std::endl;
  
   oo<<"RBkgComb : "<<RBkgComb.getVal() <<' '<<"QBkgComb : "<<QBkgComb.getVal() <<std::endl;
   oo<<"LBkgComb : "<<LBkgComb.getVal() <<std::endl;
   oo<<"widt1 : "<<widt1.getVal() <<' '<<"widt2 : "<<widt2.getVal() <<std::endl;
   oo<<"rmass : "<<rmass.getVal()  <<' '<<"gfrac : "<<gfrac.getVal() <<std::endl;
   oo<<"coef1 : "<<coef1.getVal() <<' '<<"coef2 : "<<coef2.getVal() <<std::endl;
   oo<<"SigNum : "<<SigNum.getVal() <<' '<<"BkgNum : "<<BkgNum.getVal() <<std::endl;


  // RLTotDecay.fitTo( *TempDist, Range("highMass, lowMass"), Extended( kFALSE ));
  R2TotDecay.fitTo( *TempDist2, Range("highMass, lowMass"), Extended( kFALSE ));
  if ( setReso ) Resolution.setConstant( kTRUE );
  if ( setFrac )      BFrac.setConstant( kTRUE );
   
  RBkgComb.setConstant( kTRUE );
  QBkgComb.setConstant( kTRUE );
TCanvas* t4d = new TCanvas( "t4d", outname.c_str(), 800, 600 );
  t4d->SetLeftMargin( 0.15 );
  t4d->cd();
 
  d.setBins( dbin );
  RooPlot* dfrtm4 = d.frame();
 
  TempDist2->plotOn(dfrtm4);
  t4d->SetLogy();

 //RLTotDecay.plotOn( dfrtm2 );
 //R2TotDecay.plotOn( dfrtm2 );
  R2TotDecay.plotOn( dfrtm4 , LineColor( cbkg ) );
  //dfrtm4->Draw();

  dfrtm4->SetTitle("");
  dfrtm4->Draw();
 

  cout << "dframe objects:\n";
  for (int i=0; i<dfrtm4->numItems(); i++) {
    TString obj_name=dfrtm4->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());
  }

TString bnames[] = {
    "h_dataset",
    "R2TotDecay_Norm[d]_Range[fit_nll_R2TotDecay_dataset_highMass,fit_nll_R2TotDecay_dataset_ lowMass]_NormRange[fit_nll_R2TotDecay_dataset_highMass,fit_nll_R2TotDecay_dataset_ lowMass]",
    ""
  };

  TString bsigns[] = {
    "data",
    "Background",
  };

  TLegend* bleg = new TLegend(0.6,0.65,0.80,0.80);
  Int_t bi=-1;
  while ( mnames[++bi] != "" ) {
    TObject *obj = dfrtm4->findObject(bnames[bi].Data());
    if (!obj) {
     // Warning("fitBi4",Form("Can't find item='%s' in the frame2!\n",names[i].Data()));
      cout<<"non trovato\n";
      continue;
    }
    if (bsigns[bi]=="data")    bleg->AddEntry(obj,bsigns[bi],"pe");
    else bleg->AddEntry(obj,bsigns[bi],"l");
  }
  bleg->Draw("same");



  t4d->Print( ( outname + "prebkg.pdf" ).c_str() );
  t4d->Print( ( outname + "prebkg.png" ).c_str() );



 oo<<"************ DOPO FIT R2 ************"<<std::endl;
   oo<<"SigLife: "<<SigLife.getVal() <<std::endl;
   oo<<"ResoMean : "<<ResoMean.getVal() <<' '<<"Resolution : "<<Resolution.getVal() <<std::endl;
   oo<<"PMean : "<<PMean.getVal() <<' '<<"PWidth : "<<PWidth.getVal() <<std::endl;

   oo<<"RFrac : "<<RFrac.getVal() <<' '<<"QFrac : "<<QFrac.getVal() <<std::endl;
   oo<<"BFrac : "<<BFrac.getVal() <<' '<<"PFrac : "<<PFrac.getVal() <<std::endl;
  
   oo<<"RBkgComb : "<<RBkgComb.getVal() <<' '<<"QBkgComb : "<<QBkgComb.getVal() <<std::endl;
   oo<<"LBkgComb : "<<LBkgComb.getVal() <<std::endl;
   oo<<"widt1 : "<<widt1.getVal() <<' '<<"widt2 : "<<widt2.getVal() <<std::endl;
   oo<<"rmass : "<<rmass.getVal()  <<' '<<"gfrac : "<<gfrac.getVal() <<std::endl;
   oo<<"coef1 : "<<coef1.getVal() <<' '<<"coef2 : "<<coef2.getVal() <<std::endl;
   oo<<"SigNum : "<<SigNum.getVal() <<' '<<"BkgNum : "<<BkgNum.getVal() <<std::endl;

  RQTotDecay.fitTo( *TempDist, Range("highMass, lowMass"), Extended( kFALSE ));


 oo<<"************ DOPO FIT BKG ************"<<std::endl;
   oo<<"SigLife: "<<SigLife.getVal() <<std::endl;
   oo<<"ResoMean : "<<ResoMean.getVal() <<' '<<"Resolution : "<<Resolution.getVal() <<std::endl;
   oo<<"PMean : "<<PMean.getVal() <<' '<<"PWidth : "<<PWidth.getVal() <<std::endl;

   oo<<"RFrac : "<<RFrac.getVal() <<' '<<"QFrac : "<<QFrac.getVal() <<std::endl;
   oo<<"BFrac : "<<BFrac.getVal() <<' '<<"PFrac : "<<PFrac.getVal() <<std::endl;
  
   oo<<"RBkgComb : "<<RBkgComb.getVal() <<' '<<"QBkgComb : "<<QBkgComb.getVal() <<std::endl;
   oo<<"LBkgComb : "<<LBkgComb.getVal() <<std::endl;
   oo<<"widt1 : "<<widt1.getVal() <<' '<<"widt2 : "<<widt2.getVal() <<std::endl;
   oo<<"rmass : "<<rmass.getVal()  <<' '<<"gfrac : "<<gfrac.getVal() <<std::endl;
   oo<<"coef1 : "<<coef1.getVal() <<' '<<"coef2 : "<<coef2.getVal() <<std::endl;
   oo<<"SigNum : "<<SigNum.getVal() <<' '<<"BkgNum : "<<BkgNum.getVal() <<std::endl;


  TCanvas* t2d = new TCanvas( "t2d", outname.c_str(), 800, 600 );
  t2d->SetLeftMargin( 0.15 );
  t2d->cd();
 
  d.setBins( dbin );
  RooPlot* dfrtm2 = d.frame();
 
  TempDist->plotOn(dfrtm2);
  t2d->SetLogy();

 //RLTotDecay.plotOn( dfrtm2 );
 //R2TotDecay.plotOn( dfrtm2 );
   RQTotDecay.plotOn( dfrtm2, LineColor( cbkg ) );
  dfrtm2->Draw();

  dfrtm2->SetTitle("");
  dfrtm2->Draw();
 

  cout << "dframe objects:\n";
  for (int i=0; i<dfrtm2->numItems(); i++) {
    TString obj_name=dfrtm2->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());
  }

TString b2names[] = {
    "h_dataset",
    "RQTotDecay_Norm[d]_Range[fit_nll_RQTotDecay_dataset_highMass,fit_nll_RQTotDecay_dataset_ lowMass]_NormRange[fit_nll_RQTotDecay_dataset_highMass,fit_nll_RQTotDecay_dataset_ lowMass]",
    ""
  };

  TString b2signs[] = {
    "data",
    "Background",
  };

  TLegend* b2leg = new TLegend(0.6,0.65,0.80,0.80);
  Int_t b2i=-1;
  while ( mnames[++b2i] != "" ) {
    TObject *obj = dfrtm2->findObject(b2names[b2i].Data());
    if (!obj) {
     // Warning("fitBi4",Form("Can't find item='%s' in the frame2!\n",names[i].Data()));
      cout<<"non trovato\n";
      continue;
    }
    if (b2signs[b2i]=="data")    b2leg->AddEntry(obj,b2signs[b2i],"pe");
    else b2leg->AddEntry(obj,b2signs[b2i],"l");
  }
  b2leg->Draw("same");


  t2d->Print( ( outname + "bkg.pdf" ).c_str() );
  t2d->Print( ( outname + "bkg.png" ).c_str() );

  //setto costanti le  variabili già fittate
  
  ResoMean.setConstant( kTRUE );
  PFrac.setConstant( kTRUE );
  Resolution.setConstant( kTRUE );
  PWidth.setConstant( kTRUE );
  BFrac.setConstant( kTRUE );
  QFrac.setConstant( kTRUE );
  RFrac.setConstant( kTRUE );
  RBkgComb.setConstant( kTRUE );
  LBkgComb.setConstant( kTRUE );
  QBkgComb.setConstant( kTRUE );

  // ModelRL.fitTo( wdata, Extended( kTRUE ), SumW2Error(kTRUE),  ConditionalObservables( e ), Extended( kTRUE ));
  // ModelRQ.fitTo( wdata, Extended( kTRUE ), SumW2Error(kTRUE),  ConditionalObservables( e ), Optimise(1));
  // ModelR2.fitTo( wdata, Extended( kTRUE ), SumW2Error(kTRUE),  ConditionalObservables( e ), Extended( kTRUE ));

   ModelRQ.fitTo( *data, Extended( kTRUE ),  ConditionalObservables( e ), Optimize(0));
   //ModelR2.fitTo( *data, Extended( kTRUE ),  ConditionalObservables( e ), Optimize(0));
   //ModelRL.fitTo( *data, Extended( kTRUE ),  ConditionalObservables( e ), Optimize(0));

  
 
  
  
  



  TCanvas* c2d = new TCanvas( outname.c_str(), outname.c_str(), 800, 600 );
  c2d->SetLeftMargin( 0.15 );
  c2d->cd();
  c2d->SetLogy();
  d.setBins( dbin );
  RooPlot* dframe = d.frame();
 
  data->plotOn( dframe );
 

  
  
  /*
   ModelRL.plotOn(dframe, Components( "CoreGauss" ),LineStyle( kDashed ), LineColor( kRed ) );

   ModelRL.plotOn(dframe, Components( "RBkgExpo" ),LineStyle( kDashed ), LineColor( kBlue ) );
   ModelRL.plotOn(dframe, Components( "LBkgExpo" ),LineStyle( kDashed ), LineColor( kGreen ) );
   ModelRL.plotOn(dframe, Components( "Signal"   ),LineStyle( kDashed ), LineColor( kOrange ) );
   ModelRL.plotOn(dframe, Components( "RLTotDecay" ),LineStyle( kDashed ), LineColor( kMagenta ) );
  */

  
  //ModelRQ.plotOn(dframe, Components( "CoreGauss" ),LineStyle( kDashed ), LineColor( kRed ) );
  // ModelRQ.plotOn(dframe, Components( "RBkgExpo" ),LineStyle( kDashed ), LineColor( kBlue ) );
  //  ModelRQ.plotOn(dframe, Components( "LBkgExpo" ),LineStyle( kDashed ), LineColor( kGreen ) );
   ModelRQ.plotOn(dframe, Components( "Signal"   ),LineStyle( kDashed ), LineColor( csig ) );
   //ModelRQ.plotOn(dframe, Components( "RLTotDecay" ),LineStyle( kDashed ), LineColor( kMagenta ) );
   // ModelRQ.plotOn(dframe, Components( "QBkgExpo" ),LineStyle( kDashed ), LineColor( kViolet ) );
   ModelRQ.plotOn(dframe, Components( "RQTotDecay" ),LineStyle( kDashed ), LineColor( cbkg ) );

  
 
  /*
  ModelR2.plotOn(dframe, Components( "CoreGauss" ),LineStyle( kDashed ), LineColor( kRed ) );
  ModelR2.plotOn(dframe, Components( "PromptGauss" ),LineStyle( kDashed ), LineColor( kViolet ) );
  ModelR2.plotOn(dframe, Components( "RBkgExpo" ),LineStyle( kDashed ), LineColor( kBlue ) );
  ModelR2.plotOn(dframe, Components( "QBkgExpo" ),LineStyle( kDashed ), LineColor( kGreen ) );
   ModelR2.plotOn(dframe, Components( "Signal"   ),LineStyle( kDashed ), LineColor( kOrange ) );
  */



   oo<<"************ DOPO FIT FINALE ************"<<std::endl;
   oo<<"SigLife: "<<SigLife.getVal() <<std::endl;
   oo<<"ResoMean : "<<ResoMean.getVal() <<' '<<"Resolution : "<<Resolution.getVal() <<std::endl;
   oo<<"PMean : "<<PMean.getVal() <<' '<<"PWidth : "<<PWidth.getVal() <<std::endl;

   oo<<"RFrac : "<<RFrac.getVal() <<' '<<"QFrac : "<<QFrac.getVal() <<std::endl;
   oo<<"BFrac : "<<BFrac.getVal() <<' '<<"PFrac : "<<PFrac.getVal() <<std::endl;
  
   oo<<"RBkgComb : "<<RBkgComb.getVal() <<' '<<"QBkgComb : "<<QBkgComb.getVal() <<std::endl;
   oo<<"LBkgComb : "<<LBkgComb.getVal() <<std::endl;
   oo<<"widt1 : "<<widt1.getVal() <<' '<<"widt2 : "<<widt2.getVal() <<std::endl;
   oo<<"rmass : "<<rmass.getVal()  <<' '<<"gfrac : "<<gfrac.getVal() <<std::endl;
   oo<<"coef1 : "<<coef1.getVal() <<' '<<"coef2 : "<<coef2.getVal() <<std::endl;
   oo<<"SigNum : "<<SigNum.getVal() <<' '<<"BkgNum : "<<BkgNum.getVal() <<std::endl;


   ModelRQ.plotOn( dframe, LineColor( cmis ) );
   //ModelRL.plotOn( dframe,LineStyle( kDashed ), LineColor( kOrange ) );
   //ModelR2.plotOn( dframe,LineStyle( kDashed ), LineColor( kOrange ) );

  
  cout << "dframe objects:\n";
  for (int i=0; i<dframe->numItems(); i++) {
    TString obj_name=dframe->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());
  }

//questi sono tutti insieme
  TString names[] = {
    "h_dataset",
    "ModelRQ_Int[m]_Norm[d,m]_Comp[Signal]",
    "ModelRQ_Int[m]_Norm[d,m]_Comp[RQTotDecay]",
    "ModelRQ_Int[m]_Norm[d,m]",
    ""
  };

  TString signs[] = {
    "data",
    "Signal",
    "Background",
    "Total"
  };

  
  dframe->Draw();
  
  TLegend* leg = new TLegend(0.6,0.7,0.90,0.90);
  
Int_t i=-1;
  while ( names[++i] != "" ) {
    TObject *obj = dframe->findObject(names[i].Data());
    if (!obj) {
      Warning("fitBi4",Form("Can't find item='%s' in the frame2!\n",names[i].Data()));
      cout<<"non trovato\n";
      continue;
    }
    if (signs[i]=="data")    leg->AddEntry(obj,signs[i],"pe");
    else leg->AddEntry(obj,signs[i],"l");
  }
  leg->Draw("same");

  
  /*

  leg->AddEntry("data","Data", "P");
  leg->AddEntry("Signal",   "Signal", "l");
  leg->AddEntry("RQTotDecay",  "Background","l");
  leg->AddEntry("ModelRQ" , "Total", "l");
  leg->Draw("same");
  
  
  */






  wdata.Print() ;

  c2d->Print( ( outname + "2d.pdf" ).c_str() );
  c2d->Print( ( outname + "2d.png" ).c_str() );

  ofstream of ("Lifetime.txt", ios::app);
  ifstream emp ("Lifetime.txt", ios::app);

  
  bool isEmpty = emp.peek() == EOF;
  if (isEmpty){
    of<<"Resolution ";
    if (setReso) of<<"set    "; 
    else of<<"free    ";
    of<<"Fraction ";
    if (setFrac) of<<"set    "; 
    else of<<"free    ";
    of<<"Mean ";
    if (setMean) of<<"set    "; 
    else of<<"free    ";
    of<<endl<<endl;
  }

  of<<"Vertex: "<<outname<<"\t    Lifetime: "<<SigLife.getVal()<<" +/- "<<SigLife.getError()<<endl;
  ofstream of2 ("LifetimeData.txt", ios::app);
  of2<<SigLife.getVal()<<' '<<SigLife.getError()<<endl;

 ofstream of3 ("../../Lifetime.txt", ios::app);
  ifstream emp3 ("../../Lifetime.txt", ios::app);

  
  
  
    of3<<"Resolution ";
    if (setReso) of3<<"set    "; 
    else of3<<"free    ";
    of3<<"Fraction ";
    if (setFrac) of3<<"set    "; 
    else of3<<"free    ";
    of3<<"Mean ";
    if (setMean) of3<<"set    "; 
    else of3<<"free    ";
    of3<<endl;
 

  of3<<"Vertex: "<<outname<<"\t    Lifetime: "<<SigLife.getVal()<<" +/- "<<SigLife.getError()<<endl<<endl;
  ofstream of4 ("../../LifetimeData.txt", ios::app);
  of4<<SigLife.getVal()<<' '<<SigLife.getError()<<endl;



}






/* ******* OLD MODELS ***********

********** DA RIDEFINIRE ESPONENZILE DOPPIO IN CASO ************

  RooDecay DBkgExpo( "DBkgExpo", "Double Bk Convolved Decay", d, DBkgComb, ResoGauss, RooDecay::DoubleSided );


   RooAddPdf RLBkgExpo  ("RLBkgExpo", "Convolved Right and left Bkg",  RooArgList( RBkgExpo  , LBkgExpo), RFrac );
  RooAddPdf AlBkgExpo  ("AlBkgExpo", "Convolved All Bkg",             RooArgList( RLBkgExpo , DBkgExpo), DFrac );
  RooAddPdf AQBkgExpo  ("AQBkgExpo", "Convolved All Bkg + q tail",    RooArgList( RBkgExpo , QBkgExpo,  LBkgExpo, DBkgExpo), 
			                                              RooArgList( RFrac , QFrac , LFrac));
  RooAddPdf RQBkgExpo  ("RQBkgExpo", "Convolved Right 2 and left Bkg", RooArgList( RBkgExpo , QBkgExpo,  LBkgExpo), 
                                                                       RooArgList( RFrac , QFrac));

  RooAddPdf RDBkgExpo  ("RDBkgExpo", "Convolved Right and double Bkg", RooArgList( RBkgExpo  , DBkgExpo), RFrac );
  RooAddPdf R2BkgExpo  ("R2BkgExpo", "Convolved Right 2 Bkg"         , RooArgList( RBkgExpo  , QBkgExpo), RFrac );

  RooAddPdf Expo1GBkg  ("Expo1GBkg", "1 expo+ gauss bkg"   ,    RooArgList(RBkgExpo, BkgGauss), GFrac );

  
  RooAddPdf DSTotDecay ("DSTotDecay", "Combin Total Decay double side" , RooArgList( DBkgExpo  , PromptGauss), BFrac );
  // RooAddPdf RLTotDecay ("RLTotDecay", "Combin Total Decay right left"  , RooArgList( RLBkgExpo , PromptGauss), BFrac );
  RooAddPdf RLTotDecay ("RLTotDecay", "Combin Total Decay right left"  , RooArgList( RLBkgExpo ,  CoreGauss ), BFrac );
  RooAddPdf RQTotDecay ("RQTotDecay", "Combin Total Decay 2 right left", RooArgList( RQBkgExpo ,  CoreGauss ), BFrac );
  RooAddPdf RDTotDecay ("RDTotDecay", "Combin Total Decay right double", RooArgList( RDBkgExpo ,  CoreGauss ), BFrac );
   RooAddPdf R2TotDecay ("R2TotDecay", "Combin Total Decay right 2     ", RooArgList( R2BkgExpo ,  CoreGauss ), BFrac );
 //RooAddPdf R2TotDecay ("R2TotDecay", "Combin Total Decay right 2     ", RooArgList( R2BkgExpo , PromptGauss  ), BFrac );

  RooAddPdf AlTotDecay ("AlTotDecay", "Combin Total Decay all"         , RooArgList( AlBkgExpo , PromptGauss), BFrac );
  
//RooAddPdf AQTotDecay ("AQTotDecay", "Combin Total Decay all + q tail", RooArgList( AQBkgExpo , PromptGauss), BFrac );
   RooAddPdf AQTotDecay ("AQTotDecay", "Combin Total Decay all + q tail", RooArgList( AQBkgExpo , CoreGauss ), BFrac );


  RooAddPdf E1GTotDecay ("E1GTotDecay", "Combin expo gauss and prompt ", RooArgList( Expo1GBkg , PromptGauss), BFrac );

  RooProdPdf EffExp( "EffExp", "EffExp", RooArgSet( SigExpo, EffPol) );
  RooProdPdf Signal( "Signal", "Signal 2D", RooArgSet( GaussSum,EffExp ) );


  //costruisco il modello per fit 2d
  //RooProdPdf Signal( "Signal", "Signal 2D", RooArgSet( GaussSum, SigExpo, EffPol) );
  
  RooProdPdf DSBkg ( "DSBkg", "2D bkg double side" , RooArgSet( polyn  , DSTotDecay ) );
  RooProdPdf RLBkg ( "RLBkg", "2D bkg right left"  , RooArgSet( polyn  , RLTotDecay ) );
  RooProdPdf RQBkg ( "RQBkg", "2D bkg right 2 left", RooArgSet( polyn  , RQTotDecay ) );
  RooProdPdf RDBkg ( "RDBkg", "2D bkg right double", RooArgSet( polyn  , RDTotDecay ) );
  RooProdPdf R2Bkg ( "R2Bkg", "2D bkg right 2"     , RooArgSet( polyn  , R2TotDecay ) );
  RooProdPdf AlBkg ( "AlBkg", "2D bkg all"         , RooArgSet( polyn  , AlTotDecay ) );
  RooProdPdf AQBkg ( "AQBkg", "2D bkg all + q tail", RooArgSet( polyn  , AQTotDecay ) );
  RooProdPdf E1GBkg( "AQBkg",  "2D bkg expo gauss ", RooArgSet( polyn  , E1GTotDecay) );

  
  RooExtendPdf ExtendedSignal2D ( "ExtendedSignal2D", "ExtendedSignal2D", Signal, SigNum);
  RooExtendPdf DSExtendedBackgr ( "DSExtendedBackgr", "DSExtendedBackgr", DSBkg , BkgNum);
  RooExtendPdf RLExtendedBackgr ( "RLExtendedBackgr", "RLExtendedBackgr", RLBkg , BkgNum);
  RooExtendPdf RQExtendedBackgr ( "RQExtendedBackgr", "RQExtendedBackgr", RQBkg , BkgNum);
  RooExtendPdf RDExtendedBackgr ( "RDExtendedBackgr", "RDExtendedBackgr", RDBkg , BkgNum);
  RooExtendPdf R2ExtendedBackgr ( "R2ExtendedBackgr", "R2ExtendedBackgr", R2Bkg , BkgNum);
  RooExtendPdf AlExtendedBackgr ( "AlExtendedBackgr", "AlExtendedBackgr", AlBkg , BkgNum);
  RooExtendPdf AQExtendedBackgr ( "AQExtendedBackgr", "AQExtendedBackgr", AQBkg , BkgNum);
  RooExtendPdf E1GExtendedBackgr( "E1GExtendedBackgr","E1GExtendedBackgr", E1GBkg , BkgNum);

  RooAddPdf ModelDS ("ModelDS", "Signal + bkg double side" , RooArgList( ExtendedSignal2D , DSExtendedBackgr ));
  RooAddPdf ModelRL ("ModelRL", "Signal + bkg right left"  , RooArgList( ExtendedSignal2D , RLExtendedBackgr ));
  RooAddPdf ModelAl ("ModelAL", "Signal + bkg all"         , RooArgList( ExtendedSignal2D , AlExtendedBackgr ));
  RooAddPdf ModelAQ ("ModelAQ", "Signal + bkg all + q tail", RooArgList( ExtendedSignal2D , AQExtendedBackgr ));
  RooAddPdf ModelE1G("ModelE1G", "Signal + bkg expo gauss" , RooArgList( ExtendedSignal2D , E1GExtendedBackgr));
  RooAddPdf ModelRQ ("ModelRQ", "Signal + 2 right left "   , RooArgList( ExtendedSignal2D , RQExtendedBackgr ));
  RooAddPdf ModelRD ("ModelRD", "Signal + right double "   , RooArgList( ExtendedSignal2D , RDExtendedBackgr ));
  RooAddPdf ModelR2 ("ModelR2", "Signal + right 2 "        , RooArgList( ExtendedSignal2D , R2ExtendedBackgr ));

*/
