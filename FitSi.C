
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"

void FitSi(){
//define data
//valori della ddp
const int n_punti = 20;
// valori della corrente

Float_t x[n_punti] = {300,340,360,380,400,420,440,460,480,500, 520, 540, 560, 580,600, 620,640,660,720,800};
Float_t y[n_punti] = { 0.001, 0.003, 0.004,0.006, 0.009, 0.014, 0.021, 0.03,0.046,0.066,0.095, 0.134,0.185,0.253,0.322,0.41,0.505,0.611,0.915,1.482};
Float_t ey[n_punti] = {0.00001,0.00003,0.00004,0.00006,0.00008,0.0001,0.0003,0.0004,0.0005,0.0005,0.0007,0.0009,0.003,0.004,0.004, 0.004,0.006,0.008};
Float_t ex[n_punti] = {11,12,13,13,14,14,15,16,16,17,17,18,18,19,19,20,20,21,23,25};


//crate graph
TGraphErrors *gr = new TGraphErrors(20, x, y, ex, ey);
gr->SetTitle("Diodo al Si");
gr->SetMarkerStyle(4);
gr->Draw("AP");
gr->GetXaxis()->SetTitle("Voltage (mV)");
gr->GetYaxis()->SetTitle("Current(mA)");

//define user fit function and fit
TF1 *f1 = new TF1("f1", "[0]*(exp(x/[1])-1)", 290, 580);
f1->SetParNames("I_0", "eta*V_T");


f1->SetParameter(0, 1e-3);
f1->SetParameter(1, 50);
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
     c1->SaveAs("fitSi.png");
c1->SetLogy();
c1->SetGrid();

}
