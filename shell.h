#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

/* for read/write buffers */
#define READ_BUF_SIZE 2023
#define WRITE_BUF_SIZE 2023
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*  convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* getline() is 1 if using systetm*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
* struct liststr - singly linked list
* @num: This prints the number field
* @str: This prints a string
* @next: This points to the adjacent node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
*struct passinfo - encapsulates simulated arguments for function invocation,
* facilitating consistent function pointer struct prototypes
*@arg: A string obtained from getline that contains the arguments
*@argv: An array of strings derived from arg
*@path: A string representing the current command's path
*@argc: The count of arguments
*@line_count: The count of lines
*@err_num: The error code for exit() calls
*@linecount_flag: If enabled, counts the current input line
*@fname: The filename of the program
*@env: A linked list representing a local copy of the environment variables
*@environ: A customized modified copy of the environment
*variables obtained from the linked list
*@history: The node representing the command history
*@alias: The node representing the aliases
*@env_changed: Flag indicating whether the environment variables were modified
*@status: The return status of the last executed command
*@cmd_buf: The address of a pointer to the command buffer;
used for command chaining
*@cmd_buf_type: The type of command buffer (CMD_type) such as ||, &&, or;
*@readfd: The file descriptor used for reading line input
*@histcount: The count of history line numbers
*/

typedef struct passinfo
{
char **environ;
char **argv;
int argc;
char *path;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
unsigned int line_count;
list_t *history;
list_t *alias;
int env_changed;
char *arg;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int histcount;
int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
*struct builtin - Represents a built-in command and its related function
*@type: The flag indicating the type of the built-in command
*@func: The function associated with the built-in command
*/

typedef struct builtin
{
int (*func)(info_t *);
char *type;
} builtin_table;


/* _shloop.c */
int find_builtin(info_t *);
void fork_cmd(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);

/* _parser.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

/* loophsh.c */
int loophsh(char **);

/* _errors.c */
int _eputchar(char);
void _eputs(char *);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);

/* _string.c */
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);

/* _string1.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);

/* _exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/* _tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* _realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);

/* _memory.c */
int bfree(void **);

/* _atoi.c */
int _isalpha(char);
int interactive(info_t *);
int _atoi(char *);
int is_delim(char, char *);

/* _errors1.c */
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
int _erratoi(char *);
void remove_comments(char *);
int print_d(int, int);

/* _builtin.c */
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);

/* _builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);


/*_getline.c */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);


/* _getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/* _environ.c */
int _myunsetenv(info_t *);
int _myenv(info_t *);
int _mysetenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);

/* _getenv.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* _history.c */
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
int renumber_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);



/* _lists.c */
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);


/* _lists1.c */
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);

/* _vars.c */
int replace_alias(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);


#endif

