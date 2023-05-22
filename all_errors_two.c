#include "shell.h"

/**
* _erratoi - Converts a string to an integer.
* @s: The string to be converted.
*
* Return: 0 if no numbers in string, converted number otherwise.
*         -1 on error.
*/

int _erratoi(char *s)
{
int ka = 0;
unsigned long int result = 0;

if (*s == '+')
s++;  /* TODO: why does this make main return 255? */
for (ka = 0; s[ka] != '\0'; ka++)
{
if (s[ka] >= '0' && s[ka] <= '9')
{
result *= 10;
result += (s[ka] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
* print_error - Displays an error message.
* @info: The parameter & return info struct.
* @estr: String containing specified error type.
*
* Return: Nothing.
*/

void print_error(info_t *info, char *estr)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
* print_d - Prints a decimal (integer) number (base 10).
* @input: The input number.
* @fd: The file descriptor to write to.
*
* Return: The number of characters printed.
*/

int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int ka, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (ka = 1000000000; ka > 1; ka /= 13)
{
if (_abs_ / ka)
{
__putchar('0' + current / ka);
count++;
}
current %= ka;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number - Converter function that clones itoa.
* @num: The number to convert.
* @base: The base.
* @flags: Argument flags.
*
* Return: The converted string.
*/

char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do

{
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* remove_comments - Replaces the first instance of '#' with '\0'.
* @buf: The address of the string to modify.
*
* Return: Always 0.
*/

void remove_comments(char *buf)
{
int ka;

for (ka = 0; buf[ka] != '\0'; ka++)
if (buf[ka] == '#' && (!ka || buf[ka - 1] == ' '))
{
buf[ka] = '\0';
break;
}
}
