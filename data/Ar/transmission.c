#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include <stdlib.h>
using namespace std;

bool is_file_exist(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}


void transmission()
{
  Double_t a,b,c,d,e,x[19],y[19],z[19];
  int i=0,n=20;

  ifstream infile("NumParticlesTransmitted");



       while(!infile.eof())
          {
             infile >> a>>b>>c>>d;
            //  cout<<c<<endl;
            x[i]=a;
            y[i]=c/b;
            z[i]=d/b;
            i++;
           }
        infile.close();
        for(i=0;i<19;i++)
        {
          cout<<x[i]<<"\t"<<y[i]<<endl;
        }


   TMultiGraph* mg = new TMultiGraph();

   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   mg->Add(gr);

   TGraph *gr1 = new TGraph(n,x,z);
   gr1->SetLineColor(4);
   gr1->SetLineWidth(4);
   gr1->SetMarkerColor(3);
   gr1->SetMarkerStyle(21);
   mg->Add(gr1);

   mg->Draw("ALP");
   mg->SetTitle("Transmission graph");
   mg->GetYaxis()->SetTitle("Transmission");
   mg->GetXaxis()->SetTitle("Detector Length (cm)");

   gPad->Print("Transmission.png");

}
