#define _SHELL_H_
#ifndef _SHELL_H_


#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/* toem_errors.c */
int _putfd(char c, int fd);
int _eputchar(char);
void _eputs(char *);
int _putsfd(char *str, int fd);


/* toem_string1.c */
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);
char *_strdup(const char *);


/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);


/* toem_atoi.c */
int _atoi(char *);
int is_delim(char, char *);
int interactive(info_t *);
int _isalpha(int);


/* toem_errors1.c */
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
int print_d(int, int);
int _erratoi(char *);
void remove_comments(char *);



/*toem_getline.c */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);


/* toem_builtin.c */
int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);



/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);


/* toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);



/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myunsetenv(info_t *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);


/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_memory.c */
int bfree(void **);


/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


/* loophsh.c */
int loophsh(char **);


/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);


/* toem_getenv.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);



/* toem_history.c */
char *get_history_file(info_t *info);
int renumber_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int write_history(info_t *info);



/* toem_lists.c */
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);

/* toem_lists1.c */
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);




/* for read/write buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1



/* for command chaining */
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_OR		1
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0


extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@histcount: the history line number count
 *@path: a string path for the current command
 *@argc: the argument count
 *@status: the return status of the last exec'd command
 *@history: the history node
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@linecount_flag: if on count this line of input
 *@readfd: the fd from which to read line input
 
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
      char *fname;
	list_t *env;
      int env_changed;
      list_t *alias;
	char **environ;
      list_t *history;
      int argc;
	unsigned int line_count;
      int err_num;
	int linecount_flag;
      char *path;
      int status;
      char **cmd_buf;
      int cmd_buf_type;
      int readfd;
	int histcount;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int find_builtin(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

      


#endif
