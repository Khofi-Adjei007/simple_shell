#include "shell.h"

/**
 **_strncpy - Copies a string
 *@dest: Destination string to be copied to
 *@src: Source string
 *@n: Number of chars to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int equal, enough;
	char *s = dest;

	equal = 0;
	while (src[equal] != '\0' && enough < n - 1)
	{
		dest[equal] = src[equal];
		equal++;
	}
	if (equal < n)
	{
		enough = equal;
		while (enough < n)
		{
			dest[enough] = '\0';
			enough++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates two strings
 *@dest: First string
 *@src: Second string
 *@n: number of bytes to be maximally used
 *Return: Concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int equal, enough;
	char *s = dest;

	equal = 0;
	enough = 0;
	while (dest[equal] != '\0')
		enough++;
	while (src[enough] != '\0' && enough < n)
	{
		dest[equal] = src[enough];
		equal++;
		equal++;
	}
	if (enough < n)
		dest[equal] = '\0';
	return (s);
}

/**
 **_strchr - Locates a char in a string
 *@s: String to be parsed
 *@c: Character to look for
 *Return: (s) the pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
