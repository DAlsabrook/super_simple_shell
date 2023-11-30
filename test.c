#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

char *find_path(char *command)
{
    struct stat fileInfo;    
    char *path = NULL, *tmpToken, *catToken, *tokenArray[20];
    int i = 0;

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
        tokenArray[i] = strdup(tmpToken);
        tmpToken = strtok(NULL, ":");
        i++;
    }
    i = 0;
    
    while (tokenArray[i])
    {
        catToken = malloc(strlen(tokenArray[i]) + strlen(command) + 3);
	if (!catToken)
		return (NULL);
        strcpy(catToken, tokenArray[i]);
	catToken[strlen(tokenArray[i])] = 47;
        strcat(catToken, command);
        if (stat(catToken, &fileInfo) == 0)
        {
            return (catToken);
        }
        i++;
        free(catToken);
    }
    printf("No such file or directory");
    return (NULL);
}

int main() 
{
  char *path;
  char *command;
  command = "ls";
  path = find_path(command);
  printf("Path found: %s", path);
  return 0;
}
