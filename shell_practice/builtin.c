#include "main.h"

/* exit function */
void handle_exit(char **argv)
{
	int status;

	if (argv[1] != NULL)
	{
		status = atoi(argv[1]);
		if (status < 0 || status > 255)
		{
			perror("Invalid exit status value");
			return (EXIT_FAILURE);
		}
		if (status == 0 && strcmp(argv[1], "0") != 0)
		{
			perror("Invalid exit status");
			return (EXIT_FAILURE);
		}
		exit(status);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

/**
 * handle_cd - changes directory
 * @aargv: working directory path
 * Return: 0 on success
 */
void handle_cd(char **argv)
{
	char *current_dir = getcwd(NULL, 0);
	char *home_dir;

	if (argv[1] == NULL || strcmp(argv[1], "") == 0)
	{
		home_dir = (getenv("HOME"));
		if (home_dir == NULL)
		{
			write(2, "hsh: could not access the home directory\n", 41);
		}
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		argv[1] = getenv("OLDPWD");
	}
	if (current_dir == NULL)
	{
		perror("hsh");
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("hsh");
		free(current_dir);
		return (1);
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) == -1)
	{
		perror("setenv");
	}
	if (setenv("OLDPWD", current_dir, 1) == -1)
	{
		perror("setenv");
	}

	free(current_dir);
	return (1);
}
