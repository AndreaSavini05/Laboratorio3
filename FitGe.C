#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"

void FitGe(){
//define data
//valori della ddp

//valori della corrente

Float_t x[15] = {50,60,70,80,90,100,110,120,130,140,150,200,250,300,400};
Float_t y[15] = { 0.002,0.004, 0.006, 0.009, 0.013, 0.017,0.024,0.031,0.039,0.05,0.064,0.169,0.334,0.575,1.142};
Float_t ey[15] = {0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.002,0.003,0.003,0.004,0.007};
Float_t ex[15] = {7,7,7,7,8,8,8,8,8,8,8,9,10,10,20};


//crate graph
TGraphErrors *gr = new TGraphErrors(15, x, y, ex, ey);
gr->SetTitle("Diodo al Ge");
gr->SetMarkerStyle(4);
gr->Draw("AP");
gr->GetXaxis()->SetTitle("Voltage (mV)");
gr->GetYaxis()->SetTitle("Current(mA)");

//define user fit function and fit
TF1 *f1 = new TF1("f1", "1e-3* [0]*(exp(x/[1])-1)", 48, 120);
//TF1 *f1 = new TF1("f1", "[0]*(-log([1]) + log(x))", 0, 0.098);
f1->SetParNames("I_0 [e-3]","eta*V_T");


f1->SetParameter(0, 1e-3);
f1->SetParameter(1, 29);
gStyle->SetOptFit(1111);

gr->Fit(f1, "R");



double A  = f1->GetParameter(0);
double dA = f1->GetParError(0);
double B  = f1->GetParameter(1);
 double dB = f1->GetParError(1);
double chi2 = f1->GetChisquare();
 int ndf     = f1->GetNDF();

std::cout << "\n--- RISULTATI DEL FIT IN TERMINALE ---" << std::endl;
   std::cout << "I_0 : " << A << " +/- " << dA << " V" << std::endl;
   std::cout << "eta*V_T   : " << B << " +/- " << dB << std::endl;
  std::cout << "Chi2 / ndf    : " << chi2 << " / " << ndf << std::endl;
std::cout << "--------------------------------------\n" << std::endl;


TCanvas *c1 = new TCanvas("c1", "Fit Diodo", 800, 600);

    gr->Draw("AP");
   f1->SetLineColor(kBlue);
   f1->SetLineWidth(2);
   f1->Draw("SAME");
     c1->SaveAs("fitGe.png");
c1->SetLogy();
c1->SetGrid();

}
