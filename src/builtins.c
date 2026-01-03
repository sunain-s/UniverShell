/*-----------------------------------------------------------------------------------------
 * File: builtins.c
 * Description: Built-in shell commands for UniverShell
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

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

