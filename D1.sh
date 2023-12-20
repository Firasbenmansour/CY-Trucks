#!/bin/bash


   # Fonction pour le traitement de l'option -d1
   option1() {
       # Récupération du nom du fichier CSV
       input_file=$1

       # Vérification si le fichier de cache existe
       if [ ! -f "/home/firas/Project_CY_Truck/temp/cache_conducteurs.txt" ]; then
           # Extraction des noms de conducteurs et comptage des trajets uniques
           cut -d';' -f6 "$input_file" | sort | uniq -c | sort -nr | head -n 10 > "/home/firas/Project_CY_Truck/temp/cache_conducteurs.txt"
       fi
       # Si le fichier existe, affichage de son contenu
       cat "/home/firas/Project_CY_Truck/temp/cache_conducteurs.txt"
       exit 0
   }
