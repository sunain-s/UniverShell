/*-----------------------------------------------------------------------------------------
 * File: shell.c
 * Description: Input loop
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "parser.h"
#include "shell.h"

//-----------------------------------------------------------------------------------------

int ush_launch(char **args) {
    pid_t pid, wpid;
    int status;
    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("UniverShell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("UniverShell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int ush_execute(char **args) {
    int i;
    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < ush_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return ush_launch(args);
}

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