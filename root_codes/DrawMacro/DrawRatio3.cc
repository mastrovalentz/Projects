void DrawRatio3(){
  TCanvas *c=new TCanvas ("c","Dist Canvas",1);
  c->Divide(2,2);
 
 c->cd(1);
  TH1F* rSAS=(TH1F*)hSimAcc->Clone();
  rSAS->Divide(hSim);
  rSAS->Rebin(4);
  rSAS->Scale(0.25);
  rSAS->Draw("histo");


  c->cd(2);
  TH1F* rSelSA=(TH1F*)hSel->Clone();
  rSelSA->Divide(hSimAcc);
  rSelSA->Rebin(4);
  rSelSA->Scale(0.25);
  rSelSA->Draw("histo");

  c->cd(3);
  TH1F* rSelRecSA=(TH1F*)hSelRec->Clone();
  rSelRecSA->Divide(hSimAcc);
  rSelRecSA->Rebin(4);
  rSelRecSA->Scale(0.25);
  rSelRecSA->Draw("histo");

  return;
}