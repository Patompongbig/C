#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int countpath(tree_t *t, int v, int sum){
    if (t == NULL){
        return 0;
    }

    sum += t -> data;
    int path = 0;
    if (sum == v){
        path += 1;
    }
    path += countpath(t -> left, v, sum);
    path += countpath(t -> right, v, sum);

    return path;
}

int countPathsWithSum(tree_t *t, int v){
    if (t == NULL){
        return 0;
    }

    int path_main = countpath(t, v, 0);
    int path_left = countPathsWithSum(t -> left, v);
    int path_right = countPathsWithSum(t -> right, v);

    return path_main + path_left + path_right;
}

int main(void) {
    tree_t *t = NULL;
    int n, s, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d %d", &n, &s);

    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }

    printf("%d\n", countPathsWithSum(t, s));
    return 0;
}