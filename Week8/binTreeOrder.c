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

typedef struct nodeq {
    int value;
    struct nodeq *next;
} nodeq_t;

typedef struct queue {
    nodeq_t *front;
    nodeq_t *rear;
} queue_t;

void enqueue(queue_t *q, int v){
    nodeq_t *node = (nodeq_t *)malloc(sizeof (nodeq_t));
    node -> value = v;
    node -> next = NULL;
    if (q->rear == NULL) {
        q->front = node;
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

int dequeue(queue_t *q){
    if (q -> front == NULL){
        return -1;
    }
    nodeq_t *tmp = q -> front;
    int value = tmp -> value;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(tmp);
    return value;
}

typedef nodeq_t stack_t;

void push(stack_t **s, int v){
    nodeq_t *n = (nodeq_t *)malloc(sizeof (nodeq_t));
    n -> value = v;
    n -> next = *s;
    *s = n;
}

int pop(stack_t **s){
    nodeq_t * tmp = NULL;
    int v;

    if((tmp = *s) == NULL){
        return -1;
    }
    v = tmp -> value;
    *s = tmp -> next;
    free(tmp);
    return v;
}

void print_preorder(tree_t *t){
    stack_t *s = NULL;
    tree_t *tmp = t;

    push(&s, tmp -> data);

    while (s != NULL){
        int node_value = pop(&s);
        printf("%d ", node_value);

        tmp = searchNode(t, node_value);
        if (tmp -> right != NULL){
            push(&s, tmp -> right -> data);
        }
        if (tmp -> left != NULL){
            push(&s, tmp -> left -> data);
        }
    }
    printf("\n");
}

void print_postorder(tree_t *t){
    stack_t *s = NULL;
    stack_t *n = NULL;
    tree_t *tmp = t;

    push(&n, tmp -> data);

    while (n != NULL){
        int node_value = pop(&n);
        push(&s, node_value);

        tmp = searchNode(t, node_value);
        if (tmp -> left != NULL){
            push(&n, tmp -> left -> data);
        }
        if (tmp -> right != NULL){
            push(&n, tmp -> right -> data);
        }
    }

    while (s != NULL){
        int node_value = pop(&s);
        printf("%d ", node_value);
    }
    printf("\n");
}

void print_inorder(tree_t *t){
    if (t == NULL){
        return;
    }
    print_inorder(t -> left);
    printf("%d", t -> data);
    print_inorder(t -> right);
    return;
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

    print_preorder(t);
    print_postorder(t);
    print_inorder(t);

    return 0;
}