void DrawFit( TH1F* histo, double xmin, double xmax){
 
  //TCanvas *c=new TCanvas ("c","Dist Angle Canvas",1);
  //c->Divide(1,2);

  TF1 *g1=new TF1("g1", "gaus", xmin, xmax);
  //TF1 *g2=new TF1("g2", "gaus", xmin, xmax);
  //DiffMCAngle2d->Fit(g1, "R");
  //PvMCAngCalc->Fit(g2, "R");
  
  histo->Fit(g1, "R");
  histo->Draw();
}
