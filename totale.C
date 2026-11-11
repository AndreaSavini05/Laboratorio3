
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"



void totale() {
    // 1. Crei il Canvas
    TCanvas *c1 = new TCanvas("c1", "Confronto Serie Diodo", 800, 600);

    Float_t x[15] = {50,60,70,80,90,100,110,120,130,140,150,200,250,300,400};
Float_t y[15] = { 0.002,0.004, 0.006, 0.009, 0.013, 0.017,0.024,0.031,0.039,0.05,0.064,0.169,0.334,0.575,1.142};
Float_t ey[15] = {0.00001,0.00004,0.00004,0.00006,0.00007,0.00009,0.0003,0.0003,0.0004,0.0004,0.0005,0.001,0.003,0.004,0.007};
Float_t ex[15] = {7,7,7,7,8,8,8,8,8,8,8,9,10,11,19};
    
    TGraphErrors *ge1 = new TGraphErrors(16, x, y, ex, ey);
    ge1->SetMarkerStyle(21);        // Quadrato
    ge1->SetMarkerColor(kBlue);     // Colore Blu
    ge1->SetLineColor(kBlue);

Float_t x1[20] = {300,340,360,380,400,420,440,460,480,500, 520, 540, 560, 580,600, 620,640,660,720,800};
Float_t y1[20] = { 0.001, 0.003, 0.004,0.006, 0.009, 0.014, 0.021, 0.03,0.046,0.066,0.095, 0.134,0.185,0.253,0.322,0.41,0.505,0.611,0.915,1.482};
Float_t ey1[20] = {0.00001,0.00003,0.00004,0.00006,0.00008,0.0001,0.0003,0.0004,0.0005,0.0005,0.0007,0.0009,0.003,0.004,0.004, 0.004,0.006,0.008};
Float_t ex1[20] = {11,12,13,13,14,14,15,16,16,17,17,18,18,19,19,20,20,21,23,25};


    
    TGraphErrors *ge2 = new TGraphErrors(20, x1, y1, ex1, ey1);
    ge2->SetMarkerStyle(20);        // Cerchio
    ge2->SetMarkerColor(kRed);      // Colore Rosso
    ge2->SetLineColor(kRed);

    // 4. CREAZIONE DEL MULTIGRAPH
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Confronto Misure Diodo;Tensione V (mV);Corrente I (mA)");
    
    // Aggiungi i singoli grafici al MultiGraph
    mg->Add(ge1, "P"); // "P" indica di disegnare i marker dei punti
    mg->Add(ge2, "P");

    // 5. DISEGNA IL TUTTO
    // "A" dice a ROOT di disegnare gli assi basandosi sul range globale di entrambi i grafici
    mg->Draw("A"); 


    //c1->SetLogy();
c1->SetGrid();
    // 6. Aggiorna e salva automaticamente
    c1->SaveAs("confronto_punti.png");

}
