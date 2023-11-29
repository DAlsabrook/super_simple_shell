#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
extern char **environ;

char *find_path(char *command)
{
    struct stat fileInfo;    
    char *path, *tokenArray[20], *tmpToken, *catToken;
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
        catToken = strcat(tokenArray[i], command);
        if (stat(catToken, &fileInfo) == 0)
        {
            return (catToken);
        }
        else

            printf("No such file or directory");
        i++;
    }
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
