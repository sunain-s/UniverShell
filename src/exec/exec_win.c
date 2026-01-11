#ifdef USH_PLATFORM_WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "exec.h"

int ush_launch(char **args) {
    // TODO: Windows process execution
    // For now stubbing
    if (args[0] == NULL) {
        return 1;
    }
    fprintf(stdout, "STUB: Would execute: %s\n", args[0]);
    return 1;
}

#endif /* USH_PLATFORM_WINDOWS */