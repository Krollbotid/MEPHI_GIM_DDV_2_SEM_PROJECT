#ifndef USEFUL_H
#define USEFUL_H


/*typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;*/

unsigned long long strtoint(char *s); // return int from string if there are only digits, returns 0 in other case
int scalerand(const int start, const int end); // scales rand() [0; RANDMAX] to [start; end) if start<end, returns end-1 in other case
char *readline(char *s);
//int gettimeofday(struct timeval * tp, struct timezone * tzp);

#endif