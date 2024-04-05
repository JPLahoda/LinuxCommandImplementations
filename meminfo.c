/* Jason Lahoda
Displays two components of the memory information */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
        perror("Error: could not open /proc/meminfo");
        exit(1);
    }

    unsigned long freeMemory = 0;
    unsigned long memoryBuffers = 0;
    char line[1024];

    while (fgets(line, 1024, meminfo) != NULL) {

        if (sscanf(line, "MemFree: %lu", &freeMemory) == 1) { // Read success
        } else if (sscanf(line, "Buffers: %lu", &memoryBuffers) == 1) { // Read success
        }

    }

    fclose(meminfo);

    if (freeMemory > 0) {
        printf("Free Memory: %lu KB\n", freeMemory);
    } else {
        printf("Error: could not find free memory\n");
    }

    if (memoryBuffers > 0) {
        printf("Memory Buffers: %lu KB\n", memoryBuffers);
    } else {
        printf("Error: could not find memory buffers\n");
    }

    return 0;
}