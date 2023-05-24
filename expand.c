#include "shell.h"

/**
* expand_variables - Expand variables in the input line.
* @data: A pointer to the program's data structure.
*
* This function expands variables in the
* input line by replacing certain patterns
* with their corresponding values.
* It looks for specific patterns like '#' and '$'
* followed by certain characters and
* performs the necessary replacements.
*
* Return: Nothing, but sets errno.
*/

void expand_variables(data_of_program *data)
{
int ak, ka;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

buffer_append(line, data->input_line);

for (ak = 0; line[ak]; ak++)
{
if (line[ak] == '#')
line[ak--] = '\0';
else if (line[ak] == '$' && line[ak + 1] == '?')
{
line[ak] = '\0';
long_to_string(errno, expansion, 10);
buffer_append(line, expansion);
buffer_append(line, data->input_line + ak + 2);
}
else if (line[ak] == '$' && line[ak + 1] == '$')
{
line[ak] = '\0';
long_to_string(getpid(), expansion, 10);
buffer_append(line, expansion);
buffer_append(line, data->input_line + ak + 2);
}
else if (line[ak] == '$' && (line[ak + 1] == ' ' || line[ak + 1] == '\0'))
continue;
else if (line[ak] == '$')
{
for (ka = 1; line[ak + ka] && line[ak + ka] != ' '; ka++)
expansion[ka - 1] = line[ak + ka];
temp = env_get_key(expansion, data);
line[ak] = '\0';
expansion[0] = '\0';
buffer_append(expansion, line + ak + ka);
temp ? buffer_append(line, temp) : 1;
buffer_append(line, expansion);
}
}

if (!str_compare(data->input_line, line, 0))
{
free(data->input_line);
data->input_line = str_duplicate(line);
}
}

/**
* expand_alias - Expand aliases in the input line.
* @data: A pointer to the program's data structure.
*
* This function expands aliases in the
* input line by searching for aliases
* in the data structure and replacing them
* with their corresponding values.
* It looks for specific patterns and performs
* the necessary replacements.
*
* Return: Nothing, but sets errno.
*/
void expand_alias(data_of_program *data)
{
int ak, ka, was_expanded = 0;
char line[BUFFER_SIZE] = {0},
expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

buffer_append(line, data->input_line);

for (ak = 0; line[ak]; ak++)
{
for (ka = 0; line[ak + ka] && line[ak + ka] != ' '; ka++)
expansion[ka] = line[ak + ka];
expansion[ka] = '\0';

temp = get_alias(data, expansion);
if (temp)
{
expansion[0] = '\0';
buffer_append(expansion, line + ak + ka);
line[ak] = '\0';
buffer_append(line, temp);
line[str_length(line)] = '\0';
buffer_append(line, expansion);
was_expanded = 1;
}
break;
}

if (was_expanded)
{
free(data->input_line);
data->input_line = str_duplicate(line);
}
}

/**
* buffer_append - Append a string at the end of the buffer.
* @buffer: The buffer to be filled.
* @str_to_append: The string to be copied into the buffer.
*
* This function appends the given string at the end of the buffer,
* extending the content of the buffer. It concatenates the string to
* the existing buffer content.
*
* Return: The new length of the buffer after appending the string.
*/

int buffer_append(char *buffer, char *str_to_append)
{
int length, ak;

length = str_length(buffer);
for (ak = 0; str_to_append[ak]; ak++)
{
buffer[length + ak] = str_to_append[ak];
}
buffer[length + ak] = '\0';
return (length + ak);
}
