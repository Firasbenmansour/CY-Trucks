#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"fonction.h"
#define MAX_LINE_LENGTH 1024



void freeMemory(double *min_distances, double *max_distances, double *total_distances, double *range_distances, int *num_steps) {
    free(min_distances);
    free(max_distances);
    free(total_distances);
    free(range_distances);
    free(num_steps);
}

int readMaxRouteId(FILE *file) {
    char line[MAX_LINE_LENGTH];
    int max_route_id = 0;

    fgets(line, MAX_LINE_LENGTH, file); // Ignorer la première ligne (en-tête)

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        RouteData data;
        sscanf(line, "%d;%d;%[^;];%[^;];%lf;%[^;]",
               &data.route_id, &data.step_id, data.town_a, data.town_b,
               &data.distance, data.driver_name);

        if (data.route_id > max_route_id) {
            max_route_id = data.route_id;
        }
    }

    return max_route_id;
}

void processData(FILE *file, int max_route_id, double *min_distances, double *max_distances, double *total_distances, double *range_distances, int *num_steps) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file); // Ignorer la première ligne (en-tête)

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        RouteData data;
        sscanf(line, "%d;%d;%[^;];%[^;];%lf;%[^;]",
               &data.route_id, &data.step_id, data.town_a, data.town_b,
               &data.distance, data.driver_name);

        if (min_distances[data.route_id] == 0 || data.distance < min_distances[data.route_id]) {
            min_distances[data.route_id] = data.distance;
        }

        if (data.distance > max_distances[data.route_id]) {
            max_distances[data.route_id] = data.distance;
        }

        total_distances[data.route_id] += data.distance;
        range_distances[data.route_id] = max_distances[data.route_id] - min_distances[data.route_id];
        num_steps[data.route_id]++;
    }
}




int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

Node* new_node(int route_id, double column_2_value, double column_3_value, double column_4_value, double column_5_value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        perror("Erreur lors de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    node->route_id = route_id;
    node->column_2_value = column_2_value;
    node->column_3_value = column_3_value;
    node->column_4_value = column_4_value;
    node->column_5_value = column_5_value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* right_rotate(Node* y) {
    if (y == NULL || y->left == NULL)
        return y;

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* left_rotate(Node* x) {
    if (x == NULL || x->right == NULL)
        return x;

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* right_left_rotate(Node* z) {
    if (z == NULL || z->right == NULL)
        return z;

    z->right = right_rotate(z->right);
    return left_rotate(z);
}

Node* left_right_rotate(Node* z) {
    if (z == NULL || z->left == NULL)
        return z;

    z->left = left_rotate(z->left);
    return right_rotate(z);
}

Node* insert(Node* node, int route_id, double column_2_value, double column_3_value, double column_4_value, double column_5_value) {
    if (node == NULL)
        return new_node(route_id, column_2_value, column_3_value, column_4_value, column_5_value);

    if (column_5_value > node->column_5_value)
        node->right = insert(node->right, route_id, column_2_value, column_3_value, column_4_value, column_5_value);
    else
        node->left = insert(node->left, route_id, column_2_value, column_3_value, column_4_value, column_5_value);

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if (balance > 1 && column_5_value < node->left->column_5_value)
        return right_rotate(node);

    if (balance < -1 && column_5_value > node->right->column_5_value)
        return left_rotate(node);

    if (balance > 1 && column_5_value > node->left->column_5_value) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && column_5_value < node->right->column_5_value) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void parse_line(char* line, int* route_id, double* column_2_value, double* column_3_value, double* column_4_value, double* column_5_value) {
    char* token = strtok(line, ";");
    for (int i = 1; i <= 5; i++) {
        if (token == NULL) {
            perror("Erreur lors de l'extraction des données de la ligne");
            fprintf(stderr, "Erreur survenue à la position %d\n", i);
            exit(EXIT_FAILURE);
        }

        if (i == 1) {
            *route_id = atoi(token);
        } else if (i == 2) {
            *column_2_value = atof(token);
        } else if (i == 3) {
            *column_3_value = atof(token);
        } else if (i == 4) {
            *column_4_value = atof(token);
        } else if (i == 5) {
            *column_5_value = atof(token);
        }

        token = strtok(NULL, ";");
    }
}

void in_order_traversal(Node* root, int* count, int max_count, int* result_ids, double* result_values_2, double* result_values_3, double* result_values_4, double* result_values_5) {
    if (root != NULL && *count < max_count) {
        in_order_traversal(root->right, count, max_count, result_ids, result_values_2, result_values_3, result_values_4, result_values_5);
        if (*count < max_count) {
            result_ids[*count] = root->route_id;
            result_values_2[*count] = root->column_2_value;
            result_values_3[*count] = root->column_3_value;
            result_values_4[*count] = root->column_4_value;
            result_values_5[*count] = root->column_5_value;
            (*count)++;
        }
        in_order_traversal(root->left, count, max_count, result_ids, result_values_2, result_values_3, result_values_4, result_values_5);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void write_output_file(const char* filename, int* result_ids, double* result_values_2, double* result_values_3, double* result_values_4, double* result_values_5, int count) {

    FILE* output_file = fopen(filename, "w");
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "RouteID;MoyenneTrajet;DistanceMax;DistanceMin;Distance_Range\n");

    for (int i = 0; i < count; i++) {
        fprintf(output_file, "%d;%lf;%lf;%lf;%lf\n", result_ids[i], result_values_2[i], result_values_3[i], result_values_4[i], result_values_5[i]);
    }

    fclose(output_file);
}

