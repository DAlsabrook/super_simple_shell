#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
int main (void)
{
	char *buffer;
	size_t buff_size;
	char *get_line_buffer;
	char **tokenized_array;  
	int i, x;
	int value;
	size_t tokenized_array_size;

	tokenized_array_size = 12;
	buff_size = 32;
	buffer = NULL;
	buffer = (char *)malloc(sizeof(char) * buff_size); 
	if (buffer == NULL)
	{
		perror("buffer is -1");
		free(buffer);
		return (-1);
	}
	x = 0;
	while (1)
	{
		printf("$ ");
		get_line_buffer = getline_buffer(buffer, buff_size);
		if (get_line_buffer == NULL)
		{
			perror("getline_buffer is NULL\n");
			free(buffer);
			free(get_line_buffer);
			return (-1);
		}
		if (!strcmp(get_line_buffer, "exit")) 
		{
			free(get_line_buffer);
			free(buffer);
			exit(1);
		}
		i = 0;
		printf("The buffer: %s\n", get_line_buffer);
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		for (i = 0; tokenized_array[i]; i++)
		{
			printf("The value of the tokenized_buffer at %d index is %s\n and the length is %lu\n", i, tokenized_array[i], strlen(tokenized_array[i]));
		}
		printf("%s\n", tokenized_array[0]);
		value = fork_process(tokenized_array);
		if (value == -1)
		{
			for (i = 0; tokenized_array[i]; i++)
			{
				free(tokenized_array[i]);
			}
			free(get_line_buffer);
			free(buffer);
			return (-1);
		}
		x++;
		free(buffer);
		free(get_line_buffer);
		for (i = 0; tokenized_array[i]; i++)
		{
			free(tokenized_array[i]);
		}
	}

	return (0);
}
