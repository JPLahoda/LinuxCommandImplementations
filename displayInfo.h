/* Jason Lahoda
My own implementation of the Linux PS command
This is the displayInfo header module */

#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

void displayInfo(int pid, int displayState, int displayUtime, int displayStime, int displayVsize, int displayCmdline);

#endif