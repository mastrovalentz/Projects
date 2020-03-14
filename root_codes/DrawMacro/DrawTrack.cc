void DrawTrack(){
TCanvas *c=new TCanvas ("c","Test Canvas",1);
c->Divide(2,2);

c->cd(1);
TVirtualPad *c_1 = c->cd(1);
c_1->SetLogy();
svDistance2->Draw();

c->cd(2);
MCdist2d->Draw();
TVirtualPad *c_2 = c->cd(2);
MCdist2d->Draw();

c->cd(3);
DiffMCTrack2d->Draw();
}
