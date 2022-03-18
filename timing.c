#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "structure.h"
#include "useful.h"
#include "sort.h"
#include "time.h"
#include "inout.h"
#define TESTNAMELEN 100

void timer(void (*sorter) (void *, size_t , size_t , int (*) (const void *, const void *)), int dotnumber, int amount, int multiplier){
    stc *test = NULL;
    int testlen = 0, i = 1, j = 0, begin = 0, len = scalerand(0, TESTNAMELEN + 1);
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < amount; j++){
            test = randgen(test, &testlen, len, len, multiplier * i);
            begin = clock();
            sorter((void*) test, (size_t) multiplier * i, sizeof(stc), &compid);
            time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
            test = clear(test, &testlen);
        }
        printf("Dot #%d. Amount:%d\tTime:%f\n", i, multiplier * i, time/dotnumber);
    }
    return;
}

void timing(){
    printf("Timing menu. You'll get time of sorting by:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n");
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