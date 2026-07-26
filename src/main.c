/*-----------------------------------------------------------------------------------------
 * File: main.c
 * Description: Entry point for UniverShell application
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "shell.h"

//-----------------------------------------------------------------------------------------

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    ush_loop();
    return EXIT_SUCCESS;
}