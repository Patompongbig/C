#include <stdio.h>
#include <stdlib.h>

#define __bin_tree__
#include "week9.h"

#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int depth(tree_t *t){
    if (t == NULL){
        return -1;
    }
    int height_left = depth(t -> left);
    int height_right = depth(t -> right);
    return (height_left > height_right) ? height_left + 1 : height_right + 1;
}

int is_bst(tree_t *t){
    if (t == NULL){
        return 1;
    }
    if (t -> left != NULL && t -> left -> data > t -> data){
        return 0;
    }
    return is_bst(t -> left) && is_bst(t -> right);
}

int is_avl(tree_t *t){
    if (t == NULL){
        return 1;
    }
    int height_left = depth(t -> left);
    int height_right = depth(t -> right);
    if (height_left - height_right != 1 && height_left - height_right != -1 && height_left - height_right != 0){
        return 0;
    }
    return is_avl(t -> left) && is_avl(t -> right) && is_bst(t);
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child,
        &branch);
        t = attach(t, parent, child, branch);
    }
    
    printf("%d %d\n", is_bst(t), is_avl(t));
    return 0;
}