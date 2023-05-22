#include "shell.h"

/**
* copy_string - Make a copy of a string.
* @dest: The destination string to copy to.
* @src: The source string to be copied.
* @n: The maximum number of characters to be copied.
*
* Returns: The copied string (dest).
*/

char *copy_string(char *dest, char *src, int n)
{
int ka, ak;
char *result = dest;

ka = 0;
while (src[ka] != '\0' && ka < n - 1)
{
dest[ka] = src[ka];
ka++;
}
if (ka < n)
{
ak = ka;
while (ak < n)
{
dest[ak] = '\0';
ak++;
}
}
return (result);
}

/**
* concatenate_strings - Concatenate two strings.
* @dest: The first string.
* @src: The second string.
* @n: The maximum number of bytes to be used.
*
* Returns: The concatenated string (dest).
*/

char *concatenate_strings(char *dest, char *src, int n)
{
int ka, ak;
char *result = dest;

ka = 0;
ak = 0;
while (dest[ka] != '\0')
ka++;
while (src[ak] != '\0' && ak < n)
{
dest[ka] = src[ak];
ka++;
ak++;
}
if (ak < n)
dest[ka] = '\0';
return (result);
}

/**
* find_character - Find a character in a string.
* @s: The string to be parsed.
* @c: The character to look for.
*
* Returns: A pointer to the memory area
* containing the character, or NULL if not found.
*/

char *find_character(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
