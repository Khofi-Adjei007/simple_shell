#include "shell.h"

/**
* _string_length - Returns the length of a string
* @str: The string whose length to check
*
* Return: The length of the string
*/

int _string_length(char *str)
{
int length = 0;

/* Check if the string is NULL */
if (!str)
return (0);

/* Calculate the length of the string */
while (*str++)
length++;

return (length);
}

/**
* _string_compare - Performs lexicographic comparison of two strings
* @str1: The first string
* @str2: The second string
*
* Return: Negative value if str1 < str2,
* positive value if str1 > str2, 0 if str1 == str2
*/

int _string_compare(char *str1, char *str2)
{

/*
 * Compare each character of the strings until a
 * difference is found or one of them ends
*/


while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);

str1++;
str2++;
}

/* Check if both strings have reached the end */
if (*str1 == *str2)
return (0);
else
return ((*str1 < *str2) ? -1 : 1);
}

/**
* _starts_with - Checks if a string starts with a given substring
* @string: The string to search
* @substring: The substring to find
*
* Return: Address of the next character of
* 'string' if 'substring' is found, otherwise NULL
*/

char *_starts_with(const char *string, const char *substring)
{

/*
 * Compare each character of the substring with
 * the corresponding character in the string
*/

while (*substring)
{
if (*substring++ != *string++)
return (NULL);
}

return ((char *)string);
}

/**
* _string_concatenate - Concatenates two strings
* @dest: The destination buffer
* @src: The source buffer
*
* Return: Pointer to the destination buffer
*/
char *_string_concatenate(char *dest, char *src)
{
char *result = dest;

/* Move the destination pointer to the end of the string */
while (*dest)
dest++;

/*
 * Copy each character of the source
 * string to the destination string
*/

while (*src)
*dest++ = *src++;

*dest = *src; /* Copy the null terminator */

return (result);
}
