#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next_sibling;
    struct node *first_child;
    struct node *parent;
} node_t;
typedef node_t tree_t;

void free_subtree(tree_t *subtree) {
    if (subtree == NULL)
        return;
    free_subtree(subtree->first_child);
    free_subtree(subtree->next_sibling);
    free(subtree);
}

tree_t* search_t(tree_t *t, int p){
    if (t == NULL){
        return NULL;
    }
    if (t -> value == p){
        return t;
    }
    tree_t *pos = search_t(t -> first_child, p);
    if (pos != NULL){
        return pos;
    }
    return search_t(t -> next_sibling, p);
}

tree_t* attach(tree_t *t, int p, int c){
    tree_t *n = (tree_t *)malloc(sizeof(tree_t));
    n -> value = c;
    n -> next_sibling = NULL;
    n -> parent = NULL;
    n -> first_child = NULL;
    if (t == NULL){
        return n;
    }
    tree_t *tmp = search_t(t, p);
    n -> parent = tmp;
    if (tmp -> first_child == NULL){
        tmp -> first_child = n;
    }
    else{
        tmp = tmp -> first_child;
        while (tmp -> next_sibling != NULL){
            tmp = tmp -> next_sibling;
        }
        tmp -> next_sibling = n;
    }
    return t;
}

tree_t* detach(tree_t *t, int p){
    if (t == NULL){
        return NULL;
    }

    tree_t *tmp = search_t(t, p);
    tree_t *ptr = tmp -> parent;

    if (tmp -> parent == NULL){
        free_subtree(tmp);
        return NULL;
    }

    if (ptr -> first_child == tmp) {
        ptr -> first_child = tmp -> next_sibling;
    } 
    else {
        tree_t *sibling = ptr->first_child;
        while (sibling->next_sibling != tmp) {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = tmp->next_sibling;
    }

    tmp->next_sibling = NULL;
    tmp->parent = NULL;
    free_subtree(tmp);

    return t;
}

int search(tree_t *t, int p){
    if (t == NULL){
        return 0;
    }
    if (t -> value == p){
        return 1;
    }
    if (search(t -> first_child, p)){
        return 1;
    }
    if (search(t -> next_sibling, p)){
        return 1;
    }
    return 0;
}

int degree(tree_t *t, int p){
    int count = 0;
    tree_t *tmp = search_t(t, p);
    if (tmp -> first_child != NULL){
        tmp = tmp -> first_child;
        count = 1;
        while (tmp -> next_sibling != NULL){
            tmp = tmp -> next_sibling;
            count += 1;
        }
    }
    else{
        count = 0;
    }
    return count;
}

int is_root(tree_t *t, int p){
    tree_t *tmp = search_t(t, p);
    if (tmp -> value == t -> value){
        return 1;
    }
    return 0;
}

int is_leaf(tree_t *t, int p){
    tree_t *tmp = search_t(t, p);
    if (tmp -> first_child == NULL){
        return 1;
    }
    return 0;
}

void siblings(tree_t *t, int p){
    tree_t *tmp = search_t(t, p);
    if (tmp -> parent == NULL){
        printf("\n");
        return;
    }
    tmp = tmp -> parent -> first_child;
    if (tmp -> next_sibling == NULL || tmp == NULL){
        printf("\n");
        return;
    }
    while (tmp != NULL){
        if (tmp -> value != p){
            printf("%d " ,tmp -> value);
        }
        tmp = tmp -> next_sibling;
    }
    printf("\n");
}

int depth(tree_t *t, int p){
    int count = -1;
    tree_t *tmp = search_t(t, p);
    while (tmp != NULL){
        tmp = tmp -> parent;
        count += 1;
    }
    return count;
}

void print_path(tree_t *t, int s, int e){
    tree_t *start = search_t(t, s);
    tree_t *end = search_t(t, e);
    int d = depth(t, e) - depth(t, s) + 1;
    int p[d];
    int i = 0;

    while (end != start){
        p[i] = end -> value;
        end = end -> parent;
        i += 1;
    }
    p[i] = end -> value;

    while (i != -1){
        printf("%d ", p[i]);
        i -= 1;
    }
    printf("\n");
}

int path_length(tree_t *t, int s, int e){
    int d = depth(t, e) - depth(t, s) + 1;
    return d;
}

void ancestor(tree_t *t, int a){
    tree_t *tmp = search_t(t, a);
    int d = depth(t, a) + 1;
    int p[d];
    int i = 0;

    while (tmp != t){
        p[i] = tmp -> value;
        tmp = tmp -> parent;
        i += 1;
    }
    p[i] = tmp -> value;

    while (i != -1){
        printf("%d ", p[i]);
        i -= 1;
    }
    printf("\n");
}

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

void bfs(tree_t *t){
    queue_t q = {NULL, NULL};
    tree_t *tmp = t;

    enqueue(&q, tmp -> value);

    while (q.front != NULL){
        int node_value = dequeue(&q);
        printf("%d ", node_value);

        tree_t *tmp = search_t(t, node_value);
        tree_t *sib = tmp -> first_child;
        while (sib != NULL){
            enqueue(&q, sib -> value);
            sib = sib -> next_sibling;
        }
    }
    printf("\n");
}

void descendant(tree_t *t, int d){
    tree_t *tmp = search_t(t, d);
    bfs(tmp);
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

void dfs(tree_t *t){
    stack_t *s = NULL;
    tree_t *tmp = t;

    push(&s, tmp -> value);

    while (s != NULL){
        int node_value = pop(&s);
        printf("%d ", node_value);

        tree_t *tmp = search_t(t, node_value);
        tree_t *sib = tmp -> first_child;
        stack_t *tmp_s = NULL;
        while (sib != NULL){
            push(&tmp_s, sib -> value);
            sib = sib -> next_sibling;
        }
        while (tmp_s != NULL){
            push(&s, pop(&tmp_s));
        }
    }
    printf("\n");
}

void print_tree(tree_t *t){
    stack_t *s = NULL;
    tree_t *tmp = t;

    push(&s, tmp -> value);

    while (s != NULL){
        int node_value = pop(&s);
        int d = depth(t, node_value);
        for (int i = 0 ; i < d; i++){
            printf("  ");
        }
        printf("%d\n", node_value);

        tree_t *tmp = search_t(t, node_value);
        tree_t *sib = tmp -> first_child;
        stack_t *tmp_s = NULL;
        while (sib != NULL){
            push(&tmp_s, sib -> value);
            sib = sib -> next_sibling;
        }
        while (tmp_s != NULL){
            push(&s, pop(&tmp_s));
        }
    }
    printf("\n");
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
        case 1:
            scanf("%d %d", &parent, &child);
            t = attach(t, parent, child);
            break;
        case 2:
            scanf("%d", &node);
            t = detach(t, node);
            break;
        case 3:
            scanf("%d", &node);
            printf("%d\n", search(t, node));
            break;
        case 4:
            scanf("%d", &node);
            printf("%d\n", degree(t, node));
            break;
        case 5:
            scanf("%d", &node);
            printf("%d\n", is_root(t, node));
            break;
        case 6:
            scanf("%d", &node);
            printf("%d\n", is_leaf(t, node));
            break;
        case 7:
            scanf("%d", &node);
            siblings(t, node);
            break;
        case 8:
            scanf("%d", &node);
            printf("%d\n", depth(t, node));
            break;
        case 9:
            scanf("%d %d", &start, &end);
            print_path(t, start, end);
            break;
        case 10:
            scanf("%d %d", &start, &end);
            printf("%d\n",
            path_length(t, start, end));
            break;
        case 11:
            scanf("%d", &node);
            ancestor(t, node);
            break;
        case 12:
            scanf("%d", &node);
            descendant(t, node);
            break;
        case 13:
            bfs(t);
            break;
        case 14:
            dfs(t);
            break;
        case 15:
            print_tree(t);
            break;
        }
    }
    return 0;
}
