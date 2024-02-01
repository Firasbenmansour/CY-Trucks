#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"





int main() {
    // Déclaration des fichiers d'entrée et de sortie
    FILE *inputFile, *outputFile;
     
    // Obtention du nombre maximum de trajets depuis le fichier
    int max_trajets = lireNombreMaxTrajets(); 
    
    // Allocation de mémoire pour le tableau de pointeurs vers des trajets
    Trajet **trajets = malloc(max_trajets * sizeof(Trajet*));
    if (trajets == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour le tableau de trajets");
        exit(EXIT_FAILURE);
    }

    // Initialiser le tableau de pointeurs à NULL
    for (int i = 0; i < max_trajets; i++) {
        trajets[i] = NULL;
    }
    
    // Ouverture du fichier d'entrée et Vérification si l'ouverture du fichier a réussi
    inputFile = fopen("temp/donnees_s.txt", "r");
    if (inputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    
    // Lecture et traitement des données du fichier d'entrée
    lireEtTraiterDonnees(inputFile, trajets, max_trajets);
    fclose(inputFile);


    // Ouverture du fichier de sortie et Vérification si l'ouverture du fichier a réussi
    outputFile = fopen("temp/resultat.txt", "w");
    if (outputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }
    
    // Écriture des résultats dans le fichier de sortie
    ecrireResultats(outputFile, trajets, max_trajets);
    free(trajets); // Libération de la mémoire allouée pour le tableau de trajets
    fclose(outputFile); // Fermeture du fichier de sortie

    return 0;
}
