#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int payment;
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

tree_t* attach(tree_t *t, int p, int c, int cost){
    tree_t *n = (tree_t *)malloc(sizeof(tree_t));
    n -> value = c;
    n -> next_sibling = NULL;
    n -> parent = NULL;
    n -> first_child = NULL;
    if (t == NULL){
        n->payment = cost;
        return n;
    }
    tree_t *tmp = search_t(t, p);
    n -> parent = tmp;
    n -> payment = tmp -> payment + cost;
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

typedef struct nodeq {
    int value;
    struct nodeq *next;
} nodeq_t;
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

int dfs(tree_t *t, int cost){
    stack_t *s = NULL;
    tree_t *tmp = t;
    int count = -1;

    push(&s, tmp -> value);

    while (s != NULL){
        int node_value = pop(&s);

        tree_t *tmp = search_t(t, node_value);
        if (tmp -> payment <= cost){
            count += 1;
            tree_t *sib = tmp -> first_child;
            while (sib != NULL){
                push(&s, sib -> value);
                sib = sib -> next_sibling;
            }
        }
        else{
            detach(t, node_value);
        }
    }
    return count;
}

int main(void){
    tree_t *t = NULL;
    t = attach(t, 0, 0, 0);
    int n, m, point, value, cost, count = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++){
        scanf("%d %d %d", &point, &value, &cost);
        attach(t, point, value, cost);
    }
    count = dfs(t, m);
    printf("%d", count);

    return 0;
}