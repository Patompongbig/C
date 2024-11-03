#include <stdio.h>
#include <stdlib.h>
typedef struct cell {
    int data;
    int mem_addr;
} cell_t;
typedef struct hash {
    cell_t *table;
    int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;

memory_t *init_memory(int size) {
    memory_t *memory = (memory_t *)malloc(
    sizeof(memory_t)*size);
    int i = 0;

    for (i=0; i<size; i++)
        memory[i] = rand();
    return memory;
}

cache_t *init_cache(int cache_size) {
    cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
    cache->table = (cell_t *)malloc(sizeof(cell_t) * cache_size);
    cache->cache_size = cache_size;

    int i = 0, initialized_entries = 0, total_entries = cache_size;
    for (i = 0; i < cache_size; i++) {
        cache->table[i].mem_addr = -1;
        cache->table[i].data = 0;
        initialized_entries++;
    }

    return cache;
}

void get_data(int adr, memory_t *memory, cache_t *cache) {
    int cache_index = adr % cache->cache_size;
    int loaded_cache = 0;

    if (cache->table[cache_index].mem_addr == adr) {
        printf("Address %d is loaded\n", adr);
        printf("Data: %d\n", cache->table[cache_index].data);
        loaded_cache = 1;
    }

    if (!loaded_cache) {
        if (cache->table[cache_index].mem_addr != -1) {
            printf("Index: %d is used\n", cache_index);
        }
        printf("Load from memory\n");

        int new_data = memory[adr];
        cache->table[cache_index].data = new_data;
        cache->table[cache_index].mem_addr = adr;

        printf("Data: %d\n", cache->table[cache_index].data);
    }
}

int main(void) {
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;

    scanf("%d %d %d", &memory_size, &cache_size, &n);

    memory = init_memory(memory_size);
    cache = init_cache(cache_size);

    for (i=0; i<n; i++) {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }

    return 0;
}