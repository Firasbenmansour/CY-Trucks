#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"





int main() {
    FILE *inputFile, *outputFile;
    
    
    int max_trajets = lireNombreMaxTrajets();
    
    Trajet **trajets = malloc(max_trajets * sizeof(Trajet*));
    if (trajets == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour le tableau de trajets");
        exit(EXIT_FAILURE);
    }

    // Initialiser le tableau de pointeurs à NULL
    for (int i = 0; i < max_trajets; i++) {
        trajets[i] = NULL;
    }
    
    inputFile = fopen("temp/donnees_s.txt", "r");
    if (inputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    
    lireEtTraiterDonnees(inputFile, trajets, max_trajets);
    fclose(inputFile);


    // Ouverture du fichier de sortie
    outputFile = fopen("temp/resultat.txt", "w");
    if (outputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    ecrireResultats(outputFile, trajets, max_trajets);
    free(trajets);
    fclose(outputFile);

    return 0;
}
