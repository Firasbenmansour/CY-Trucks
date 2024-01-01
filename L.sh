#!/bin/bash

input_file=$1

# Déclaration de la fonction
traitementL() {

    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    
    if [ -f "$input_file" ]; then
        echo "Le fichier existe"

        # Vérification que le fichier est un fichier CSV
        if [[ "$input_file" == *.csv ]]; then
            awk -F';' '{sum[$1]+=$5} END {for(i in sum) print i";"sum[i]}' "$input_file" > juste.sh
            sort -t';' -k2,2nr -k5,5nr juste.sh > ordre.sh
            head -11 ordre.sh > final.sh
            rm juste.sh ordre.sh
            
            cat final.sh
            
            # Calcul du temps d'exécution
            end_time=$(date +%s.%N)
            execution_time=$(echo "$end_time - $start_time" | bc)
            echo "Temps d'exécution : $execution_time secondes"
            exit 0
        else
            exit 1
        fi
    else 
        echo "le fichier n'existe pas"
    fi
    
    exit 0
}

