
/*
 * _strcmp - Compares 2 strings to see if they are the same
 * @s1: First string to use
 * @s2: Second string to use
 *
 * Return: 0 if string are the same. Greater than 0 if different
 */
int _strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        ++i;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
