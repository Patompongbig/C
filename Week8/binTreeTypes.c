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

typedef struct queue {
    int *arr;
    int capacity;
    int front;
    int rear;
} queue_t;

int enqueue(queue_t *q, int v) {
    if (q->rear == q->capacity)
        return 0;
    
    q->arr[++q->rear] = v;
    return 1;
}

int dequeue(queue_t *q) {
    int v;
    if (q->front > q->rear)
        return 0;
    
    v = q->arr[q->front++];
    return v;
}

int size(tree_t *t) {
    if (t == NULL)
        return 0;
    return size(t->left) + size(t->right) + 1;
}

int is_full(tree_t *t){
    if (t == NULL){
        return 1;
    }
    if (t -> left == NULL && t -> right == NULL){
        return 1;
    }
    if (t -> left != NULL && t -> right != NULL){
        return is_full(t -> left) && is_full(t -> right);
    }
    return 0;
}

int depth(tree_t *t){
    int h = 0;
    while (t != NULL){
        h += 1;
        t = t -> left;
    }
    return h;
}

int is_perfect(tree_t *t){
    if (t == NULL){
        return 0;
    }
    if (is_full(t) == 1){
        tree_t *tmp_left = t -> left;
        tree_t *tmp_right = t -> right;
        while (tmp_left != NULL && tmp_right != NULL){
            tmp_left = tmp_left -> left;
            tmp_right = tmp_right -> right;
        }
        if (tmp_left == NULL && tmp_right == NULL){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int is_complete(tree_t *t){
    int space = size(t);
    queue_t q = {NULL, space, 0, -1};
    q.arr = (int *)malloc(sizeof(int) * space);

    tree_t *tmp = t;
    int v = tmp -> data;
    int found = 0;
    enqueue(&q, v);

    while(q.rear >= q.front){
        v = dequeue(&q);
        tmp = searchNode(t, v);

        if (tmp -> left != NULL && tmp -> right != NULL){
            if(found){
                return 0;
            }
            enqueue(&q, tmp -> left -> data);
            enqueue(&q, tmp -> right -> data);
        }
        else if (tmp -> left == NULL && tmp -> right != NULL){
            return 0;
        }

        else if (is_full(tmp) == 1){
            found = 1;
        }
        else{
            if (found){
                return 0;
            }
            found = 1;
            enqueue(&q, tmp -> left -> data);
        }
    }
    return 1;
}

int is_degenerate(tree_t *t){
    if (t == NULL){
        return 0;
    }
    if (t -> left == NULL && t -> right == NULL){
        return 1;
    }
    if (t -> left != NULL && t -> right != NULL){
        return 0;
    }
    if (t -> left == NULL){
        return is_degenerate(t -> right);
    }
    else{
        return is_degenerate(t -> left);
    }
}

int is_skewed(tree_t *t){
    if (t == NULL){
        return 0;
    }
    if(is_degenerate(t) == 1){
        if(t -> left == NULL){
            while(t != NULL){
                if (t -> left != NULL){
                    return 0;
                }
                t = t -> right;
            }
            return 1;
        }
        else{
            while(t != NULL){
                if (t -> right != NULL){
                    return 0;
                }
                t = t -> left;
            }
            return 1;
        }
    }
    else{
        return 0;
    }
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

    printf("%d %d %d %d %d\n", is_full(t),
        is_perfect(t), is_complete(t),
        is_degenerate(t), is_skewed(t));
    return 0;
}