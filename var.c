#include "shell.h"

/**
* is_chain_delimiter - Checks if the current
* character in the buffer is a chain delimiter
* @info: The parameter struct
* @buf: The character buffer
* @p: Address of the current position in buf
*
* Return: 1 if it is a chain delimiter, 0 otherwise
*/

int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
size_t ak = *p;

/* Check for logical OR operator */
if (buf[ak] == '|' && buf[ak + 1] == '|')
{
buf[ak] = 0;
ak++;
info->cmd_buf_type = CMD_OR;
}

/* Check for logical AND operator */
else if (buf[ak] == '&' && buf[ak + 1] == '&')
{
buf[ak] = 0;
ak++;
info->cmd_buf_type = CMD_AND;
}

/* Check for semicolon delimiter */

else if (buf[ak] == ';')
{
buf[ak] = 0; /* Replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);

*p = ak;
return (1);
}

/**
* check_chain_status - Checks if we should continue
* chaining based on the last status
* @info: The parameter struct
* @buf: The character buffer
* @p: Address of the current position in buf
* @ka: Starting position in buf
* @len: Length of buf
*
* Return: Void
*/

void check_chain_status(info_t *info,
char *buf, size_t *p, size_t ka, size_t len)
{
size_t ak = *p;

/* Check if the last command was an AND command */
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[ka] = 0;
ak = len;
}
}

/* Check if the last command was an OR command */
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[ka] = 0;
ak = len;
}
}

*p = ak;
}

/**
* replace_aliases - Replaces aliases in the tokenized string
* @info: The parameter struct
*
* Return: 1 if aliases are replaced, 0 otherwise
*/

int replace_aliases(info_t *info)
{
int ka;
list_t *node;
char *p;

for (ka = 0; ka < 10; ka++)
{
/* Find the node that starts with the given alias */
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);

free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);

p = _strdup(p + 1);
if (!p)
return (0);

info->argv[0] = p;
}

return (1);
}

/**
* replace_variables - Replaces variables in the tokenized string
* @info: The parameter struct
*
* Return: 1 if variables are replaced, 0 otherwise
*/

int replace_variables(info_t *info)
{
int ka = 0;
list_t *node;

for (ka = 0; info->argv[ka]; ka++)
{
if (info->argv[ka][0] != '$' || !info->argv[ka][1])
continue;

/* Check if the variable is "$?" */
if (!_strcmp(info->argv[ka], "$?"))
{
replace_string(&(info->argv[ka]),
	_strdup(convert_number(info->status, 10, 0)));
continue;
}

/* Check if the variable is "$$" */
if (!_strcmp(info->argv[ka], "$$"))
{
replace_string(&(info->argv[ka]),
	_strdup(convert_number(getpid(), 10, 0)));
continue;
}

/* Find the node that starts with the given variable */
node = node_starts_with(info->env, &info->argv[ka][1], '=');
if (node)
{
replace_string(&(info->argv[ka]),
	_strdup(_strchr(node->str, '=') + 1));
continue;
}

replace_string(&info->argv[ka], _strdup(""));
}

return (0);
}

/**
* replace_string - Replaces a string
* @old: Address of the old string
* @new: New string
*
* Return: 1 if the string is replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

