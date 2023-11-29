#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
extern char **environ;

char *find_path(char *command)
{
	struct stat fileInfo;	
	char *path;
	char *pathToken;
	char *catToken;
	int i = 0;

	if (!command)
		return (NULL);
	while (environ[i])
	{
		if ((strncmp(environ[i], "PATH=", 5)) == 0)
		{
			path = environ[i] + 5;
		}
		i++;
	}

	i = 0;
	pathToken = strtok(path, ":");

	while (pathToken[i])
	{
		catToken = strcat(pathToken[i], command);
		if (stat(catToken, fileInfo) == 0)
		{
			return (catToken);
		}
		else

			printf("No such file or directory");
	}
	return (NULL);
}
