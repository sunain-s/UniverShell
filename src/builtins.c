/*-----------------------------------------------------------------------------------------
 * File: builtins.c
 * Description: Built-in shell commands for UniverShell
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>

//-----------------------------------------------------------------------------------------
// Built-in command declarations

int ush_cd(char **args);
int ush_help(char **args);
int ush_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &ush_cd,
    &ush_help,
    &ush_exit
};

int ush_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

//-----------------------------------------------------------------------------------------
// Built-in command implementations

int ush_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "UniverShell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("UniverShell");
        }
    }
    return 1;
}

int ush_help(char **args) {
    int i;
    printf("UniverShell: A lightweight cross-platform shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are commands are built in:\n");

    for (i = 0; i < ush_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}
