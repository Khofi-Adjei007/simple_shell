#include "shell.h"

/**
 * _strncpy - Copy strings
 * @dest: The destination string
 * @src: The source string
 * @n: The number of characters to be copied
 *
 * Return: A pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenate two strings
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of bytes to be used
 *
 * Return: A pointer to the destination string
 */
char *_strncat(char *dest, const char *src, int n)
{
	int dest_len = 0;
	int i;

	while (dest[dest_len] != '\0')
		dest_len++;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _strchr - Locate a character in a string
 * @s: The string to be searched
 * @c: The character to search for
 *
 * Return: A pointer to the first occurrence of the character in the string
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	if (c == '\0')
		return ((char *)s);

	return (NULL);
}

