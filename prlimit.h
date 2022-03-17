#ifndef _PRLIMIT_H
#define _PRLIMIT_H

typedef struct options {
    unsigned long soft;
    unsigned long hard;
    unsigned int pid;
} options_t;

#endif
