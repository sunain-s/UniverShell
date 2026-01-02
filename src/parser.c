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
}
