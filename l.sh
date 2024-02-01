generer_histogramme_l() {
gnuplot <<EOF
reset
set term pngcairo size 800,600 enhanced font 'arial,10'
set title 'Les 10 trajets les plus longs' font 'Times-New-Roman,20,20'
set xlabel "Identifiants Trajets" font 'arial,12'
set ylabel "Distance (km)" font 'arial,12'
set datafile separator ";"
set style data histograms
set style fill solid noborder
set boxwidth 2.5 relative
set xtic rotate by 0 font 'arial,11'
set yrange [0:*]
set grid y
set output 'images/histogramme_l.png'
plot 'temp/donnees_traitement_l.txt' using 2:xtic(1) lc rgb '#478778' notitle
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

traitementL() {
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
    
    # Vérification si le fichier de cache existe
    fichier_cache="temp/donnees_traitement_l.txt"
            LC_NUMERIC="C" awk -F';' '
            NR>1{
                 sum[$1]+=$5
                } 
            END {
                for(route in sum) {
                    printf "%.3f %s\n", sum[route], route;
                }
            }' "$fichier_entree" | LC_NUMERIC="C" sort -k1 -nr | head -n 10 | sort -k2 -nr | awk '{printf "%s;%s\n", $2, $1}' > "$fichier_cache"
    
    # stopper l'animation
    stop_animation
    echo -e "\rTraitement terminé.      "
            
    cat "$fichier_cache"    
    # Génération de l'histogramme
    generer_histogramme_l            
    #Calcul du temps d'exécution
    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
}
