#include "shell.h"

/**
* builtin_exit - Terminate the program with
* the specified status
* @data: Pointer to the program's data structure
*
* This function terminates the program with
* the specified status. If an argument
* is provided, it checks if it is a valid number.
* If the argument is not a number,
* it returns an error. If no argument is provided,
* it terminates the program with
* the default status. The function also frees all
* allocated data before exiting.
*
* Return: Zero if successful, or a non-zero number if an error occurs.
*/

int builtin_exit(data_of_program *data)
{
int ak;

if (data->tokens[1] != NULL)
{
for (ak = 0; data->tokens[1][ak]; ak++)
{
if ((data->tokens[1][ak] < '0' || data->tokens[1][ak] > '9') &&
data->tokens[1][ak] != '+')
{
errno = 2;
return (2);
}
}
errno = _atoi(data->tokens[1]);
}

free_all_data(data);
exit(errno);
}

/**
* builtin_cd - Change the current directory
* @data: Pointer to the program's data structure
*
* This function changes the current working directory.
* If an argument is provided,
* it checks if it is a valid directory path and
* changes the working directory to it.
* If the argument is "-", it changes the directory
* to the previous working directory.
* If no argument is provided, it changes the
* directory to the home directory.
*
* Return: Zero if successful,
* or a non-zero number if an error occurs.
*/

int builtin_cd(data_of_program *data)
{
char *dir_home = env_get_key("HOME", data);
char *dir_old = NULL;
char old_dir[128] = {0};
int error_code = 0;

if (data->tokens[1])
{
if (str_compare(data->tokens[1], "-", 0))
{
dir_old = env_get_key("OLDPWD", data);
if (dir_old)
error_code = set_work_directory(data, dir_old);
_print(env_get_key("PWD", data));
_print("\n");

return (error_code);
}
else
{
return (set_work_directory(data, data->tokens[1]));
}
}
else
{
if (!dir_home)
dir_home = getcwd(old_dir, 128);

return (set_work_directory(data, dir_home));
}

return (0);
}

/**
* set_work_directory - Set the working directory
* @data: Pointer to the program's data structure
* @new_dir: Path to be set as the working directory
*
* This function sets the working directory to
* the specified path. It first retrieves
* the current working directory and compares it
* with the new directory. If they are
* different, it attempts to change the directory
* using chdir(). If an error occurs,
* it returns the corresponding error code.
* Otherwise, it updates the "PWD" environment
* variable and sets the "OLDPWD" variable to
* the previous working directory.
*
* Return: Zero if successful, or a non-zero
* number if an error occurs.
*/

int set_work_directory(data_of_program *data, char *new_dir)
{
char old_dir[128] = {0};
int err_code = 0;

getcwd(old_dir, 128);

if (!str_compare(old_dir, new_dir, 0))
{
err_code = chdir(new_dir);
if (err_code == -1)
{
errno = 2;
return (3);
}
env_set_key("PWD", new_dir, data);
}

env_set_key("OLDPWD", old_dir, data);
return (0);
}

/**
* builtin_help - Display help information for the shell
* @data: Pointer to the program's data structure
*
* This function displays help information for
* the shell. If no argument is provided,
* it prints a general help message. If an argument
* is provided, it checks if it matches
* any of the available help messages and prints the
* corresponding message. If no match
* is found, it returns an error.
*
* Return: Zero if successful, or a non-zero number if an error occurs.
*/

int builtin_help(data_of_program *data)
{
int ak, length = 0;
char *messages[6] = {NULL};

messages[0] = HELP_MSG;

/* Validate arguments */
if (data->tokens[1] == NULL)
{
_print(messages[0] + 6);
return (1);
}

if (data->tokens[2] != NULL)
{
errno = E2BIG;
perror(data->command_name);
return (5);
}

messages[1] = HELP_EXIT_MSG;
messages[2] = HELP_ENV_MSG;
messages[3] = HELP_SETENV_MSG;
messages[4] = HELP_UNSETENV_MSG;
messages[5] = HELP_CD_MSG;

for (ak = 0; messages[ak]; ak++)
{
/* Print the length of the string */
length = str_length(data->tokens[1]);
if (str_compare(data->tokens[1], messages[ak], length))
{
_print(messages[ak] + length + 1);
return (1);
}
}

/* If there is no match, print an error and return 0 */
errno = EINVAL;
perror(data->command_name);
return (0);
}

/**
* builtin_alias - Add, remove, or show aliases
* @data: Pointer to the program's data structure
*
* This function handles the alias built-in command.
* If no arguments are provided,
* it prints all the defined aliases. If arguments are
* provided, it either sets or
* prints each alias depending on the format of the arguments.
* If the argument contains
* an "=", it sets the alias. Otherwise, it prints
* the corresponding alias value.
*
* Return: Zero if successful, or a non-zero
* number if an error occurs.
*/

int builtin_alias(data_of_program *data)
{
int ak = 0;

/* If there are no arguments, print all aliases */
if (data->tokens[1] == NULL)
return (print_alias(data, NULL));

while (data->tokens[++ak])
{
/* If there are arguments, set or print each alias */
if (count_characters(data->tokens[ak], "="))
set_alias(data->tokens[ak], data);
else
print_alias(data, data->tokens[ak]);
}

return (0);
}
