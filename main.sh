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

# Vérification si le deuxième argument est -d1 et appel de la fonction option1
if [ "$2" = "-d1" ]; then
    option1 "$1"
fi

# Si l'option n'est pas valide
echo "Option non valide"
exit 1
