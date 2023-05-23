#include "shell.h"

/**
* _myexit - Exits the shell
* @info: Structure containing relevant information. Used to maintain
*  consistent function prototype.
* This function is responsible for terminating the shell execution.
* If the command used to invoke the shell is not "exit", the function
* returns without performing any action. Otherwise, the shell is exited
* with the specified exit status.
* Return: Does not return if info->argv[0] is "exit". Otherwise, returns
*  void.
*/


int _myexit(info_t *info)
{
int exitcheck;
if (info->argv[1])  /* If there is an exit arguement */
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
* _mycd - Change the current directory of the process
* @info: Structure containing relevant information. Used to maintain
*  consistent function prototype
* This function is responsible for changing the current directory of the
* shell process. The directory to change to is specified in `info->argv[1]`.
* If no directory is provided, the function changes the directory to the
* user's home directory.
*
* Return: Always returns 0.
*/

int _mycd(info_t *info)
{
char *s, *dir, buffer[2023];
int chdir_ret;
s = getcwd(buffer, 2023);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
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
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 2023));
}
return (0);
}


/**
* _myhelp - Display help information for the shell
* @info: Structure containing relevant information. Used to maintain
*   Consistent function prototype.
* This function is responsible for displaying help information for the shell.
* It provides a brief explanation of the available built-in commands and their
* usage. The help information is printed to the standard output.
*
* Return: Always returns 0.
*/

int _myhelp(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("Help call works. Function not yet implemented.\n");
if (0)
_puts(*arg_array); /* Temporary unused workaround */
return (0);
}


