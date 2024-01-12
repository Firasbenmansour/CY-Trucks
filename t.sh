#!/bin/bash


traitementT() {
    input_file="data.csv"
    dossier_temp="temp"  # Nom du dossier temporaire existant
    dossier_fichiers_c="fichiers_c"
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
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
            printf("%s : %d : %d\n", city, trip_count[city], trip_departure[city]);
        }
    }' "$input_file" > "$dossier_temp/donnees_traitement_t.txt"
    # (sort donnees_preparees.txt | uniq -d) pour verifier que y'a pas des doublants
    # Calcul du temps d'exécution
    gcc "$dossier_fichiers_c/t_avl_nbTrajets.c" "$dossier_fichiers_c/ville.c" -o "$dossier_fichiers_c/t_AVL_nbTrajets" 
    ./"$dossier_fichiers_c/t_AVL_nbTrajets" > "$dossier_temp/villes_triees_nbTrajets.txt"
    
    head -n 10 "$dossier_temp/villes_triees_nbTrajets.txt" >"$dossier_temp/Top10_villes.txt"
    
    gcc "$dossier_fichiers_c/t_avl_ordreAlpha.c" "$dossier_fichiers_c/ville.c" -o "$dossier_fichiers_c/t_AVL_ordreAlpha"
    ./"$dossier_fichiers_c/t_AVL_ordreAlpha" > "$dossier_temp/villes_triees_ordreAlpha.txt"
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    
}
