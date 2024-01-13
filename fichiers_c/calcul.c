#include <stdio.h>
#include <stdlib.h>
#include"fonction.h"
int main() {
    FILE *file = fopen("data.csv", "r");

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    int max_route_id = readMaxRouteId(file);

    // Allocate dynamically sized arrays
    double *min_distances = calloc(max_route_id + 1, sizeof(double));
    double *max_distances = calloc(max_route_id + 1, sizeof(double));
    double *total_distances = calloc(max_route_id + 1, sizeof(double));
    double *range_distances = calloc(max_route_id + 1, sizeof(double));
    int *num_steps = calloc(max_route_id + 1, sizeof(int));

    if (min_distances == NULL || max_distances == NULL || total_distances == NULL || range_distances == NULL || num_steps == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        freeMemory(min_distances, max_distances, total_distances, range_distances, num_steps);
        fclose(file);
        return 1;
    }

    // Return to the beginning of the file
    fseek(file, 0, SEEK_SET);

    processData(file, max_route_id, min_distances, max_distances, total_distances, range_distances, num_steps);

    fclose(file);

    FILE *outputFile = fopen("resultats.csv", "w");
    if (outputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        freeMemory(min_distances, max_distances, total_distances, range_distances, num_steps);
        return 1;
    }

    fprintf(outputFile, "routeid;moyenneetape;distancemaximale;distanceminimale;distancerange\n");

    for (int i = 0; i <= max_route_id; i++) {
        if (num_steps[i] > 0) {
            double avg_distance = total_distances[i] / num_steps[i];
            fprintf(outputFile, "%d;%.3lf;%.3lf;%.3lf;%.3lf\n", i, avg_distance, max_distances[i], min_distances[i], range_distances[i]);
        }
    }

    fclose(outputFile);

    freeMemory(min_distances, max_distances, total_distances, range_distances, num_steps);

    return 0;
}


