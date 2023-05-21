#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 *
 * Return: Pointer to the string array of environment variables
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove a variable from the environment
 * @info: Structure containing potential arguments.
 * @var: Variable to be removed
 *
 * Return: 1 on successful delete, 0 otherwise
 */
int _unsetenv(info_t *info, const char *var)
{
	list_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		if (_starts_with(node->str, var) && node->str[_strlen(var)] == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set or update an environment variable
 * @info: Structure containing potential arguments.
 * @var: Variable name
 * @value: Variable value
 *
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, const char *var, const char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

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
		p = _starts_with(node->str, var);
		if (p && *p == '=')
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

