void DrawAngle(){
TCanvas *c=new TCanvas ("c","Test Canvas",1);
c->Divide(2,2);

c->cd(1);
TVirtualPad *c_1 = c->cd(1);
c_1->SetLogy();
svDist2Calc->Draw();

c->cd(2);
MCdist2d->Draw();
TVirtualPad *c_2 = c->cd(2);
c_2->SetLogy();

c->cd(3);
DiffMCAngle2d->Draw();

}
