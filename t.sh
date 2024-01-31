#!/bin/bash

generer_histogramme_t() {
gnuplot <<EOF
reset
set term pngcairo size 1280,720 enhanced font 'arial,10'
set title 'Les 10 villes les plus traversées' font '0,15'
set datafile separator ":"
set grid
set xlabel "Villes" font '0,12'
set ylabel "Nombres de trajets" font '0,12'
set style data histograms
set style histogram cluster gap 1
set style fill solid noborder
set xtic font '0,12'
set ytic font '0,12'
set xtics rotate by -30
set boxwidth 1.5
set output 'images/histogramme_t.png'
plot 'temp/villes_triees_ordreAlpha.txt' using 2:xtic(1) title 'Total de trajet' lc rgb "spring-green", \
     "" using 3:x2tic(1) title 'Ville de départ' lc rgb "dark-green"
EOF
}


traitementT() {
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

    # Utilisation d'awk pour traiter les données
    awk -F';' '
    NR>1 {
        if ($2 == 1) { si on est dans l etape 1 du trajet
            depart_trajet[$3]++;  # compteur de nombre de fois une ville a été un point de départ
        }
        if (!compte_trajet[$1, $3]) {   # Si la combinaison unique d identifiant de trajet et ville de départ n a pas été rencontrée
            compte_trajet[$1, $3]++;    # compteur associé à la combinaison unique
            compte_trajet2[$3]++;       # compteur de nombre de trajets
        }
        if (!compte_trajet[$1, $4]) {   # Si la combinaison unique d identifiant de trajet et ville d arrivée n a pas été rencontrée
            compte_trajet[$1, $4]++;    
            compte_trajet2[$4]++;       
        }
    }
    END {
        
        for (ville in depart_trajet) {
            # Imprime la ville, le nombre de trajets et le nombre de départs
            printf("%s : %d : %d\n", ville, compte_trajet2[ville], depart_trajet[ville]);
        }
    }' "$fichier_entree" > "$dossier_temp/donnees_traitement_t.txt"



  
    
    # Compilation des programmes C avec make
    make -C "$dossier_fichiers_c" > makeFileLogs.txt

    # Exécution des programmes C et redirection des résultats vers les fichiers temporaires
    "$dossier_fichiers_c/t_AVL_nbTrajets" > "$dossier_temp/villes_triees_nbTrajets.txt"
    
    head -n 10 "$dossier_temp/villes_triees_nbTrajets.txt" > "$dossier_temp/Top10_villes.txt"

    "$dossier_fichiers_c/t_AVL_ordreAlpha" > "$dossier_temp/villes_triees_ordreAlpha.txt"
    
    cat "$dossier_temp/villes_triees_ordreAlpha.txt"
    generer_histogramme_t

    temps_fin=$(date +%s.%N)
    temps_execution=$(echo "$temps_fin - $temps_debut" | bc)
    echo "Temps d'exécution : $temps_execution secondes"
    
}    
