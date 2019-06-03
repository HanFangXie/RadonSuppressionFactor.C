// this script is used to estimate the flowrate suppression of radon in the SN Demo tracker
// written by F Xie
// related work by F. Xie, X. R. Liu, J. Mott & R. Saakyan @ UCL HEP

#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TROOT.h>
using namespace std;

Double_t Suppression(Double_t *x, Double_t *par){
  Double_t fl = x[0];    //flowrate
  Double_t V_t = par[0];    //volume_tracker
  Double_t ratio_gt = par[1];    // ratio of activity gas over activity tracker
  Double_t lamda = par[2];    //decay_const_lamda
  Double_t f_s;    //factor of suppression
  f_s = (1+fl/(V_t*lamda))/(1+ratio_gt);    // equation
  return f_s;
 }

void flowSuppression(){
TF1 *f1 = new TF1("factor1",Suppression, 0, 35,3);
f1->SetParameter(0,15.2*1000);    //volume_tracker 15.2m^3 *1000 translate to litre
f1->SetParameter(1,0);    //assuming
f1->SetParameter(2,log(2)/(3.8235*24*60));    // radon half life T_1/2 3.8235 days, *24hours *60minuts, lamda=ln(2)/T_1/2
f1->SetLineColor(kRed);
f1->GetHistogram()->GetYaxis()->SetTitle("suppression factor");    //setting Y axis name
f1->GetHistogram()->GetXaxis()->SetTitle("flowrate / lpm");    //setting X axis name

TF1 *f2 = new TF1("factor2",Suppression, 0, 35,3);
f2->SetParameter(0,15.2*1000);    //volume_tracker 15.2m^3 *1000 translate to litre
f2->SetParameter(1,0.05);    //assuming
f2->SetParameter(2,log(2)/(3.8235*24*60));    // radon half life T_1/2 3.8235 days, *24hours *60minuts, lamda=ln(2)/T_1/2
f2->SetLineColor(kGreen+1);

TF1 *f3 = new TF1("factor3",Suppression, 0, 35,3);
f3->SetParameter(0,15.2*1000);    //volume_tracker 15.2m^3 *1000 translate to litre
f3->SetParameter(1,0.10);    //assuming
f3->SetParameter(2,log(2)/(3.8235*24*60));    // radon half life T_1/2 3.8235 days, *24hours *60minuts, lamda=ln(2)/T_1/2
f3->SetLineColor(kBlue);

TF1 *f4 = new TF1("factor4",Suppression, 0, 35,3);
f4->SetParameter(0,15.2*1000);    //volume_tracker 15.2m^3 *1000 translate to litre
f4->SetParameter(1,0.15);    //assuming
f4->SetParameter(2,log(2)/(3.8235*24*60));    // radon half life T_1/2 3.8235 days, *24hours *60minuts, lamda=ln(2)/T_1/2
f4->SetLineColor(kMagenta+1);

//draw plots
f1->Draw();
f2->Draw("SAME");
f3->Draw("SAME");
f4->Draw("SAME");  // draw the 4 funcs on the same plot

TLegend* leg = new TLegend(0.25,0.65,0.45,0.85);
leg->AddEntry(f1, "A_{G}/A_{T} = 0%", "l");
leg->AddEntry(f2, "A_{G}/A_{T} = 5%", "l");
leg->AddEntry(f3, "A_{G}/A_{T} = 10%", "l");
leg->AddEntry(f4, "A_{G}/A_{T} = 15%", "l");
leg->SetFillStyle(0);
leg->SetLineColor(0);
leg->Draw();
}
