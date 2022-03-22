#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define bufsiz 80
/*#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 

// MSVC defines this in winsock2.h!?

int gettimeofday(struct timeval * tp, struct timezone * tzp) {
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
} */

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

char *readline(char *s){
	printf("%s", s);
	char buf[bufsiz+1] = {0}; //#define bufsiz 80
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = scanf("%80[^\n]",buf);
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
			scanf("%*c");
		}
	} while (n>0);
	if (len>0){
		ans[len]='\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}