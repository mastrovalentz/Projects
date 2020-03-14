void DrawRatio(){

  TH1F* rRS=(TH1F*)hRec->Clone();
  rRS->Divide(hSim);
  rRS->Draw("histo");
  rRS->Rebin(4);
  rRS->Scale(0.25);

  TH1F* rRA=(TH1F*)hRec->Clone();
  rRA->Divide(hAll);
  rRA->Draw("histo");
  rRA->Rebin(4);
  rRA->Scale(0.25);

  TH1F* rAS=(TH1F*)hAll->Clone();
  rAS->Divide(hSim);
  rAS->Draw("histo");
  rAS->Rebin(4);
  rAS->Scale(0.25);

  TH1F* rSelS=(TH1F*)hSel->Clone();
  rSelS->Divide(hSim);
  rSelS->Draw("histo");
  rSelS->Rebin(4);
  rSelS->Scale(0.25);

  TH1F* rSelRecS=(TH1F*)hSelRec->Clone();
  rSelRecS ->Divide(hSim);
  rSelRecS->Draw("histo");
  rSelRecS->Rebin(4);
  rSelRecS->Scale(0.25);
  return;
}
