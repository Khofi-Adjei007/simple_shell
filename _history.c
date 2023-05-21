#include "shell.h"

/**
 * handle_history - Manages the history functionality
 * @info: Parameter struct
 *
 * Return: 1 on success, 0 otherwise
 */
int handle_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (0);

	int linecount = 0;
	ssize_t fsize = 0;
	struct stat st;

	if (stat(filename, &st) == 0)
		fsize = st.st_size;

	if (fsize < 2)
		goto cleanup;

	char *buf = malloc(sizeof(char) * (fsize + 1));

	if (!buf)
		goto cleanup;

	int fd = open(filename, O_RDONLY);

	if (fd == -1)
		goto cleanup_buf;

	ssize_t rdlen = read(fd, buf, fsize);

	buf[fsize] = '\0';
	close(fd);

	if (rdlen <= 0)
		goto cleanup_buf;

	int last = 0;

	for (int i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != fsize)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);

cleanup_buf:
	free(buf);
cleanup:
	free(filename);
	return (info->histcount > 0);
}

