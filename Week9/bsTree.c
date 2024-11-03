#include <stdio.h>
#include <stdlib.h>

typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t bst_t;

bst_t* insert(bst_t *t, int value){
    bst_t *n = (bst_t *)malloc(sizeof(bst_t));
    n -> data = value;
    n -> left = NULL;
    n -> right =NULL;

    if (t == NULL){
        return n;
    }

    bst_t *tmp = t;
    bst_t *parent = NULL;
    while(tmp != NULL){
        parent = tmp;
        if (tmp -> data < value){
            tmp = tmp -> right;
        }
        else{
            tmp = tmp -> left;
        }
    }

    if (parent -> data < value){
        parent -> right = n;
    }
    else{
        parent -> left = n;
    }

    return t;
}

bst_t* delete(bst_t *t, int value){
    bst_t *tmp = t;
    bst_t *n = t;
    while(tmp -> data != value){
        n = tmp;
        if (tmp -> data < value){
            tmp = tmp -> right;
        }
        else{
            tmp = tmp -> left;
        } 
    }

    if (tmp -> left != NULL && tmp -> right != NULL){
        n = tmp -> right;
        while (n -> left != NULL){
            n = n -> left;
        }
        int new = n -> data;
        delete(t, new);
        tmp -> data = new;
        return t;
    }

    else if (tmp -> left != NULL || tmp -> right != NULL){
        if (n != tmp){
            if (n -> left == tmp){
                if (tmp -> left != NULL){
                    n -> left = tmp -> left;
                    tmp -> left = NULL;
                }
                else{
                    n -> left = tmp -> right;
                    tmp -> right = NULL;
                }
            }
            else{
                if (tmp -> left != NULL){
                    n -> right = tmp -> left;
                    tmp -> left = NULL;
                }
                else{
                    n -> right = tmp -> right;
                    tmp -> right = NULL;
                }
            }
            free(tmp);
            return t;
        }
        else{
            if (tmp -> left != NULL){
                    n = tmp -> left;
                    tmp -> left = NULL;
                }
            else{
                    n = tmp -> right;
                    tmp -> right = NULL;
                }
                free(tmp);
                return n;
        }
    }

    else{
        if (n != tmp){
            if (n -> left == tmp){
                n -> left = NULL;
            }
            else{
                n -> right = NULL;
            }
            free(tmp);
            return t;
        }
        else{
            free(tmp);
            return NULL;
        }
    }
    return t;
}

int find(bst_t *t, int value){
    bst_t *tmp = t;
    while(tmp != NULL){
        if (tmp -> data == value){
            return 1;
        }
        else if (tmp -> data < value){
            tmp = tmp -> right;
        }
        else{
            tmp = tmp -> left;
        }
    }
    return 0;
}

int find_min(bst_t *t){
    bst_t *tmp = t;
    while(tmp -> left != NULL){
        tmp = tmp -> left;
    }
    return tmp -> data;
}

int find_max(bst_t *t){
    bst_t *tmp = t;
    while(tmp -> right != NULL){
        tmp = tmp -> right;
    }
    return tmp -> data;
}

int in_order_kth(bst_t *t, int *k) {
    if (t == NULL) {
        return -1;
    }

    int result = in_order_kth(t->left, k);
    if (result != -1) {
        return result;
    }

    (*k)--;
    if (*k == 0) {
        return t->data;
    }

    return in_order_kth(t->right, k);
}

int find_k_th(bst_t *t, int k) {
    return in_order_kth(t, &k);
}

int main(void) {
    bst_t *t = NULL;
    int n, i;
    int command, data, k;
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                scanf("%d", &data);
                printf("%d\n", find(t, data));
                break;
            case 4:
                printf("%d\n", find_min(t));
                break;
            case 5:
                printf("%d\n", find_max(t));
                break;
            case 6:
                scanf("%d", &k);
                printf("%d\n", find_k_th(t, k));
                break;
        }
    }
    return 0;
}