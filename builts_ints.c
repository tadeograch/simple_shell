#include "holberton.h"
/**
* find_built_in_3 - find builts in
* @args: arguments
* @env: environment variables
* @buffer: user buffer
* Return: result 0 or -1
*/
int find_built_in_3(char **args, char **env, char *buffer)
{
	int i = 0;

	built_in functions[] = {
		{"exit", fexit},
		/*{"help", fhelp}, BORRAR*/
		{"cd", fcd},
		{"env", fenv},
		{NULL, NULL}
	};
	while (functions[i].name != NULL)
	{
		if (_strcmp(args[0], functions[i].name) == 0)
		{
			if (functions[i].f(args, env, buffer) == -1)
			{
				return (-1);
			}
			return (0);
		}
		else
		{
			i++;
		}
	}
	return (1);
}

/**
* fexit - command exit function
* @args: arguments
* @env: environment variables
* @buffer: user buffer
* Return: result...
*/
int fexit(char **args, char **env, char *buffer)
{
	(void)env;

	free(buffer);
	free(args);
	exit(0);
}
/**
* fcd - command cd function
* @args: arguments
* @env: environment variables
* @buffer: user buffer
* Return: result 0
*/
int fcd(char **args, char **env, char *buffer)
{
	char *path = "HOME=", *tmp = NULL;
	int i, k, len = 5;

	if (args[1] == NULL)
	{
		for (i = 0; env[i] != NULL; i++)
		{
			if (_strncmp(path, env[i], len) == 0)
				break;
		}
		tmp = malloc(_strlen(env[i]) + 1);
		if (tmp == NULL)
		{
			perror("");
			return (0);
		}
		strcpy(tmp, env[i]);
		strtok(tmp, "=");
		tmp = strtok(NULL, "\n");
		tmp = str_concat(tmp, "/");
		if (tmp == NULL)
		{
			free(tmp);
			return (0);
		}
		chdir(tmp);
		free(tmp);
	}
	else
	{
		if (_strcmp(args[1], "-") == 0)
		{
			updir(tmp, buffer, args);
			return (0);
		}
		else if (chdir(args[1]) != 0)
			cderror(tmp);
	}
		free(buffer), free(args);
		return (0);
}
/**
* updir - function goes up one directory
* @tmp: path
* @buffer: user buffer
* @args: user arguments
* Return: result 0
*/
int updir(char *tmp, char *buffer, char **args)
{
	char *cwd = NULL;
	int lencwd = 0;

	if (chdir("..") != 0)
	{
		free(tmp);
		perror("");
	}
	cwd = malloc(100);
	getcwd(cwd, 100);
	lencwd = _strlen(cwd);
	write(1, cwd, lencwd);
	write(1, "\n", 1);
	free(cwd);
	free(tmp);
	free(buffer);
	free(args);
	return (0);
}
/**
* cderror - function for cd errors
* @tmp: path
* Return: void
*/
void cderror(char *tmp)
{
	free(tmp);
	perror("");
}
