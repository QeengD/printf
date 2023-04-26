#include "main.h"

/****** PRINT POINTER ******/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	temp[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		temp[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((switch & F_ZERO) && !(switch & F_MINUS))
		padd = '0';
	if (switch & F_PLUS)
		extra_c = '+', length++;
	else if (switch & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/ return (write(1, &temp[i], BUFF_SIZE - i - 1)); /
	return (write_pointer(temp, ind, length,
		width, switch, padd, extra_c, padd_start));
}

/********* PRINT NON PRINTABLE *********/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(switch);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			temp[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], temp, i + offset);

		i++;
	}

	temp[i + offset] = '\0';

	return (write(1, temp, i + offset));
}

/********* PRINT REVERSE *********/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(temp);
	UNUSED(switch);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/********* PRINT A STRING IN ROT13 *********/
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(temp);
	UNUSED(switch);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
