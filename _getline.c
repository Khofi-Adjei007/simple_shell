#include "shell.h"

/**
* _getline - read line from prompt.
* @data: program's data struct.
*
* Return: return counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[25] = {NULL};
	static char array_operators[25] = {'\0'};
	ssize_t bytes_read, n = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (n = 0; array_commands[n]; n++)
		{
			free(array_commands[n]);
			array_commands[n] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		n = 0;
		do {
			array_commands[n] = str_duplicate(_strtok(n ? NULL : buff, "\n;"));
			n = check_logic_ops(array_commands, n, array_operators);
		} while (array_commands[n++]);
	}

	data->input_line = array_commands[0];
	for (n = 0; array_commands[n]; n++)
	{
		array_commands[n] = array_commands[n + 1];
		array_operators[n] = array_operators[n + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - identify and split for || and && operators
* @array_commands: array of commands.
* @n: index to be checked in the array_commands
* @array_operators: each previous command logical operators' array
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int n, char array_operators[])
{
	int m;
	char *temp = NULL;

	for (m = 0; array_commands[n] != NULL  && array_commands[n][m]; m++)
	{
		if (array_commands[n][m] == '&' && array_commands[n][m + 1] == '&')
		{
			temp = array_commands[n];
			array_commands[n][m] = '\0';
			array_commands[n] = str_duplicate(array_commands[n]);
			array_commands[n + 1] = str_duplicate(temp + m + 2);
			n++;
			array_operators[n] = '&';
			free(temp);
			m = 0;
		}
		if (array_commands[n][m] == '|' && array_commands[n][m + 1] == '|')
		{
			temp = array_commands[n];
			array_commands[n][m] = '\0';
			array_commands[n] = str_duplicate(array_commands[n]);
			array_commands[n + 1] = str_duplicate(temp + m + 2);
			n++;
			array_operators[n] = '|';
			free(temp);
			m = 0;
		}
	}
	return (n);
}
