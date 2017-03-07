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
  Double_t a,b,c,d,e,x[19],y[19];
  int i=0,n=19;

  ifstream infile("NumParticlesTransmitted");



       while(!infile.eof())
          {
             infile >> a>>b>>c>>d;
            //  cout<<c<<endl;
            x[i]=a;
            y[i]=c/b;
            i++;
           }
        infile.close();
        for(i=0;i<19;i++)
        {
          cout<<x[i]<<"\t"<<y[i]<<endl;
        }

   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Transmission graph");
   gr->GetYaxis()->SetTitle("Transmission");
   gr->GetXaxis()->SetTitle("Detector Length (cm)");
   gr->Draw("ALP");
   gPad->Print("Transmission.png");

}
