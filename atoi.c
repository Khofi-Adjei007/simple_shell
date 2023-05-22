#include "shell.h"

/**
* interactive - checks if the shell is in interactive mode
* @info: pointer to the info_t struct
*
* Return: 1 if in interactive mode, 0 otherwise
*/

int interactive(ino_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - checks if a character is a delimiter
* @c: the character to check
* @delim: the delimiter string
*
* Return: 1 if the character is a delimiter, 0 otherwise
*/

int is_delim(char c, char *delim)
{
while (*delim)
{
if (*delim++ == c)
return (1);
}
return (0);
}

/**
* is_alpha - checks if a character is alphabetic
* @c: the character to check
*
* Return: 1 if the character is alphabetic, 0 otherwise
*/

int is_alpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi - converts a string to an integer
* @s: the string to be converted
*
* Return: the converted number if successful, 0 otherwise
*/

int _atoi(char *s)
{
int ka, sign = 1, flag = 0, output;
unsigned int result = 0;

for (ka = 0; s[ka] != '\0' && flag != 2; ka++)
{
if (s[ka] == '-')
sign *= -1;

if (s[ka] >= '0' && s[ka] <= '9')
{
flag = 1;
result *= 10;
result += (s[ka] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}

