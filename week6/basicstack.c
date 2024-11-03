#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef node_t stack_t;

stack_t* push(stack_t *s, int value){
    stack_t *n = (stack_t *)malloc(sizeof(stack_t));
    n -> data = value;
    n -> next = s;
    return n;
}

void top(stack_t *s){
    if (s != NULL){
        printf("%d", s -> data);
    }
    else{
        printf("Stack is empty.");
    }
}

stack_t* pop(stack_t *s){
    if (s == NULL){
        return s;
    }
    stack_t *tmp = NULL;
    tmp = s;
    s = s -> next;
    free(tmp);
    return s;
}

void empty(stack_t *s){
    if (s == NULL){
        printf("Stack is empty.");
    }
    else{
        printf("Stack is not empty.");
    }
}

void size(stack_t *s){
    int count = 0;
    node_t *ptr;

    for (ptr = s; ptr != NULL; ptr = ptr -> next){
        count += 1;
    }
    printf("%d", count);
}

int main(void) {
    stack_t *s = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                s = push(s, value);
                break;
            case 2:
                top(s);
                break;
            case 3:
                s = pop(s);
                break;
            case 4:
                empty(s);
                break;
            case 5:
                size(s);
                break;
        }
    }
    return 0;
}