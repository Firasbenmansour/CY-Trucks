#ifndef FONCTION_H
#define FONCTION_H

#define MAX_LINE_LENGTH 1024

typedef struct {
    int route_id;
    int step_id;
    char town_a[100];
    char town_b[100];
    double distance;
    char driver_name[100];
} RouteData;

typedef struct Node {
    int route_id;
    double column_2_value;
    double column_3_value;
    double column_4_value;
    double column_5_value;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

void freeMemory(double *min_distances, double *max_distances, double *total_distances, double *range_distances, int *num_steps);
int readMaxRouteId(FILE *file);
void processData(FILE *file, int max_route_id, double *min_distances, double *max_distances, double *total_distances, double *range_distances, int *num_steps);
int max(int a, int b);
int height(Node* node);
Node* new_node(int route_id, double column_2_value, double column_3_value, double column_4_value, double column_5_value);
Node* right_rotate(Node* y);
Node* left_rotate(Node* x);
Node* right_left_rotate(Node* z);
Node* left_right_rotate(Node* z);
Node* insert(Node* node, int route_id, double column_2_value, double column_3_value, double column_4_value, double column_5_value);
void parse_line(char* line, int* route_id, double* column_2_value, double* column_3_value, double* column_4_value, double* column_5_value);
void in_order_traversal(Node* root, int* count, int max_count, int* result_ids, double* result_values_2, double* result_values_3, double* result_values_4, double* result_values_5);
void free_tree(Node* root);
void write_output_file(const char* filename, int* result_ids, double* result_values_2, double* result_values_3, double* result_values_4, double* result_values_5, int count);

#endif /* FONCTION_H */



