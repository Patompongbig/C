#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
int *data;
int last_index;
} heap_t;

heap_t *init_heap(int m){
    heap_t *h = (heap_t*)malloc(sizeof(heap_t));
    h -> data = (int*)malloc(sizeof(int)*(m+1));
    h -> last_index = 0;
    return h;
}

heap_t *insert(heap_t *m, int value){
    m -> last_index++;
    m -> data[m -> last_index] = value;
    int tmp_index1 = m -> last_index;
    int tmp_index2 = (m -> last_index)/2;
    while(tmp_index1 > 1 && m -> data[tmp_index2] < m -> data[tmp_index1]){
        m -> data[tmp_index1] = m -> data[tmp_index2];
        m -> data[tmp_index2] = value;
        tmp_index1 = tmp_index2;
        tmp_index2 = tmp_index2 / 2;
    }
    return m;
}

heap_t *delete_max(heap_t *m){
    if (m -> last_index == 0){
        return m;
    }
    m -> data[1] = m -> data[m -> last_index];
    m -> last_index--;
    int index = 1;
    while (index * 2 <= m -> last_index) {
        int swap = index;
        int i = index * 2;

        if (i <= m -> last_index && m -> data[i] > m -> data[swap]) {
            swap = i;
        }
        if (i + 1 <= m -> last_index && m -> data[i + 1] > m -> data[swap]) {
            swap = i + 1;
        }
        if (swap == index) {
            break;
        }

        int tmp = m -> data[index];
        m -> data[index] = m -> data[swap];
        m -> data[swap] = tmp;

        index = swap;
    }
    return m;
}

int find_max(heap_t *m){
    if (m -> last_index > 0){
        return m -> data[1];
    }
    return -1;
}

heap_t *update_key(heap_t *m, int old_key, int new_key){
    int index = 1;
    while (m -> data[index] != old_key){
        index++;
    }
    m -> data[index] = new_key;
    if(m -> data[index] > m -> data[index / 2]){
        while (index > 1){
            int swap = index;
            int i = index / 2;
            if (m -> data[i] < m -> data[swap]){
                swap = i;
            }
            if (swap == index){
                break;
            }

            int tmp = m -> data[index];
            m -> data[index] = m -> data[swap];
            m -> data[swap] = tmp;

            index = swap;
        }
    }
    else {
        while (index * 2 <= m -> last_index){
            int swap = index;
            int i = index * 2;

            if (i <= m -> last_index && m -> data[i] > m -> data[swap]){
                swap = i;
            }
            if (i + 1 <= m -> last_index && m -> data[i + 1] > m -> data[swap]){
                swap = i + 1;
            }
            if (swap == index){
                break;
            }

            int tmp = m -> data[index];
            m -> data[index] = m -> data[swap];
            m -> data[swap] = tmp;

            index = swap;
        }
    }
    return m;
}

void bfs(heap_t *m){
    int i = 1;
    while(i <= m -> last_index){
        printf("%d ", m -> data[i]);
        i++;
    }
    printf("\n");
    return;
}


int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;

    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
        case 1:
            scanf("%d", &data);
            insert(max_heap, data);
            break;
        case 2:
            delete_max(max_heap);
            break;
        case 3:
            printf("%d\n", find_max(max_heap));
            break;
        case 4:
            scanf("%d %d", &old_key, &new_key);
            update_key(max_heap, old_key,
            new_key);
            break;
        case 5:
            bfs(max_heap);
            break;
        }
    }
    return 0;
}