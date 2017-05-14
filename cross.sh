#!/bin/bash
#Written by Rohith Saradhy 07-03-17
energy=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 ) # in keV... 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40

run1_mac="/home/devbot/Geant4_Workspace/PropCounter/run1.mac" #change line 31
mkdir /home/devbot/Geant4_Workspace/PropCounter/data/Ar
file_name="/home/devbot/Geant4_Workspace/PropCounter/data/Ar/cross.txt"
touch "$file_name"
for energ in "${energy[@]}"
do


sed -i '19s/.*/'"\\/gun\\/energy "$energ" keV"'/' $run1_mac
exampleB1 run1.mac

phot=$(<phot_energ)
compt=$(<compt_energ)
tot=$(<tot_energ)

if [ ! -f  phot_energ ]; then
  phot='0'
fi
if [ ! -f  compt_energ ]; then
  compt='0'
fi
if [ ! -f  tot_energ ]; then
  tot='0'
fi


echo -e $energ "\t" $phot "\t" $compt "\t" $tot >> $file_name
rm phot_energ
rm compt_energ
rm tot_energ

done
