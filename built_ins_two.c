#include "shell.h"

/**
* builtins_list - Search for a match and execute
* the associated built-in function.
* @data: Pointer to the program's data structure.
*
* Return: The return value of the executed
* function if there is a match,
* otherwise -1.
*/

int builtins_list(data_of_program *data)
{
int ka;
builtins options[] = {
{"exit", builtin_exit},
{"help", builtin_help},
{"cd", builtin_cd},
{"alias", builtin_alias},
{"env", builtin_env},
{"setenv", builtin_set_env},
{"unsetenv", builtin_unset_env},
{NULL, NULL}
};

/* Walk through the structure */
for (ka = 0; options[ka].builtin != NULL; ka++)
{
/* If there is a match between the given command and a built-in */
if (str_compare(options[ka].builtin, data->command_name, 0))
{
/* Execute the function and return its return value */
return (options[ka].function(data));
}
/* If there is no match, return -1 */
}
return (-1);
}

