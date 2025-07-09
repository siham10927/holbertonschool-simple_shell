#include "main.h"

/**
 * main - program that returns a simple shell with limited funtionality
 * @ac: void
 * @av: void
 * Return: 0 on yay, else 127 if nay
 */
int main(__attribute__((unused)) int ac, char *av[])
{
	size_t bufsize;
	ssize_t read;
	char *cmd[1024], *buffer, *str;
	int built_in_checker, exit_status, status, i;

	status = 0;

	while (1)
	{
		buffer = NULL;
		bufsize = 0;
		i = 0;
		get_input(&buffer, &bufsize, &read);
		str = strdup(buffer);
		free(buffer);
		line_to_array(str, cmd);
		built_in_checker = checkbuiltin(cmd, environ, str, &status);

		if (built_in_checker == 1)
		{
			continue;
		}
		if (executable_cmd(cmd[0]) == 0)
		{
			cmd[0] = find_executable_in_path(&(cmd[0]), av[0]);
			i = 1;
			if (cmd[0] == NULL)
			{
				free(str);
				return (127);
			}
		}
		exit_status = fork_the_child(cmd, environ, &str, &status);
		if (i == 1)
		{
			free(cmd[0]);
		}
		free(str);
	}
	exit(exit_status);
}
