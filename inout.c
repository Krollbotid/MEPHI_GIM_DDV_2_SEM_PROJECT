#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "structure.h"
#include "useful.h"

char *freadline(FILE *file){
	char buf[80+1] = {0};
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = fscanf(file, "%80[^\n]",buf);
		if (n<0){
			if(!ans){
				return NULL;
			}
		} else if (n>0){
			int buf_len = strlen(buf);
			int str_len = len + buf_len;
			ans = (char*) realloc(ans, (str_len+1)*sizeof(char));
			strncpy(ans+len, buf, buf_len);
			len = str_len;
		} else {
			fscanf(file, "%*c");
		}
	} while (n>0);
	if (len>0){
		ans[len]='\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}

stc* consin(stc *mystc, int *stclen, int *sortstate){
    char *s=readline("Print amount of new entries: ");
    if(!s){
        printf("ERROR!!! PRINT NORMAL AMOUNT!");
        return mystc;
    }
    int amount=strtoint(s), i=0;
    free(s);
    for (; i<amount; i++){
        printf("Input entry #%d:\n",i+1);
        stc in;
        in.name = readline("Enter name: ");
        if (!(in.name)){
            printf("ERROR!!! WRONG ENTERING!\n");
            break;
        }
        s=readline("Enter id (natural number): ");
        if (!s){
            printf("ERROR!!! WRONG ENTERING!\n");
            return mystc;
        }
        in.id=strtoint(s);
        free(s);
        if(in.id>=0){
            *stclen = *stclen+1;
            mystc = (stc*) realloc(mystc, (*stclen)*sizeof(stc));
            memcpy((void*) mystc+sizeof(stc)*(*stclen-1), &in, sizeof(stc));
	        *sortstate=0;
        } else {
            printf("ERROR!!! IT IS NOT NATURAL NUMBER!\n");
            break;
        }
    }
    return mystc;
}

stc* filin(stc *mystc, int *stclen, int *sortstate){
    char *name=readline("Print name of file: ");
    FILE *file = fopen(name, "r");
    free(name);
    int count=1;
    if (file != NULL){
        stc in;
        char *s=NULL;
	    do{
            s=freadline(file);
            if(!(s)){
                break;
            }
            in.name = freadline(file);
            if (!(in.name)){
                printf("ERROR!!! STRUCTURE #%d IS NOT FULL!\n", count);
                break;
            }
            s=freadline(file);
            if (!s){
                printf("ERROR!!! STRUCTURE #%d IS NOT FULL!\n", count);
                break;
            }
            in.id=strtoint(s);
            free(s);
            if(in.id>=0){
                *stclen = *stclen+1;
		        *sortstate=0;
                mystc = (stc*) realloc(mystc, (*stclen)*sizeof(stc));
                memcpy((void*) mystc+sizeof(stc)*(*stclen-1), &in, sizeof(stc));
                count++;
            } else {
                printf("ERROR!!! ID FIELD IN STRUCTURE #%d IS NOT NATURAL NUMBER!\n", count);
                break;
            }
	    } while(s);
        fclose(file);
    } else {
        printf("ERROR!!! THIS FILE DOESN'T EXIST!\n");
    }
    return mystc;
}

stc* randgen(stc *mystc, int *stclen, int minlength, int maxlength, int amount){
    int i=0;
    const int chbegin=32, chend=126;
    for (; i<amount; i++){
        stc in;
        int j=0, len=0;
        if (minlength==maxlength){
            len=minlength;
        } else {
            len = scalerand(minlength, maxlength+1);
        }
        in.name = (char*) calloc((size_t) len+1, (size_t) sizeof(char));
        for (j=0; j<len; j++){
            in.name[j]=scalerand(chbegin, chend+1);
        }
        in.name[len]='\0';
        in.id=rand();
        *stclen = *stclen+1;
        mystc = (stc*) realloc(mystc, (*stclen)*sizeof(stc));
        memcpy((void*) mystc+sizeof(stc)*(*stclen-1), &in, sizeof(stc));
    }
    return mystc;
}

stc* randin(stc *mystc, int *stclen, int *sortstate){
    char *s=readline("Print amount (natural number) of new entries: ");
    int amount=strtoint(s);
    free(s);
    if(amount<1){
        printf("ERROR!!! PRINT NORMAL AMOUNT!");
        return mystc;
    }

    s=readline("Print max length (natural number) of name: ");
    int maxlength=strtoint(s);
    free(s);
    if(maxlength<1){
        printf("ERROR!!! PRINT NORMAL AMOUNT!");
        return mystc;
    }

    s=readline("Print min length (natural number) of name: ");
    int minlength=strtoint(s);
    free(s);
    if(minlength<1){
        printf("ERROR!!! PRINT NORMAL AMOUNT!");
        return mystc;
    }
    
    if (minlength>maxlength){
        printf("ERROR!!! MIN LENGTH > MAX LENGTH!");
        return mystc;
    }
    *sortstate=0;
    mystc=randgen(mystc, stclen, minlength, maxlength, amount);
    return mystc;
}

stc* consout(stc *mystc, int *stclen){
    int i=0;
    for (; i<*stclen; i++){
        stc out=mystc[i];
        printf("ENTRY #%d:\nIdentificator: %lld\nName: %s\n", i+1, out.id, out.name);
    }
    return mystc;
}

stc* filout(stc *mystc, int *stclen){
    char *name=readline("Print name of file: ");
    FILE *file = fopen(name, "w");
    free(name);
    int i=0;
    if (file != NULL){
        for (; i<*stclen; i++){
            stc out=mystc[i];
            fprintf(file, "%lld\n%s\n", out.id, out.name);
        }
        fclose(file);
    }
    return mystc;
}

stc* input(stc *mystc, int *stclen, int *sortstate){
    printf("Input menu:\n1.Input from console\n2.Input from file\n3.Random generation of array\n");
    char *s=readline("Write id of menu part: ");
    int id=strtoint(s);
    free(s);
    if ((id<1)||(id>3)){
        printf("ERROR!!! PRINT NORMAL ID!\n");
        return mystc;
    }
    switch(id){
        case 1:
            mystc=consin(mystc, stclen, sortstate);
            break;
        case 2:
            mystc=filin(mystc, stclen, sortstate);
            break;
        case 3:
            mystc=randin(mystc, stclen, sortstate);
            break;
    }
    return mystc;
}

stc* output(stc *mystc, int *stclen){
    if(mystc==NULL){
        printf("ERROR!!! ARRAY IS EMPTY!\n");
        return mystc;
    }
    printf("Output menu:\n1.Output to console\n2.Output to file\n");
    char *s=readline("Write id of menu part: ");
    int id=strtoint(s);
    free(s);
    if ((id!=1)&&(id!=2)){
        printf("ERROR!!! PRINT NORMAL ID!\n");
        return mystc;
    }
    switch(id){
        case 1:
            mystc=consout(mystc, stclen);
            break;
        case 2:
            mystc=filout(mystc, stclen);
            break;
    }
    return mystc;
}

stc *clear (stc *mystc, int *stclen){
    if (mystc != NULL){
        while (*stclen > 0){
            free(mystc[*stclen - 1].name);
            *stclen = *stclen - 1;
        }
        free(mystc);
        mystc = NULL;
    }
    return mystc;
}