generer_histogramme_s() {
gnuplot <<EOF
set term pngcairo size 1280,720 enhanced font 'arial,10'
set title 'Statistiques sur les étapes' font 'Times-New-Roman,20'
set xlabel "Identifiants Trajets" font 'arial,12' offset 0,-2
set ylabel "Distance (km)" font 'arial,12'
set datafile separator ";"
set xtic rotate by 45 font 'arial,10' offset -2,-2.5
set tics out nomirror
set output 'images/histogramme_s.png'
plot "temp/final.txt" using 2:xtic(4) with filledcurves above fillcolor rgb '#478778' title 'Distances max/min (km)' lt rgb '#478778', \
     '' u 4:xtic(1) w filledcurves above fillcolor rgb '#478778' notitle lt rgb '#478778', \
     '' u 3:xtic(1) w l lw 2 lc rgb '#023020' title 'Distance moyenne (km)', \
     '' u 4:xtic(1) w l lc rgb "white" lw 2 notitle, \
     '' u 2:xtic(1) w filledcurves above fillcolor rgb 'white' notitle
EOF
}

afficher_animation(){
    local chars="/-\|"
    while true; do
        for ((i = 0; i < ${#chars}; i++)); do
            sleep 0.1
            echo -e "\rTraitement en cours... ${chars:$i:1} \c" 
        done
    done
}

stop_animation() {
    # Stopper l'animation
    kill $PID_ANIMATION
    wait $PID_ANIMATION 2>/dev/null
}

traitementS() {
    fichier_entree="data/data.csv"
    dossier_temp="temp"
    dossier_fichiers_c="progc"

    # Mesure du temps d'exécution - début
    temps_debut=$(date +%s.%N)
    
    # Animation 
    afficher_animation &
    PID_ANIMATION=$!
    
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$fichier_entree" ]; then
        stop_animation
        echo -e "\rTraitement échoué!      "
        echo "Le fichier '$fichier_entree' n'existe pas."
        exit 1
    fi
    
    
    # Extraction des données nécessaires du fichier CSV dans un fichier temporaire
    cat "$fichier_entree" | tail -n +2 | cut -d ';' -f 1,5 > "$dossier_temp/donnees_s.txt" 
    
    # Calcul du nombre de trajets distincts et sauvegarde dans un fichier temporaire
    trajet_count=$(awk -F';' '!seen[$1]++ {count++} END {print count}' "$dossier_temp/donnees_s.txt")
    echo "$trajet_count" > "$dossier_temp/nombre_trajets.txt"
    
    # Compilation des programmes C avec make
    make -C "$dossier_fichiers_c" > "$dossier_temp/makeFileLogs.txt" 2>&1
    # Vérification du statut de sortie de make
    if [ $? -ne 0 ]; then
        stop_animation
        echo -e "\rTraitement échoué!      "
        echo "Erreur lors de la compilation avec make. Veuillez vérifier le Makefile."
        echo "Makefile logs:"             
        cat "$dossier_temp/makeFileLogs.txt"
        exit 1
    fi
    
    "$dossier_fichiers_c/S_CALCUL" #calcul des statiatiques
    "$dossier_fichiers_c/S_AVL"  #trie AVL
    
    # Extraction des 50 premières lignes du fichier résultat AVL
    head -n 50 "$dossier_temp/resultat_avl.txt" > "$dossier_temp/final.txt"
    
    # Stopper l'animation
    stop_animation
    echo -e "\rTraitement terminé.      "
    
    cat "$dossier_temp/final.txt"
    #générer l'histogramme
    generer_histogramme_s
    # Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
}
