#include "shell.h"

/**
* env_get_key - Retrieve the value of
* an environment variable.
* @key: The environment variable to retrieve.
* @data: Pointer to the program's data structure.
*
* Return: A pointer to the value of the
* variable or NULL if it doesn't exist.
*/

char *env_get_key(char *key, data_of_program *data)
{
int ak, key_length = 0;

/* Validate the arguments */
if (key == NULL || data->env == NULL)
return (NULL);

/* Calculate the length of the requested variable */
key_length = str_length(key);

for (ak = 0; data->env[ak]; ak++)
{
/* Iterate through the environment variables and check for a match */
if (str_compare(key, data->env[ak], key_length) &&
data->env[ak][key_length] == '=')
{
/* Return the value of the variable (key=value format) */
return (data->env[ak] + key_length + 1);
}
}

/* Return NULL if the variable was not found */
return (NULL);
}

/**
* env_set_key - Overwrite the value of an environment
* variable or create it if it doesn't exist.
* @key: Name of the variable to set.
* @value: New value for the variable.
* @data: Pointer to the program's data structure.
*
* Return: 1 if the parameters are NULL,
* 2 if there is an error, or 0 if successful.
*/
int env_set_key(char *key, char *value, data_of_program *data)
{
int ak, key_length = 0, is_new_key = 1;

/* Validate the arguments */
if (key == NULL || value == NULL || data->env == NULL)
return (1);

/* Calculate the length of the variable */
key_length = str_length(key);

for (ak = 0; data->env[ak]; ak++)
{
/* Iterate through the environment variables and check for a match */
if (str_compare(key, data->env[ak], key_length) &&
data->env[ak][key_length] == '=')
{
/* If the key already exists, free the current variable */
is_new_key = 0;
free(data->env[ak]);
break;
}
}

/* Create a new string in the format "key=value" */
data->env[ak] = str_concat(str_duplicate(key), "=");
data->env[ak] = str_concat(data->env[ak], value);

if (is_new_key)
{
/* If the variable is new, add a NULL value at the end of the list */
data->env[ak + 1] = NULL;
}

return (0);
}

/**
* env_remove_key - Remove a key from the environment.
* @key: The key to remove.
* @data: Pointer to the program's data structure.
*
* Return: 1 if the key was removed, 0 if the key does not exist.
*/
int env_remove_key(char *key, data_of_program *data)
{
int ak, key_length = 0;

/* Validate the arguments */
if (key == NULL || data->env == NULL)
return (0);

/* Calculate the length of the key */
key_length = str_length(key);

for (ak = 0; data->env[ak]; ak++)
{
/* Iterate through the environment variables and check for a match */
if (str_compare(key, data->env[ak], key_length) &&
data->env[ak][key_length] == '=')
{
/* If the key exists, remove it */
free(data->env[ak]);

/* Shift the remaining keys one position down */
ak++;
for (; data->env[ak]; ak++)
{
data->env[ak - 1] = data->env[ak];
}

/* Set the NULL value at the new end of the list */
data->env[ak - 1] = NULL;
return (1);
}
}

return (0);
}

/**
* print_environ - Print the current environment variables.
* @data: Pointer to the program's data structure.
*
* Return: None.
*/
void print_environ(data_of_program *data)
{
int ka;

for (ka = 0; data->env[ka]; ka++)
{
/* Iterate through the environment variables and print each one */
_print(data->env[ka]);
_print("\n");
}
}
