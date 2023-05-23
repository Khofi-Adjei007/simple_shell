#include "shell.h"

/**
* _eputs - Prints a string to stderr
* @str: The string to be printed
*
* Description: This function writes the characters of the input string
* to the standard error stream (stderr).
*
* Return: None
*/

void _eputs(char *str)
{
int ka = 0;

if (!str)
return;

while (str[ka] != '\0')
{
_eputchar(str[ka]);
ka++;
}
}

/**
* _eputchar - Writes a character to stderr
* @c: The character to be printed
*
* Description: This function writes a single character to the standard
* error stream (stderr).
*
* Return: On success, 1 is returned. On error, -1 is returned, and errno
* is set appropriately.
*/

int _eputchar(char c)
{
static int ka;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || ka >= WRITE_BUF_SIZE)
{
write(2, buf, ka);
ka = 0;
}

if (c != BUF_FLUSH)
buf[ka++] = c;

return (1);
}

/**
* _putfd - Writes a character to a given file descriptor
* @c: The character to be printed
* @fd: The file descriptor to write to
*
* Description: This function writes a single character to the specified
* file descriptor.
*
* Return: On success, 1 is returned. On error, -1 is returned, and errno
* is set appropriately.
*/

int _putfd(char c, int fd)
{
static int ka;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || ka >= WRITE_BUF_SIZE)
{
write(fd, buf, ka);
ka = 0;
}

if (c != BUF_FLUSH)
buf[ka++] = c;

return (1);
}

/**
* _putsfd - Prints a string to a given file descriptor
* @str: The string to be printed
* @fd: The file descriptor to write to
*
* Description: This function writes the characters of the input string to
* the specified file descriptor.
*
* Return: The number of characters written.
*/

int _putsfd(char *str, int fd)
{
int ka = 0;

if (!str)
return (0);

while (*str)
{
ka += _putfd(*str++, fd);
}

return (ka);
}

