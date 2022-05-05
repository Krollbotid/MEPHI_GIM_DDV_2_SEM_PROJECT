#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "useful.h"
#include <math.h>
#include "sort.h"
#include "inout.h"

int compid(const void *x1, const void *x2){
    unsigned long long y1 = (*(stc*)x1).id, y2 = (*(stc*)x2).id;
    if (y1 > y2){
        return 1;
    } else {
        if (y1 == y2){
            return 0;
        } else {
            return -1;
        }
    }
}

int compname(const void *x1, const void *x2){
    stc *t1 = (stc*) x1, *t2 =  (stc*) x2;
    char *y1 = (*t1).name, *y2 = (*t2).name;
    return strcmp((const char*) y1, (const char*) y2);
}

int compint(const void *x1, const void *x2){
    unsigned long long y1 = *((int*) x1), y2 = *((int*) x2);
    if (y1 > y2) {
        return 1;
    }
    if (y1 == y2){
        return 0;
    }
    return -1;
}

int binsearch(void *beg, size_t number, size_t size, void *item, size_t sortstate){
    int (*comparator) (const void *, const void *) = NULL;
    switch(sortstate){
	    case 1:
	        comparator = &compid;
	        break;
	    case 2:
	        comparator = &compname;
	        break;
	    default:
	        return -1;
    }
    int left=0, right = (int) number-1, search=-1, mid=-1;
    while(left<right){
	    mid = left + (right-left)/2;
	    int comp=comparator(item, beg+mid*size);
	    if (comp==0){
	        search=mid;
	        break;
	    }
	    if (comp==1){
	        left=mid+1;
	    } else {
	        right=mid;
	    }
    }
    if (search==-1){
	    search=left;
    }
    return search;
}

void swap(void *fir, void *sec, size_t size){
    void *buf=malloc(size);
    memcpy(buf, (const void*) fir, size);
    memcpy(fir, (const void*) sec, size);
    memcpy(sec, (const void*) buf, size);
    free(buf);
}

void combsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)){
    const double factor = 1.2473309;
	int step = number, i, swaps = 1;
    while((step > 1) || (swaps)){
        step = (int) (step / factor);
        if (step < 1){
            step = 1;
        }
        swaps = 0;
        for (i = 0; i < number - step; i++) {
            if (comparator(first + i * size, first + (i + step) * size) > 0){
                swap(first + i * size, first + (i + step) * size, size);
                swaps = 1;
            }
        }
    }
}

void insertsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)){
    int i=0;
    void *key=malloc(size);
    for (i=1; i<number; i++){
        memcpy(key, (const void*) first+i*size, size);
        int j=i-1;
        while((j>=0)&&(comparator(first+j*size, key)>0)){
            memcpy(first+(j+1)*size, (const void*) first+j*size, size);
            j-=1;
        }
        memcpy(first+(j+1)*size, (const void*) key, size);
    }
    free(key);
}

void doubleselectionsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)){
    int i=0;
    for (i=0; i<number/2+1; i++){
        int max=i, min=i, j=i;
        for (; j<number-i; j++){
            if(comparator(first+j*size, first+max*size)>0){
                max=j;
            }
            if(comparator(first+min*size, first+j*size)>0){
                min=j;
            }
        }
        if (max!=(number-i-1)){
            swap(first+max*size, first+(number-i-1)*size, size);
        }
        if (min!=i){
            swap(first+min*size, first+i*size, size);
        }
    }
}

void oddevensort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    int i = 0, sorted = 0;
	while (!sorted) {
        sorted = 1;
		for (i = 0; i + 1 < number; i += 2) {
			if (comparator(first + i * size, first + (i + 1) * size) > 0) {
				swap(first + i * size, first + (i + 1) * size, size);
                sorted = 0;
			}
		}
        for (i = 1; i + 1 < number; i += 2) {
			if (comparator(first + i * size, first + (i + 1) * size) > 0) {
				swap(first + i * size, first + (i + 1) * size, size);
                sorted = 0;
			}
		}
	}
}

void shakersort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    int left = 0, right = number - 1, i = 0, border = right;
	while (left < right) {
		for (i = left; i < right; i++) {
			if (comparator(first + i * size, first + (i + 1) * size) > 0) {
				swap(first + i * size, first + (i + 1) * size, size);
                border = i;
			}
		}
        right = border;
        for (i = right; i > left; i--) {
			if (comparator(first + i * size, first + (i - 1) * size) < 0) {
				swap(first + i * size, first + (i - 1) * size, size);
                border = i;
			}
		}
        left = border;
	}
}

int partition(void *first, int left, int right, size_t size, int (*comparator) (const void *, const void *)) {
    void *pivot = first + right * size;
    int i = left - 1, j;
    for (j = left; j < right; j++) {
        if (comparator(pivot, first + j * size) > 0) {
            i++;
            swap(first + j * size, first + i * size, size);
        }
    }
    swap(first + (i + 1) * size, first + right * size, size);
    return i + 1;
}

void qs(void *first, int left, int right, size_t size, int (*comparator) (const void *, const void *)) {
    if (left < right) {
        int pivot = partition(first, left, right, size, comparator);
        qs(first, pivot + 1 , right, size, comparator);
        qs(first, left , pivot - 1, size, comparator);
    }
}

void quicksort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) {
    qs(first, 0, number - 1, size, comparator);
}

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
    int* newarr = (int*)malloc(number * sizeof(int));
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
void heapify(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*), int i) {
    int max = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < number && (comparator(first + size * left, first + size * max) == 1)) {
        max = left;
    }
    if (right < number && (comparator(first + size * right, first + size * max) == 1)) {
        max = right;
    }
    if (max != i) {
        swap(first + size * max, first + size * i, size);
        heapify(first, number, size, comparator, max);
    }
    return;
}

void heapsort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    int i;
    for (i = number / 2 - 1; i >= 0; i--) {
        heapify(first, number, size, comparator, i);
    }
    for (i = number - 1; i >= 0; i--) {
        swap(first, first + size * i, size);
        heapify(first, i, size, comparator, 0);
    }
}
void isort(void* first, int left, int right, size_t size, int (*comparator) (const void*, const void*), int maxdepth) {
    if (left < right) {
        if (!maxdepth) {
            heapsort(first + size * left, right - left + 1, size, comparator);
        } else {
            int pivot = partition(first, left, right, size, comparator);
            isort(first, pivot + 1, right, size, comparator, maxdepth - 1);
            isort(first, left, pivot - 1, size, comparator, maxdepth - 1);
        }
    }
}
void introsort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    isort(first, 0, number - 1, size, comparator, 2 * log(number) / log(2));
}

void pigeonholesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*)) { // only for ints!
    int i;
    int *ptr = (int*) first;
    List *list = (List*) malloc(sizeof(List)), *ptr2, *ptr_prev;
    list->count = 0;
    list->next = NULL;
    list->number = *ptr;
    for (i = 0; i < number; i++) {
        ptr2 = list;
        ptr_prev = NULL;
        while (ptr2 && (*ptr > ptr2->number)) {
            ptr_prev = ptr2;
            ptr2 = ptr2->next;
        }
        if (ptr2) {
            if (*ptr == ptr2->number) {
                ptr2->count = ptr2->count + 1;
            } else {
                ptr2 = (List*) malloc (sizeof(List));
                ptr2->count = 1;
                ptr2->number = *ptr;
                if (!ptr_prev) {
                    ptr2->next = list;
                    list = ptr2;
                } else {
                    ptr2->next = ptr_prev->next;
                    ptr_prev->next = ptr2;
                }
            }
        } else {
            ptr2 = (List*) malloc (sizeof(List));
            ptr_prev->next = ptr2;
            ptr2->count = 1;
            ptr2->next = NULL;
            ptr2->number = *ptr;
        }
        ptr++;
    }
    ptr = (int*) first;
    while (list) {
        ptr2 = list;
        while (ptr2->count) {
            *ptr = list->number;
            ptr++;
            ptr2->count = ptr2->count - 1;
        }
        list = list->next;
        free(ptr2);
    }
    return;
}
void sortint() {
    printf("Sort menu:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n7.Bubble sort\n8.Gnome sort\n9.Merge sort\n10.Heap sort\n11.Introspective sort\n12.Pigeonhole sort\n");
    char *s = readline("Write id of menu part: ");
    int id = strtoint(s);
    free(s);
    if (id < 1 || id > 12){
        printf("ERROR!!! PRINT NORMAL ID!\n");
        return;
    }
    int k = 20;
    void *src = readintfrombinary(k);
    int *ptr = (int*) src;
    for (int i = 0; i < k; i++) {
        printf("%d ", *ptr);
        printf("\n");
        ptr++;
    }
    printf("\n-------\n");
    void (*sort[]) (void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) = {
            combsort,
            insertsort,
            doubleselectionsort,
            oddevensort,
            quicksort,
            shakersort,
            Bubblesort,
            Gnomesort,
            Mergesort,
            heapsort,
            introsort,
            pigeonholesort
    };
    sort[id - 1](src, k, sizeof(int), compint);
    ptr = (int*) src;
    for (int i = 0; i < k; i++) {
        printf("%d ", *ptr);
        printf("\n");
        ptr++;
    }
    return;
}

stc* sort(stc *mystc, int *stclen, int *sortstate){
    if(mystc==NULL){
        printf("ERROR!!! ARRAY IS EMPTY!\n");
        return mystc;
    }
    if(*stclen<2){
        *sortstate=3;
        return mystc;
    }
    printf("Sort menu:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n7.Bubble sort\n8.Gnome sort\n9.Merge sort\n10.Heap sort\n11.Introspective sort\n");
    char *s=readline("Write id of menu part: ");
    int id=strtoint(s);
    free(s);
    if ((id<1)||(id>11)){
        printf("ERROR!!! PRINT NORMAL ID!\n");
        return mystc;
    }
    printf("Sort mode:\n1.Sort by id\n2.Sort by name\n");
    s=readline("Write id of mode: ");
    int mode=strtoint(s);
    free(s);
    if ((mode<1)||(mode>2)){
        printf("ERROR!!! PRINT NORMAL ID OF MODE!\n");
        return mystc;
    }
    void *first = (void*) mystc;
    size_t number = (size_t) *stclen, size = sizeof(stc);
    int (*comparator) (const void *, const void *) = NULL;
    switch(mode){
        case 1:
            comparator = &compid;
            break;
        case 2:
            comparator = &compname;
            break;
    }
    void (*sort[]) (void *first, size_t number, size_t size, int (*comparator) (const void *, const void *)) = {
            combsort,
            insertsort,
            doubleselectionsort,
            oddevensort,
            quicksort,
            shakersort,
            Bubblesort,
            Gnomesort,
            Mergesort,
            heapsort,
            introsort
    };
    sort[id - 1] (first, number, size, comparator);
    *sortstate=mode;
    return mystc;
}
