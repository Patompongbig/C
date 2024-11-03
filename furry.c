#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node *next;
} node_t;

void push(node_t **stack, float value) {
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = value;
    n->next = *stack;
    *stack = n;
}

float pop(node_t **stack) {
    if (*stack == NULL) {
        return 0.0;
    }
    node_t *tmp = *stack;
    float c = tmp->data;
    *stack = tmp->next;
    free(tmp);
    return c;
}

int is_empty(node_t *stack) {
    return stack == NULL;
}

int main(void){
    node_t *land = NULL, *island = NULL;
    char side;
    int i, num, length, round = 0;
    float car_l;

    scanf("%d", &length);
    scanf("%d", &num);

    for (i = 0; i < num; i++){
        scanf("%f %c", &car_l, &side);
        if (side == 'L'){
            push(&land, car_l / 100);
        }
        else{
            push(&island, car_l / 100);
        }
    }

    while(!is_empty(land) || !is_empty(island)){
        float sum = 0.0;

        while (!is_empty(land) && (land->data + sum) <= (float)length){
            sum += pop(&land);
        }
        
        round++;

        if (is_empty(land) && is_empty(island)){
            break;
        }
        
        sum = 0.0;

        while (!is_empty(island) && (island->data + sum) <= (float)length){
            sum += pop(&island);
        }
        round++;
    }
    printf("%d", round);

    return 0;
}