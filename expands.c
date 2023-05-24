#include "shell.h"

/**
* expand_variables - Expand
* variables in the input line.
* @data: Pointer to the program's data structure.
*
* Return: None, but sets errno.
*/

void expand_variables(data_of_program *data)
{
int ak, ka;
char line[BUFFER_SIZE] = {0},
expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

buffer_add(line, data->input_line);

for (ak = 0; line[ak]; ak++)
{
if (line[ak] == '#')
line[ak--] = '\0';
else if (line[ak] == '$' && line[ak + 1] == '?')
{
line[ak] = '\0';
long_to_string(errno, expansion, 10);
buffer_add(line, expansion);
buffer_add(line, data->input_line + ak + 2);
}
else if (line[ak] == '$' && line[ak + 1] == '$')
{
line[ak] = '\0';
long_to_string(getpid(), expansion, 10);
buffer_add(line, expansion);
buffer_add(line, data->input_line + ak + 2);
}
else if (line[ak] == '$' && (line[ak + 1] == ' ' || line[ak + 1] == '\0'))
continue;
else if (line[ak] == '$')
{
for (ka = 1; line[ak + ka] && line[ak + ka] != ' '; ka++)
expansion[ka - 1] = line[ak + ka];
temp = env_get_key(expansion, data);
line[ak] = '\0', expansion[0] = '\0';
buffer_add(expansion, line + ak + ka);
temp ? buffer_add(line, temp) : 1;
buffer_add(line, expansion);
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
* @data: Pointer to the program's data structure.
*
* Return: None, but sets errno.
*/

void expand_alias(data_of_program *data)
{
int ak, ka, was_expanded = 0;
char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

if (data->input_line == NULL)
return;

buffer_add(line, data->input_line);

for (ak = 0; line[ak]; ak++)
{
for (ka = 0; line[ak + ka] && line[ak + ka] != ' '; ka++)
expansion[ka] = line[ak + ka];
expansion[ka] = '\0';

temp = get_alias(data, expansion);
if (temp)
{
expansion[0] = '\0';
buffer_add(expansion, line + ak + ka);
line[ak] = '\0';
buffer_add(line, temp);
line[str_length(line)] = '\0';
buffer_add(line, expansion);
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
* buffer_add - Append a string at the end of the buffer.
* @buffer: Buffer to be filled.
* @str_to_add: String to be copied into the buffer.
*
* Return: The new length of the buffer.
*/
int buffer_add(char *buffer, char *str_to_add)
{
int length, ak;

length = str_length(buffer);

for (ak = 0; str_to_add[ak]; ak++)
{
buffer[length + ak] = str_to_add[ak];
}
buffer[length + ak] = '\0';

return (length + ak);
}
