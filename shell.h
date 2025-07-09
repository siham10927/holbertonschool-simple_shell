#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>

char **tokenize(char *line);
int execute_command(char *command);
int execute(char **args);
char *read_input();
void handle_non_interactive_mode(char *environment);
void interactive_loop(void);
void noninteractive(void);
void free_args(char **args);
char *whitespace_trimer(const char *str);
#endif
