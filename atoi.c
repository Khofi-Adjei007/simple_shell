#include "shell.h"

/**
* is_interactive - checks if the shell is running in interactive mode
* @info: pointer to the struct containing relevant information
* Returns: 1 if the shell is running in interactive mode, 0 otherwise
*/

int interactive(info_t *info)
{
if (isatty(STDIN_FILENO))
{
if (info->readfd <= 2)
	return (1);
}
return (0);
}

/**
* is_delim - determines whether a character is a delimiter
* @c: the character to check
* @delimiter: the string of delimiters to compare against
* Return: 1 if the character is a delimiter, 0 otherwise
*/

int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
	return (1);
return (0);
}


/**
* _isalpha - checks if a character is an alphabetic character
* @c: the character to be checked
* Return: 1 if the character is alphabetic, 0 otherwise
*/

int _isalpha(char c)
{
/* Check if the character is within the range of alphabets */
/* in either uppercase or lowercase */
if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
return (1);
else
return (0);
}

/**
* _atoi - converts a string to an integer
* @s: the string to be converted
*
* Return: 0 if the string does not contain any numbers, the converted
*  integer value otherwise
*/
int _atoi(char *s)
{
int result = 0;
int sign = 1;
int ka = 0;

/* Check for negative sign */
if (s[0] == '-')
{
sign = -1;
ka++;
}

/* Iterate through the string */
while (s[ka] != '\0')
{
/* Check if the current character is a digit */
if (s[ka] >= '0' && s[ka] <= '9')
{
/* Multiply the result by 10 and add the digit */
result = result * 10 + (s[ka] - '0');
}
else
{
/* Invalid character found, return 0 */
return (0);
}
ka++;
}

/* Apply the sign to the result */
result *= sign;

return (result);
}

