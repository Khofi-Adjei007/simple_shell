#include "shell.h"

/**
* _eputs - Outputs a string to stderr.
* @str: The string to be displayed.
*
* Return: Nothing.
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
* _eputchar - Writes a character to the standard error stream.
* @c: The character to be printed.
*
* Return: On success, 1.
* On error, -1 is returned, and errno is set appropriately.
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
* _putfd - Writes a character to the specified file descriptor.
* @c: The character to be printed.
* @fd: The file descriptor to write to.
*
* Return: On success, 1.
* On error, -1 is returned, and errno is set appropriately.
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
* _putsfd - Outputs a string to the specified file descriptor.
* @str: The string to be displayed.
* @fd: The file descriptor to write to.
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

