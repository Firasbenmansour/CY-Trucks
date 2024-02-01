#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"




int main() {
    // Initialisation de la racine de l'arbre AVL à NULL
    Distance* racine = NULL;

    // Ouverture des fichiers d'entrée et de sortie
    FILE* fichierResultats = fopen("temp/resultat.txt", "r");
    FILE* fichierResultatsAVL = fopen("temp/resultat_avl.txt", "w");

    // Vérification si l'ouverture des fichiers a réussi
    if (fichierResultats == NULL || fichierResultatsAVL == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        exit(EXIT_FAILURE);
    }

    // Variables pour stocker les valeurs lues depuis le fichier
    int id;
    double min;
    double moy;
    double max;
    double valeur;

    // Lecture des résultats depuis le fichier et insertion dans l'arbre AVL
    while (fscanf(fichierResultats, "%d;%lf;%lf;%lf;%lf", &id, &min, &moy, &max, &valeur) == 5) {
        racine = insertAVL(racine, id, min, moy, max, valeur);
    }

    // Affichage des résultats dans l'ordre décroissant dans le fichier de sortie AVL
    AffichageDecroissant(racine, fichierResultatsAVL);

    // Fermeture des fichiers
    fclose(fichierResultats);
    fclose(fichierResultatsAVL);

    // Libération de la mémoire utilisée par l'arbre AVL
    libererMemoireAVL_s(racine);

    return 0;
}
