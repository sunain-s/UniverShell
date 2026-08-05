/*-----------------------------------------------------------------------------------------
 * File: parser.c
 * Description: Input line parsing
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

//-----------------------------------------------------------------------------------------

char *ush_read_line() {
    int bufsize = RL_BUFSIZE;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "UniverShell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF) {
            free(buffer);
            return NULL;
        }
        
        // EOF or newline, end of input and replace with null character
        if (c == '\n') {
            buffer[pos] = '\0';
            return buffer;
        } else {
            if (pos + 1 >= bufsize) {
                bufsize += RL_BUFSIZE;
                buffer = realloc(buffer, bufsize);
                if (!buffer) {
                    fprintf(stderr, "UniverShell: allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }

            buffer[pos] = c;
        }
        pos++;
    }
}

char **ush_split_line(char *line) {
    int bufsize = TOK_BUFSIZE;
    int pos = 0;
    char **tokens = malloc(sizeof(char*) * bufsize);
    char *token;

    if (!tokens) {
        fprintf(stderr, "UniverShell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        if (pos + 1 >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, sizeof(char*) * bufsize);
            if (!tokens) {
                fprintf(stderr, "UniverShell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        tokens[pos] = token;
        pos++;

        token = strtok(NULL, TOK_DELIM);
    }

    if (pos >= bufsize) {
        bufsize += TOK_BUFSIZE;
        tokens = realloc(tokens, sizeof(char*) * bufsize);
        if (!tokens) {
            fprintf(stderr, "UniverShell: allocation error\n");
            exit(EXIT_FAILURE);
        }
    }

    tokens[pos] = NULL;
    return tokens;
}