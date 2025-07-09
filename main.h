#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef bool (*CommandHandler)(char **);

typedef struct
{
	char *name;
	CommandHandler handler;
} Command;

void handle_builtin(char *lineptr);
int handle_tokens(char *lineptr, char *env[]);
bool handle_exit(char *tokens[]);
void print_env(char *env[]);
bool handle_echo(char *tokens[]);
void handle_PATH(char *tokens[], char *env[]);
int handle_execs(char *tokens[], char *env[]);

extern Command built_in_commands[];
extern int token_count;
extern pid_t pid;
#endif
