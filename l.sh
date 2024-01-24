#!/bin/bash

generer_histogramme_l() {
gnuplot <<EOF
reset
set term pngcairo size 800,600 enhanced font 'arial,10'
set title 'Les 10 trajets les plus longs' font '0,15'
set xlabel "Identifiants Trajets" font '0,12'
set ylabel "Distance (km)" font '0,12'
set datafile separator ";"
set style data histograms
set style fill solid noborder
set boxwidth 1.5 relative
set xtic rotate by 0 font '0,11'
set output 'images/histogramme_l.png'
plot 'temp/donnees_traitement_l.txt' using 2:xtic(1) lc rgb "red" notitle
EOF
}


traitementL() {
    fichier_entree="data/data.csv"
    
    # Mesure du temps d'exécution
    temps_debut=$(date +%s.%N)
    
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$fichier_entree" ]; then
        echo "Le fichier '$fichier_entree' n'existe pas."
        exit 1
    fi
    
    # Vérification si le fichier de cache existe
    fichier_cache="temp/donnees_traitement_l.txt"
    if [ -f "$fichier_entree" ]; then
        echo "Le fichier existe"

        # Vérification que le fichier est un fichier CSV
        if [[ "$fichier_entree" == *.csv ]]; then
            LC_NUMERIC="C" awk -F';' 'NR>1{sum[$1]+=$5} 
            END {
                for(route in sum) {
                    printf "%.3f %s\n", sum[route], route;
                }
            }' "$fichier_entree" | LC_NUMERIC="C" sort -k1 -nr | head -n 10 | sort -k2 -nr | awk '{printf "%s;%s\n", $2, $1}' > "$fichier_cache"
            
            cat "$fichier_cache"
            generer_histogramme_l
            
            # Calcul du temps d'exécution
            temps_fin=$(date +%s.%N)
            temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
            echo "Temps d'exécution : $temps_execution secondes"
            
            exit 0
        else
            exit 1
        fi
    else 
        echo "Le fichier n'existe pas"
    fi
    
    exit 0
}

#verivier les allocations
