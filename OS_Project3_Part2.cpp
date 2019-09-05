/*
 * PROCESS 2
*/ 

/*
 * Gabriel Tomberlin
 * Operating Systems
 * Project 3 - Named Pipe part 2 (reader)
 * November 15, 2018
 * - CODE EXECUTED ON UBUNTU VIRTUAL MACHINE
*/


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PF "/home/osboxes/Desktop/OS/my_fifo"

using namespace std;

int c;
int res;
char buffer[1024];

int main() {
        int b = access(PF, F_OK);

        // Check if the named pipe exist at that location
        if (b < 0) {
                cout << "Named pipe does not exist!" << endl;
                exit(0);
        } else {
                c = open(PF, O_RDONLY);

                while (true) {
                        b = access(PF, F_OK);

                        // Check each loop to see if the named pipe still exists
                        if (b == 0) {
                                // Retrieve the data from the buffer
                                res = read(c, buffer, 1024);

                                // Check if the close command was read
                                if (strstr(buffer, "~")) {
                                        close(c);
                                        exit(0);
                                } else { // No close command, print buffer
                                        cout << buffer;
                                }
                        } else {
                                close(c);
                                exit(0);
                        }
                }
                close(c);
        }
}
