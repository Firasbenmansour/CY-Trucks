#!/bin/bash

generate_histogram_d1() {

gnuplot <<EOF
reset
set size 1,1
set term pngcairo size 600,800 enhanced font 'arial,10'
set grid y
set datafile separator ";"
set style fill solid border -1
set boxwidth 1.5 relative
set xlabel "Conducteurs" rotate by 180 font '0,12' offset 0,-9 
set y2label "Distance (km)" font '0,12' offset 3,0
set ylabel "Conducteurs avec le plus de trajets" font '0,15' offset 4,0
set xtic rotate by 90 font '0,10' offset 0.5,-9.5
set ytic rotate by 90 font '0,11' offset 74,1
set style data histograms
set output 'images/histogramme_d1.png'
plot 'temp/donnees_traitement_d1.txt' using 2:xticlabels(1) notitle lc rgb "green"
EOF
convert images/histogramme_d1.png -rotate 90 images/histogramme_d1.png
} 





traitementD1() {
    # Récupération du nom du fichier CSV
    input_file="$1"
    
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    
    # Vérification si le fichier de cache existe
    cache_file="temp/donnees_traitement_d1.txt"
    if [ ! -f "$cache_file" ]; then
        # Extraction des noms de conducteurs et comptage des trajets uniques
        conducteurs_trajets=$(awk -F';' 'NR>1 {conducteurs[$6" "$2]++} END {for (cond in conducteurs) print conducteurs[cond], cond}' "$input_file" | sort -nr | head -n 10)
        echo "$conducteurs_trajets" | awk '{print $2, $3";", $1}'> "$cache_file"
    fi
    # Si le fichier existe, affichage de son contenu
    cat "$cache_file"
    
    # Calcul du temps d'exécution
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    generate_histogram_d1
    exit 0
}
