#include <iostream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"

void FitGe() {
    // 1. Dati sperimentali
    Float_t x[15]  = {50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 200, 250, 300, 400};
    Float_t y[15]  = {0.002, 0.004, 0.006, 0.009, 0.013, 0.017, 0.024, 0.031, 0.039, 0.050, 0.064, 0.169, 0.334, 0.575, 1.142};
    Float_t ey[15] = {0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.003, 0.003, 0.004, 0.007};
    Float_t ex[15] = {7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 9, 10, 10, 20};

    // 2. Creazione Canvas e Grafico
    TCanvas *c1 = new TCanvas("c1", "Fit Diodo", 800, 600);
    c1->SetLogy();
    c1->SetGrid();
    gStyle->SetOptFit(1111);

    TGraphErrors *gr = new TGraphErrors(15, x, y, ex, ey);
    gr->SetTitle("Diodo al Ge;Voltage (mV);Current (mA)");
    gr->SetMarkerStyle(4);

    // 3. Definizione funzioni (nomi univoci: "f1" e "f2")
    TF1 *f1 = new TF1("f1", "1e-3 * [0] * (exp(x/[1]) - 1)", 48, 110);
    f1->SetParNames("I_0 (mA) [10^(-3)]", "eta*V_T (mV)");
    f1->SetParameters(1.0, 29.0);
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);

    TF1 *f2 = new TF1("f2", "[0] * (exp(x/[1]) - 1)", 110, 400);
    f2->SetParNames("I_0", "eta*V_T");
    f2->SetParameters(1e-3, 50.0); // Stima iniziale per la seconda regione
    f2->SetLineColor(kRed);
    f2->SetLineWidth(2);

    // 4. Esecuzione dei due fit
    gr->Fit(f1, "R");
    gr->Fit(f2, "R+");

    // 5. Stampa risultati (puoi aggiungere anche f2 nello stesso modo)
    std::cout << "\n--- RISULTATI FIT 1 (48 - 120 mV) ---" << std::endl;
    std::cout << "I_0 [e-3] : " << f1->GetParameter(0) << " +/- " << f1->GetParError(0) << " mA" << std::endl;
    std::cout << "eta*V_T   : " << f1->GetParameter(1) << " +/- " << f1->GetParError(1) << " mV" << std::endl;
    std::cout << "Chi2 / ndf: " << f1->GetChisquare() << " / " << f1->GetNDF() << std::endl;
    std::cout << "-------------------------------------\n" << std::endl;

    // 6. Disegno e salvataggio finale
    gr->Draw("AP");
    c1->Update();
    c1->SaveAs("fitGe.png");
}

