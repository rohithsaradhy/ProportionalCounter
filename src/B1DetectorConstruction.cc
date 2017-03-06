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
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Materials that are required...
  G4int ncomponents;
  G4String name;

  G4Material* Air = nist->FindOrBuildMaterial("G4_AIR"); // Air
  G4Material* Xe = nist->FindOrBuildMaterial("G4_Xe"); // Xenon
  G4Material* CO2= nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE"); // Carbon Dioxide
  G4Material* Ar = nist->FindOrBuildMaterial("G4_Ar"); // Argon

  G4double co2_percent, density,fractionmass;
  // Mixing CO2 with Ar
  co2_percent = 30; // percent of CO2 in the mixture.
  density = ((3994.8 + 4.062*co2_percent)/2240)*kg/m3; // calculating the density of the mixture of gases at stp.
  G4Material* Gas = new G4Material(name="ArCO2Mix",density,ncomponents=2);
  Gas->AddMaterial(CO2, fractionmass=co2_percent*perCent);
  Gas->AddMaterial(Ar, fractionmass=(100-co2_percent)*perCent);



  //Making the geometry now!

  //Making world volume
  G4double world_x = 100*cm;
  G4double world_y = 100*cm;
  G4double world_z = 100*cm;
  G4Box* worldBox = new G4Box("World", world_x,world_y,world_z);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Air,"World");
  G4double pos_x = 0.0*cm;
  G4double pos_y = 0.0*cm;
  G4double pos_z = 0.0*cm;
  G4VPhysicalVolume* World = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y,pos_z),worldLog,"Proportional Counter World",0,false,0);


  G4double innerRadius = 0.*cm;
  G4double outerRadius = 1.*cm;
  G4double hz = 5.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

  G4Tubs* CounterTube
    = new G4Tubs("Gas_Counter",
                 innerRadius,
                 outerRadius,
                 hz,
                 startAngle,
                 spanningAngle);

  G4LogicalVolume* CounterLog = new G4LogicalVolume(CounterTube, Xe, "Proportional  Counter");

   pos_x =  0.0*cm;
   pos_y =  0.0*cm;
   pos_z =  0.0*cm;

  G4VPhysicalVolume* CounterPhys
    = new G4PVPlacement(0,                       // no rotation
                        G4ThreeVector(pos_x, pos_y, pos_z),
                                                 // translation position
                        CounterLog,              // its logical volume
                        "Counter",               // its name
                        worldLog,                // its mother (logical) volume
                        false,                   // no boolean operations
                        0);










  fScoringVolume = CounterLog;

  //
  //always return the physical World Volume
  //
  return World;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
