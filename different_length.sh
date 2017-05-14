#!/bin/bash
#Written by Rohith Saradhy 07-03-17
length=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) # in cm/2...

run1_mac="/home/devbot/Geant4_Workspace/PropCounter/run1.mac" #change line 31
event_file="/home/devbot/Geant4_Workspace/PropCounter/src/B1EventAction.cc" # ofstream out("/home/devbot/Geant4_Workspace/GermaniumDectector/data/Proton.txt"); @ line 61
constructor_file="/home/devbot/Geant4_Workspace/PropCounter/src/B1DetectorConstruction.cc" # changing the length of the detector
runAction_file="/home/devbot/Geant4_Workspace/PropCounter/src/B1RunAction.cc" #adding the length to the file

for len in "${length[@]}"
do

#echo $stable "stability"
#echo $chrge "-charge"
#echo $energ" MeV -energy"
#echo $mas"-Mass"
#echo $mu_src
#echo $run1_mac
#echo $event_file
#editing the source file
#sed -i '71s/.*/'"name, "$mas", 2.99598e-16*MeV,  +"$chrge"*eplus,"'/' $mu_src
#sed -i '75s/.*/'$stable", 2196.98*ns,             NULL,"'/' $mu_src
#gedit $mu_src
#editing the event file
mkdir /home/devbot/Geant4_Workspace/PropCounter/data/Ar/

file_name="/home/devbot/Geant4_Workspace/PropCounter/data/Ar/EnergyDeposited_at_Length="$len"cm.txt"
#echo $file_name

touch "$file_name"
sed -i '67s@.*@'"ofstream out(\""$file_name"\");"'@' $event_file
sed -i '120s@.*@'"G4double hz = $len*cm;"'@' $constructor_file
sed -i '51s@.*@'"double length = $len;"'@' $runAction_file
#gedit $event_file
#editing run1.mac file
# sed -i '28s/.*/'"\\/gun\\/energy "$energ" MeV"'/' $run1_mac
#gedit $run1_mac

# read -p "Press [Enter] key to start Continue..."
#cd /home/devbot/Softwares/G4.10.02.p01/geant4.10.02.p01_build
#make clean
#make -j 48
#make install
# read -p "Press [Enter] key to CONTINUE..."
cd  /home/devbot/Geant4_Workspace/PropCounter/
make -j48
exampleB1 run1.mac
#read -p "Press [Enter] key to start Continue..."





done
mv /home/devbot/Geant4_Workspace/PropCounter/test.txt /home/devbot/Geant4_Workspace/PropCounter/data/Ar/NumParticlesTransmitted
