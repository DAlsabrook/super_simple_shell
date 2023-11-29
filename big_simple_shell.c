#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
int main (void)
{
	char *buffer;
	size_t buff_size;
	int characters;
	char *token;
	char *getline_buffer;
	char *stored_buffer;
	char *tokenized_array[12]; // could create buffer based on size characters from line 29 but that would require a separate function 

	int i, x;
	int status;
	int value;
	pid_t my_pid; 

	buff_size = 32;
	buffer = NULL;
	//buffer = (char *)malloc(sizeof(char) * buff_size); // can set to null, getline will do this automatically but we still have to free it
	//if (buffer == NULL)
	//{
	//	perror("buffer is -1");
	//	free(buffer);
	//	return (-1);
	//}
	x = 0;
	while (1)
	{
		printf("$ ");
		characters = getline(&buffer, &buff_size, stdin);
		if (characters == -1)
		{
			perror("line is -1\n");
			free(buffer);
			return (-1);
		}
		getline_buffer = (char *)malloc(sizeof(char) * (strlen(buffer)));
		if (getline_buffer == NULL)
		{
			perror("getline_buffer is -1");
			free(buffer);
			free(getline_buffer);
			return (-1);
		}
		strncpy(getline_buffer, buffer, (strlen(buffer) - 1));
		if (!strcmp(getline_buffer, "exit")) 
		{
			free(getline_buffer);
			free(buffer);
			exit(1);
		}
		i = 0;
		printf("The buffer: %s\n", getline_buffer);
		token = strtok(getline_buffer, " ");
		while (token != NULL)
		{
			stored_buffer = strdup(token);
			tokenized_array[i] = stored_buffer;
			printf("%s\n", tokenized_array[i]);
			token = strtok(NULL, " ");
			i++;
			stored_buffer = NULL;
		}
		tokenized_array[i] = NULL;
		for (i = 0; tokenized_array[i]; i++)
		{
			printf("The value of the tokenized_buffer at %d index is %s\n and the length is %lu\n", i, tokenized_array[i], strlen(tokenized_array[i]));
		}
		printf("%s\n", tokenized_array[0]);
		my_pid = fork();
		if (my_pid == -1)
		{
			printf("my_pid is -1\n");
			return (-1);
		}
		else if (my_pid == 0)
		{
			value = execve(tokenized_array[0], tokenized_array, NULL);
			if (value == -1)
			{
				perror("value is -1\n");
				return (-1);
			}
		}
		else
		{
			wait(&status);
			printf("loop %d is finished\n", x);
		}
		x++;
		free(buffer);
		free(getline_buffer);
		for (i = 0; tokenized_array[i]; i++)
		{
			free(tokenized_array[i]);
		}
	}

	return (0);
}
