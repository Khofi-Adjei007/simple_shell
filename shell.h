#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "macros.h"


/**
 * struct builtins -  This is the builtins data's struct
 * @builtin: List the names of the builtin
 * @function: This is the function to be called for each associated builtin
 */



typedef struct builtins
{
char *builtin;
int (*function)(data_of_program *data);
} builtins;



/**
 * contains executables prototypes
 * _program_name: This is the executable's name
 * @env: This is the environ's duplicate
 * @input_line: This is the pointer for _getline input
 * struct info- This is the program's data struct
 * @alias_list: This is the aliases pointers' array.
 * @command_name: This is the pointer to the user's first command
 * @tokens: tokenized input's arrays pointer
 * @exec_counter: number of comands to be executed
 * @file_descriptor: descriptor of commands input
 */

typedef struct info
{
char **tokens;
char *command_name;
char **alias_list;
char *program_name;
int exec_counter;
int file_descriptor;
char *input_line;
char **env;
} data_of_program;



void handle_ctrl_c(int opr UNUSED);
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);

int buffer_add(char *buffer, char *str_to_add);
void expand_variables(data_of_program *data);
void expand_alias(data_of_program *data);


void tokenize(data_of_program *data);
char *_strtok(char *line, char *delim);


int check_logic_ops(char *array_commands[], int i, char array_operators[]);
int _getline(data_of_program *data);


int execute(data_of_program *data);


int find_program(data_of_program *data);
char **tokenize_path(data_of_program *data);


void free_array_of_pointers(char **directories);
void free_all_data(data_of_program *data);
void free_recurrent_data(data_of_program *data);


int str_length(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_duplicate(char *string);
void str_reverse(char *string);
char *str_concat(char *string1, char *string2);


int set_work_directory(data_of_program *data, char *new_dir);
int builtin_exit(data_of_program *data);
int builtin_help(data_of_program *data);
int builtin_cd(data_of_program *data);
int builtin_alias(data_of_program *data);

int builtin_env(data_of_program *data);
int builtin_unset_env(data_of_program *data);
int builtin_set_env(data_of_program *data);


void print_environ(data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
char *env_get_key(char *name, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);


int print_alias(data_of_program *data, char *alias);
int set_alias(char *alias_string, data_of_program *data);
char *get_alias(data_of_program *data, char *alias);

int _printe(char *string);
int _print(char *string);
int _print_error(int errorcode, data_of_program *data);


int _atoi(char *s);
void long_to_string(long number, char *string, int base);
int count_characters(char *string, char *character);


#endif
