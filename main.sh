#!/bin/bash


# Fichier de données
fichier_data="data.csv"
# Vérifier si le fichier 'data.csv' existe dans le répertoire courant
if [ -e "$fichier_data" ]; then
  
    # Vérification si le répertoire 'data' existe, sinon le créer
    if [ ! -d "data" ]; then
        mkdir "data"
    fi

    # Déplacement du fichier vers le répertoire 'data'
    mv "$fichier_data" "data/"

else
    # Le fichier 'data.csv' n'existe pas dans le répertoire courant,
    # vérifions s'il existe dans le répertoire 'data'
    if [ ! -e "data/$fichier_data" ]; then
        echo "Le fichier '$fichier_data' n'existe pas"
        exit 1
    fi
fi

# Répertoire temporaire
dossier="temp"

# Vérifier si le dossier existe
if [ -d "$dossier" ]; then
    rm -rf "$dossier"/*
else
    mkdir "$dossier"
fi


# Répertoire des images
dossier_images="images"

# Vérifier si le dossier images existe
if [ ! -d "$dossier_images" ]; then
    mkdir "$dossier_images"
fi


source d1.sh
source l.sh
source t.sh
source d2.sh
source s.sh

echo "-------------------------------------------------------------"
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
    echo "-------------------------------------------------------------"
    exit 0

elif [ "$1" = "-d1" ]; then
    traitementD1
    echo "-------------------------------------------------------------"
    exit 0
elif [ "$1" = "-d2" ]; then
    traitementD2
    echo "-------------------------------------------------------------"
    exit 0
elif [ "$1" = "-l" ]; then
    traitementL 
    echo "-------------------------------------------------------------"
    exit 0
elif [ "$1" = "-t" ]; then
    traitementT 
    echo "-------------------------------------------------------------"
    exit 0
elif [ "$1" = "-s" ]; then
    traitementS 
    echo "-------------------------------------------------------------"
    exit 0
else
    echo "Option non valide. Tapez -h pour obtenir de l'aide."
    echo "-------------------------------------------------------------"
    exit 1
fi
