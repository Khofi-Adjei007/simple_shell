#include "shell.h"

/**
* execute - Execute a command with its
* corresponding path variables.
* @data: A pointer to the program's data structure.
*
* This function executes a command by searching
* for it in the built-in programs
* list first. If found, it executes the built-in
* program. If not found, it searches
* for the program in the file system and executes it.
* It creates a child process
* using fork() and calls execve() to execute the program.
* The function waits for
* the child process to complete and checks its exit status.
*
* Return: (0) if successful, (-1) on failure.
*/

int execute(data_of_program *data)
{
int retval = 0, status;
pid_t pid;

/* Check if program is a built-in command */
retval = search_builtins(data);
if (retval != -1)
return (retval);

/* Search for program in the file system */
retval = find_program(data);
if (retval)
return (retval);
else
{
/* Program found, create a child process */
pid = fork();
if (pid == -1)
{
/* Fork failed */
perror(data->command_name);
exit(EXIT_FAILURE);
}
if (pid == 0)
{
/* Child process executes the program */
retval = execve(data->tokens[0], data->tokens, data->env);
if (retval == -1)
{
/* Error in execve */
perror(data->command_name);
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process waits for child and checks exit status */
wait(&status);
if (WIFEXITED(status))
errno = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
errno = 128 + WTERMSIG(status);
}
}

return (0);
}

