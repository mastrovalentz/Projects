void frac (double binw){
   double start=MCdist2d->GetXaxis()->FindBin(0.0);
   double stop =MCdist2d->GetXaxis()->GetLast();
   
   TCanvas *c=new TCanvas ("c","Rapp Canvas",1);
   c->Divide(3,2);

   int N=(stop-start)/binw;
   double x[N], ytrk[N], yang[N], yANB[N], yAll[N], yRCN[N], yRCo[N];
   double nonzero=0.0;
   for (int i=0; i<=N; i++)
   {
     x[i]=i+0.5;
     double mc_int  = MCdist2d    ->Integral(start+binw*i, start+binw*(i+1));
     double ang_int = svDist2Calc ->Integral(start+binw*i, start+binw*(i+1));
     double trk_int = svDistance2 ->Integral(start+binw*i, start+binw*(i+1));
     double ANB_int = DistAllNoBs ->Integral(start+binw*i, start+binw*(i+1));
     double All_int = DistAllTrk  ->Integral(start+binw*i, start+binw*(i+1));
     double RCN_int = DistRCNoBs  ->Integral(start+binw*i, start+binw*(i+1));
     double RCo_int = DistRCOnly  ->Integral(start+binw*i, start+binw*(i+1));

     if(mc_int!=0){
       ytrk[i]=trk_int/mc_int;
       yang[i]=ang_int/mc_int;
       yANB[i]=ANB_int/mc_int;
       yAll[i]=All_int/mc_int;
       yRCN[i]=RCN_int/mc_int;
       yRCo[i]=RCo_int/mc_int;
     }
     else {
       ytrk[i]=0;
       yang[i]=0;
       yANB[i]=0;
       yAll[i]=0;
       yRCN[i]=0;
       yRCo[i]=0;     
     }
     if (yang[i]>0.02) nonzero=x[i];

   }
   
   
   c->cd(1);
   TGraph* gr1 = new TGraph(N,x,ytrk);
   gr1->SetTitle("ratio track MC");
   gr1->Draw("AC*");

   c->cd(2);
   TGraph* gr2 = new TGraph(N,x,yang);
   gr2->SetTitle("ratio angle MC");
   gr2->Draw("AC*");
   
   c->cd(3);
   TGraph* gr3 = new TGraph(N,x,yANB);
   gr3->SetTitle("ratio AllNoBs MC");
   gr3->Draw("AC*");

   c->cd(4);
   TGraph* gr4 = new TGraph(N,x,yAll);
   gr4->SetTitle("ratio AllTrk MC");
   gr4->Draw("AC*");

   c->cd(5);
   TGraph* gr5 = new TGraph(N,x,yRCN);
   gr5->SetTitle("ratio RCNoBs MC");
   gr5->Draw("AC*");

   c->cd(6);
   TGraph* gr6 = new TGraph(N,x,yRCo);
   gr6->SetTitle("ratio RCOnly MC");
   gr6->Draw("AC*");


   //   TF1 *f1 =new TF1 ("f1", "[0]+[1]*exp([2]*x)", 0, nonzero);
   //   gr1->Fit(f1, "R");
   return;
}