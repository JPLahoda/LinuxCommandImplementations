/* Jason Lahoda
Displays two components of the CPU information */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
        perror("Error: could not open /proc/cpuinfo");
        exit(1);
    }

    int numProcessors = 0;
    int cacheSize = 0;
    char line[1024];

    while (fgets(line, 1024, cpuinfo) != NULL) {

        if (sscanf(line, "processor       : %d", &numProcessors) == 1) { // Read success
        } else if (sscanf(line, "cache size      : %d", &cacheSize) == 1) { // Read success
        }

    }

    fclose(cpuinfo);

    if (numProcessors > 0) {
        printf("Number of processors: %d\n", numProcessors);
    } else {
        printf("Error: could not find number of processors\n");
    }

    if (cacheSize > 0) {
        printf("Cache size in each CPU: %d KB\n", cacheSize);
    } else {
        printf("Error: could not determine cache size\n");
    }

    return 0;
}