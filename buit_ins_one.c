#include "shell.h"

/**
* builtin_env - Display the current environment variables
* @data: Pointer to the program's data structure
*
* This function is a built-in command that displays the environment variables
* where the shell is running. If there are no arguments, it prints the entire
* environment. If there is an argument in the form "NAME=VALUE", it temporarily
* sets the environment variable with the given name to the specified value,
* prints the environment, and then restores the original value.
*
* Return: Always returns 0.
*/

int builtin_env(data_of_program *data)
{
int ak;
char cpname[60] = {'\0'};
char *var_copy = NULL;

if (data->tokens[1] == NULL)
print_environment(data);
else
{
for (ak = 0; data->tokens[1][ak]; ak++)
{
if (data->tokens[1][ak] == '=')
{
var_copy = duplicate_string(get_env_key(cpname, data));
if (var_copy != NULL)
	set_env_key(cpname, data->tokens[1] + ak + 1, data);

print_environment(data);
if (get_env_key(cpname, data) == NULL)
{
	print_string(data->tokens[1]);
	print_string("\n");
}
else
{
	set_env_key(cpname, var_copy, data);
	free(var_copy);
}
return (0);
}
cpname[ak] = data->tokens[1][ak];
}
errno = 2;
perror(data->command_name);
errno = 127;
}

return (0);
}

/**
* builtin_set_env - Set or create an environment variable
* @data: Pointer to the program's data structure
*
* This function is a built-in command that sets the value of an environment
* variable or creates a new one. It requires two arguments: the variable name
* and the value to set. If there are more than two arguments, an error is
* displayed. The function updates the environment variables accordingly.
*
* Return: Always returns 0.
*/

int builtin_set_env(data_of_program *data)
{
if (data->tokens[1] == NULL || data->tokens[2] == NULL)
return (0);
if (data->tokens[3] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

set_env_key(data->tokens[1], data->tokens[2], data);

return (0);
}

/**
* builtin_unset_env - Remove an environment variable
* @data: Pointer to the program's data structure
*
* This function is a built-in command that removes an environment variable.
* It requires one argument: the name of the variable to unset. If there is
* more than one argument, an error is displayed. The function removes the
* specified environment variable from the environment.
*
* Return: Always returns 0.
*/

int builtin_unset_env(data_of_program *data)
{
if (data->tokens[1] == NULL)
return (0);
if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

remove_env_key(data->tokens[1], data);

return (0);
}

