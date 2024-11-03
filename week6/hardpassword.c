#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *next;
} node_t;

void push(node_t **stack, char value) {
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
    char c = tmp->data;
    *stack = tmp->next;
    free(tmp);
    return c;
}

int main(void) {
    node_t *stack = NULL;
    int i;
    char password[200000];

    scanf("%s", password);

    for (i = 0; password[i] != 'x' && password[i] != '\0'; i++) {
        push(&stack, password[i]);
    }

    if (password[i] != 'x') {
        printf("0");
        return 0;
    }

    i++;
    while (password[i] != 'y' && password[i] != '\0') {
        if (pop(&stack) != password[i]) {
            printf("0");
            return 0;
        }
        i++;
    }

    if (password[i] != 'y') {
        printf("0");
        return 0;
    }

    if (stack != NULL) {
        printf("0");
    } else {
        printf("1");
    }

    return 0;
}