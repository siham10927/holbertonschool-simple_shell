#include "simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

/**
 * read_input - read input from stdin
 *
 * Return: A dynamically allocated string containing the user input.
 *         The caller is responsible for freeing the memory.
 */
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

/**
 * free_args - free memory
 * @args: arguments
*/
void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}

/**
 * tokenize - divide arguments
 * @line: of arguments
 * Return: tokens
*/
char **tokenize(char *line)
{
	char **tokens = NULL;
	char *token = strtok(line, " \t\n");
	int token_count = 0;

	while (token)
	{
		tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
		if (tokens == NULL)
		{
			perror("realloc error");
			exit(EXIT_FAILURE);
		}
		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup error");
			exit(EXIT_FAILURE);
		}
		token_count++;
		token = strtok(NULL, " \t\n");
	}
	tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
	if (tokens == NULL)
	{
		perror("realloc error");
		exit(EXIT_FAILURE);
	}
	tokens[token_count] = NULL;

	return (tokens);

}

/**
 * execute - execute command line
 * @args: line of arguments
 *
 * Return: 0
 */

int execute(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		int status;

		waitpid(pid, &status, 0);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
	}
	else
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (0);
}
