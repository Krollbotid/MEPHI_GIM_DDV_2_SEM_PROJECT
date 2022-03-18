#include <string.h>
#include <stdlib.h>

unsigned long long strtoint(char *s){
    if(s!=NULL){
        char digits[10]="0123456789";
        int i=0, chfound=0;
        unsigned long long ans=0;
        for (i=0; i<strlen(s); i++){
            int isdigit=0, j=0;
            for (j=0; j<10; j++){
                if (s[i]==digits[j]){
                    isdigit=1;
                    ans=ans*10+j;
                    break;
                }
            }
            if (!isdigit){
                chfound=1;
                break;
            }
        }
        if (chfound){
            return -1;
        } else {
            return ans;
        }
    } else {
        return -1;
    }
}

int scalerand(const int start, const int end){
    if (end > start){
        return start + (rand() %(end-start));
    } else {
        return end-1;
    }
}