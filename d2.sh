generer_histogramme_d2() {
gnuplot <<EOF
reset
set size 1,1
set term pngcairo size 600,800 enhanced font 'arial,10'
set ylabel "Conducteurs et la plus grande distance" font 'Times-New-Roman,20' offset 4,0
set xlabel "Conducteurs" rotate by 180 font 'arial,12' offset 0,-9 
set y2label "Distance (km)" font 'arial,12' offset 3,0
set datafile separator ";"
set style fill solid noborder
set boxwidth 2.5 relative
set locale 'fr_FR.UTF-8' 
set format y "%.f" 
set xtic rotate by 90 font 'arial,10' offset 0.5,-9.5
set ytic rotate by 90 font 'arial,11' offset 74,1
set style data histograms
set yrange [0:*]
set grid y
set output 'images/histogramme_d2.png'
plot 'temp/donnees_traitement_d2.txt' using 2:xticlabels(1) notitle lc rgb '#478778'
EOF
convert images/histogramme_d2.png -rotate 90 images/histogramme_d2.png
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

traitementD2() {
    fichier_entree="data/data.csv"
    
    # Mesure du temps d'exécution
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
    
    fichier_cache="temp/donnees_traitement_d2.txt"
    
        # Extraction des noms des conducteurs et de leurs distances totales
        LC_NUMERIC="C" awk -F';' '
        NR>1{
             distance[$6] += $5
             } 
        END {
            for (conducteur in distance) {
                printf "%.3f %s\n", distance[conducteur], conducteur;
            }
        }' "$fichier_entree" | LC_NUMERIC="C" sort -k1 -nr | head -n 10 | awk '{print $2, $3";", $1}'> "$fichier_cache"
    
    # stopper l'animation
    stop_animation
    echo -e "\rTraitement terminé.      "

    # Si le fichier existe, affichage de son contenu
    cat "$fichier_cache"  
    # Génération de l'histogramme
    generer_histogramme_d2   
    # Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
}
