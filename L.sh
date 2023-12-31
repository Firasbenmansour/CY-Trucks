#!/bin/bash

input_files=$1

# Déclaration de la fonction
traitementL() {
    if [ -f "$input_files" ]; then
        echo "Le fichier existe"

        # Assurez-vous que le fichier est un fichier CSV
        if [[ "$input_files" == *.csv ]]; then
        awk -F';' '{sum[$1]+=$5} END {for(i in sum) print i";"sum[i]}' "$input_files" > juste.sh
        sort -t';' -k2,2nr -k5,5nr juste.sh > ordre.sh
        head -11 ordre.sh > final.sh
        rm juste.sh ordre.sh
        
        cat final.sh
        exit 0
        else
        exit 1
        fi
  else 
  echo "le fichier n'existe pas"
  fi
  
  }
  traitementL
