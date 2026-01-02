/*-----------------------------------------------------------------------------------------
 * File: parser.c
 * Description: Input line parsing
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define RL_BUFSIZE 1024

//-----------------------------------------------------------------------------------------

char *shell_read_line() {
    int bufsize = RL_BUFSIZE;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "UniverShell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();
        
        // EOF or newline, end of input and replace with null character
        if (c == EOF || c == '\n') {
            buffer[pos] = '\0';
            return buffer;
        } else {
            buffer[pos] = c;
        }
        pos++;

        // reallocate memory if buffer exceeded
        if (pos >= bufsize) {
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "UniverShell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
