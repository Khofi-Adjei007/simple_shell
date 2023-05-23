#include "shell.h"

/**
 * clear_info - Initializes struct for info_t.
 * @info: Structure's address
 */
void clear_info(info_t *info)
{
*info = (info_t){0};
}

/**
 * set_info - Initializes struct for info_t.
 * @info: Structure's address
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
int dent = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *));
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
else
{
for (dent = 0; info->argv[dent]; dent++)
;
}
info->argc = dent;

replace_alias(info);
replace_vars(info);
}
}


/**
 * free_info - It frees struct field of info_t.
 * @info: Structure's address
 * @all: true if all fields are freed
 */
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);
free_list(&(info->env));
free_list(&(info->history));
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}
