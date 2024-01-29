#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    int id_trajet;
    double distance;
} Etape;

typedef struct {
    int id_trajet;
    double min_distance;
    double max_distance;
    double moyenne_distance;
    int nombre_etapes;
} TrajetInfo;

void updateTrajetInfo(TrajetInfo *info, double distance) {
    if (distance < info->min_distance) {
        info->min_distance = distance;
    }
    if (distance > info->max_distance) {
        info->max_distance = distance;
    }
    info->moyenne_distance += distance;
    info->nombre_etapes++;
}

int main() {
    FILE *inputFile, *outputFile;
    char buffer[MAX_BUFFER_SIZE];
    TrajetInfo trajets[100]; // Vous pouvez ajuster la taille en fonction du nombre maximal d'ID de trajets attendus

    // Initialisation des informations de trajets
    for (int i = 0; i < 100; i++) {
        trajets[i].id_trajet = -1;
        trajets[i].min_distance = __DBL_MAX__;
        trajets[i].max_distance = -1;
        trajets[i].moyenne_distance = 0;
        trajets[i].nombre_etapes = 0;
    }

    // Ouverture du fichier d'entrée
    inputFile = fopen("temp/donnees_s.txt", "r");
    if (inputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }

    // Lecture et traitement des données
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        char *token = strtok(buffer, ";|");
        int id_trajet = atoi(token);

        token = strtok(NULL, ";|");
        double distance = atof(token);

        int index = -1;
        for (int i = 0; i < 100; i++) {
            if (trajets[i].id_trajet == id_trajet) {
                index = i;
                break;
            } else if (trajets[i].id_trajet == -1) {
                trajets[i].id_trajet = id_trajet;
                index = i;
                break;
            }
        }

        updateTrajetInfo(&trajets[index], distance);
    }

    // Fermeture du fichier d'entrée
    fclose(inputFile);

    // Ouverture du fichier de sortie
    outputFile = fopen("temp/resultat.txt", "w");
    if (outputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    // Écriture des résultats dans le fichier de sortie
    for (int i = 0; i < 100; i++) {
        if (trajets[i].id_trajet != -1) {
            trajets[i].moyenne_distance /= trajets[i].nombre_etapes;
            double difference_max_min = trajets[i].max_distance - trajets[i].min_distance;
            fprintf(outputFile, "%d;%.2f;%.2f;%.2f;%.2f\n", trajets[i].id_trajet, trajets[i].min_distance,
                    trajets[i].moyenne_distance, trajets[i].max_distance, difference_max_min);
        }
    }

    // Fermeture du fichier de sortie
    fclose(outputFile);

    return 0;
}
