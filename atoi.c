1`#include "shell.h"

/**
* interactive – This function returns true if shell
* is currently running interactively.
* @info: Pointer to a struct that contains an address
* Return: Returns a boolean value indicating whether the
* shell is running in interactive mode.
* *Specifically, returns 1 if the shell is interactive,
* and 0 if otherwise.
*/

int interactive(info_t *info)
{

/**
 * Check if standard input is a terminal and if the read file
 * descriptor is within the range of standard input to standard error
*/

return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* Function to determine if a character is a delimeter
*
* is_delim – This function determines if a character
* given is a delimter and returns true if it is.
* @c: The Character that will be checked for delimiting
* @delim: a null-terminated string of characters used as delimiters.
* Return: Determines whether the input character
* is a delimiter and returns 1 if it is; otherwise, returns 0.
*/

int is_delim(char c, char *delim)
{

/*
 * Iterate through each character in the delimiter string
 * and check if it matches the provided character
*/

while (*delim)
if (*delim++ == c)
return (1);

/* The provided character is not a delimiter */
return (0);
}

/**
* _atoi – This function converts a string to an integer
* @s: This determines the string to be converted
* Return: This function returns 0 if the there are no numbers 1 otherwise
*/

int _atoi(char *s)
{
int j, sign = 1, flag = 0, output;
unsigned int result = 0;

/* Iterate through each character in the string */
for (j = 0; s[j] != '\0' && flag != 2; i++)
{

/*
 * If a negative sign is encountered,
 * set the sign variable to -1
*/

if (s[j] == '-')
sign *= -1;

/*
 * If the character is a digit, set the flag
 * variable to 1 and add it to the result
*/

if (s[j] >= '0' && s[j] <= '9')
{
flag = 1;
result *= 10;
result += (s[j] - '0');
}

/*
 * If a non-digit character is encountered after a digit
 * character, set the flag variable to 2 to exit the loop
*/

else if (flag == 1)
flag = 2;
}

/* Multiply the result by the sign to get the final output */
if (sign == -1)
output = -result;
else
output = result;

return (output);
}


/**
* _isalpha – Tests whether a given character
* is an alphabetic character or not.
* @c: The character being examined.
* Return: This function returns 1 if the input character is
* an alphabetic character and 0 otherwise.
*/

int _isalpha(int c)
{

/*
 * Check if the character is within the ASCII range
 * of uppercase or lowercase letters
*/

if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);

/* The character is not an alphabetic character */
else
return (0);
}
