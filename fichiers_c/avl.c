#include <stdio.h>
#include "fonction.h"

int main() {
    AVLNode* avl_tree = NULL;

    // Lire le fichier CSV et insérer les données dans l'arbre AVL
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
        avl_tree = insert(avl_tree, route_id, distance);
    }

    // Fermer le fichier
    fclose(file);

    // Afficher les 50 premières routes avec la plus grande différence
    printf("Top 50 Routes avec la plus grande différence de distance :\n");
    print_top_routes(avl_tree, 50);

    return 0;
}




