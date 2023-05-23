#include "shell.h"

/**
 * get_history_file - Obtain the history file
 * @info: Structure parameter
 *
 * Return: Allocated string containg history file
 */
char *get_history_file(info_t *info)
{
char *buf, *dir;
size_t buf_len;

dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);

buf_len = _strlen(dir) + _strlen("/") + _strlen(HIST_FILE) + 1;
buf = malloc(sizeof(char) * buf_len);
if (!buf)
return (NULL);

_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}



/**
 * write_history - Creates a file or appends to an existing file.
 * @info: struct parameter
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
ssize_t fd;
list_t *node = NULL;

fd = open(get_history_file(info), O_CREAT | O_TRUNC | O_WRONLY, 0644);
if (fd == -1)
return (-1);

while (info->history)
{
_putsfd(info->history->str, fd);
_putfd('\n', fd);
info->history = info->history->next;
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}


/**
 * read_history - Reads history from file
 * @info: Structure parameter
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
int last = 0, linecount = 0;
ssize_t rdlen;
struct stat st;
char *buf = NULL, *filename = get_history_file(info);

if (!filename)
return (0);

int fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);

if (!fstat(fd, &st) || st.st_size < 2)
{
close(fd);
return (0);
}

while ((rdlen = read(fd, buf, 1)) > 0 && *buf != '\n')
{
if (*buf == '\0')
break;

if (linecount >= last + rdlen)
{
buf[linecount] = '\0';
build_history_list(info, buf + last, linecount++);
last = linecount;
}
else
{
buf = realloc(buf, (linecount + 1) * sizeof(char));
if (!buf)
{
close(fd);
return (0);
}
buf[linecount] = '\0';
build_history_list(info, buf + last, linecount++);
last = linecount;
}
}

close(fd);
free(buf);

info->histcount = linecount;

while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);

renumber_history(info);
return (info->histcount);
}

/**
 * build_history_list - Adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;

if (info->history)
{
node = info->history;
}
add_node_end(&node, buf, linecount);

info->history = node;
return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
list_t *node = info->history;
int j = 0;

while (node)
{
node->num = j++;
node = node->next;
}
return (info->histcount = j);
}
