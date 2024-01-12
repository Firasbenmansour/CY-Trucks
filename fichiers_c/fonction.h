#ifndef FONCTION_H
#define FONCTION_H

typedef struct route {
    char route_id[20];
    float distance;
    struct route* next;
} Route;

typedef struct routeList {
    Route* head;
    Route* tail;
} Routelist;

typedef struct AVLNode {
    char route_id[20];
    float difference;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

Routelist* initialize_list();
void insert_route(Routelist* list, char route_id[20], float distance);
void calculate_differences(Routelist* list);
int max(int a, int b);
int height(AVLNode* node);
int get_balance(AVLNode* node);
AVLNode* new_node(char route_id[20], float difference);
AVLNode* right_rotate(AVLNode* y);
AVLNode* left_rotate(AVLNode* x);
AVLNode* insert(AVLNode* root, char route_id[20], float difference);
void in_order_traversal(AVLNode* root);
void print_top_routes(AVLNode* root, int count);

#endif /* FONCTION_H */


