#include "shell.h"

/**
* main - Entry point of the shell program
* @ac: Number of command-line arguments
* @av: Array of command-line argument strings
*
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };  // Initialize info structure
int fd = 2;  /* File descriptor for stderr */

/* Update the file descriptor using inline assembly */
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

/* Check if a file is specified as an argument */
if (ac == 2)
{
/* Open the file in read-only mode */
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
/* Handle file open errors */
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;  /* Set the file descriptor for reading commands */
}

populate_env_list(info);  /* Populate the environment linked list */
read_history(info);  /* Read command history from file */
hsh(info, av);  /* Start the shell program */

return (EXIT_SUCCESS);
}

