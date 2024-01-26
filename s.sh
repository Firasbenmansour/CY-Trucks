#!/bin/bash

traitementS() {
    input_file="data/data.csv"
    dossier_temp="temp"  # Nom du dossier temporaire existant
    dossier_fichiers_c="fichiers_c"
    
    
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$input_file" ]; then
        echo "Le fichier '$input_file' n'existe pas."
        exit 1
    fi

    # Compilation du programme C
    gcc "$dossier_fichiers_c/calcul.c" "$dossier_fichiers_c/avl.c" "$dossier_fichiers_c/fonction.c" -o "$dossier_fichiers_c/s"

    # Exécution du programme et redirection de la sortie vers un fichier
    ./"$dossier_fichiers_c/s" > "$dossier_temp/50_Route_more_Distance_Range.txt"

    # Calcul du temps d'exécution
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
}

# Appel de la fonction de traitement
traitementT

