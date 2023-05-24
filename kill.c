#include "shell.h"

/**
* execute - Execute a command by searching
* for its entire path and executing it.
* @data: Pointer to the program's data structure.
*
* Return: 0 on success, -1 otherwise.
*/

int execute(data_of_program *data)
{
int retval = 0, status;
pid_t pid;

/* Check if the program is a built-in command */
retval = builtins_list(data);
if (retval != -1)
return (retval);

/* Search for the program in the file system */
retval = find_program(data);
if (retval)
{
/* If program is not found */
return (retval);
}
else
{
/* If program is found */
pid = fork(); /* Create a child process */
if (pid == -1)
{
/* If the fork call failed */
perror(data->command_name);
exit(EXIT_FAILURE);
}
if (pid == 0)
{
/* I am the child process, execute the program */
retval = execve(data->tokens[0], data->tokens, data->env);
if (retval == -1)
	perror(data->command_name), exit(EXIT_FAILURE);
}
else
{
/*
 * I am the parent, wait for the child
 * and check the exit status
*/

wait(&status);
if (WIFEXITED(status))
	errno = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
	errno = 128 + WTERMSIG(status);
}
}

return (0);
}

