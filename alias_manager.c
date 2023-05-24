#include "shell.h"

/**
* print_alias - Display aliases or a specific alias.
* @data: Pointer to the program's data structure.
* @alias: Name of the alias to be printed (optional).
*
* Return: 0 if successful, or a non-zero value if an error occurred.
*/

int print_alias(data_of_program *data, char *alias)
{
int ka, ak, alias_length;
char buffer[300] = {'\0'};

if (data->alias_list)
{
alias_length = str_length(alias);
for (ka = 0; data->alias_list[ka]; ka++)
{
if (!alias || (str_compare(data->alias_list[ka], alias, alias_length)
&& data->alias_list[ka][alias_length] == '='))
{
for (ak = 0; data->alias_list[ka][ak]; ak++)
{
buffer[ak] = data->alias_list[ka][ak];
if (data->alias_list[ka][ak] == '=')
break;
}
buffer[ak + 1] = '\0';
buffer_add(buffer, "'");
buffer_add(buffer, data->alias_list[ka] + ak + 1);
buffer_add(buffer, "'\n");
_print(buffer);
}
}
}

return (0);
}

/**
* get_alias - Get the value of a specific alias.
* @data: Pointer to the program's data structure.
* @name: Name of the requested alias.
*
* Return: The value of the requested alias if found, or NULL otherwise.
*/
char *get_alias(data_of_program *data, char *name)
{
int ka, alias_length;

/* Validate the arguments */
if (name == NULL || data->alias_list == NULL)
return (NULL);

alias_length = str_length(name);

for (ka = 0; data->alias_list[ka]; ka++)
{
if (str_compare(name, data->alias_list[ka], alias_length) &&
data->alias_list[ka][alias_length] == '=')
{
/* Return the value of the key "NAME=" when found */
return (data->alias_list[ka] + alias_length + 1);
}
}

/* Return NULL if the alias was not found */
return (NULL);
}

/**
* set_alias - Add or override an alias.
* @alias_string: Alias to be set in the form "name='value'".
* @data: Pointer to the program's data structure.
*
* Return: 0 if successful, or a non-zero value if an error occurred.
*/
int set_alias(char *alias_string, data_of_program *data)
{
int ka, ak;
char buffer[250] = {'0'}, *temp = NULL;

/* Validate the arguments */
if (alias_string == NULL || data->alias_list == NULL)
return (1);

/* Iterate over the alias string to find the '=' character */
for (ka = 0; alias_string[ka]; ka++)
{
if (alias_string[ka] != '=')
buffer[ka] = alias_string[ka];
else
{
/* Search if the value of the alias is another alias */
temp = get_alias(data, alias_string + ka + 1);
break;
}
}

/* Iterate over the alias list to check for a matching variable name */
for (ak = 0; data->alias_list[ak]; ak++)
{
if (str_compare(buffer, data->alias_list[ak], ka) &&
data->alias_list[ak][ka] == '=')
{
/* If the alias already exists, free the old value */
free(data->alias_list[ak]);
break;
}
}

/* Add or update the alias */
if (temp)
{
/* If the alias already exists, update it */
buffer_add(buffer, "=");
buffer_add(buffer, temp);
data->alias_list[ak] = str_duplicate(buffer);
}
else
{
/* If the alias does not exist, add it */
data->alias_list[ak] = str_duplicate(alias_string);
}

return (0);
}

