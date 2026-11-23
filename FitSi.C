
#include <iostream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"

void FitSi() {

    const int n_punti = 20;
    Float_t x[n_punti]  = {300, 340, 360, 380, 400, 420, 440, 460, 480, 500, 520, 540, 560, 580, 600, 620, 640, 660, 720, 800};
    Float_t y[n_punti]  = {0.001, 0.003, 0.004, 0.006, 0.009, 0.014, 0.021, 0.030, 0.046, 0.066, 0.095, 0.134, 0.185, 0.253, 0.322, 0.410, 0.505, 0.611, 0.915, 1.482};
    Float_t ey[n_punti] = {0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.003, 0.003, 0.003, 0.003, 0.004, 0.004, 0.004, 0.006, 0.008};
    Float_t ex[n_punti] = {10, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 40, 40};

    TCanvas *c1 = new TCanvas("c1", "Fit Diodo Si", 800, 600);
    c1->SetLogy();
    c1->SetGrid();
    gStyle->SetOptFit(1111);

    TGraphErrors *gr = new TGraphErrors(n_punti, x, y, ex, ey);
    gr->SetTitle("Diodo al Si;Voltage (mV);Current (mA)");
    gr->SetMarkerStyle(4);

    
    double x_split = 580.0;

    TF1 *f1 = new TF1("f1", "1e-6 * [0] * (exp(x/[1]) - 1)", 300, x_split);
    f1->SetParNames("I_ (mA) [e-6]", "eta*V_T (mV)");
    f1->SetParameters(1.0, 45.0);
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);

    TF1 *f2 = new TF1("f2", "1e-4 * [0] * (exp(x/[1]) - 1)", x_split, 800);
    f2->SetParNames("I_0 [e-4]", "eta*V_T");
    f2->SetParameters(1.0, 80.0);
    f2->SetLineColor(kRed);
    f2->SetLineWidth(2);

    gr->Fit(f1, "R");
    gr->Fit(f2, "R+");

    std::cout << "\n--- RISULTATI FIT 1 (300 - 560 mV) ---" << std::endl;
    std::cout << "I_0 [e-6] : " << f1->GetParameter(0) << " +/- " << f1->GetParError(0) << " mA" << std::endl;
    std::cout << "eta*V_T   : " << f1->GetParameter(1) << " +/- " << f1->GetParError(1) << " mV" << std::endl;
    std::cout << "Chi2 / ndf: " << f1->GetChisquare() << " / " << f1->GetNDF() << std::endl;

    std::cout << "\n--- RISULTATI FIT 2 (560 - 800 mV) ---" << std::endl;
    std::cout << "I_0 [e-4] : " << f2->GetParameter(0) << " +/- " << f2->GetParError(0) << " mA" << std::endl;
    std::cout << "eta*V_T   : " << f2->GetParameter(1) << " +/- " << f2->GetParError(1) << " mV" << std::endl;
    std::cout << "Chi2 / ndf: " << f2->GetChisquare() << " / " << f2->GetNDF() << std::endl;
    std::cout << "--------------------------------------\n" << std::endl;


    gr->Draw("AP");
    c1->Update();
    c1->SaveAs("fitSi.png");
}

