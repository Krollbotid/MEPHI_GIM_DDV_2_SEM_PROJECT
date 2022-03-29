#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "useful.h"
#include "sort.h"
#include "inout.h"
#include <sys/time.h>
#define TESTNAMELEN 100

void timer(void (*sorter) (void *, size_t , size_t , int (*) (const void *, const void *)), int dotnumber, int amount, int multiplier){
    stc *test = NULL;
    int testlen = 0, i, j, len = scalerand(0, TESTNAMELEN + 1);
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
    int dotnumber = (int) strtoint(s);
    free(s);
    if (dotnumber<0){
        printf("ERROR!!! PRINT NORMAL DOTS AMOUNT!\n");
        return;
    }
    s=readline("Write amount (natural number) of measures for each dot: ");
    int amount = (int) strtoint(s);
    free(s);
    if (amount<0){
        printf("ERROR!!! PRINT NORMAL MEASURES AMOUNT!\n");
        return;
    }
    printf("Program will generate multiplier*number_of_dot elements for each dot.\n");
    s=readline("Write multiplier (natural number) for number of elements: ");
    int multiplier = (int) strtoint(s);
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

void timinger(stc *src, void (*sorter) (void *, size_t , size_t , int (*) (const void *, const void *)), int srclen, double *time) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sorter((void*) src, (size_t) srclen, sizeof(stc), &compid);
    gettimeofday(&end, NULL);
    *time += ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
}

void cvs() {
    printf("Timing menu. You'll get time of sorting by:\n1.Comb sort\n2.Insertion sort\n3.Double selection sort\n4.Odd-even sort\n5.Shaker sort\n6.Quick sort\n");
    FILE *file;
    file = fopen("results.csv", "w");
    fprintf (file, "method / ");

    int amount = 10, exp = 5;
    int srclen = 0, srcsortstate = 0, amountoftests = 10;
    int i, k, j;

    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            fprintf (file, "%d / ", amount1);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    stc *src = NULL;
    filin(src, &srclen, &srcsortstate);

    fprintf (file, "combsort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &combsort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fprintf (file, "insertsort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &insertsort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fprintf (file, "doubleselectionsort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &doubleselectionsort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fprintf (file, "oddevensort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &oddevensort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fprintf (file, "shakersort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &shakersort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fprintf (file, "quicksort / ");
    for (i = 0; i < exp; i++) {
        for (k = 1; k < 10; k++) {
            int amount1 = amount * k;
            stc *test = (stc*) malloc(amount1 * sizeof(stc));
            double *time = (double*) malloc(sizeof(double)), *ptr = time;
            for (j = 0; j < amountoftests; j++) {
                memcpy(test, src, amount1 * sizeof(stc));
                timinger(test, &quicksort, amount1, time);
                src += amount1;
            }
            test = clear(test, &testlen);
            fprintf (file, "%f / ", *ptr/amountoftests);
            ptr++;
            free(time);
        }
        amount *= 10;
    }
    fprintf (file, "\n");

    fclose(file);
}