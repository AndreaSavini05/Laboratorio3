
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"

void FitGe(){
//define data
//valori della ddp

//valori della corrente

Float_t x[10] = {};
Float_t y[10] = {};
Float_t ex[10] = {};
Float_t ey[10] = {};

TCanvas *c1 = new TCanvas("c1", "Fit Diodo", 800, 600);
c1->SetLogy();
c1->SetGrid();

//crate graph
TGraphErrors *gr = new TGraphErrors(10, x, y, ex, ey);
gr->SetTitle("DIodo al Ge");

//draw
gr->SetMarkerStyle(4);
gr->Draw("AP");
gr->GetXaxis()->SetTitle("Voltage (eV)");
gr->GetYaxis()->SetTitle("Current(mA)");

//define user fit function and fit
TF1 *f1 = new TF1("f1", "[0]*(exp(x/[1])-1)", 400, 800);

f1->SetParameter(0, 3e-6);
f1->SetParameter(1, 50.);
f1->SetParName(0, "I0");
f1->SetParName(1, "Eta*V_T");
gStyle->SetOptFit(1111);
gr->Fit("f1", "R");
}
