#include "structure.h"
#ifndef INOUT_H
#define INOUT_H

stc* input(stc *mystc, int *stclen, int *sortstate);
stc* output(stc *mystc, int *stclen);
stc* clear(stc *mystc, int *stclen);
stc* randgen(stc *mystc, int *stclen, int minlength, int maxlength, int amount);
stc* filin(stc *mystc, int *stclen, int *sortstate);
void *readintfrombinary(long long size);

#endif
