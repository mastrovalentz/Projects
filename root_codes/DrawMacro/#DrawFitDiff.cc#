void DrawDiff(){
TCanvas *c=new TCanvas ("c","Dist Canvas",1);
c->Divide(3,3);

c->cd(1);
TVirtualPad *c_1 = c->cd(1);
c_1->SetLogy();
DistDiff2->Draw();

c->cd(2);
TVirtualPad *c_2 = c->cd(2);
c_2->SetLogy();
DiffMCTrack2d->Draw();

c->cd(3);
TVirtualPad *c_3 = c->cd(3);
c_3->SetLogy();
DiffMCAngle2d->Draw();

c->cd(4);
TVirtualPad *c_4 = c->cd(4);
c_4->SetLogy();
DiffMCAllNoBs->Draw();

c->cd(5);
TVirtualPad *c_5 = c->cd(5);
c_5->SetLogy();
DiffMCAllTrk->Draw();

c->cd(6);
TVirtualPad *c_6 = c->cd(6);
c_6->SetLogy();
DiffMCRCNoBs->Draw();

c->cd(7);
TVirtualPad *c_7 = c->cd(7);
c_7->SetLogy();
DiffMCRCOnly->Draw();

c->cd(8);
TVirtualPad *c_8 = c->cd(8);
c_8->SetLogy();

c->cd(9);
TVirtualPad *c_9 = c->cd(9);
c_9->SetLogy();



}
