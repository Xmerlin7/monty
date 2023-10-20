#include "monty.h"

/**
 * errors - Prints error messages
 * @error_code: error code
 */
void errors(int error_code, ...)
{
	va_list _arg;
	char *_op;
	int num;

	va_start(_arg, error_code);
	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n",
					va_arg(_arg, char *));
			break;
		case 3:
			num = va_arg(_arg, int);
			_op = va_arg(_arg, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", num, _op);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(_arg, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * more_errors - handles errors
 * @error_code: error codes
 */
void more_errors(int error_code, ...)
{
	va_list _arg;
	char *_op;
	int num;

	va_start(_arg, error_code);
	switch (error_code)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n",
					va_arg(_arg, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n",
					va_arg(_arg, int));
			break;
		case 8:
			num = va_arg(_arg, unsigned int);
			_op = va_arg(_arg, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", num, _op);
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n",
					va_arg(_arg, unsigned int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_error - handles errors
 * @error_code: error codes
 */
void string_error(int error_code, ...)
{
	va_list _arg;
	int num;

	va_start(_arg, error_code);
	num = va_arg(_arg, int);
	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", num);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", num);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
