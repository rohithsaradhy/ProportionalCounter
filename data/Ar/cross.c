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


void cross()
{
  Double_t a,b,c,d,e,x[100],y[100],z[100];
  int i=0,n=39;

  ifstream infile("cross.txt");



       while(!infile.eof())
          {
             infile >>a>>b>>c>>d;
            //  cout<<c<<endl;
            x[i]=a;
            y[i]=b/100000;
            z[i]=c/100000 * 1000000;
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
  // gr->Draw("ALP");
   
	 

   TGraph *gr1 = new TGraph(n,x,z);
   gr1->SetLineColor(4);
   gr1->SetLineWidth(4);
   gr1->SetMarkerColor(3);
   gr1->SetMarkerStyle(21);
   gr1->Draw("ALP");
   gr1->SetTitle(" Average Energy Deposited due to Compton Effect at Different Incident Energies");
   gr1->GetYaxis()->SetTitle("Energy Deposited (eV)");
   gr1->GetXaxis()->SetTitle("Incident Photon Energy (keV)");

   
  // gPad->SetTitle("Energy Deposited due to Photo Electric Effect at Different Incident Energies for 100k photons");
   //gPad->GetYaxis()->SetTitle("Energy Deposited in MeV");
   //gPad->GetXaxis()->SetTitle("Incident Photon Energy in keV");

   //gPad->Print("cross.png");

}
