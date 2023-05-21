#include "shell.h"

/**
* _myenv – This function Prints the current working environment.
* @info: Pointer Struct having potential arguments
* to maintain the constant function prototype.
* Return: whiles 0.
*/

int _myenv(info_t *info)
{
/* Prints the information of the current environment */
print_list_str(info->env);
return (0);
}

/**
* _mysetenv – This function starts a new environment
* variable or changes an existing one.
* @info: Pointer Struct having potential arguments to maintain
* the constant function prototype.
* Return: Always 0.
*/

int _mysetenv(info_t *info)
{
if (info->argc != 4)
{
_eputs("Incorrect number of arguments\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}



/**
* _myunsetenv – This trashes an environment variable.
* @info: Pointer Struct having potential arguments to
* maintain the constant function prototype.
* Return: Always 0.
*/

int _myunsetenv(info_t *info)
{
int m;
if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (m = 1; m <= info->argc; m++)
_unsetenv(info, info->argv[m]);

return (0);
}


/**
* populate_env_list - Fills the env linked list environment.
* @info: Pointer Struct having potential arguments to
* maintain the constant function prototype.
* Return: Always 0.
*/

int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t m;

for (m = 0; environ[m]; m++)
add_node_end(&node, environ[m], 0);
info->env = node;
return (0);
}

/**
* _getenv - Gets the value of the environment variable.
* @info: Pointer Struct with potential arguments.
* @identifier: The environment variable identifier.
* Return: The value of the environment variable.
*/

char *_getenv(info_t *info, const char *identifier)
{
list_t *node = info->env;
char *p;
while (node)
{
p = starts_with(node->str, identifier);
if (p && *p)
	return (p);
node = node->next;
}
return (NULL);
}

