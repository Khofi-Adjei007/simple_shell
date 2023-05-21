#include "shell.h"

#define WRITE_BUF_SIZE 1024

/**
 * _eputs - Prints the string inputted
 * @str: The string to be printed
 */
void _eputs(char *str)
{
	if (!str)
		return;

	while (*str)
		_eputchar(*str++);
}

/**
 * _eputchar - Writes the char c to stderr
 * @c: The char to be printed
 * @buf: The buffer for storing characters
 * @index: The current index in the buffer
 *
 * Return: 1 on success, -1 on error
 */
int _eputchar(char c, char *buf, int *index)
{
	if (c == BUF_FLUSH || *index >= WRITE_BUF_SIZE)
	{
		write(2, buf, *index);
		*index = 0;
	}

	if (c != BUF_FLUSH)
		buf[(*index)++] = c;

	return (1);
}

/**
 * _putfd - Writes char c to the given file descriptor
 * @c: The char to be printed
 * @fd: The file descriptor to write to
 * @buf: The buffer for storing characters
 * @index: The current index in the buffer
 *
 * Return: 1 on success, -1 on error
 */
int _putfd(char c, int fd, char *buf, int *index)
{
	if (c == BUF_FLUSH || *index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, *index);
		*index = 0;
	}

	if (c != BUF_FLUSH)
		buf[(*index)++] = c;

	return (1);
}

/**
 * _putsfd - Prints the string inputted
 * @str: The inputted string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of chars put
 */
int _putsfd(char *str, int fd)
{
	int count = 0;
	char buf[WRITE_BUF_SIZE];
	int index = 0;

	if (!str)
		return (0);

	while (*str)
		count += _putfd(*str++, fd, buf, &index);

	return (count);
}

