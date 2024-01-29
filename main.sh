#!/bin/bash

# Fichier de données
fichier_data="data.csv"
echo "-----------------------------------------------------------"
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
echo "-----------------------------------------------------------"
source d1.sh
source l.sh
source t.sh
source d2.sh
source s.sh

if [ "$1" = "-h" ]; then
    # Afficher le message d'aide
    echo "  Options valides : $0 [-h | -d1 | -d2 | -l | -t | -s]"
    echo -e "\n  Utilité:"
    echo "  -h      Afficher ce message d'aide"
    echo "  -d1     Exécuter le traitement D1"
    echo "  -d2     Exécuter le traitement D2"
    echo "  -l      Exécuter le traitement L"
    echo "  -t      Exécuter le traitement T"
    echo "  -s      Exécuter le traitement S"
    exit 0

elif [ "$1" = "-d1" ]; then
    traitementD1
    exit 0
elif [ "$1" = "-d2" ]; then
    traitementD2 
    exit 0
elif [ "$1" = "-l" ]; then
    traitementL 
    exit 0
elif [ "$1" = "-t" ]; then
    traitementT 
    exit 0
elif [ "$1" = "-s" ]; then
    traitementS 
    exit 0
else
    echo "Option non valide. Tapez -h pour obtenir de l'aide."
    exit 1
fi
