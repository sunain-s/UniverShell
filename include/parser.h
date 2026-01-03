/*-----------------------------------------------------------------------------------------
 * File: parser.h
 * Description: Public interface for the UniverShell line parser.
 * Author: Sunain Syed
-----------------------------------------------------------------------------------------*/

#ifndef UNIVERSHELL_PARSER_H
#define UNIVERSHELL_PARSER_H

char *shell_read_line(void);

char **shell_split_line(char *line);

#endif /* UNIVERSHELL_PARSER_H */