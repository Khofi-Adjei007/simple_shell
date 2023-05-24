#include "shell.h"

/**
* getCommandLine - reads a line of input from the prompt.
* @programData: structure containing program data
*
* Returns: the number of bytes read.
*/

int getCommandLine(data_of_program *programData)
{
char buff[BUFFER_SIZE] = {'\0'};
static char *commandArray[12] = {NULL};
static char operatorArray[12] = {'\0'};
ssize_t bytesRead, ak = 0;

/* Check if there are no more commands in the array */
/* and verify the logical operators */
if (!commandArray[0] || (operatorArray[0] == '&' && errno != 0) ||
(operatorArray[0] == '|' && errno == 0))
{
/* Free the memory allocated in the command array if it exists */
for (ak = 0; commandArray[ak]; ak++)
{
free(commandArray[ak]);
commandArray[ak] = NULL;
}

/* Read from the file descriptor into buff */
bytesRead = read(programData->file_descriptor, &buff, BUFFER_SIZE - 1);
if (bytesRead == 0)
return (-1);

/* Split lines based on newline or semicolon */
ak = 0;
do {
commandArray[ak] = str_duplicate(_strtok(ak ? NULL : buff, "\n;"));
/* Check and split for logical AND (&&) and OR (||) operators */
ak = checkLogicalOperators(commandArray, ak, operatorArray);
} while (commandArray[ak++]);
}

/* Obtain the next command (command 0) and remove it from the array */
programData->input_line = commandArray[0];
for (ak = 0; commandArray[ak]; ak++)
{
commandArray[ak] = commandArray[ak + 1];
operatorArray[ak] = operatorArray[ak + 1];
}

return (str_length(programData->input_line));
}


/**
* checkLogicalOperators - checks and splits commands
* based on logical AND (&&) and OR (||) operators
* @commandArray: array of commands
* @ak: index in the commandArray to be checked
* @operatorArray: array of logical operators for each previous command
*
* Returns: index of the last command in the commandArray.
*/
int checkLogicalOperators(char *commandArray[], int ak, char operatorArray[])
{
char *temp = NULL;
int ka;

/* Check for the '&' character in the command line */
for (ka = 0; commandArray[ak] != NULL && commandArray[ak][ka]; ka++)
{
if (commandArray[ak][ka] == '&' && commandArray[ak][ka + 1] == '&')
{
/* Split the line when '&&' is found */
temp = commandArray[ak];
commandArray[ak][ka] = '\0';
commandArray[ak] = str_duplicate(commandArray[ak]);
commandArray[ak + 1] = str_duplicate(temp + ka + 2);
ak++;
operatorArray[ak] = '&';
free(temp);
ka = 0;
}
if (commandArray[ak][ka] == '|' && commandArray[ak][ka + 1] == '|')
{
/* Split the line when '||' is found */
temp = commandArray[ak];
commandArray[ak][ka] = '\0';
commandArray[ak] = str_duplicate(commandArray[ak]);
commandArray[ak + 1] = str_duplicate(temp + ka + 2);
ak++;
operatorArray[ak] = '|';
free(temp);
ka = 0;
}
}
return (ak);
}

