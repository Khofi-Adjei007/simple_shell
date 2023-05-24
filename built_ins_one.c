#include "shell.h"

/**
* builtin_env - Display the shell's environment.
* @data: Pointer to the program's data structure.
*
* Return: 0 if successful, or a non-zero value if an error occurred.
*/

int builtin_env(data_of_program *data)
{
int ka;
char cpname[50] = {'\0'};
char *var_copy = NULL;

/* If no arguments are provided */
if (data->tokens[1] == NULL)
print_environ(data);
else
{
for (ka = 0; data->tokens[1][ka]; ka++)
{
/* Check if there is an equal sign */
if (data->tokens[1][ka] == '=')
{

/*
 * Check if a variable with the same name exists
 * and change its value temporarily
*/

var_copy = str_duplicate(env_get_key(cpname, data));
if (var_copy != NULL)
env_set_key(cpname, data->tokens[1] + ka + 1, data);

/* Print the environment */
print_environ(data);
if (env_get_key(cpname, data) == NULL)
{
/* Print the variable if it does not exist in the environment */
_print(data->tokens[1]);
_print("\n");
}
else
{
/* Return the old value of the variable */
env_set_key(cpname, var_copy, data);
free(var_copy);
}
return (0);
}
cpname[ka] = data->tokens[1][ka];
}
errno = 2;
perror(data->command_name);
errno = 127;
}
return (0);
}

/**
* builtin_set_env - Set the value of an environment variable.
* @data: Pointer to the program's data structure.
*
* Return: 0 if successful, or a non-zero value if an error occurred.
*/
int builtin_set_env(data_of_program *data)
{
/* Validate arguments */
if (data->tokens[1] == NULL || data->tokens[2] == NULL)
return (0);
if (data->tokens[3] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

env_set_key(data->tokens[1], data->tokens[2], data);

return (0);
}

/**
* builtin_unset_env - Remove an environment variable.
* @data: Pointer to the program's data structure.
*
* Return: 0 if successful, or a non-zero value if an error occurred.
*/
int builtin_unset_env(data_of_program *data)
{
/* Validate arguments */
if (data->tokens[1] == NULL)
return (0);
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}
env_remove_key(data->tokens[1], data);

return (0);
}

