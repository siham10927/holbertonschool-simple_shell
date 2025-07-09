#include "main.h"

/**
 * handle_PATH - Handle other using PATH env.
 * @tokens: An array of tokens from the input string.
 * @env: environment variables
 */
void handle_PATH(char *tokens[], char *env[])
{
	char *path_env;
	char *path_copy;
	char *path_token;
	char command_path[1024];
	int i;

	path_env = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			/* Point to the value after "PATH=" */
			path_env = &env[i][5];
			break;
		}
	}
	if (path_env == NULL)
	{
		fprintf(stderr, "PATH environment variable not found.\n");
		exit(EXIT_FAILURE);
	}
	path_copy = strdup(path_env);
	path_token = strtok(path_copy, ":");
	/* Check each directory in PATH for the executable */
	while (path_token != NULL)
	{
		strncpy(command_path, path_token, sizeof(command_path));
		strncat(command_path, "/", sizeof(command_path) - strlen(command_path) - 1);
		strncat(command_path, tokens[0],
			sizeof(command_path) - strlen(command_path) - 1);
		/* Attempt to execute the command */
		if (execve(command_path, tokens, env) == 0)
			exit(1);
		/* Move to the next directory in PATH */
		path_token = strtok(NULL, ":");
	}
	/*  command was not found in any of the directories */
	fprintf(stderr, "Command not found: %s\n", tokens[0]);
	free(path_copy);
}
