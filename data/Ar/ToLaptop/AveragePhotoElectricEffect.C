void AveragePhotoElectricEffect()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Apr 23 11:17:50 2017) by ROOT version6.06/02
   TCanvas *c1 = new TCanvas("c1", "c1",0,67,1920,979);
   c1->Range(-5.475,-0.0003198684,49.275,0.002878815);
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
   0.000433388,
   0.000414317,
   0.00102819,
   0.00170846,
   0.0021491,
   0.00233656,
   0.00230158,
   0.0021195,
   0.00189192,
   0.00164359,
   0.00141817,
   0.0012085,
   0.0010477,
   0.000903398,
   0.000781356,
   0.000674289,
   0.000594452,
   0.00051744,
   0.00045828,
   0.000406462,
   0.000363844,
   0.000328048,
   0.000299526,
   0.00026347,
   0.000248425,
   0.000230838,
   0.000208441,
   0.000196053,
   0.000184318,
   0.000172564,
   0.000163781,
   0.000152561,
   0.00014467,
   0.000137097,
   0.000135523,
   0.000122805,
   0.000115422,
   0.000115123,
   0.000112692};
   TGraph *graph = new TGraph(39,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle(" Average Energy Deposited due to Photo Electric Effect at Different Incident Energies");
   graph->SetFillColor(1);
   graph->SetLineColor(2);
   graph->SetLineWidth(4);
   graph->SetMarkerColor(4);
   graph->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1"," Average Energy Deposited due to Photo Electric Effect at Different Incident Energies",100,0,43.8);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(0.002558947);
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
   Graph_Graph1->GetYaxis()->SetTitle("Energy Deposited (MeV)");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.25);
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
   TText *AText = pt->AddText(" Average Energy Deposited due to Photo Electric Effect at Different Incident Energies");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
