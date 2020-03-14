void DrawRatio2(){
  TCanvas *c=new TCanvas ("c","Dist Canvas",1);
  c->Divide(2,2);
 
 c->cd(1);
  TH1F* rRS=(TH1F*)hRec->Clone();
  rRS->Divide(hSim);
  rRS->Rebin(4);
  rRS->Scale(0.25);
  rRS->Draw("histo");

  c->cd(2);
  TH1F* rAS=(TH1F*)hAll->Clone();
  rAS->Divide(hSim);
  rAS->Rebin(4);
  rAS->Scale(0.25);
  rAS->Draw("histo");

  c->cd(3);
  TH1F* rSelS=(TH1F*)hSel->Clone();
  rSelS->Divide(hSim);
  rSelS->Rebin(4);
  rSelS->Scale(0.25);
  rSelS->Draw("histo");

  c->cd(4);
  TH1F* rSelRecS=(TH1F*)hSelRec->Clone();
  rSelRecS ->Divide(hSim);
  rSelRecS->Rebin(4);
  rSelRecS->Scale(0.25);
  rSelRecS->Draw("histo");

  return;
}
