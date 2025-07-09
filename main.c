#include "main.h"

pid_t pid;

/**
 * main - Entry point of the shell program
 * @ac: The number of command-line arguments (unused)
 * @av: An array of command-line arguments (unused)
 * @env: The array of environment variables
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac __attribute__((unused)),
		char **av __attribute__((unused)), char **env)
{
	char *prompt = "($) ", *lineptr;
	int status;
	size_t n;
	bool is_interactive;

	n = 0;
	lineptr = NULL;
	if (isatty(STDIN_FILENO)) /* Determine if it's interactive*/
	{
		printf("%s", prompt);
		is_interactive = true;
		fflush(stdout);
	}
	else
		is_interactive = false;

	while (1)
	{
		getline(&lineptr, &n, stdin);
		pid = fork(); /* Create a child process */
		if (pid < 0) /* fork failed */
			return (1);
		else if (pid == 0)
		{ /* Child process */
			handle_tokens(lineptr, env);
			exit(0);
		}
		else
		{ /* Parent process - wait for the child process to finish */
			wait(&status);
			if (is_interactive == false)
				exit(0);
			printf("%s", prompt);
			fflush(stdout);
		}
	}
	free(lineptr);
	return (0);
}
