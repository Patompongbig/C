#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char arr[], int l, int m, int r){
    int i, j, k;
    int nl = m - l + 1, nr = r - m;
    char L[nl], R[nr];
    
    for (i = 0; i < nl; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < nr; j++){
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < nl && j < nr){
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < nl){
        arr[k++] = L[i++];
    }
    while (j < nr){
        arr[k++] = R[j++];
    }
}

void merge_sort(char arr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void anagram(char dict[][51], char sorted_dict[][51], int m, char key[]){
    char sorted_key[51];
    strcpy(sorted_key, key);
    
    int len = strlen(key);
    merge_sort(sorted_key, 0, len - 1);

    int found = 0;
    for (int i = 0; i < m; i++) {
        if (strcmp(sorted_dict[i], sorted_key) == 0) {
            printf("%s ", dict[i]);
            found = 1;
        }
    }
    printf("\n");
    if (!found) {
        printf("");
    }
}

int main(void){
    int m, n;
    char key[51];

    scanf("%d %d", &m, &n);

    char dict[m][51];
    char sorted_dict[m][51];

    for (int i = 0; i < m; i++) {
        scanf("%s", dict[i]);
        strcpy(sorted_dict[i], dict[i]);

        int len = strlen(dict[i]);
        merge_sort(sorted_dict[i], 0, len - 1);
    }

    for (int i = 0; i < n; i++) {
        scanf("%s", key);
        anagram(dict, sorted_dict, m, key);
    }

    return 0;
}