#include "sort.h"
#include <stdlib.h>
void Bubblesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int i = 0;
    for (i = 0; i < number - 1; i++) {
        int j;
        for (j = (number - 1); j > i; j--) {
            if (comparator(first + (j - 1) * size, first + j * size) > 0) {
                swap(first + (j - 1) * size, first + j * size, size);
            }
        }
    }
}

void Gnomesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int i = 1;
    int j = 2;
    while (i < number) {
        if (comparator(first + i * size, first + (i - 1) * size) > 0) {
            i = j;
            j++;
        }
        else {
            swap(first + (i - 1) * size, first + i * size, size);
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
        }
    }
}



void Mergesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int mid = number / 2;
    if (number % 2 == 1)
        mid++;
    int a = 1;
    int* newarr = (int*) malloc(number * sizeof(int));
    int st;
    while (a < number) {
        st = a;
        int k = 0;
        int l = mid;
        int m = 0;
        while (st <= mid) {
            while ((k < st) && (l < number) && (l < (mid + st))) {
                if (comparator(first + l * size, first + k * size) > 0) {
                    newarr[m] = *((int*) (first + k * size));
                    k++; m++;
                }
                else {
                    newarr[m] = *((int*) (first + l * size));
                    l++; m++;
                }
            }
            while (k < st) {
                newarr[m] = *((int*) (first + k * size));
                k++; m++;
            }
            while ((l < (mid + st)) && (l < number)) {
                newarr[m] = *((int*) (first + l * size));
                l++; m++;
            }
            st = st + a;
        }
        a = a * 2;
        for (k = 0; k < number; k++)
            *((int*) (first + k * size)) = newarr[k];
    }
    free(newarr);
}