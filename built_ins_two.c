#include "shell.h"

/**
* builtins_list - Search for a match and execute the
* associated built-in command
* @data: Pointer to the program's data structure
*
* This function searches for a match between the
* given command and the available
* built-in commands. If a match is found, it
* executes the corresponding function
* and returns the return value of that function.
* If there is no match, it returns -1.
*
* Return: Returns the return value of the executed
* function if there is a match,
* otherwise returns -1.
*/

int builtins_list(data_of_program *data)
{
int ak;
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

/* Iterate through the options structure */
for (ak = 0; options[ak].builtin != NULL; ak++)
{
/* Check if there is a match between the given command and a built-in */
if (str_compare(options[ak].builtin, data->command_name, 0))
{
/* Execute the associated function and return its return value */
return (options[ak].function(data));
}
}

/* If there is no match, return -1 */
return (-1);
}

