#include "shell.h"

/**
* displayAlias - display, add, or remove aliases
* @programData: struct containing program data
* @aliasName: name of the alias to be displayed
* Return: 0 if successful, otherwise returns a non-zero value
*/

int displayAlias(data_of_program *programData, char *aliasName)
{
int ak, ka, aliasLength;
char buffer[300] = {'\0'};

if (programData->aliasList)
{
aliasLength = str_length(aliasName);
for (ak = 0; programData->aliasList[ak]; ak++)
{
if (!aliasName || (str_compare(programData->aliasList[ak],
aliasName, aliasLength)
&&	programData->aliasList[ak][aliasLength] == '='))
{
for (ka = 0; programData->aliasList[ak][ka]; ka++)
{
buffer[ka] = programData->aliasList[ak][ka];
if (programData->aliasList[ak][ka] == '=')
	break;
}
buffer[ka + 1] = '\0';
addToBuffer(buffer, "'");
addToBuffer(buffer, programData->aliasList[ak] + ka + 1);
addToBuffer(buffer, "'\n");
_print(buffer);
}
}
}

return (0);
}

/**
* getAliasValue - get the value of an alias
* @programData: struct containing program data
* @aliasName: name of the alias requested
* Return: the value of the alias if found, otherwise returns NULL
*/

char *getAliasValue(data_of_program *programData, char *aliasName)
{
int ak, aliasLength;

/* Validate the arguments */
if (aliasName == NULL || programData->aliasList == NULL)
return (NULL);

aliasLength = str_length(aliasName);

for (ak = 0; programData->aliasList[ak]; ak++)
{
if (str_compare(aliasName, programData->aliasList[ak], aliasLength) &&
programData->aliasList[ak][aliasLength] == '=')
{
return (programData->aliasList[ak] + aliasLength + 1);
}
}
return (NULL);
}

/**
* setAlias - add or override an alias
* @aliasString: alias to be set in the format (name='value')
* @programData: struct containing program data
* Return: 0 if successful, otherwise returns a non-zero value
*/

int setAlias(char *aliasString, data_of_program *programData)
{
int ak, ka;
char buffer[300] = {'0'}, *temp = NULL;

/* Validate the arguments */
if (aliasString == NULL ||  programData->aliasList == NULL)
return (1);

for (ak = 0; aliasString[ak]; ak++)
{
if (aliasString[ak] != '=')
buffer[ak] = aliasString[ak];
else
{
temp = getAliasValue(programData, aliasString + ak + 1);
break;
}
}

for (ka = 0; programData->aliasList[ka]; ka++)
{
if (str_compare(buffer, programData->aliasList[ka], ak) &&
programData->aliasList[ka][ak] == '=')
{
free(programData->aliasList[ka]);
break;
}
}

if (temp)
{
bufferAdd(buffer, "=");
bufferAdd(buffer, temp);
programData->aliasList[ka] = strDuplicate(buffer);
}
else
programData->aliasList[ka] = strDuplicate(aliasString);
return (0);
}

