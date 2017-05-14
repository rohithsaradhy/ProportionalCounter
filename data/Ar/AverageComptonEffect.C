void AverageComptonEffect()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Apr 23 11:25:48 2017) by ROOT version6.06/02
   TCanvas *c1 = new TCanvas("c1", "c1",0,67,1920,979);
   c1->Range(-5.475,-0.0123201,49.275,0.1108809);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[39] = {
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   13,
   14,
   15,
   16,
   17,
   18,
   19,
   20,
   21,
   22,
   23,
   24,
   25,
   26,
   27,
   28,
   29,
   30,
   31,
   32,
   33,
   34,
   35,
   36,
   37,
   38,
   39,
   40};
   Double_t Graph0_fy1[39] = {
   0.00051825,
   0.00939016,
   0.0326368,
   0.0896478,
   0.082291,
   0.0656118,
   0.0860769,
   0.0828266,
   0.0809875,
   0.0742916,
   0.0854653,
   0.0735275,
   0.0710022,
   0.0747684,
   0.0730332,
   0.068371,
   0.0744844,
   0.047732,
   0.058671,
   0.0440003,
   0.0452606,
   0.0349331,
   0.0358253,
   0.037629,
   0.0321322,
   0.0307879,
   0.0264093,
   0.0293393,
   0.0258264,
   0.0266377,
   0.0213537,
   0.0190114,
   0.0194733,
   0.0186835,
   0.020751,
   0.0199893,
   0.0116253,
   0.0107686,
   0.0117693};
   TGraph *graph = new TGraph(39,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle(" Average Energy Deposited due to Compton Effect at Different Incident Energies");
   graph->SetFillColor(1);
   graph->SetLineColor(4);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(3);
   graph->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1"," Average Energy Deposited due to Compton Effect at Different Incident Energies",100,0,43.8);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(0.09856075);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Incident Photon Energy (keV)");
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Energy Deposited (eV)");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.15,0.9342405,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText(" Average Energy Deposited due to Compton Effect at Different Incident Energies");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
