#include "main.h"

/**
 * get_switch - Calculates active switch
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: switch:
 */
int get_switch(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i;
	int switch = 0;
	const char switch_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int switch_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; switch_CH[j] != '\0'; j++)
			if (format[curr_i] == switch_CH[j])
			{
				switch |= switch_ARR[j];
				break;
			}

		if (switch_CH[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (switch);
}
