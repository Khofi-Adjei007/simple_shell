#include "shell.h"

/**
* _getline - Read one line from the prompt.
* @data: Pointer to the program's data structure.
*
* Return: The number of bytes read.
*/

int _getline(data_of_program *data)
{
char buff[BUFFER_SIZE] = {'\0'};
static char *array_commands[10] = {NULL};
static char array_operators[10] = {'\0'};
ssize_t bytes_read, ak = 0;

/* Check if there are no more commands in the array */
/* and check the logical operators */
if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
(array_operators[0] == '|' && errno == 0))
{
/* Free the allocated memory in the array if it exists */
for (ak = 0; array_commands[ak]; ak++)
{
free(array_commands[ak]);
array_commands[ak] = NULL;
}

/* Read from the file descriptor into the buffer */
bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
if (bytes_read == 0)
return (-1);

/* Split lines by '\n' or ';' */
ak = 0;
do {
array_commands[ak] = str_duplicate(_strtok(ak ? NULL : buff, "\n;"));
/* Check and split for '&&' and '||' operators */
ak = check_logic_ops(array_commands, ak, array_operators);
} while (array_commands[ak++]);
}

/* Obtain the next command (command 0) and remove it from the array */
data->input_line = array_commands[0];
for (ak = 0; array_commands[ak]; ak++)
{
array_commands[ak] = array_commands[ak + 1];
array_operators[ak] = array_operators[ak + 1];
}

return (str_length(data->input_line));
}

/**
* check_logic_ops - Check and split for '&&' and '||' operators.
* @array_commands: Array of commands.
* @ak: Index in the array_commands to be checked.
* @array_operators: Array of logical operators for each previous command.
*
* Return: Index of the last command in the array_commands.
*/

int check_logic_ops(char *array_commands[], int ak, char array_operators[])
{
char *temp = NULL;
int ka;

/* Check for the '&' character in the command line */
for (ka = 0; array_commands[ak] != NULL  && array_commands[ak][ka]; ka++)
{
if (array_commands[ak][ka] == '&' && array_commands[ak][ka + 1] == '&')
{
/* Split the line when '&&' is found */
temp = array_commands[ak];
array_commands[ak][ka] = '\0';
array_commands[ak] = str_duplicate(array_commands[ak]);
array_commands[ak + 1] = str_duplicate(temp + ka + 2);
ak++;
array_operators[ak] = '&';
free(temp);
ka = 0;
}
if (array_commands[ak][ka] == '|' && array_commands[ak][ka + 1] == '|')
{
/* Split the line when '||' is found */
temp = array_commands[ak];
array_commands[ak][ka] = '\0';
array_commands[ak] = str_duplicate(array_commands[ak]);
array_commands[ak + 1] = str_duplicate(temp + ka + 2);
ak++;
array_operators[ak] = '|';
free(temp);
ka = 0;
}
}
return (ak);
}
