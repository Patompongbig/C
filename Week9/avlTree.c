#include <stdio.h>
#include <stdlib.h>

#define __avl_tree__
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t avl_t;
#endif

int find_min(avl_t *t) {
    if (t == NULL) {
        return -1;
    }
    if (t->left == NULL) {
        return t->data;
    }
    return find_min(t->left);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(avl_t *n) {
    return (n == NULL) ? -1 : n->height;
}

int get_balance(avl_t *t) {
    if (t == NULL) {
        return 0;
    }
    return height(t->left) - height(t->right);
}

avl_t *right_rotation(avl_t *n) {
    avl_t *tmp = n->left;
    n->left = tmp->right;
    tmp->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    return tmp;
}

avl_t *left_rotation(avl_t *n) {
    avl_t *tmp = n->right;
    n->right = tmp->left;
    tmp->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    return tmp;
}

avl_t *left_right_rotation(avl_t *n) {
    n->left = left_rotation(n->left);
    return right_rotation(n);
}

avl_t *right_left_rotation(avl_t *n) {
    n->right = right_rotation(n->right);
    return left_rotation(n);
}

avl_t *insert(avl_t *t, int value) {
    if (t == NULL) {
        avl_t *node = (avl_t *)malloc(sizeof(avl_t));
        node->data = value;
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    
    if (value < t->data) {
        t->left = insert(t->left, value);
    } else if (value > t->data) {
        t->right = insert(t->right, value);
    } else {
        return t;  // Duplicate values are not allowed in AVL tree
    }

    t->height = max(height(t->left), height(t->right)) + 1;

    int balance = get_balance(t);

    // Left Left Case
    if (balance > 1 && value < t->left->data) {
        return right_rotation(t);
    }

    // Right Right Case
    if (balance < -1 && value > t->right->data) {
        return left_rotation(t);
    }

    // Left Right Case
    if (balance > 1 && value > t->left->data) {
        return left_right_rotation(t);
    }

    // Right Left Case
    if (balance < -1 && value < t->right->data) {
        return right_left_rotation(t);
    }

    return t;
}

avl_t *delete(avl_t *t, int value) {
    if (t == NULL) {
        return t;
    }

    if (value < t->data) {
        t->left = delete(t->left, value);
    } else if (value > t->data) {
        t->right = delete(t->right, value);
    } else {
        // Node to be deleted found
        if (t->left == NULL || t->right == NULL) {
            avl_t *temp = (t->left != NULL) ? t->left : t->right;
            if (temp == NULL) {
                temp = t;
                t = NULL;
            } else {
                *t = *temp;
            }
            free(temp);
        } else {
            int min_value = find_min(t->right);
            t->data = min_value;
            t->right = delete(t->right, min_value);
        }
    }

    if (t == NULL) {
        return t;
    }

    t->height = max(height(t->left), height(t->right)) + 1;
    int balance = get_balance(t);

    // Left Left Case
    if (balance > 1 && get_balance(t->left) >= 0) {
        return right_rotation(t);
    }

    // Left Right Case
    if (balance > 1 && get_balance(t->left) < 0) {
        return left_right_rotation(t);
    }

    // Right Right Case
    if (balance < -1 && get_balance(t->right) <= 0) {
        return left_rotation(t);
    }

    // Right Left Case
    if (balance < -1 && get_balance(t->right) > 0) {
        return right_left_rotation(t);
    }

    return t;
}

int main(void) {
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                print_tree(t);
                printf("\n");
                break;
        }
    }
    return 0;
}
