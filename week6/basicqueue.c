#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef node_t queue_t;

queue_t* enqueue(queue_t* q, int value){
    queue_t *n = (queue_t *)malloc(sizeof(queue_t));
    n -> data = value;
    n -> next = q;
    return n;
}

queue_t* dequeue(queue_t* q) {
    if (q == NULL) {
        printf("Queue is empty.\n");
        return q;
    }
    if (q->next == NULL) {
        printf("%d\n", q->data);
        free(q);
        return NULL;
    }
    queue_t* ptr = q;
    while (ptr->next->next != NULL) {
        ptr = ptr->next;
    }
    printf("%d\n", ptr->next->data);
    free(ptr->next);
    ptr->next = NULL;
    return q;
}

void show(queue_t *q){
    if (q == NULL){
        printf("Queue is empty.\n");
    }
    queue_t *ptr = NULL;
    while (q != NULL){
        ptr = enqueue(ptr, q -> data);
        q = q -> next;
    }
    while (ptr != NULL){
        printf("%d ", ptr -> data);
        ptr = ptr -> next;
    }
    printf("\n");
}

void empty(queue_t *q){
    if (q == NULL){
        printf("Queue is empty.\n");
    }
    else{
        printf("Queue is not empty.\n");
    }
}

void size(queue_t *q){
    int count = 0;
    while (q != NULL){
        count++;
        q = q-> next;
    }
    printf("%d\n", count);
}

int main(void) {
    queue_t *q = NULL;
    int n, i, command, value;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                q = enqueue(q, value);
                break;
            case 2:
                q = dequeue(q);
                break;
            case 3:
                show(q);
                break;
            case 4:
                empty(q);
                break;
            case 5:
                size(q);
                break;
        }
    }
    return 0;
}