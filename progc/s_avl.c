#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"




int main() {
    Distance* racine = NULL;
    FILE* fichierResultats = fopen("temp/resultat.txt", "r");
    FILE* fichierResultatsAVL = fopen("temp/resultat_avl.txt", "w");

    if (fichierResultats == NULL || fichierResultatsAVL == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        exit(EXIT_FAILURE);
    }

    int id;
    double min;
    double moy;
    double max;
    double valeur;

    while (fscanf(fichierResultats, "%d;%lf;%lf;%lf;%lf", &id, &min, &moy, &max, &valeur) == 5) {
        racine = insertAVL(racine, id, min, moy, max, valeur);
    }

    parcoursDecroissant(racine, fichierResultatsAVL);

    fclose(fichierResultats);
    fclose(fichierResultatsAVL);

    libererMemoireAVL(racine);

    return 0;
}
