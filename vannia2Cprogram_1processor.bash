#!/bin/bash

for i in {1..200..50}; 
  do  
      $HOME/Dropbox/micromegas_3.6.9.2/DMSF2/mainObs $i ; 
#      rm mpsi$i.txt ; 
done

