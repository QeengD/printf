#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * nagative_write_char - Prints a string
 * @c: char types.
 * @temp: temp array to handle print
 * @switch:  Calculates active switch.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char temp[],
	int switch, int width, int precision, int size)
{ /* char is stored at left and paddind at temp's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (switch & F_ZERO)
		padd = '0';

	temp[i++] = c;
	temp[i] = '\0';

	if (width > 1)
	{
		temp[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			temp[BUFF_SIZE - i - 2] = padd;

		if (switch & F_MINUS)
			return (write(1, &temp[0], 1) +
					write(1, &temp[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &temp[BUFF_SIZE - i - 1], width - 1) +
					write(1, &temp[0], 1));
	}

	return (write(1, &temp[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char temp[],
	int switch, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((switch & F_ZERO) && !(switch & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (switch & F_PLUS)
		extra_ch = '+';
	else if (switch & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, temp, switch, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the temp
 * @temp: temp
 * @switch: switch
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char temp[],
	int switch, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && temp[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && temp[ind] == '0')
		temp[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		temp[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			temp[i] = padd;
		temp[i] = '\0';
		if (switch & F_MINUS && padd == ' ')/* Asign extra char to left of temp */
		{
			if (extra_c)
				temp[--ind] = extra_c;
			return (write(1, &temp[ind], length) + write(1, &temp[1], i - 1));
		}
		else if (!(switch & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				temp[--ind] = extra_c;
			return (write(1, &temp[1], i - 1) + write(1, &temp[ind], length));
		}
		else if (!(switch & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				temp[--padd_start] = extra_c;
			return (write(1, &temp[padd_start], i - padd_start) +
				write(1, &temp[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		temp[--ind] = extra_c;
	return (write(1, &temp[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the temp
 * @temp: Array of chars
 * @switch: switch specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char temp[],
	int switch, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && temp[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		temp[--ind] = '0';
		length++;
	}

	if ((switch & F_ZERO) && !(switch & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			temp[i] = padd;

		temp[i] = '\0';

		if (switch & F_MINUS) /* Asign extra char to left of temp [temp>padd]*/
		{
			return (write(1, &temp[ind], length) + write(1, &temp[0], i));
		}
		else /* Asign extra char to left of padding [padd>temp]*/
		{
			return (write(1, &temp[0], i) + write(1, &temp[ind], length));
		}
	}

	return (write(1, &temp[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @temp: Arrays of chars
 * @ind: Index at which the number starts in the temp
 * @length: Length of number
 * @width: Width specifier
 * @switch: switch specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char temp[], int ind, int length,
	int width, int switch, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			temp[i] = padd;
		temp[i] = '\0';
		if (switch & F_MINUS && padd == ' ')/* Asign extra char to left of temp */
		{
			temp[--ind] = 'x';
			temp[--ind] = '0';
			if (extra_c)
				temp[--ind] = extra_c;
			return (write(1, &temp[ind], length) + write(1, &temp[3], i - 3));
		}
		else if (!(switch & F_MINUS) && padd == ' ')/* extra char to left of temp */
		{
			temp[--ind] = 'x';
			temp[--ind] = '0';
			if (extra_c)
				temp[--ind] = extra_c;
			return (write(1, &temp[3], i - 3) + write(1, &temp[ind], length));
		}
		else if (!(switch & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				temp[--padd_start] = extra_c;
			temp[1] = '0';
			temp[2] = 'x';
			return (write(1, &temp[padd_start], i - padd_start) +
				write(1, &temp[ind], length - (1 - padd_start) - 2));
		}
	}
	temp[--ind] = 'x';
	temp[--ind] = '0';
	if (extra_c)
		temp[--ind] = extra_c;
	return (write(1, &temp[ind], BUFF_SIZE - ind - 1));
}
