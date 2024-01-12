#!/bin/bash

generate_histogram() {
   gnuplot << EOF
    set terminal pngcairo enhanced font 'Arial,10'
    set output 'images/histogramme_l1.png'

    set xlabel 'l’identifiant du trajet'
    set ylabel ' la distance '

    # Setting up horizontal bars
    set style data boxes
    set style fill solid border -1
    set boxwidth 0.5

    # Rotate driver names for better readability and adjust range if necessary
    set ytics nomirror rotate by -45

    # Set xtics to auto-rotate if there are many labels, and adjust range if necessary
    set xtics rotate

    # Use 'using' to specify the axis: 2 for x-values (number of deliveries) and 1 for y-tics (driver names)
    plot 'temp/donnees_traitement_l.txt' using 3:xticlabels(1) with boxes notitle
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
            awk -F';' '{sum[$1]+=$5} END {for(i in sum) print i " ; " sum[i]}' "$input_file" | sort -t';' -k2,2nr -k5,5nr | head -10 > "$cache_file"
            
            cat "$cache_file"
            generate_histogram
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
