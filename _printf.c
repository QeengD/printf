#include "main.h"

/**
 * _printf - formatted output conversion and print data.
 * @format: input string.
 *
 * Return: number of chars printed.
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, len = 0, ibuf = 0;
	va_list arguments;
	char *buffer;

	if (!format)
		return (-1);

	va_start(arguments, format);
	buffer = malloc(sizeof(char) * 1024);

	if (!buffer)
		return (-1);

	while (format[i])
	{
		if (format[i] == '%')
			len += handle_conversion(format, &i, &ibuf, buffer, arguments);
		else
			len += handle_char(format[i], &ibuf, buffer);

		i++;
		if (ibuf >= 1024)
			len += print_buffer(buffer, &ibuf);
	}

	len += print_buffer(buffer, &ibuf);

	va_end(arguments);
	free(buffer);

	return (len);
}
