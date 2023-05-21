#include "shell.h"
/**
 * _erratoi - Converts strings to integer
 * @s: String to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int _erratoi(char *s)
{
	long int result = strtol(s, NULL, 10);

	if (result < INT_MIN || result > INT_MAX)
		return (-1);
	return ((int)result);
}

/**
 * print_error - Prints error messages
 * @info: Structure of parameter & return info
 * @estr: Strings containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	char error_message[256];

	sprintf(error_message, "%s: %d: %s: %s", info->fname,
			info->line_count, info->argv[0], estr);
	_eputs(error_message);
}

/**
 * print_d - Function prints a decimal number
 * @input: The input
 * @fd: Filedescriptor to write to
 *
 * Return: number of chars printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int _abs_;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	if (_abs_ == 0)
	{
		__putchar('0');
		count++;
	}
	else
	{
		int length = 0, temp = _abs_;

		while (temp != 0)
		{ length++;
		temp /= 10; }
		count += length;
		char *digits = malloc((length + 1) * sizeof(char));

		if (digits == NULL)
			return (count);
		for (int i = length - 1; i >= 0; i--)
		{ digits[i] = (_abs_ % 10) + '0';
		_abs_ /= 10; }
		digits[length] = '\0';
		_eputs(digits);
		free(digits);
	}
	return (count);
}

/**
 * convert_number - Converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{ n = -num;
		sign = '-'; }
	char *array = (flags & CONVERT_LOWERCASE) ?
		"0123456789abcdef" : "0123456789ABCDEF";

	ptr = &buffer[49];
	*ptr = '\0';
	do { *--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
	*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Function replaces first instance of '#' with '\0'
 * @buf: Address of the string to modify
 *
 * Return: return 0 always;
 */
void remove_comments(char *buf)
{
	char *comment_pos = strchr(buf, '#');

	if (comment_pos != NULL && (comment_pos == buf || *(comment_pos - 1) == ' '))
		*comment_pos = '\0';
}

