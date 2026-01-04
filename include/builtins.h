/*-----------------------------------------------------------------------------------------
 * File: builtins.h
 * Description: Public interface for the UniverShell built-in commands.
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#ifndef UNIVERSHELL_BUILTINS_H
#define UNIVERSHELL_BUILTINS_H

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

int ush_num_builtins(void);

#endif /* UNIVERSHELL_BUILTINS_H */