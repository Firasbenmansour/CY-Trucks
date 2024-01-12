#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"



Routelist* initialize_list() {
    Routelist* list = (Routelist*)malloc(sizeof(Routelist));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insert_route(Routelist* list, char route_id[20], float distance) {
    Route* new_route = (Route*)malloc(sizeof(Route));
    strcpy(new_route->route_id, route_id);
    new_route->distance = distance;
    new_route->next = NULL;

    if (list->head == NULL) {
        list->head = new_route;
        list->tail = new_route;
    } else {
        list->tail->next = new_route;
        list->tail = new_route;
    }
}

void calculate_differences(Routelist* list) {
    Route* current = list->head;

    while (current != NULL) {
        Route* temp = current;
        float max_distance = current->distance;
        float min_distance = current->distance;

        while (temp != NULL) {
            if (temp->distance > max_distance) {
                max_distance = temp->distance;
            }

            if (temp->distance < min_distance) {
                min_distance = temp->distance;
            }

            temp = temp->next;
        }

        float difference = max_distance - min_distance;
        printf("Route ID: %s, Différence de distance: %f\n", current->route_id, difference);

        current = current->next;
    }
}




int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    return (node == NULL) ? 0 : node->height;
}


int get_balance(AVLNode* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

AVLNode* new_node(char route_id[20], float difference) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node != NULL) {
        strcpy(node->route_id, route_id);
        node->difference = difference;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insert(AVLNode* root, char route_id[20], float difference) {
    if (root == NULL)
        return new_node(route_id, difference);

    if (difference < root->difference)
        root->left = insert(root->left, route_id, difference);
    else if (difference > root->difference)
        root->right = insert(root->right, route_id, difference);
    else // Ignore duplicate differences
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root);

    // Left Left Case
    if (balance > 1 && difference < root->left->difference)
        return right_rotate(root);

    // Right Right Case
    if (balance < -1 && difference > root->right->difference)
        return left_rotate(root);

    // Left Right Case
    if (balance > 1 && difference > root->left->difference) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Left Case
    if (balance < -1 && difference < root->right->difference) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void in_order_traversal(AVLNode* root) {
    if (root != NULL) {
        in_order_traversal(root->right);
        printf("Route ID: %s, Différence de distance: %f\n", root->route_id, root->difference);
        in_order_traversal(root->left);
    }
}

void print_top_routes(AVLNode* root, int count) {
    if (root != NULL && count > 0) {
        print_top_routes(root->right, count);
        printf("Route ID: %s, Différence de distance: %f\n", root->route_id, root->difference);
        print_top_routes(root->left, --count);
    }
}

