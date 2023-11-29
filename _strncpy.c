
/**
 * _strcpy - copies string from pointer
 * @dest: destination of copy
 * @src: source to copy from
 *
 * Return: copied sting
 */
char *_strncpy(char *dest, char *src, int num)
{
	int i;

	for (i = 0; i <= num; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
