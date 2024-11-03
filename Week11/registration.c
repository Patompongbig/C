#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 21
#define HASHMAP_SIZE 100003

typedef struct node {
    int num;
} node_t;

typedef struct heap {
    node_t **data;
    int last_index;
} heap_t;

typedef struct cell {
    char name[MAX_LENGTH];
    heap_t *suffix_heap;
    struct cell *next;
} cell_t;

typedef struct hash {
    cell_t *table[HASHMAP_SIZE];
} hash_t;

typedef hash_t cache_t;

void swap(heap_t *pq, int index, int parent_index) {
    node_t *tmp = pq -> data[index];
    pq -> data[index] = pq -> data[parent_index];
    pq -> data[parent_index] = tmp;
}

void bubble_up(heap_t *pq, int index) {
    int parent_index = (index - 1) / 2;
    if (index == 0) {
        return;
    }
    if (pq -> data[index] -> num < pq -> data[parent_index] -> num) {
        swap(pq, index, parent_index);
        bubble_up(pq, parent_index);
    }
}

void sort(heap_t *pq, int index) {
    int i = 2 * index + 1;
    int current = index;

    if (i <= pq -> last_index && pq -> data[i] -> num < pq -> data[current] -> num) {
        current = i;
    }
    if (i + 1 <= pq -> last_index && pq -> data[i+1] -> num < pq -> data[current] -> num) {
        current = i + 1;
    }

    if (current != index) {
        swap(pq, index, current);
        sort(pq, current);
    }
}

heap_t *init_heap(int size) {
    heap_t *pq = (heap_t *)malloc(sizeof(heap_t));
    pq->data = (node_t **)malloc(size * sizeof(node_t *));
    pq->last_index = -1;
    return pq;
}

void insert(heap_t *pq, node_t *new_node) {
    pq -> last_index++;
    pq -> data[pq->last_index] = new_node;
    bubble_up(pq, pq->last_index);
}

node_t *delete_min(heap_t *pq) {
    if (pq -> last_index == -1) {
        return NULL;
    }
    node_t *min_node = pq -> data[0];
    pq -> data[0] = pq -> data[pq -> last_index];
    pq -> last_index--;
    sort(pq, 0);
    return min_node;
}

cache_t *init_cache() {
    cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        cache->table[i] = NULL;
    }
    return cache;
}

unsigned long hash_name(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASHMAP_SIZE;
}

int is_numeric(const char *name, int *start) {
    int len = strlen(name);
    int i = len - 1;

    while (i >= 0 && name[i] >= '0' && name[i] <= '9') {
        i--;
    }

    if (i < len - 1 && i >= 0) {
        *start = i + 1;
        return 1;
    }
    return 0;
}

void extract_base_and_suffix(const char *name, char *base_name, int *suffix_number) {
    int start = 0;

    if (is_numeric(name, &start)) {
        strncpy(base_name, name, start);
        base_name[start] = '\0';
        *suffix_number = atoi(&name[start]);
    } else {
        strcpy(base_name, name);
        *suffix_number = 0;
    }
}

cell_t *find_entry(cell_t *head, const char *base_name) {
    while (head != NULL) {
        if (strcmp(head->name, base_name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

cell_t *adding(cache_t *cache, unsigned long index, const char *key) {
    cell_t *new_entry = (cell_t *)malloc(sizeof(cell_t));
    strcpy(new_entry -> name, key);
    new_entry -> suffix_heap = init_heap(101);

    for (int i = 0; i <= 100; i++) {
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node -> num = i;
        insert(new_entry -> suffix_heap, new_node);
    }

    new_entry->next = cache->table[index];
    cache->table[index] = new_entry;
    return new_entry;
}

void register_name(const char *name, cache_t *cache) {
    char base_name[MAX_LENGTH];
    int suffix_number;

    extract_base_and_suffix(name, base_name, &suffix_number);
    unsigned long index = hash_name(base_name);

    cell_t *entry = find_entry(cache->table[index], base_name);
    if (entry == NULL) {
        entry = adding(cache, index, base_name);
    }

    if (suffix_number > 0) {
        printf("OK\n");
    } else {
        node_t *next_available = delete_min(entry->suffix_heap);
        if (next_available -> num == 0) {
            printf("OK\n");
        } else {
            printf("Change to %s%d\n", base_name, next_available -> num);
        }
        free(next_available);
    }
}

int main(void) {
    int n;
    char name[MAX_LENGTH];

    cache_t *cache = init_cache();

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        register_name(name, cache);
    }

    for (int i = 0; i < HASHMAP_SIZE; i++) {
        cell_t *entry = cache -> table[i];
        while (entry != NULL) {
            cell_t *tmp = entry;
            entry = entry -> next;
            free(tmp -> suffix_heap -> data);
            free(tmp -> suffix_heap);
            free(tmp);
        }
    }
    free(cache);

    return 0;
}
