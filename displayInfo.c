/* Jason Lahoda
My own implementation of the Linux PS command
This is the displayInfo module 
It prints information about a specific process based on the args passed to it */

#include "displayInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void displayInfo(int pid, int displayState, int displayUtime, int displayStime, int displayVsize, int displayCmdline) {
    FILE *statFile;
    unsigned long utime = 0;
    unsigned long stime = 0;
    unsigned long vsize = 0;
    char path[1024];
    char statBuffer[1024];
    char state;
    char cmdline[1024];

    snprintf(path, 1024, "/proc/%d/stat", pid); // Format path to the process /proc entry

    if (access(path, F_OK) != 0) { // Check if PID exists
        fprintf(stderr, "Process at PID %d does not exist\n", pid);
        exit(EXIT_FAILURE);
    }

    statFile = fopen(path, "r");

    if (statFile == NULL) { // In case stat file fails
        perror("Error opening stat file");
        exit(EXIT_FAILURE);
    }

    if (fgets(statBuffer, sizeof(statBuffer), statFile) == NULL) { // Read stat file
        perror("Error opening stat file");
        fclose(statFile);
        exit(EXIT_FAILURE);
    }

    // Parse through stat file
    sscanf(statBuffer, "%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %*d %*u %lu %*d %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*d %*d %*u %*u %*u %*u %*d %*u %*u %*u %*u %*u %*u %*u %*d", &state, &utime, &stime, &vsize);
    
    // Format path to cmdline file
    snprintf(path, 1024, "/proc/%d/cmdline", pid);

    // Read the command line
    FILE *cmdlineFile = fopen(path, "r");

    if (cmdlineFile == NULL) {
        if (errno == 0) { // Ignoring the "Success" error, meaning the file was empty
        } 
        else { // Some other error
            perror("Error opening cmdline file");
            fclose(statFile);
            exit(EXIT_FAILURE);
        }
    }

    if (fgets(cmdline, sizeof(cmdline), cmdlineFile) == NULL) {
        if (errno == 0) { // Ignoring the "Success" error, meaning the file was empty
        } 
        else { // Some other error
            perror("Error opening cmdline file");
            fclose(statFile);
            fclose(cmdlineFile);
            exit(EXIT_FAILURE);
        }
    }

    // Close the opened files
    fclose(statFile);
    fclose(cmdlineFile);

    printf("%d: %c", pid, state); // Display
    if (displayUtime) {
        printf(" utime=%lu", utime);
    }
    if (displayStime) {
        printf(" stime=%lu", stime);
    }
    if (displayVsize) {
        printf(" size=%lu", vsize);
    }
    if (displayCmdline) {
        printf(" [%s]", cmdline);
    }
    printf("\n");
}