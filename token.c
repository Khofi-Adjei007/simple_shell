#include "shell.h"
/**
 * tokenize - Function separates the string using a designed delimiter
 * @data: Pointer to the program's data
 * Return: Array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int dex, kaf, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (dex = 0; data->input_line[dex]; dex++)
	{
		for (kaf = 0; delimiter[kaf]; kaf++)
		{
			if (data->input_line[dex] == delimiter[kaf])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	dex = 0;
	data->tokens[dex] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[dex++])
	{
		data->tokens[dex] = str_duplicate(_strtok(NULL, delimiter));
	}
}
