void DrawPVDiff3d(){
TCanvas *c=new TCanvas ("c","Dist Canvas",1);
c->Divide(3,2);

c->cd(1);
TVirtualPad *c_1 = c->cd(1);
c_1->SetLogy();
PvMCTrkCalc3d->Draw();
    
c->cd(2);
TVirtualPad *c_2 = c->cd(2);
c_2->SetLogy();
PvMCAngCalc3d->Draw();

c->cd(3);
TVirtualPad *c_3 = c->cd(3);
c_3->SetLogy();
PvMCAllNoBs3d->Draw();
    
c->cd(4);
TVirtualPad *c_4 = c->cd(4);
c_4->SetLogy();
PvMCAllTrk3d->Draw();
    
c->cd(5);
TVirtualPad *c_5 = c->cd(5);
c_5->SetLogy();
PvMCRCNoBs3d->Draw();
    
c->cd(6);
TVirtualPad *c_6 = c->cd(6);
c_6->SetLogy();
PvMCRCOnly3d->Draw();
    
}

