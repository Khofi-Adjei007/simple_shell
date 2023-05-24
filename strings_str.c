#include "shell.h"
/**
 * _strtok - This function separates strings with delimiters
 * @line: The pointer to array we receive in getline.
 * @delim: The chars we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int index;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (index = 0; delim[index] != '\0'; index++)
		{
			if (*str == delim[index])
			break;
		}
		if (delim[index] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (index = 0; delim[index] != '\0'; index++)
		{
			if (*str == delim[index])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
