/*
 * PROCESS 1
*/

/*
 * Gabriel Tomberlin
 * Operating Systems
 * Project 3 - Named Pipe part 1 (writer)
 * November 15, 2018
 * - CODE EXECUTED ON UBUNTU VIRTUAL MACHINE
*/


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PF "/home/osboxes/Desktop/OS/my_fifo"

using namespace std;

int c;
int res;
char buffer[1024];

int main() {
        // Remove any named pipe if already exists (clean run)
        remove("my_fifo");

        // Attempt to create the named pipe
        int a = mkfifo(PF, 0777);

        // Check if it was createed
        if (a < 0) {
                cout << "ERROR CREATING FIFO" << endl;
                cout << "Error: " << errno << endl;
        }

        int b = access(PF, F_OK);

        // Check if a named pipe exists at that location
        if (b < 0) {
                cout << "No named pipe exists!" << endl;
                exit(0);
        } else {
                // Open the pipe for writing
                c = open(PF, O_WRONLY);

                cout << "Named Pipe entered. Close pipe and exit program by entering '~'." << endl;

                while (true) {
                        // Retrieve user input as characters, max 1024 bytes
                        fgets(buffer, 1024, stdin);

                        // Check if the close command was given
                        if (strstr(buffer, "~")) {
                                // Write the close command before closing to tell the reader to close as well
                                res = write(c, buffer, 1024);
                                close(c);
                                exit(0);
                        } else {
                                // Write the contents of the buffer to the pipe
                                res = write(c, buffer, 1024);
                        }
                }
                close(c);
        }
}
