//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
// #include "temp_data.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "B1RunAction.hh"
#include<iostream>
#include<fstream>


using namespace std;

ifstream getter1;
ofstream saver1;
string process;
double data;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//G4double total_energy = 0;

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  int NumParticles;
  if (!fScoringVolume) {
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // check if we are in scoring volume


  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

    // G4Track* aTrack = step->GetTrack();

  if(step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "Mylar1Physical" && step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PC_World"
  )
  {

    getter1.open("NumParticles.txt");
    getter1>>NumParticles;
    getter1.close();
    NumParticles++;
    // G4cout<<"Particle Escaped, Total jailbreaks are now \t"<<NumParticles<<endl;
    saver1.open("NumParticles.txt");
    saver1<<NumParticles;
    saver1.close();
  } // adding the number of particles passed through



  G4Track* aTrack = step->GetTrack();
   const G4ParticleDefinition* part = aTrack->GetDefinition();

  //  if(aTrack->GetCurrentStepNumber()==1)
  //  {
   //
  //    cout<<"Particle that is coming is \t"<<part->GetPDGEncoding()<<endl;
  //  }

   if(part->GetPDGEncoding() == 11&& step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "Counter")
   {
     if(aTrack->GetCurrentStepNumber()==1)
     {
      //  cout<<"Electron has come out \t"<<part->GetPDGEncoding()<<endl;
       saver1.open("Numelectrons.txt");
       saver1<<1;
       saver1.close();
     }

   } //getting electrons ejected!

   if(aTrack->GetParentID() == 0)
   {
     process = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
     //G4cout<<process<<G4endl;
     if(process == "phot")
     {
       data =0;
       getter1.open("phot");
       getter1>>data;
       getter1.close();
       data++;
       saver1.open("phot");
       saver1<<data;
       saver1.close();
      //  Saving energy deposited by Photo-electric effect
       data =0;
       getter1.open("phot_energ");
       getter1>>data;
       getter1.close();
       data+= step->GetTotalEnergyDeposit();
       saver1.open("phot_energ");
       saver1<<data;
       saver1.close();

     }


     if(process == "compt")
     {
       data =0;
       getter1.open("compt");
       getter1>>data;
       getter1.close();
       data++;
       saver1.open("compt");
       saver1<<data;
       saver1.close();
       data =0;
       getter1.open("compt_energ");
       getter1>>data;
       getter1.close();
       data+= step->GetTotalEnergyDeposit();
       saver1.open("compt_energ");
       saver1<<data;
       saver1.close();

     }

     data=0;
     getter1.open("tot_energ");
     getter1>>data;
     getter1.close();
     data+=step->GetTotalEnergyDeposit();
     saver1.open("tot_energ");
     saver1<<data;
     saver1.close();

    }

    if (volume != fScoringVolume) return;

    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();

    //total_energy+=edepStep;
    //G4cout<<"Energy Deposited: "<<edepStep<<" StepLength: "<<step->GetStepLength()<<" Total Energy:"<<total_energy<<G4endl;
    fEventAction->AddEdep(edepStep);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
