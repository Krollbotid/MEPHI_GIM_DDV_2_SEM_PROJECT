#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "useful.h"
#include "sort.h"
#include "inout.h"
#define TESTNAMELEN 100

void timer(void (*sorter) (void *, size_t , size_t , int (*) (const void *, const void *)), int dotnumber, int amount, int multiplier){
    stc *test = NULL;
    int testlen = 0, i = 1, j = 0, begin = 0, len = scalerand(0, TESTNAMELEN + 1);
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < amount; j++){
            test = randgen(test, &testlen, len, len, multiplier * i);
	        struct timeval start, end;
	        gettimeofday(&start, NULL);
            sorter((void*) test, (size_t) multiplier * i, sizeof(stc), &compid);
	        gettimeofday(&end, NULL);
            time += ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
            test = clear(test, &testlen);
        }
        printf("Dot #%d. Amount:%d\tTime in microsecs:%f\n", i, multiplier * i, time/dotnumber);
    }
    return;
}

void timing(){
    printf("Timing menu. You'll get time of sorting by:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n");
    char *s=readline("Write amount (natural number) of dots for each sort: ");
    int dotnumber=strtoint(s);
    free(s);
    if (dotnumber<0){
        printf("ERROR!!! PRINT NORMAL DOTS AMOUNT!\n");
        return;
    }
    s=readline("Write amount (natural number) of measures for each dot: ");
    int amount=strtoint(s);
    free(s);
    if (amount<0){
        printf("ERROR!!! PRINT NORMAL MEASURES AMOUNT!\n");
        return;
    }
    printf("Program will generate multiplier*number_of_dot elements for each dot.\n");
    s=readline("Write multiplier (natural number) for number of elements: ");
    int multiplier=strtoint(s);
    free(s);
    if (multiplier<0){
        printf("ERROR!!! PRINT NORMAL MULTIPLIER!\n");
        return;
    }
    printf("Dots for comb sort:\n");
    timer(&combsort, dotnumber, amount, multiplier);
    printf("Dots for insert sort:\n");
    timer(&insertsort, dotnumber, amount, multiplier);
    printf("Dots for double selection sort:\n");
    timer(&doubleselectionsort, dotnumber, amount, multiplier);
    printf("Dots for odd-even sort:\n");
    timer(&oddevensort, dotnumber, amount, multiplier);
    printf("Dots for odd-even sort:\n");
    timer(&shakersort, dotnumber, amount, multiplier);
    printf("Dots for odd-even sort:\n");
    timer(&quicksort, dotnumber, amount, multiplier);
}

void timinger(stc *src, void (*sorter) (void *, size_t , size_t , int (*) (const void *, const void *)), int srclen, int *time) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
    sorter((void*) src, (size_t) srclen, sizeof(stc), &compid);
	gettimeofday(&end, NULL);
    *time += ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
}

void timingfromfile(){
    printf("Timing menu. You'll get time of sorting by:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n");
    int amount = 100, exp = 3, srclen = 0, srcsortstate = 0, amountoftests = 10;
    stc *src = NULL;
    filin(src, &srclen, &srcsortstate);
    int testlen = 0, i = 1, k = 0, j = 0;
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            memcpy(test, src, amount1 * sizeof(stc));
            double *time = (double*) malloc(6 * sizeof(double)), *ptr = time;
            for (j = 0; j < amount; j++) {
                timinger(test, &combsort, amount1, time);
                timinger(test, &insertsort, amount1, time + 1);
                timinger(test, &doubleselectionsort, amount1, time + 2);
                //timinger(test, &oddevensort, amount1, time + 3);
                timinger(test, &shakersort, amount1, time + 4);
                //timinger(test, &combsort, amount1, time + 5);
            }
            test = clear(test, &testlen);
            for (i = 0; i < 6; i++) {
                printf("Sort #%d\tAmount:%d\tTime in microsecs:%f\n", i + 1, amount1, *ptr/amount);
                ptr++;
            }
            free(time);
        }
        amount *= 10;
    }
}