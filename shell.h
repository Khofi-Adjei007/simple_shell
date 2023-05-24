#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf */
#include <unistd.h> /* for fork, execve */
#include <stdlib.h>
#include <string.h> /* for strtok */
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files */

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct program_info - structure containing the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read by _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor for the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environment variables
 * @alias_list: array of pointers with aliases
 */
typedef struct program_info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtin_func - structure for the built-in functions
 * @builtin: the name of the built-in
 * @function: the associated function to be called for each built-in
 */
typedef struct builtin_func
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Initialize the program's data structure */
void initialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Create an infinite loop that displays the prompt */
void run_shell(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line from the standard input */
int get_line(data_of_program *data);

/* Split each line into logical operators if they exist */
int check_logical_operators(char *array_commands[], int ak, char array_operators[]);


/*======== expansions.c ========*/

/* Expand variables in the input */
void expand_variables(data_of_program *data);

/* Expand aliases in the input */
void expand_alias(data_of_program *data);

/* Append a string to the end of the buffer */
int buffer_append(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Tokenize the input string using a specified delimiter */
void tokenize(data_of_program *data);

/* Create a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its full path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* Check if the command matches a built-in and execute it */
int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

/* Create an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for the program in the directories of the PATH */
int find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Free the memory allocated for an array of pointers */
void free_pointer_array(char **directories);

/* Free the fields needed in each loop */
void free_recurring_data(data_of_program *data);

/* Free all fields of the program's data structure */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Terminate the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* Set the working directory */
int set_working_directory(data_of_program *data, char *new_dir);

/* Display help information */
int builtin_help(data_of_program *data);

/* Set, unset, and display aliases */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Display the environment variables */
int builtin_env(data_of_program *data);

/* Create or modify an environment variable */
int builtin_set_env(data_of_program *data);

/* Delete an environment variable */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Get the value of an environment variable */
char *get_env_key(char *name, data_of_program *data);

/* Set the value of an environment variable */
int set_env_key(char *key, char *value, data_of_program *data);

/* Remove an environment variable */
int remove_env_key(char *key, data_of_program *data);

/* Print the current environment */
void print_environment(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Print a string to the standard output */
int print_string(char *string);

/* Print a string to the standard error */
int print_error_string(char *string);

/* Print an error message based on the error code */
int print_error_message(int error_code, data_of_program *data);


/************** HELPERS FOR STRING MANIPULATION **************/


/*======== helpers_string.c ========*/

/* Count the number of characters in a string */
int string_length(char *string);

/* Duplicate a string */
char *duplicate_string(char *string);

/* Compare two strings */
int compare_strings(char *string1, char *string2, int length);

/* Concatenate two strings */
char *concatenate_strings(char *string1, char *string2);

/* Reverse a string */
void reverse_string(char *string);


/*======== helpers_numbers.c ========*/

/* Convert a long integer to a string */
void long_to_string(long number, char *string, int base);

/* Convert a string to an integer */
int string_to_integer(char *s);

/* Count the occurrences of a character in a string */
int count_character_occurrences(char *string, char *character);


/*======== alias_management.c ========*/

/* Print the list of aliases */
int print_aliases(data_of_program *data, char *alias);

/* Get the value of an alias */
char *get_alias_value(data_of_program *data, char *alias);

/* Set the value of an alias */
int set_alias_value(char *alias_string, data_of_program *data);


#endif /* SHELL_H */

