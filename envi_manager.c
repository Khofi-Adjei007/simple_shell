#include "shell.h"

/**
* get_environment_variable -
* Retrieves the value of an environment variable
* @variable: The name of the environment variable
* @data: Pointer to the program's data structure
*
* This function retrieves the
* value of the specified environment variable.
* It searches through the environment
* variables stored in the program's data
* structure and returns a pointer to the
* value if found. If the variable does
* not exist, it returns NULL.
*
* Return: (A pointer to the value of the
* environment variable) or (NULL if not found).
*/

char *get_environment_variable(char *variable, data_of_program *data)
{
int ak, variable_length = 0;

/* Validate arguments */
if (variable == NULL || data->environment == NULL)
return (NULL);

/* Determine the length of the variable name */
variable_length = str_length(variable);

for (ak = 0; data->environment[ak]; ak++)
{
/* Iterate through the environment and check for a match */
if (str_compare(variable, data->environment[ak], variable_length) &&
data->environment[ak][variable_length] == '=')
{
/* Return the value of the variable */
return (data->environment[ak] + variable_length + 1);
}
}

/* Variable not found */
return (NULL);
}

/**
* set_environment_variable - Sets or overwrites
* the value of an environment variable
* @variable: The name of the variable to set
* @value: The new value of the variable
* @data: Pointer to the program's data structure
*
* This function sets or overwrites the value
* of the specified environment variable.
* It searches through the environment variables
* stored in the program's data structure
* and either sets the value if the variable already
* exists or creates a new variable
* if it doesn't exist. If successful, it returns 0.
* If any of the parameters are NULL,
* it returns 1. If there is an error, it returns 2.
*
* Return: (0 on success), (1 if parameters are NULL), (2 on error).
*/
int set_environment_variable(char *variable,
char *value, data_of_program *data)
{
int ak, variable_length = 0, is_new_variable = 1;

/* Validate arguments */
if (variable == NULL || value == NULL || data->environment == NULL)
return (1);

/* Determine the length of the variable name */
variable_length = str_length(variable);

for (ak = 0; data->environment[ak]; ak++)
{
/* Iterate through the environment and check for a match */
if (str_compare(variable, data->environment[ak], variable_length) &&
data->environment[ak][variable_length] == '=')
{
/* Variable already exists, overwrite its value */
is_new_variable = 0;
free(data->environment[ak]);
break;
}
}

/* Create a string of the form "variable=value" */
data->environment[ak] = str_concat(str_duplicate(variable), "=");
data->environment[ak] = str_concat(data->environment[ak], value);

if (is_new_variable)
{
/* If it's a new variable, set the next position to NULL */
data->environment[ak + 1] = NULL;
}

return (0);
}

/**
* remove_environment_variable -
* Removes an environment variable
* @variable: The variable to remove
* @data: Pointer to the program's data structure
*
* This function removes the specified
* environment variable from the program's
* data structure. It searches through the
* environment variables and if a match
* is found, it removes the variable and
* shifts the remaining variables down.
* If successful, it returns 1. If the
* variable does not exist, it returns 0.
* If any of the parameters are NULL, it returns 0.
*
* Return: (1 if the variable was removed),
* (0 if the variable does not exist or parameters are NULL).
*/

int remove_environment_variable(char *variable, data_of_program *data)
{
int ak, variable_length = 0;

/* Validate arguments */
if (variable == NULL || data->environment == NULL)
return (0);

/* Determine the length of the variable name */
variable_length = str_length(variable);

for (ak = 0; data->environment[ak]; ak++)
{
/* Iterate through the environment and check for a match */
if (str_compare(variable, data->environment[ak], variable_length) &&
data->environment[ak][variable_length] == '=')
{
/* Variable exists, remove it and shift remaining variables */
free(data->environment[ak]);

/* Shift remaining variables down by one position */
ak++;
for (; data->environment[ak]; ak++)
{
data->environment[ak - 1] = data->environment[ak];
}

/* Set the last position to NULL */
data->environment[ak - 1] = NULL;

return (1);
}
}

return (0);
}

/**
* print_environment - Prints the current environment variables
* @data: Pointer to the program's data structure
*
* This function prints the current environment variables stored in the
* program's data structure. It iterates through the environment variables
* and prints each one followed by a newline character.
*
* Return: None
*/
void print_environment(data_of_program *data)
{
int ka;

for (ka = 0; data->environment[ka]; ka++)
{
_print(data->environment[ka]);
_print("\n");
}
}

