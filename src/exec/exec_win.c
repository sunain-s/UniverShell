#ifdef USH_PLATFORM_WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "exec.h"

static size_t ush_quoted_arg_length(const char *arg) {
    size_t length = 0;

    while (*arg != '\0') {
        if (*arg == '"') {
            length++;
        }
        length++;
        arg++;
    }

    return length;
}

static int ush_needs_quotes(const char *arg) {
    return strpbrk(arg, " \t\"") != NULL;
}

static char *ush_build_command_line(char **args) {
    size_t length = 0;
    int i;

    for (i = 0; args[i] != NULL; i++) {
        if (i > 0) {
            length++;
        }

        if (ush_needs_quotes(args[i])) {
            length += 2;
            length += ush_quoted_arg_length(args[i]);
        } else {
            length += strlen(args[i]);
        }
    }

    char *command_line = malloc(length + 1);
    char *cursor = command_line;

    if (command_line == NULL) {
        return NULL;
    }

    for (i = 0; args[i] != NULL; i++) {
        const char *arg = args[i];

        if (i > 0) {
            *cursor++ = ' ';
        }

        if (ush_needs_quotes(arg)) {
            *cursor++ = '"';

            while (*arg != '\0') {
                if (*arg == '"') {
                    *cursor++ = '\\';
                }
                *cursor++ = *arg;
                arg++;
            }

            *cursor++ = '"';
        } else {
            size_t arg_length = strlen(arg);
            memcpy(cursor, arg, arg_length);
            cursor += arg_length;
        }
    }

    *cursor = '\0';
    return command_line;
}

int ush_launch(char **args) {
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_information;
    char *command_line;

    if (args[0] == NULL) {
        return 1;
    }

    command_line = ush_build_command_line(args);
    if (command_line == NULL) {
        fprintf(stderr, "UniverShell: allocation error\n");
        return 1;
    }

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_information, sizeof(process_information));

    if (!CreateProcessA(
        NULL,
        command_line,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startup_info,
        &process_information
    )) {
        fprintf(stderr, "UniverShell: failed to execute %s (error %lu)\n", args[0], GetLastError());
        free(command_line);
        return 1;
    }

    WaitForSingleObject(process_information.hProcess, INFINITE);
    CloseHandle(process_information.hProcess);
    CloseHandle(process_information.hThread);
    free(command_line);

    return 1;
}

#endif /* USH_PLATFORM_WINDOWS */