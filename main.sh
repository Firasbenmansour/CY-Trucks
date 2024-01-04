#!/bin/bash


dossier="temp"

# Vérifier si le dossier existe
if [ -d "$dossier" ]; then
    echo "Le dossier '$dossier' existe déjà."
    echo "Vidage du dossier '$dossier'"
    rm -rf "$dossier"/*
else
    echo "Le dossier '$dossier' n'existe pas."
    mkdir "$dossier"
    echo "Le dossier '$dossier' a été créé avec succès."
fi



dossier_images="images"

# Vérifier si le dossier images existe
if [ -d "$dossier_images" ]; then
    echo "Le dossier '$dossier_images' existe déjà."
else
    echo "Le dossier '$dossier_images' n'existe pas."
    mkdir "$dossier_images"
    echo "Le dossier '$dossier_images' a été créé avec succès."
fi

source d1.sh
source l.sh
source t.sh
source d2.sh
# Vérification des options et appel des fonctions correspondantes
if   [ "$2" = "-d1" ]; then
    traitementD1 "$1"
elif [ "$2" = "-l" ]; then
    traitementL "$1"
elif [ "$2" = "-t" ]; then
    traitementT "$1"
elif [ "$2" = "-d2" ]; then
    traitementD2 "$1"
else
    echo "Option non valide."
    exit 1
fi
