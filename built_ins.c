#include "shell.h"

/**
* _myexit - Terminate the shell
* @info: Pointer to the info structure
* containing potential arguments
*
* This function is responsible for exiting the shell.
* It checks if there is an argument provided for the "exit" command.
* If an argument is present, it converts it to an
* integer and sets it as the exit status.
* If the argument is not a valid number, it prints
* an error message and returns an error code.
* If no argument is provided, the exit status is set to a default value.
*
* Return: The exit status to be used by the calling function
*/

int _myexit(info_t *info)
{
int exitcheck;

if (info->argv[1])  /* Check if there is an exit argument */
{
exitcheck = _erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = _erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}



/**
* change_directory - Change the current working directory
* @info: Pointer to the info structure containing potential arguments
*
* This function is responsible for changing the current
* working directory of the shell process.
* If no argument is provided, it attempts to change to the home directory.
* If the argument is a hyphen ("-"), it attempts to
* change to the previous working directory (if available).
* For any other argument, it attempts to change to the specified directory.
* After changing the directory successfully, it updates the
* environment variables related to the working directory.
*
* Return: Always returns 0
*/

int _mycd(info_t *info)
{
char *s, *dir, buffer[2030];
int chdir_ret;

s = getcwd(buffer, 2030);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: What should this be? */
	chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: What should this be? */
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "Can't change directory to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 2030));
}
return (0);
}

/**
* display_help - Display help information
* @info: Pointer to the info structure containing potential arguments
*
* This function is responsible for displaying
* help information for the shell.
* Currently, the function is not fully implemented.
* It simply prints a message stating that
* the help function is not yet implemented.
* The argument array is temporarily used
* to avoid unused variable warnings.
*
* Return: Always returns 0
*/




int _myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("Help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* Temporary unused workaround */
return (0);
}

