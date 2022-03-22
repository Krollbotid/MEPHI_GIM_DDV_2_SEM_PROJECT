#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "useful.h"
#include "sort.h"

stc* insertindex(stc *mystc, int *stclen, int index, stc *in){
    *stclen = *stclen+1;
    mystc = (stc*) realloc(mystc, (*stclen)*sizeof(stc));
    if(index==*stclen-1){
        memcpy((void*) mystc+sizeof(stc)*(*stclen-1), (void*) in, sizeof(stc));
    } else {
        memmove((void*) mystc+sizeof(stc)*(index+1), (void*) mystc+sizeof(stc)*(index), (*stclen-1-index)*sizeof(stc));
        memcpy((void*) mystc+sizeof(stc)*(index), in, sizeof(stc));
    }
    return mystc;
}

stc* removeindex(stc *mystc, int *stclen, int index, int count){
    int i=0;
    for (; i<count; i++){
        free(mystc[i+index].name);
    }
    memmove((void*) mystc+sizeof(stc)*(index), (void*) mystc+(index+count)*sizeof(stc), (*stclen-count-index)*sizeof(stc));
    mystc = (stc*) realloc(mystc, (*stclen-count)*sizeof(stc));
    *stclen=*stclen-count;
    return mystc;
}

stc* removeread(stc *mystc, int *stclen){
    if(mystc==NULL){
        printf("ERROR!!! ARRAY IS EMPTY!\n");
        return mystc;
    }

    char *s=readline("Enter index (not negative integer): ");
    if (!s){
        printf("ERROR!!! WRONG ENTERING!\n");
        return mystc;
    }
    int index=strtoint(s);
    free(s);
    if ((index>*stclen-1)||(index<0)){
        printf("ERROR!!! OUT OF RANGE!");
        return mystc;
    }

    s=readline("Enter count (not negative integer): ");
    if (!s){
        printf("ERROR!!! WRONG ENTERING!\n");
        return mystc;
    }
    int count=strtoint(s);
    free(s);
    if (!count){
        return mystc;
    }
    if (((index+count)>*stclen)||(count<0)){
        printf("ERROR!!! OUT OF RANGE!\n");
        return mystc;
    }

    mystc=removeindex(mystc, stclen, index, count);
    return mystc;
}

stc* indexread(stc* mystc, int *stclen, int *sortstate, stc *in){
    char *s=readline("Enter index (not negative integer): ");
    if (!s){
        printf("ERROR!!! WRONG ENTERING!\n");
        return mystc;
    }
    int index=strtoint(s);
    free(s);
    if ((index>*stclen)||(index<0)){
        printf("ERROR!!! OUT OF RANGE!");
        return mystc;
    }
    mystc=insertindex(mystc, stclen, index, in);
    *sortstate=0;
    return mystc;
}

stc* insertsorted(stc* mystc, int *stclen, int *sortstate, stc *in){
    if (*sortstate==0){
	    printf("ERROR!!! ARRAY IS NOT SORTED!");
        free(in->name);
	    return mystc;
    }
    int index=binsearch((void*) mystc, (size_t) *stclen, sizeof(stc), (void*) in, (size_t) *sortstate);
    mystc=insertindex(mystc, stclen, index, in);
    return mystc;
}

stc* insert(stc* mystc, int *stclen, int *sortstate){
    if(mystc==NULL){
        printf("ERROR!!! ARRAY IS EMPTY! TRY INPUT INSTEAD!\n");
        return mystc;
    }
    printf("Insert menu:\n1.Insert by index\n2.Insert into sorted array\n");
    char *s=readline("Write id of menu part: ");
    int id=strtoint(s);
    free(s);
    if (id<0){
        printf("ERROR!!! PRINT NORMAL ID!\n");
        return mystc;
    }
    stc in;
    in.name = readline("Enter name: ");
    if (!(in.name)){
        printf("ERROR!!! WRONG ENTERING!\n");
        return mystc;
    }
    s=readline("Enter amount (natural number): ");
    if (!s){
        printf("ERROR!!! WRONG ENTERING!\n");
        return mystc;
    }
    in.id=strtoint(s);
    free(s);
    if(in.id<0){
        printf("ERROR!!! IT IS NOT NATURAL NUMBER!\n");
        return mystc;
    }
    switch(id){
        case 1:
            mystc = indexread(mystc, stclen, sortstate, &in);
            break;
        case 2:
            mystc = insertsorted(mystc, stclen, sortstate, &in);
            break;
        default:
            printf("ERROR!!! PRINT NORMAL ID!\n");
            break;
    }
    return mystc;
}
