#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <getopt.h>
#include "./prlimit.h"

// a hardcoded number that sets the maximum number
// of open files that the supplied PID can handle
#define MAX_OPEN_FILES 10

// hardcode the resource that we'll be changing
#define RESOURCE RLIMIT_NOFILE

#define OPTARG "p:s:h:"


/**
* limit open file - limits the number of open files that
                    a given PID can hold to 10.
* Usage: ./limit-open-files.out <PID>
*/

int main(int argc, char ** argv) {
    options_t options; 
    int err = 0;
    int opt;

    while((opt = getopt(argc, argv, OPTARG)) != EOF) {
        switch(opt) {
            case 'p':
                options.pid = atoi(optarg);
                break;
            case 's':
                options.soft = atoi(optarg);
                break;
            case 'h':
                options.hard = atoi(optarg);
                break;
            default:
                break;
        }
    }

    struct rlimit old = {0};
    struct rlimit new = {
        .rlim_cur = options.soft,
        .rlim_max = options.hard,
    };

    err = prlimit(options.pid, RLIMIT_NOFILE, &new, &old);
    if (err == -1) {
        perror("prlimit - get and set:");
        return 1;
    }

    printf("before: soft=%lld; hard=%lld\n", (long long)old.rlim_cur, (long long)old.rlim_max);

    err = prlimit(options.pid, RLIMIT_NOFILE, NULL, &old);
    if (err == -1) {
        perror("prlimit - get:");
        return 1;
    }
    printf("now: soft=%lld;hard=%lld\n", (long long)old.rlim_cur, (long long)old.rlim_max);

    return 0;
}
