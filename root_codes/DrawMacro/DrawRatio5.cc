void DrawRatio5(TH1F *h11, TH1F* h21, int r=1){
  
  TH1F *h1=(TH1F*)h11->Clone();
  TH1F *h2=(TH1F*)h21->Clone();

  h1->Rebin(r);
  h2->Rebin(r);
  TH1F *f=(TH1F*)h1->Clone();
  int nBin=h1->GetNbinsX();
  double e, s;
  for (int i=1; i<nBin; i++){
    if (h2->GetBinContent(i)!=0){
      e=h1->GetBinContent(i)/h2->GetBinContent(i);
      s=sqrt(e*(1-e)/h2->GetBinContent(i));
    }
    else { e=0; s=0;}
    
    f->SetBinContent(i, e);
    f->SetBinError  (i, s);
  }
  f->Draw("esame");
  
  return;
}
