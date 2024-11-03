#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

void push(node_t **stack, int value) {
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = value;
    n->next = *stack;
    *stack = n;
}

int pop(node_t **stack) {
    if (*stack == NULL) {
        return 0;
    }
    node_t *tmp = *stack;
    int c = tmp->data;
    *stack = tmp->next;
    free(tmp);
    return c;
}

int is_empty(node_t *stack) {
    return stack == NULL;
}

int main(void){
    node_t *main = NULL, *sub = NULL;
    int num, i, n, sort = 1;
    scanf("%d", &num);

    for (i = 0;i < num;i++){
        scanf("%d", &n);
        if (n == sort){
            push(&main, n);
            sort++;
        }
        else {
            push(&sub, n);
        }
        while (!is_empty(sub) && sub->data == sort) {
            push(&main, pop(&sub));
            sort++;
        }
    }

    if (is_empty(sub)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}