#include "main.h"

void print_temp(chr temp[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chrs.
 */
int _printf(const chr *format, ...)
{
	int i, printed = 0, printed_chrs = 0;
	int switch, width, precision, size, buff_ind = 0;
	va_list list;
	chr temp[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			temp[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_temp(temp, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chrs++;
		}
		else
		{
			print_temp(temp, &buff_ind);
			switch = get_switch(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, temp,
				switch, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chrs += printed;
		}
	}

	print_temp(temp, &buff_ind);

	va_end(list);

	return (printed_chrs);
}

/**
 * print_temp - Prints the contents of the temp if it exist
 * @temp: Array of chrs
 * @buff_ind: Index at which to add next chr, represents the length.
 */
void print_temp(chr temp[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &temp[0], *buff_ind);

	*buff_ind = 0;
}
