#include <iostream>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TAxis.h>

void Calibrazione() {

    const int n_punti = 5;

    // Variabile indipendente X (Multimetro)
    double v_multi[n_punti]  = {}; 
    // Variabile dipendente Y (Oscilloscopio)
    double v_oscill[n_punti] = {}; 
    
    //non so se vanno messe
    double x_err[n_punti]    = {};  
    // Incertezze sulle Y (le tue incertezze su V_oscill)
    double y_err[n_punti]    = {}; 



    TGraphErrors *graph = new TGraphErrors(n_punti, v_multi, v_oscill, x_err, y_err);
    graph->SetTitle("Calibrazione Oscilloscopio;Tensione Multimetro V_{multi} [V];Tensione Oscilloscopio V_{oscill} [V]");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kBlack);

 

    TF1 *fit_func = new TF1("fit_func", "[0] + [B]*x", 0, 6);
    
    // Rinominiamo i parametri per chiarezza nella legenda delle statistiche
    fit_func->SetParNames("A (Intercetta)", "B (coefficiente angolare)");

    //  "S" per salvare i risultati completi

    graph->Fit(fit_func, "S");


    double A  = fit_func->GetParameter(0);
    double dA = fit_func->GetParError(0);
    double B  = fit_func->GetParameter(1);
    double dB = fit_func->GetParError(1);
    double chi2 = fit_func->GetChisquare();
    int ndf     = fit_func->GetNDF();

    std::cout << "\n--- RISULTATI DEL FIT IN TERMINALE ---" << std::endl;
    std::cout << "Intercetta (A): " << A << " +/- " << dA << " V" << std::endl;
    std::cout << "Pendenza   (B): " << B << " +/- " << dB << std::endl;
    std::cout << "Chi2 / ndf    : " << chi2 << " / " << ndf << std::endl;
    std::cout << "--------------------------------------\n" << std::endl;


    TCanvas *c1 = new TCanvas("c1", "Calibrazione", 800, 600);
    c1->SetGrid();

    // Disegna i punti ("AP" = Aggiungi assi, disegna Punti) 
    // e la funzione di fit sopra ("SAME")
    graph->Draw("AP");
    fit_func->SetLineColor(kBlue);
    fit_func->SetLineWidth(2);
    fit_func->Draw("SAME");
}
