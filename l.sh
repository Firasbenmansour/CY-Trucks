#!/bin/bash

generate_histogram_l() {
gnuplot <<EOF
reset
set term pngcairo size 800,600 enhanced font 'arial,10'
set title 'Les 10 trajets les plus longs' font '0,15'
set xlabel "Identifiants Trajets" font '0,12'
set ylabel "Distance (km)" font '0,12'
set datafile separator ";"
set style data histograms
set style fill solid border -1
set boxwidth 1.5 relative
set xtic rotate by 0 font '0,11'
set output 'images/histogramme_l.png'
plot 'temp/donnees_traitement_l.txt' using 2:xtic(1) lc rgb "red" notitle
EOF
}


traitementL() {
    input_file=$1
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    cache_file="temp/donnees_traitement_l.txt"
    if [ -f "$input_file" ]; then
        echo "Le fichier existe"

        # Vérification que le fichier est un fichier CSV
        if [[ "$input_file" == *.csv ]]; then
                LC_NUMERIC="C" awk -F';' 'NR>1{sum[$1]+=$5} 
        END {
        for(route in sum) {
            printf "%.3f %s\n", sum[route], route;
        }
        }' "$input_file" | LC_NUMERIC="C" sort -k1 -nr | head -n 10 | sort -k2 -nr | awk '{printf "%s;%s\n", $2, $1}' > "$cache_file"
            cat "$cache_file"
            generate_histogram_l
            # Calcul du temps d'exécution
            end_time=$(date +%s.%N)
            execution_time=$(echo "$end_time - $start_time" | bc)
            echo "Temps d'exécution : $execution_time secondes"
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
