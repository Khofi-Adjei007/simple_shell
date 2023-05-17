#include "shell.h"

/**
 * _myhistory - displays list of history, starting at 0.
 * @info: Structure containing potential arguments.
 *  Return: return 0 always
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - it assigns alias to string
 * @info: struct parameter
 * @str: string alias
 *
 * Return: return 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *q, b;
	int ret;

	p = _strchr(str, '=');
	if (!q)
		return (1);
	b = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = b;
	return (ret);
}

/**
 * set_alias - assigns alias to string
 * @info: struct parameter
 * @str: string alias
 *
 * Return: return 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - for printing of alias string
 * @node: the alias node
 *
 * Return: return 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *c = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (c = node->str; c <= q; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imitates the alias builtin
 * @info: Structure containing potential arguments.
 *
 *  Return: return 0 always
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *q = NULL;
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
	for (j = 1; info->argv[j]; j++)
	{
		q = _strchr(info->argv[j], '=');
		if (q)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
