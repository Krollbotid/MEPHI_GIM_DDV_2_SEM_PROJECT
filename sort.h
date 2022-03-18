#include "structure.h"
#include "stddef.h"
#ifndef SORT_H
#define SORT_H

int compid(const void *x1, const void *x2);
void combsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void insertsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void doubleselectionsort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void oddevensort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void shakersort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
void quicksort(void *first, size_t number, size_t size, int (*comparator) (const void *, const void *));
int binsearch(void *beg, size_t number, size_t size, void *item, size_t sortstate);
stc* sort(stc *mystc, int *stclen, int *sortstate);

#endif