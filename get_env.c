#include "shell.h"

/**
 * get_environ - Returns string array copy of our environ
 * @info: Struct containing potential arguments.
 * Return: Return 0 always
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove a variable from the environment
 * @info: Struct containing potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @var: String env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t unique = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), unique);
			unique = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		unique++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable.
 * @info: Struct containing potential arguments. Used to maintain
 * @var: String env var property
 * @value: String env var value
 *  Return: Return 0 always.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
