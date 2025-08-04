#include <stdio.h>
#include <stdlib.h>

void remove_duplicates(int *arr, int *size) {
    int *ptr1, *ptr2, *end, i, j;
    end = arr + *size;

    for (ptr1 = arr; ptr1 < end; ptr1++) {
        ptr2 = ptr1 + 1;
        for (i = (ptr1 - arr) + 1; i < *size; ) {
            if (*ptr1 == arr[i]) {
                // Shift elements left to overwrite the duplicate
                for (j = i; j < *size - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                (*size)--;  // Decrease size
                end--;      // Update end pointer
            } else {
                i++;
            }
        }
    }
}

int main() {
    int n, i;
    int *arr;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));  // Dynamic allocation

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", arr + i);  // Using pointer arithmetic
    }

    remove_duplicates(arr, &n);

    printf("Array after removing duplicates:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    free(arr);  // Free allocated memory
    return 0;
}