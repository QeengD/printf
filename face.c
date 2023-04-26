#include "main.h"

/********* PRINT UNSIGNED NUMBER *********/
/**
 * print_unsigned - Prints an unsigned number
 * @types: List a of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		temp[i--] = '0';

	temp[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		temp[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, temp, switch, width, precision, size));
}

/***** PRINT UNSIGNED NUMBER IN OCTAL  ******/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char temp[],
	int switch, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		temp[i--] = '0';

	temp[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		temp[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (switch & F_HASH && init_num != 0)
		temp[i--] = '0';

	i++;

	return (write_unsgnd(0, i, temp, switch, width, precision, size));
}

/***** PRINT UNSIGNED NUMBER IN HEXADECIMAL *****/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", temp,
		switch, 'x', width, precision, size));
}

/***** PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ******/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char temp[],
	int switch, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", temp,
		switch, 'X', width, precision, size));
}

/***** PRINT HEXX NUM IN LOWER OR UPPER *****/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @temp: temp array to handle print
 * @switch:  Calculates active switch
 * @flag_ch: Calculates active switch
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char temp[],
	int switch, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		temp[i--] = '0';

	temp[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		temp[i--] = map_to[num % 16];
		num /= 16;
	}

	if (switch & F_HASH && init_num != 0)
	{
		temp[i--] = flag_ch;
		temp[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, temp, switch, width, precision, size));
}

