#!/bin/bash

generate_histogram() {
   gnuplot << EOF
    set terminal pngcairo enhanced font 'Arial,10'
    set output 'images/histogramme_conducteurs.png'

    set xlabel 'Nombre de trajets'
    set ylabel 'Conducteurs'

    # Setting up horizontal bars
    set style data boxes
    set style fill solid border -1
    set boxwidth 0.5

    # Rotate driver names for better readability and adjust range if necessary
    set ytics nomirror rotate by -45

    # Set xtics to auto-rotate if there are many labels, and adjust range if necessary
    set xtics rotate

    # Use 'using' to specify the axis: 2 for x-values (number of deliveries) and 1 for y-tics (driver names)
    plot 'temp/cache_conducteurs.txt' using 3:xticlabels(1) with boxes notitle
EOF
}




traitementD1() {
    # Récupération du nom du fichier CSV
    input_file="$1"
    
    # Mesure du temps d'exécution
    start_time=$(date +%s.%N)
    
    # Vérification si le fichier de cache existe
    cache_file="temp/cache_conducteurs.txt"
    if [ ! -f "$cache_file" ]; then
        # Extraction des noms de conducteurs et comptage des trajets uniques
        conducteurs_trajets=$(awk -F';' 'NR>1 {conducteurs[$6]++} END {for (cond in conducteurs) print conducteurs[cond], cond}' "$input_file" | sort -nr | head -n 10)
        echo "$conducteurs_trajets" | awk '{print $2, $3, $1}' > "$cache_file"
    fi
    # Si le fichier existe, affichage de son contenu
    cat "$cache_file"
    
    # Calcul du temps d'exécution
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    generate_histogram
    exit 0
}
