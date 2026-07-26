/*-----------------------------------------------------------------------------------------
 * File: shell.c
 * Description: Input loop
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"
#include "exec.h"

void ush_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = ush_read_line();
        args = ush_split_line(line);
        status = ush_execute(args);

        free(line);
        free(args);
    } while (status);
}