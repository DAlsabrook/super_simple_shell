
/*
 * _strdup - Takes a source string and copies into a variable
 * @src: source string to duplicate
 *
 * Return: duplicated string
 */
char *_strdup(char *src)
{
	char *copy;
	int i, len;

	len = _strlen(src);
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	for (i = 0, src[i], i++)
	{
		copy[i] = src[i];
	}
	copy[i] = '\0';
	/*possibly need to free copy. may be freed when stored_buffer if set to null in main*/
	return (copy);
}
