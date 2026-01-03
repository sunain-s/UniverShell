/*-----------------------------------------------------------------------------------------
 * File: shell.c
 * Description: Input loop
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "shell.h"

//-----------------------------------------------------------------------------------------

void shell_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    } while (status);
}