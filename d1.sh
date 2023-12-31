#!/bin/bash

option1() {
    # Récupération du nom du fichier CSV
    input_file="$1"
    
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    
    # Vérification si le fichier de cache existe
    cache_file="temp/cache_conducteurs.txt"
    if [ ! -f "$cache_file" ]; then
        # Extraction des noms de conducteurs et comptage des trajets uniques
        conducteurs_trajets=$(awk -F';' 'NR>1 {conducteurs[$6]++} END {for (cond in conducteurs) print conducteurs[cond], cond}' "$input_file" | sort -nr | head -n 10)
        echo "$conducteurs_trajets" > "$cache_file"
    fi
    # Si le fichier existe, affichage de son contenu
    cat "$cache_file"
    
    # Calcul du temps d'exécution
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    
    exit 0
}
