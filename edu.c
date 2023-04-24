#include "main.h"
/**
 * edu - finds the first index of a character in a string
 * @str: the string to search
 * @c: the character to find
 *
 * Return: the index of the first occurrence of c in str, or -1 if not found
 */
int edu(const char *str, char c)
{
int i = 0;
while (str[i])
{
if (str[i] == c)
return (i);
i++;
}
return (-1);
}
/**
 * is_palindrome - checks if a string is a palindrome
 * @str: the string to check
 *
 * Return: 1 if the string is a palindrome, 0 otherwise
 */
int is_palindrome(const char *str)
{
int len = strlen(str);
for (int i = 0; i < len / 2; i++)
{
if (str[i] != str[len - i - 1])
return (0);
}
return (1);
}
