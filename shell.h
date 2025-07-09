#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>


#define TRUE 1

/* Shell status codes - these are returned by the evaluate stage of the REPL */
#define EXIT_COMMAND 0
#define COMMAND_NOT_FOUND 127
#define ENV_COMMAND 10
#define EOF_ENCOUNTERED -1
#define EXECUTABLE_COMMAND 1
#define EMPTY_INPUT 3
#define NOT_FOUND 2

extern char **environ;

/**
 * struct InputBuffer - a wrapper around the state needed for getline()
 * and its return value
 * Description:
 * getline(char **lineptr, size_t *n, FILE *stream) has three state
 * requirements: - reads an entire line
 * from `stream` and stores the address of the buffer containing the text
 * into *lineptr.
 * If *lineptr is set to NULL before the call, then getline() will allocate
 * a buffer for storing the line.
 * @buffer: a string buffer
 * @buffer_length: variable
 * @input_length: to store the number of bytes read by getline()
 */
typedef struct
{
	char *buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

void print_prompt(void);
void print_command_not_found_error(char *str);
void printenv_with_environ(void);
InputBuffer *new_input_buffer(void);
char *readline(FILE *stream, InputBuffer *input_buffer);
void close_input_buffer(InputBuffer *input_buffer);
int evaluate(char *str);
int execute(char **command);
void trim(char * const string);
void parse(char *command);
int is_executable(char *str);
void initialise_command_array(char *line, char *args[], int max_args);
int find_executable(const char *command);
void get_first_string(char *const str, char delimiter);
int file_exist_pwd(char *file);
void print_not_found_error(char *str, char *exe_name);
void process_command(
		char *command,
		char *args[],
		InputBuffer *input_buffer,
		int *exit_code,
		char *exe_name
		);
int is_exit(char *str);
int is_env(char *str);
int is_eof(char *str);
int is_empty(char *str);
int is_not_found(char *str);

#endif /* SHELL_H */
