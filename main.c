/* Jason Lahoda
My own implementation of the Linux PS command
This is the main module 
It parses through each command line arg to store in variables for the displayInfo method */

#include "displayInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int pid = -1; //
    int displayState = 0;
    int displayUtime = 1;
    int displayStime = 0;
    int displayVsize = 0;
    int displayCmdline = 1;

    for (int i = 1; i < argc; i++) { // Parse through each command line arg to store in variables for the method
        if (strcmp(argv[i], "-p") == 0) {
            if (argc == 2) { // Must be more than 2 arg if -p is passed (more than MYps and -p)
                fprintf(stderr, "Usage: MYps -p <pid> -s -U -S -v -c\n");
                exit(EXIT_FAILURE);
            }
            pid = atoi(argv[i + 1]);
            i++;
            if (pid < 1) { // Arg after -p must be an int
                fprintf(stderr, "Usage: MYps -p <pid> -s -U -S -v -c\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            displayState = 1;
        } else if (strcmp(argv[i], "-U") == 0) { // DO NOT display Utime
            displayUtime = 0;
        } else if (strcmp(argv[i], "-S") == 0) { 
            displayStime = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            displayVsize = 1;
        } else if (strcmp(argv[i], "-c") == 0) { // DO NOT display Cmdline
            displayCmdline = 0;
        } else {
            fprintf(stderr, "Usage: MYps -p <pid> -s -U -S -v -c\n");
            exit(EXIT_FAILURE);
        }
    }

    if (pid == -1) { // No -p arg given, use PID of current process
        pid = getpid();
    }

    displayInfo(pid, displayState, displayUtime, displayStime, displayVsize, displayCmdline);
    return 0;
}