#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "structure.h"
#include "inout.h"
#include "useful.h"
#include "insertremove.h"
#include "sort.h"
#include "timing.h"

int main(){
    srand(time(NULL));
    stc *mystc = NULL;
    int stclen = 0, work = 1, sortstate=0;
    while (work){
        printf("Menu:\n1.Input\n2.Clear array\n3.Output\n4.Insert 1 element\n5.Remove n elements by index\n6.Sort array\n7.Timing\n8.Exit\n");
        char *s=readline("Write id of menu part:");
        int id=strtoint(s);
        free(s);
        if ((id<1)||(id>8)){
            printf("ERROR!!! PRINT NORMAL ID!\n");
            continue;
        }
        switch(id){
            case 1:
                mystc=input(mystc, &stclen, &sortstate);
                break;
            case 2:
                mystc=clear(mystc, &stclen);
                break;
            case 3:
                mystc=output(mystc, &stclen);
                break;
            case 4:
                mystc=insert(mystc, &stclen, &sortstate);
                break;
            case 5:
                mystc=removeread(mystc, &stclen);
                break;
            case 6:
                mystc=sort(mystc, &stclen, &sortstate);
                break;
            case 7:
                timing();
                break;
            case 8:
                work = 0;
                break;
        }
    }
    mystc=clear(mystc, &stclen);
    return 0;
}
