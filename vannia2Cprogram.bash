#!/bin/bash

for i in {4..57..20}; 
  do  
      err="err".$i ;
      out="out".$i ;
      qsub -N mainObs$i -b y -e $err -q gen.q -wd $HOME/micromegas_4.1.7/NuMod $HOME/micromegas_4.1.7/NuMod/mainObs.c $i ; 
#      rm mpsi$i.txt ; 
done

