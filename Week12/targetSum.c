#include <stdio.h>

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int nl = m - l + 1, L[nl];
    int nr = r - m, R[nr];
    
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

void merge_sort(int arr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void target_sum(int arr[], int n, int key) {
    int found = 0;

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue; 
        }

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == key) {
                printf("%d %d %d\n", arr[i], arr[left], arr[right]);
                found = 1;
                
                while (left < right && arr[left] == arr[left + 1]) {
                    left++;
                }
                while (left < right && arr[right] == arr[right - 1]) {
                    right--;
                }
                
                left++;
                right--;
            } 
            else if (sum < key) {
                left++;
            } 
            else {
                right--;
            }
        }
    }
    if (!found) {
        printf("\n");
    }
}

int main(void) {
    int n, key;
    scanf("%d %d", &n, &key);
    int num[n];

    for (int i = 0; i < n; i++){
        scanf("%d", &num[i]);
    }

    merge_sort(num, 0, n - 1);

    target_sum(num, n, key);

    return 0;
}
