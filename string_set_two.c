#include "shell.h"

/**
* string_copy - Copies a string from source to destination
* @dest: The destination string
* @src: The source string
*
* Return: Pointer to the destination string
*/
char *string_copy(char *dest, char *src)
{
int ka = 0;

if (dest == src || src == NULL)
return (dest);

/* Copy each character from source to destination */
while (src[ka])
{
dest[ka] = src[ka];
ka++;
}

dest[ka] = '\0';
return (dest);
}

/**
* string_duplicate - Creates a duplicate of a string
* @str: The string to duplicate
*
* Return: Pointer to the duplicated string
*/

char *string_duplicate(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);

/* Calculate the length of the string */
while (*str++)
length++;

ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);

/* Copy characters in reverse order to create the duplicate string */
for (length++; length--;)
ret[length] = *--str;

return (ret);
}

/**
* print_string - Prints a string to stdout
* @str: The string to be printed
*
* Return: Nothing
*/
void print_string(char *str)
{
int ka = 0;

if (!str)
return;

/* Print each character of the string */
while (str[ka] != '\0')
{
_putchar(str[ka]);
ka++;
}
}

/**
* write_character - Writes a character to stdout
* @c: The character to print
*
* Return: On success, returns 1.
* On error, returns -1, and errno is set appropriately.
*/

int write_character(char c)
{
static int ka;
static char buf[WRITE_BUF_SIZE];

/* Flush the buffer or write the character to buffer */
if (c == BUF_FLUSH || ka >= WRITE_BUF_SIZE)
{
write(1, buf, ka);
ka = 0;
}
if (c != BUF_FLUSH)
buf[ka++] = c;

return (1);
}
