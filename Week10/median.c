#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int size;
    int capacity;
} heap_t;

heap_t *init_heap(int capacity) {
    heap_t *h = (heap_t*)malloc(sizeof(heap_t));
    h->data = (int*)malloc(sizeof(int) * (capacity + 1));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void insert_max_heap(heap_t *h, int value) {
    h->size++;
    h->data[h->size] = value;
    int idx = h->size;
    while (idx > 1 && h->data[idx / 2] < h->data[idx]) {
        int temp = h->data[idx];
        h->data[idx] = h->data[idx / 2];
        h->data[idx / 2] = temp;
        idx /= 2;
    }
}

void insert_min_heap(heap_t *h, int value) {
    h->size++;
    h->data[h->size] = value;
    int idx = h->size;
    while (idx > 1 && h->data[idx / 2] > h->data[idx]) {
        int temp = h->data[idx];
        h->data[idx] = h->data[idx / 2];
        h->data[idx / 2] = temp;
        idx /= 2;
    }
}

int remove_max(heap_t *h) {
    int max = h->data[1];
    h->data[1] = h->data[h->size--];
    int idx = 1;
    while (idx * 2 <= h->size) {
        int left = idx * 2;
        int right = left + 1;
        int larger = (right <= h->size && h->data[right] > h->data[left]) ? right : left;
        if (h->data[idx] >= h->data[larger]) break;
        int temp = h->data[idx];
        h->data[idx] = h->data[larger];
        h->data[larger] = temp;
        idx = larger;
    }
    return max;
}

int remove_min(heap_t *h) {
    int min = h->data[1];
    h->data[1] = h->data[h->size--];
    int idx = 1;
    while (idx * 2 <= h->size) {
        int left = idx * 2;
        int right = left + 1;
        int smaller = (right <= h->size && h->data[right] < h->data[left]) ? right : left;
        if (h->data[idx] <= h->data[smaller]) break;
        int temp = h->data[idx];
        h->data[idx] = h->data[smaller];
        h->data[smaller] = temp;
        idx = smaller;
    }
    return min;
}

void rebalance_heaps(heap_t *max_heap, heap_t *min_heap) {
    if (max_heap->size > min_heap->size + 1) {
        int max = remove_max(max_heap);
        insert_min_heap(min_heap, max);
    } else if (min_heap->size > max_heap->size) {
        int min = remove_min(min_heap);
        insert_max_heap(max_heap, min);
    }
}

float get_median(heap_t *max_heap, heap_t *min_heap) {
    if (max_heap->size == min_heap->size) {
        return (max_heap->data[1] + min_heap->data[1]) / 2.0;
    } else {
        return max_heap->data[1];
    }
}

int main() {
    int n, num;
    scanf("%d", &n);

    heap_t *max_heap = init_heap(n);
    heap_t *min_heap = init_heap(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &num);

        if (max_heap->size == 0 || num <= max_heap->data[1]) {
            insert_max_heap(max_heap, num);
        } else {
            insert_min_heap(min_heap, num);
        }

        rebalance_heaps(max_heap, min_heap);

        printf("%.1f\n", get_median(max_heap, min_heap));
    }

    free(max_heap->data);
    free(max_heap);
    free(min_heap->data);
    free(min_heap);

    return 0;
}