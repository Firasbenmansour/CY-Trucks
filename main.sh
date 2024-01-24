#!/bin/bash

# Fichier de données
fichier_data="data.csv"

# Vérifier si le fichier 'data.csv' existe dans le répertoire courant
if [ -e "$fichier_data" ]; then
    echo "Le fichier '$fichier_data' existe dans le répertoire courant."
    
    # Vérification si le répertoire 'data' existe, sinon le créer
    if [ ! -d "data" ]; then
        mkdir "data"
    fi

    # Déplacement du fichier vers le répertoire 'data'
    mv "$fichier_data" "data/"
    
    echo "Déplacement vers le répertoire 'data' effectué avec succès."
else
    # Le fichier 'data.csv' n'existe pas dans le répertoire courant,
    # vérifions s'il existe dans le répertoire 'data'
    if [ -e "data/$fichier_data" ]; then
        echo "Le fichier '$fichier_data' existe dans le répertoire 'data'."
    else
        echo "Le fichier '$fichier_data' n'existe pas dans le répertoire courant ni dans le répertoire 'data'."
        exit 1
    fi
fi

# Répertoire temporaire
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


# Répertoire des images
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
source s.sh
# Vérification des options et appel des fonctions correspondantes
if   [ "$1" = "-d1" ]; then
    traitementD1 
elif [ "$1" = "-l" ]; then
    traitementL 
elif [ "$1" = "-t" ]; then
    traitementT 
elif [ "$1" = "-d2" ]; then
    traitementD2 
elif [ "$1" = "-s" ]; then
    traitementS 
else
    echo "Option non valide."
    exit 1
fi
