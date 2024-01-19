#!/bin/bash
generate_histogram_t() {
gnuplot <<EOF
reset
set term pngcairo size 1280,720 enhanced font 'arial,10'
set title 'Les 10 villes les plus traversées' font '0,15'
set datafile separator ":"
set grid
set xlabel "Villes" font '0,12'
set ylabel "Nombres de trajets" font '0,12'
set style data histograms
set style histogram cluster gap 1
set style fill solid border -1
set xtic font '0,12'
set ytic font '0,12'
set boxwidth 1.5
set output 'images/histogramme_t.png'
plot 'temp/villes_triees_ordreAlpha.txt' using 2:xtic(1) title 'Total de trajet' lc rgb "spring-green", \
     "" using 3:x2tic(1) title 'Ville de départ' lc rgb "dark-green"
EOF
}
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
    awk -F';' '
    
    NR>1 {
        trip_count[$3]++;
        trip_count[$4]++;
        trip_departure[$3]++;
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
    generate_histogram_t
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    
}
