#!/bin/bash

# Chemin vers le fichier CSV sur votre machine Windows
csv_file="/home/sofack/Téléchargements/data.csv"

# Vérification de la présence du fichier CSV
if [ ! -f "$csv_file" ]; then
    echo "Le fichier CSV n'existe pas."
    exit 1
fi

# Extraction des noms des conducteurs et de leurs distances totales
awk -F ';' '/^[0-9]+/{conducteur=$2" "$3; distance[conducteur]+=$5} END{for (c in distance) print c, distance[c]}' "$csv_file" \
    | sort -k2 -n -r \
    | head -n 10 \
    > distances_conducteurs.txt
    echo "$distances_conducteurs.txt" | awk '{print $2, $3, $1}' > "$/home/Téléchargements/temp/distances_conducteurs.txt"

    # Si le fichier existe, affichage de son contenu
    cat "$/home/Téléchargements/temp/distances_conducteurs.txt"
    
    # Calcul du temps d'exécution
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    echo "Temps d'exécution : $execution_time secondes"
    exit 0

# Création du graphique avec GNUplot
gnuplot -persist <<EOF
set term png
set output 'histogramme_distances_conducteurs.png'
set style fill solid
set boxwidth 0.5
set ylabel "Conducteurs"
set xlabel "Distance totale parcourue"
set title "Top 10 des conducteurs avec la plus grande distance"
set ytics nomirror
set yrange [0:10]
plot 'distances_conducteurs.txt' using 2:0:xtic(1) with boxes
EOF

echo "Traitement terminé. Le graphique a été enregistré sous le nom 'histogramme_distances_conducteurs.png'."
mv histogramme_distance_conducteurs.png home/Téléchargements/temp
