#include <stdio.h>
#include "ville.h"

int main() {
    // Ouverture du fichier de données en mode lecture
    FILE* fichier = fopen("temp/Top10_villes.txt", "r");

    // Vérification de l'ouverture du fichier
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char ligne[256];
    char nom[100];
    int nbTrajets;
    int nbDeparts;
    Ville* racine = NULL;

    // Lecture des lignes du fichier
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Extraction des données depuis la ligne
        if (sscanf(ligne, "%[^:] : %d : %d", nom, &nbTrajets, &nbDeparts) != 3) {
            printf("Format invalide : %s\n", ligne);
            continue;
        }

        // Insertion d'une ville dans l'arbre AVL 
        racine = insertionAlpha(racine, nom, nbTrajets, nbDeparts);
    }

    // Fermeture du fichier
    fclose(fichier);

    // Affichage des villes dans un ordre croissant 
    AffichageCroissant_t(racine);
    
    // Libération de la mémoire utilisée par l'arbre AVL
    libererMemoireAVL(racine);

    return 0;
}
