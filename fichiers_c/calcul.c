#include <stdio.h>
#include "fonction.h"

int main() {
    Routelist* route_list = initialize_list();

    // Lire le fichier CSV et insérer les données dans la liste
    FILE* file = fopen("data.csv", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char route_id[20];
        float distance;
        sscanf(line, "%19[^;];%f", route_id, &distance);
        insert_route(route_list, route_id, distance);
    }

    // Fermer le fichier
    fclose(file);

    // Calculer et afficher les différences de distance
    calculate_differences(route_list);

    return 0;
}


