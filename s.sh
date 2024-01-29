#!/bin/bash
generer_histogramme_s() {
gnuplot <<EOF
set term pngcairo size 1280,720 enhanced font 'arial,10'
set datafile separator ";"
set xtic rotate by 45 font '0,8' offset -2,-2.5
set ylabel "Distance (km)" font '0,12'
set xlabel "Identifiants Trajets" font '0,12' offset 0,-2
set title 'Statistiques sur les étapes' font '0,15'
set tics out nomirror
set output 'images/histogramme_s.png'
plot "images/histogramme_s.png" using 2:xtic(3) with filledcurves above fillcolor rgb '#E6ADAD' title 'Distance moyenne' lt rgb '#E6ADAD', \
     '' u 3:xtic(1) w filledcurves above fillcolor rgb '#FFFFFF' notitle lt rgb '#FFFFFF', \
     '' u 4:xtic(1) w l lw 2 title 'Moyenne', \
     '' u 2:xtic(1) w l lc rgb "white" lw 2 notitle, \
     '' u 3:xtic(1) w l lc rgb "white" lw 2 notitle

EOF
}
traitementS() {
    fichier_entree="data/data.csv"
    dossier_temp="temp"
    dossier_fichiers_c="progc"

    # Mesure du temps d'exécution - début
    temps_debut=$(date +%s.%N)

    # Vérification de l'existence du fichier CSV
    if [ ! -f "$fichier_entree" ]; then
        echo "Le fichier '$fichier_entree' n'existe pas."
        exit 1
    fi
    cat "$fichier_entree" | tail -n +2 | cut -d ';' -f 1,5 > "$dossier_temp/donnees_s.txt"
    
    make -C "$dossier_fichiers_c" > makeFileLogs.txt
    "$dossier_fichiers_c/S_CALCUL"
    "$dossier_fichiers_c/S_AVL"
    
     
    head -n 50 "$dossier_temp/resultat_avl.txt" > "$dossier_temp/final.txt"
    generer_histogramme_s
    cat "$dossier_temp/final.txt"
    # Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
}


