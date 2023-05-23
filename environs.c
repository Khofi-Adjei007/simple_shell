#include "shell.h"

/**
* _myenv - displays the current environment variables
* @info: Pointer to the structure that holds potential
* arguments. It is used to maintain
*  a constant function prototype.
* Return: Always returns 0
*/

int _myenv(info_t *info)
{
print_list_str(info->env);
return (0);
}


/**
* _getenv - retrieves the value of an environment variable
* @info: Pointer to the structure that holds
* potential arguments. It is used to maintain
*  a constant function prototype.
* @name: Name of the environment variable
*
* Return: The value of the environment variable
*/

char *_getenv(info_t *info, const char *name)
{
list_t **node =(list_t **)&(info->environ);
if (environ == NULL || name == NULL)
return (NULL);
while (*node != NULL)
{
char *p = *((char **)(*node));
char *equals = strchr(p, '=');
if (equals != NULL)


{
size_t len = equals - p;
if (strncmp(p, name, len) == 0 && name[len] == '\0')
return (equals + 1);
}
node++;
}
return (NULL);
}


/**
* _mysetenv - Assigns a new value to an
* environment variable or creates a new one
* @info: Pointer to the structure containing
* relevant arguments. Maintains
* constant function prototype.
* Return: Always 0
*/

int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Invalid number of arguments\n");
return (1);
}

if (_setenv(info, info->argv[1], info->argv[2]) == 0)
return (0);

return (1);
}




/**
* _myunsetenv - Deletes an environment variable
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int _myunsetenv(info_t *info)
{
int ka;
if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (ka = 1; ka <= info->argc; ka++)
_unsetenv(info, info->argv[ka]);
return (0);
}

/**
* populate_env_list - Creates and populates an environment linked list
* @info: Structure containing potential arguments. Used to maintain
*         constant function prototype.
* Return: Always 0
*/

int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t ka;
for (ka = 0; environ[ka]; ka++)
add_node_end(&node, environ[ka], 0);
info->env = node;
return (0);
}

