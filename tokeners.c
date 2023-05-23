#include "shell.h"

/**
* split_string - Splits a string into words based on delimiters.
* @str: The input string to be split.
* @delimiters: The delimiters used for splitting the string.
* Return: A pointer to an array of strings, or NULL on failure.
*/

char **split_string(char *str, char *delimiters)
{
int ka, ak, k, m, num_words = 0;
char **result;

if (str == NULL || str[0] == '\0')
return (NULL);

/* Set default delimiter to space if not provided */
if (!delimiters)
delimiters = " ";

/* Count the number of words */
for (ka = 0; str[ka] != '\0'; ka++)
{
if (!is_delim(str[ka], delimiters) && (is_delim(str[ka + 1], delimiters) || !str[ka + 1]))
num_words++;
}

if (num_words == 0)
return (NULL);

result = malloc((num_words + 1) * sizeof(char *));
if (!result)
return (NULL);

/* Split the string into words */
for (ka = 0, ak = 0; ak < num_words; ak++)
{
/* Skip leading delimiters */
while (is_delim(str[ka], delimiters))
ka++;

k = 0;
/* Copy characters until the next delimiter or end of string */
while (!is_delim(str[ka + k], delimiters) && str[ka + k])
k++;

result[ak] = malloc((k + 1) * sizeof(char));
if (!result[ak])
{
/* Free memory and return NULL on failure */
for (k = 0; k < ak; k++)
free(result[k]);
free(result);
return (NULL);
}

/* Copy the word */
for (m = 0; m < k; m++)
result[ak][m] = str[ka++];

result[ak][m] = '\0';
}

result[ak] = NULL;
return (result);
}

/**
* split_string2 - Splits a string into words based on a single delimiter.
* @str: The input string to be split.
* @delimiter: The delimiter used for splitting the string.
* Return: A pointer to an array of strings, or NULL on failure.
*/

char **split_string2(char *str, char delimiter)
{
int ka, ak, k, m, num_words = 0;
char **result;

if (str == NULL || str[0] == '\0')
return (NULL);

/* Count the number of words */
for (ka = 0; str[ka] != '\0'; ka++)
{
if ((str[ka] != delimiter && str[ka + 1] == delimiter) ||
(str[ka] != delimiter && !str[ka + 1]) || str[ka + 1] == delimiter)
num_words++;
}

if (num_words == 0)
return (NULL);

result = malloc((num_words + 1) * sizeof(char *));
if (!result)
return (NULL);

/* Split the string into words */
for (ka = 0, ak = 0; ak < num_words; ak++)
{
/* Skip leading delimiters */
while (str[ka] == delimiter && str[ka] != delimiter)
ka++;

k = 0;
/* Copy characters until the next delimiter or end of string */
while (str[ka + k] != delimiter && str[ka + k] && str[ka + k] != delimiter)
k++;

result[ak] = malloc((k + 1) * sizeof(char));
if (!result[ak])
{
/* Free memory and return NULL on failure */
for (k = 0; k < ak; k++)
free(result[k]);
free(result);
return (NULL);
}

/* Copy the word */
for (m = 0; m < k; m++)
result[ak][m] = str[ka++];

result[ak][m] = '\0';
}

result[ak] = NULL;
return (result);
}
