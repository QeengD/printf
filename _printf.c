#include "main.h"

void prnt_bufr(char bufr[], int *buf_in);

int _printf(const char *format, ...)
{
	int i, printed = 0, prntd_chr = 0;
	int flg, width, precsn, size, buf_in = 0;
	va_list list;
	char bufr[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			bufr[buf_in++] = format[i];
			if (buf_in == BUFF_SIZE)
				prnt_bufr(bufr, &buf_in);
			/* write(1, &format[i], 1);*/
			prntd_chr++;
		}
		else
		{
			prnt_bufr(bufr, &buf_in);
			flg = get_flags(format, &i);
			width = get_width(format, &i, list);
			precsn = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, bufr,
				flg, width, precsn, size);
			if (printed == -1)
				return (-1);
			prntd_chr += printed;
		}
	}

	prnt_bufr(bufr, &buf_in);

	va_end(list);

	return (prntd_chr);
}


void prnt_bufr(char bufr[], int *buf_in)
{
	if (*buf_in > 0)
		write(1, &bufr[0], *buf_in);

	*buf_in = 0;
}
