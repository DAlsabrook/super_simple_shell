#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
char *_strdup(char *src);
extern char **environ;

char *find_path(char *command)
{
	struct stat fileInfo;
	char *path = NULL;
	char *tokenArray[20];
	char *tmpToken;
	int i = 0;
	int sizeToken;
	char *combine_array;

	if (!command)
		return (NULL);
	while (!path && environ[i])
	{
		if ((strncmp(environ[i], "PATH=", 5)) == 0)
		{
			path = environ[i] + 5;
		}
		i++;
	}
	tmpToken = strtok(path, ":");
	i = 0;
	while (tmpToken)
	{
		tokenArray[i] = _strdup(tmpToken);
		tmpToken = strtok(NULL, ":");
		i++;
	}
	i = 0;
	while (tokenArray[i])
	{
		sizeToken = strlen(tokenArray[i]);
		combine_array = malloc(sizeof(char) * strlen(tokenArray[i]) + strlen(command) + 2);
		strcpy(combine_array, tokenArray[i]);
		combine_array[sizeToken] = 47;
		combine_array[sizeToken + 1] = '\0';
		strcat(combine_array, command);
		if (stat(combine_array, &fileInfo) == 0)
		{
			return (combine_array);
		}
		i++;
		free(combine_array);
	}
	printf("No such file or directory found\n");
	return (NULL);
}
char *_strdup(char *src)
{
	char *copy;
	int i, len;

	len = strlen(src);
	copy = malloc(len + 1);
	if (!copy)
	{
		return (NULL);
	}
	for (i = 0; src[i]; i++)
	{
		copy[i] = src[i];
	}
	copy[i] = '\0';
	return (copy);
}
int main (void)
{
	char *path;
	char *command;
	command = "ls";
	path = find_path(command);
	printf("Path found: %s\n", path);
	return (0);
}




















































































