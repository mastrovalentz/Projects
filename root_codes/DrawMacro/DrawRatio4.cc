void DrawRatio4(){

  TH1F *f=(TH1F*)hSel->Clone();
  int nBin=hSel->GetNbinsX();
  double e, s;
  for (int i=1; i<nBin; i++){
    if (hSimAcc->GetBinContent(i)!=0){
      e=hSel->GetBinContent(i)/hSimAcc->GetBinContent(i);
      s=sqrt(e*(1-e)/hSimAcc->GetBinContent(i));
    }
    else { e=0; s=0;}
    
    f->SetBinContent(i, e);
    f->SetBinError  (i, s);
  }
  f->Draw("e");
  
  return;
}
