#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include <stdlib.h>
// #include "limit.h"
using namespace std;
bool is_file_exist(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

void plot()
{
  string len[20];
  Double_t c;
  string temp,hist,filename,canvasname,canvas, histname,sav_file;

  ostringstream* convert  ;

  for(int i=2;i<21;i++)
  {
    len[i-2]=to_string(i);
  }

  TH1D * Hist[20];
  ifstream infile;
  for(int i=0;i<19;i++)
  {
     histname = "For Length = "+len[i];
     cout<<histname<<endl;
     filename="EnergyDeposited_at_Length="+len[i]+"cm.txt";
     hist = histname+";Deposited Energy in  MeV; Counts";
     Hist[i]= new TH1D(histname.c_str(),hist.c_str(),1000,-0.05,0.05);

  if(is_file_exist(filename.c_str()))
     {
       cout<<filename<<" FOUND!"<<endl;
       infile.open(filename.c_str());

       while(!infile.eof())
          {
             infile >> c;
            //  cout<<c<<endl;
             Hist[i]->Fill(c);

           }
        infile.close();
     }

    }


  TCanvas* can[20];
  for(i=0;i<19;i+=2)
  {

  canvasname = "Energy Deposited at length "+len[i]+" cm";
  canvas = canvasname+";Deposited Energy in  MeV; Counts";
  can[i] = new TCanvas(canvasname.c_str(),canvas.c_str(),800,600);

    // Hist[i]->Fit("landau");
    Hist[i]->Draw();
    gPad->SetLogy();

  canvasname+=".png";
  // can[i]->Print(canvasname.c_str());
  }
}
