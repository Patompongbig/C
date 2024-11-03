#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bit_code {
    int num;           
    char* key;        
    struct bit_code *left, *right;
} bit_code_t;

typedef struct heap {
    bit_code_t **data;  
    int last_index;    
} heap_t;

bit_code_t* bit_tree(char* word, int freq) {
    bit_code_t* tree = (bit_code_t*)malloc(sizeof(bit_code_t));
    tree->left = NULL;
    tree->right = NULL;
    tree->key = strdup(word);  
    tree->num = freq;        
    return tree;
}

heap_t *init_heap(int m) {
    heap_t *h = (heap_t*)malloc(sizeof(heap_t));
    h->data = (bit_code_t**)malloc(sizeof(bit_code_t*) * (m + 1));
    h->last_index = 0;  
    return h;
}

heap_t *insert(heap_t *m, bit_code_t* tree) {
    m->last_index++;
    int current_index = m->last_index;
    int parent_index = current_index / 2;

    while (current_index > 1 && tree->num < m->data[parent_index]->num) {
        m->data[current_index] = m->data[parent_index];
        current_index = parent_index;
        parent_index = parent_index / 2;
    }
    m->data[current_index] = tree;
    return m;
}

bit_code_t* delete_min(heap_t *m) {
    if (m->last_index == 0) return NULL;  

    bit_code_t* min_node = m->data[1];  
    m->data[1] = m->data[m->last_index]; 
    m->last_index--;

    int current = 1;
    int child = 2 * current;
    while (child <= m->last_index) {
        if (child + 1 <= m->last_index && m->data[child + 1]->num < m->data[child]->num)
            child++;

        if (m->data[current]->num > m->data[child]->num) {
            bit_code_t* temp = m->data[current];
            m->data[current] = m->data[child];
            m->data[child] = temp;
            current = child;
            child = 2 * current;
        } else {
            break;
        }
    }
    return min_node;
}

bit_code_t* build_huffman_tree(heap_t* heap) {
    while (heap->last_index > 1) {
        bit_code_t* left = delete_min(heap);
        bit_code_t* right = delete_min(heap);

        bit_code_t* internal_node = bit_tree("", left->num + right->num);
        internal_node->left = left;
        internal_node->right = right;

        insert(heap, internal_node);
    }
    return delete_min(heap); 
}
void capture_codes(bit_code_t* root, char* code, int top, char codes[][100]) {
    if (root->left) {
        code[top] = '0';
        capture_codes(root->left, code, top + 1, codes);
    }

    if (root->right) {
        code[top] = '1';
        capture_codes(root->right, code, top + 1, codes);
    }

    if (root->left == NULL && root->right == NULL) {
        code[top] = '\0';  
        strcpy(codes[root->num], code);  
        printf("%s: %s\n", root->key, code);  
    }
}

int main(void) {
    heap_t *max_heap = NULL;
    int n, i;
    int freq;
    char key[16];
    char codes[1000][100]; 

    scanf("%d", &n);

    max_heap = init_heap(n);
    for (i = 0; i < n; i++) {
        scanf("%s %d", key, &freq);
        bit_code_t* node = bit_tree(key, freq);  
        insert(max_heap, node); 
    }

    bit_code_t* huffman_tree = build_huffman_tree(max_heap);

    char code[100];
    capture_codes(huffman_tree, code, 0, codes);

    return 0;
}