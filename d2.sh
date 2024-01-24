#!/bin/bash
generer_histogramme_d2() {
gnuplot <<EOF
reset
set size 1,1
set term pngcairo size 600,800 enhanced font 'arial,10'
set grid y
set datafile separator ";"
set style fill solid noborder
set boxwidth 1.5 relative
set locale 'fr_FR.UTF-8'  # Set the locale to one that uses a comma as a decimal separator
set format y "%.f" 
set xlabel "Conducteurs" rotate by 180 font '0,12' offset 0,-9 
set y2label "Distance (km)" font '0,12' offset 3,0
set ylabel "Conducteurs et la plus grande distance" font '0,15' offset 4,0
set xtic rotate by 90 font '0,10' offset 0.5,-9.5
set ytic rotate by 90 font '0,11' offset 74,1
set style data histograms
set output 'images/histogramme_d2.png'
plot 'temp/donnees_traitement_d2.txt' using 2:xticlabels(1) notitle lc rgb "blue"
EOF
convert images/histogramme_d2.png -rotate 90 images/histogramme_d2.png
}



traitementD2() {
    # Récupération du nom du fichier CSV
    fichier_entree="data/data.csv"
    
    # Mesure du temps d'exécution
    temps_debut=$(date +%s.%N)
    
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$fichier_entree" ]; then
        echo "Le fichier '$fichier_entree' n'existe pas."
        exit 1
    fi

    # Vérification si le fichier de cache existe
    fichier_cache="temp/donnees_traitement_d2.txt"
    if [ ! -f "$fichier_cache" ]; then
        # Extraction des noms des conducteurs et de leurs distances totales
        LC_NUMERIC="C" awk -F';' 'NR>1{distance[$6] += $5} 
        END {
            for (conducteur in distance) {
                printf "%.3f %s\n", distance[conducteur], conducteur;
            }
        }' "$fichier_entree" | LC_NUMERIC="C" sort -k1 -nr | head -n 10 | awk '{print $2, $3";", $1}'> "$fichier_cache"
    fi

    # Si le fichier existe, affichage de son contenu
    cat "$fichier_cache"

    # Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"

    generer_histogramme_d2

    exit 0
}
