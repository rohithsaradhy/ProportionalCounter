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
  G4NistManager* nist = G4NistManager::Instance();

  // Materials that are required...
  G4int ncomponents;
  G4String name;

  G4Material* Air = nist->FindOrBuildMaterial("G4_Galactic"); // Air G4_Galactic G4_AIR
  G4Material* Xe = nist->FindOrBuildMaterial("G4_Ar"); // Xenon G4_Xe; Krypton G4_Kr; Argon G4_Ar
  G4Material* CO2= nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE"); // Carbon Dioxide
  G4Material* Cu  = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* Mylar = 	nist->FindOrBuildMaterial("G4_MYLAR");
  G4Material* Ar = nist->FindOrBuildMaterial("G4_Ar");

  G4Element* Cr = nist->FindOrBuildElement("Cr");
	G4Element* Mn = nist->FindOrBuildElement("Mn");
	G4Element* Fe = nist->FindOrBuildElement("Fe");
	G4Element* Ni = nist->FindOrBuildElement("Ni");
  G4Element* Si = nist->FindOrBuildElement("Si");
  G4Element* C  = nist->FindOrBuildElement("C");




  G4double co2_percent, density,fractionmass;
  // Mixing CO2 with Ar
  co2_percent = 30; // percent of CO2 in the mixture.
  density = ((3994.8 + 4.062*co2_percent)/2240)*kg/m3; // calculating the density of the mixture of gases at stp.
  G4Material* Gas = new G4Material(name="ArCO2Mix",density,ncomponents=2);
  Gas->AddMaterial(CO2, fractionmass=co2_percent*perCent);
  Gas->AddMaterial(Ar, fractionmass=(100-co2_percent)*perCent);

  //Making stainless steel...
  G4Material* StainlessSteel = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
	StainlessSteel->AddElement(C, fractionmass=0.001);
	StainlessSteel->AddElement(Si, fractionmass=0.007);
	StainlessSteel->AddElement(Cr, fractionmass=0.18);
	StainlessSteel->AddElement(Mn, fractionmass=0.01);
	StainlessSteel->AddElement(Fe, fractionmass=0.712);
	StainlessSteel->AddElement(Ni, fractionmass=0.09);


  //Making the geometry now!

  //Making world volume
  G4double world_x = 50*cm;
  G4double world_y = 50*cm;
  G4double world_z = 50*cm;
  G4Box* worldBox = new G4Box("World", world_x,world_y,world_z);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Air,"World");
  G4double pos_x = 0.0*cm;
  G4double pos_y = 0.0*cm;
  G4double pos_z = 0.0*cm;
  G4VPhysicalVolume* World = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y,pos_z),worldLog,"PC_World",0,false,0);


// Setting up the detector .
  G4double innerRadius = 0.05*cm;
  G4double outerRadius = 1.*cm;

G4double hz = 10*cm;
  hz=hz/2;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

  G4Tubs* CounterTube
    = new G4Tubs("Gas_Counter",
                 innerRadius,
                 outerRadius,
                 hz,
                 startAngle,
                 spanningAngle);

  G4LogicalVolume* CounterLog = new G4LogicalVolume(CounterTube, Xe, "ProportionalCounter");

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


//Creating the cathode cylinder...

innerRadius = 1.*cm;
outerRadius = 1.1*cm;
G4Tubs* CuTube
  = new G4Tubs("Cu_Shell",
               innerRadius,
               outerRadius,
               hz,
               startAngle,
               spanningAngle);

G4LogicalVolume* CuTubeLog = new G4LogicalVolume(CuTube, Cu, "Cu_Shell Log");


G4VPhysicalVolume* CuTubePhys
  = new G4PVPlacement(0,                       // no rotation
                      G4ThreeVector(pos_x, pos_y, pos_z),
                                               // translation position
                      CuTubeLog,              // its logical volume
                      "Cu Shell Physical",               // its name
                      worldLog,                // its mother (logical) volume
                      false,                   // no boolean operations
                      0);


// Anode wire geometry

innerRadius = 0.*cm;
outerRadius = .05*cm;
G4Tubs* Anode
  = new G4Tubs("Anode",
               innerRadius,
               outerRadius,
               hz,
               startAngle,
               spanningAngle);

G4LogicalVolume* AnodeLog = new G4LogicalVolume(Anode, Cu, "Anode Log");


G4VPhysicalVolume* AnodePhys
  = new G4PVPlacement(0,                       // no rotation
                      G4ThreeVector(pos_x, pos_y, pos_z),
                                               // translation position
                      AnodeLog,              // its logical volume
                      "Anode Physical",               // its name
                      worldLog,                // its mother (logical) volume
                      false,                   // no boolean operations
                      0);


//Mylar Material!!!

innerRadius = 0.*cm;
outerRadius = 1*cm;
G4double thickness = 0.01*cm;
G4Tubs* Mylar1
  = new G4Tubs("Mylar1",
               innerRadius,
               outerRadius,
               thickness,
               startAngle,
               spanningAngle);

G4LogicalVolume* Mylar1Log = new G4LogicalVolume(Mylar1, Mylar, "Mylar1Log");

pos_z = -(hz+thickness);
G4VPhysicalVolume* Mylar1Phys
  = new G4PVPlacement(0,                       // no rotation
                      G4ThreeVector(pos_x, pos_y, pos_z),
                                               // translation position
                      Mylar1Log,              // its logical volume
                      "Mylar1Physical",               // its name
                      worldLog,                // its mother (logical) volume
                      false,                   // no boolean operations
                      0);
// Second Mylar
innerRadius = 0.*cm;
outerRadius = 1*cm;
thickness = 0.01*cm;
G4Tubs* Mylar2
  = new G4Tubs("Mylar2",
               innerRadius,
               outerRadius,
               thickness,
               startAngle,
               spanningAngle);

G4LogicalVolume* Mylar2Log = new G4LogicalVolume(Mylar2, Mylar, "Mylar2Log");

pos_z = +(hz+thickness);
G4VPhysicalVolume* Mylar2Phys
  = new G4PVPlacement(0,                       // no rotation
                      G4ThreeVector(pos_x, pos_y, pos_z),
                                               // translation position
                      Mylar2Log,              // its logical volume
                      "Mylar2Physical",               // its name
                      worldLog,                // its mother (logical) volume
                      false,                   // no boolean operations
                      0);









  fScoringVolume = CounterLog; // sending the logical volume.

  //
  //always return the physical World Volume
  //
  return World;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
