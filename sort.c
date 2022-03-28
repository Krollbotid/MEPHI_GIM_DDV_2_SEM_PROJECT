#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "useful.h"

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

stc* sort(stc *mystc, int *stclen, int *sortstate){
    if(mystc==NULL){
        printf("ERROR!!! ARRAY IS EMPTY!\n");
        return mystc;
    }
    if(*stclen<2){
        *sortstate=3;
        return mystc;
    }
    printf("Sort menu:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n");
    char *s=readline("Write id of menu part: ");
    int id=strtoint(s);
    free(s);
    if ((id<1)||(id>6)){
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
    switch(id){
        case 1:
            combsort(first, number, size, comparator);
            break;
        case 2:
            insertsort(first, number, size, comparator);
            break;
        case 3:
            doubleselectionsort(first, number, size, comparator);
            break;
        case 4:
            oddevensort(first, number, size, comparator);
            break;
        case 5:
            shakersort(first, number, size, comparator);
            break;
        case 6:
            quicksort(first, number, size, comparator);
            break;
    }
    *sortstate=mode;
    return mystc;
}
