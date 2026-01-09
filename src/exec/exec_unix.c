#ifndef _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exec.h"

int ush_launch(char **args) {
    pid_t pid;
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
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

#endif /* _WIN32 */