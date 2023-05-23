#include "shell.h"

/*
* _myhistory - Displays the command history
* @info: Structure containing relevant arguments. Used to maintain
* constant function prototype.
* Return: Always returns 0.
* Description: This function displays the command history list. Each command
*  is shown on a separate line, accompanied by a line number
*  Starting at 0.
*/

int _myhistory(info_t *info)
{
print_list(info->history);   /* prints the command history list */
return (0);
}


/**
* unset_alias - removes an alias for a given string
* @info: Structure containing relevant information
* @str: The string representing the alias
*
* This function is responsible for removing
* an alias for a given string. It takes
* the alias string as input and searches for
* it in the alias data structure stored
* in the info structure. If a matching alias is
* found, it is removed from the data
* structure. If no matching alias is found,
* the function returns an error.
*
* Return: Always 0 on success, 1 on error
*/



int unset_alias(info_t *info, char *str)
{
char *p, c;
int ret = 0;

p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = '\0';

/* Traverse the alias list and search for the matching alias */
list_t *node
while (node)
{
if (strcmp(node->str, str) == 0)
{
node = info->alias;

/* Delete the node with the matching alias */
delete_node_at_index(&(info->alias), get_node_index(info->alias, node));
ret = 1;
break;
}
node = node->next;
}
*p = c;
return (ret);
}


/**
* set_alias - Associates a string with an alias in the shell
* @info: Pointer to the parameter struct
* that contains relevant information
* @str: The string representing the alias to be set
*
* Return: 0 on success, 1 on error
*/


int set_alias(info_t *info, char *str)
{
char *equal_sign_position;

equal_sign_position = find_character(str, '=');
if (!equal_sign_position)

return (1);

if (!*++equal_sign_position)
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* display_alias - outputs the content of an alias node
* @node: The alias node to be printed
*
* Return: 0 on success, 1 on error
*/

int print_alias(list_t *node)
{
char *p = NULL, *ka = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (ka = node->str; ka <= p; ka++)
_putchar(*ka);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}


/**
* _myalias - replicates the behavior of the alias
* built-in command (man alias)
* @info: Pointer to the structure that contains
* potential arguments. Used to maintain
*  a constant function prototype.
* Return: Always 0
*/

int _myalias(info_t *info)
{
int ak = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (ak = 1; info->argv[ak]; ak++)
{
p = _strchr(info->argv[ak], '=');
if (p)
set_alias(info, info->argv[ak]);
else
print_alias(node_starts_with(info->alias, info->argv[ak], '='));
}
return (0);
}

