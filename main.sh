#!/bin/bash

#creer dossier
dossier="temp"
dossier1="images"

# Vérifier si le dossier existe 
 if [ -d "$dossier" ]; then
 echo "le dossier existe deja"
echo "Vidage du dossier '$dossier'"
        rm -rf "$dossier"/*

    else
        echo "Le dossier '$dossier' n'existe pas."

    mkdir "$dossier"
    echo "Le dossier '$dossier' a été créé avec succès."

fi


#chmod +drwx dossier


source D1.sh

# Vérification si le deuxième argument est -d1 et appel de la fonction option1
if [ "$2" = "-d1" ]; then
    option1 "$1"
fi

# Si l'option n'est pas valide
echo "Option non valide. Les options disponibles sont : -d1"
exit 1
