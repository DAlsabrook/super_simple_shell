#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

char *get_path_var(char* command)
{
    char *path = NULL;
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
    return (path);
}

char **tokenize_path(char *path)
{
    int i = 0, count = 0;
    char *tmpToken, **tokenArray;
    while (path[i])
    {
        if (path[i] == ':')
            count++;
        i++;
    }
    tokenArray = malloc(sizeof(char *) * (count + 1));
    tmpToken = strtok(path, ":");
    i = 0;
    while (tmpToken)
    {
        tokenArray[i] = strdup(tmpToken);
        tmpToken = strtok(NULL, ":");
        i++;
    }
    return (tokenArray);
}

char *find_path(char *command)
{
    struct stat fileInfo;    
    char *path = NULL, **tokenArray, *catToken;
    int i = 0;

    path = get_path_var(command);
    tokenArray = tokenize_path(path);

    while (tokenArray[i])
    {
        catToken = malloc(strlen(tokenArray[i]) + strlen(command) + 2);
        if (!catToken)
          return (NULL);
        strcpy(catToken, tokenArray[i]);
        strcat(catToken, "/");
        strcat(catToken, command);
        if (stat(catToken, &fileInfo) == 0)
        {
            return (catToken);
        }
        i++;
        free(catToken);
    }
    printf("No such file or directory\n");
    return (NULL);
}

int main()
{
  char *path;
  char *command;
  command = "ls";
  path = find_path(command);
  printf("Path found: %s\n", path);
  return 0;
}
