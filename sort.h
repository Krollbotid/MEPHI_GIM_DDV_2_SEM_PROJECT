#include "structure.h"
#include "stddef.h"
#ifndef SORT_H
#define SORT_H

int compid(const void *x1, const void *x2);
int compint(const void *x1, const void *x2);
void swap(void *fir, void *sec, size_t size);
void combsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void insertsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void doubleselectionsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
int binsearch(void *beg, size_t number, size_t size, void *item, size_t sortstate);
void oddevensort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void shakersort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void quicksort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void Bubblesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
void Gnomesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
void Mergesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
void heapsort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
void introsort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
stc* sort(stc *mystc, int *stclen, int *sortstate);

typedef struct List {
    int number;
    int count;
    struct List *next;
} List;

void pigeonholesort(void* first, size_t number, size_t size, int (*comparator) (const void*, const void*));
void sortint();

#endif