## Design Description

I split the C files into modules by creating separate files for the main method and the displayInfo method. The 
main method initializes variables, parses through command line arguments, and handles error cases. The command line 
arguments are used to initialize the boolean variables (of type int, either zero or one). It then passes these 
variables to the displayInfo method. The displayInfo method then uses these variables to decide what information it 
needs from the proc file system. It needs to retrieve data about a specific process that will be printed at the end 
of the method. I chose a manual approach to parsing through the cmdline file by using sscanf() and a buffer to 
extract specific information about a process. It is extremely difficult to 
implement this feature in a way that automatically finds specific information, because formatting greatly varies 
between different systems. I also added many error cases to help debug highly unusual outcomes. I experienced 
problems caused by issues related to these error cases.

## Testing Plan

I tested the program by first ensuring that the command line arguments retrieved the correct information. I read 
the information for specific processes manually by utilizing 'cat' in the proc directory to verify if the 
information was correct. Then, I ensured that the error cases were properly handled with a clear explanation for 
why they happened. There were no bugs that I was unable to resolve.

# Test Cases:

-Parse through each command line arg to store in variables for the displayInfo method
-Check if arg after -p must be an int
-Check if -p is the only arg
-Check if PID exists
-Check if stat file fails (is null)
-Check if stat file can be read
-Check for "Success" error, meaning the cmdline file was empty# LinuxCommandImplementations
