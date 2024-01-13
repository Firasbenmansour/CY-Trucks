#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"fonction.h"


int main() {
    FILE* file = fopen("resultats.csv", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    Node* root = NULL;
    char line[256];

    // Ignorer la première ligne (entêtes)
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        int route_id;
        double column_2_value, column_3_value, column_4_value, column_5_value;

        parse_line(line, &route_id, &column_2_value, &column_3_value, &column_4_value, &column_5_value);

        root = insert(root, route_id, column_2_value, column_3_value, column_4_value, column_5_value);
    }

    fclose(file);

    int count = 0;
    int max_count = 50;
    int result_ids[max_count];
    double result_values_2[max_count], result_values_3[max_count], result_values_4[max_count], result_values_5[max_count];

    in_order_traversal(root, &count, max_count, result_ids, result_values_2, result_values_3, result_values_4, result_values_5);

    // Écriture des résultats dans le fichier de sortie
    write_output_file("output.txt", result_ids, result_values_2, result_values_3, result_values_4, result_values_5, count);

    // Libération de la mémoire
    free_tree(root);

    return 0;
}






