#!/bin/bash

generer_histogramme_d1() {
gnuplot <<EOF
reset
set size 1,1
set term pngcairo size 600,800 enhanced font 'arial,10'
set grid y
set datafile separator ";"
set style fill solid noborder
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
    fichier_entree="data/data.csv"

    # Mesure du temps d'exécution
    temps_debut=$(date +%s.%N)
    
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$fichier_entree" ]; then
        echo "Le fichier '$fichier_entree' n'existe pas."
        exit 1
    fi
    
    fichier_cache="temp/donnees_traitement_d1.txt"
    
        # Extraction des noms de conducteurs et comptage des trajets uniques
    awk -F';' '
        NR>1{
             conducteurs[$6" "$2]++
            } 
        END {
        for (cond in conducteurs)
            print conducteurs[cond], cond
            }' "$fichier_entree" | sort -nr | head -n 10 | awk '{print $2, $3";", $1}' > "$fichier_cache"
    
     cat "$fichier_cache"
    
    # Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
    generer_histogramme_d1
    
}
