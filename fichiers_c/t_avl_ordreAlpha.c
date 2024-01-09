#include <stdio.h>
#include "ville.h"

int main() {
    FILE* fichier = fopen("temp/Top10_villes.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char ligne[256];
    char nom[100];
    int nbTrajets;
    int nbDeparts;
    Ville* racine = NULL;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (sscanf(ligne, "%[^:] : %d : %d", nom, &nbTrajets, &nbDeparts) != 3) {
            printf("Format invalide : %s\n", ligne);
            continue;
        }

        racine = insertionAlpha(racine, nom, nbTrajets, nbDeparts);
    }

    fclose(fichier);

    trierVilles(racine);

    return 0;
}
