#!/bin/bash

input_file="data.csv"
traitementT() {
    dossier_temp="temp"  # Nom du dossier temporaire existant

    # Vérification de l'existence du fichier CSV
    if [ ! -f "$input_file" ]; then
        echo "Le fichier '$input_file' n'existe pas."
        exit 1
    fi

    # Utilisation d'AWK pour préparer les données et les enregistrer dans le dossier temporaire
    awk -F';' 'BEGIN { 
        PROCINFO["sorted_in"]="@ind_str_asc"  # for consistent traversal order
    }
    NR>1 {
        trip_count[$3]++;
        trip_departure[$3]++;
        trip_count[$4]++;
    }
    END {
        for (city in trip_count) {
            print city":", trip_count[city]" trajets, "trip_departure[city]" départs";
        }
    }' "$input_file" > "$dossier_temp/donnees_preparees.txt"
    # (sort donnees_preparees.txt | uniq -d) pour verifier que y'a pas des doublants

}
