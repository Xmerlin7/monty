#include "monty.h"

/**
 * open_file - opens a file
 * @file_name: the file namepath
 * Return: void
 */
void open_file(char *file_name)
{
	FILE *_fd = fopen(file_name, "r");

	if (file_name == NULL || _fd == NULL)
		errors(2, file_name);

	read_file(_fd);
	fclose(_fd);
}

/**
 * read_file - reads a file
 * @_fd: pointer to file descriptor
 * Return: void
 */
void read_file(FILE *_fd)
{
	int line_number, format = 0;
	char *buff = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buff, &len, _fd) != -1; line_number++)
	{
		format = parse_line(buff, line_number, format);
	}
	free(buff);
}

/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @line_number: line number
 * @format: storage format.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int parse_line(char *buffer, int line_number, int format)
{
	char *_opcode, *val;
	const char *delim = "\n ";

	if (buffer == NULL)
		errors(4);

	_opcode = strtok(buffer, delim);
	if (_opcode == NULL)
		return (format);
	val = strtok(NULL, delim);

	if (strcmp(_opcode, "stack") == 0)
		return (0);
	if (strcmp(_opcode, "queue") == 0)
		return (1);

	find_function(_opcode, val, line_number, format);
	return (format);
}

/**
 * call_funtion - calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_funtion(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *_node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			errors(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				errors(5, ln);
		}
		_node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&_node, ln);
		if (format == 1)
			add_to_queue(&_node, ln);
	}
	else
		func(&head, ln);
}

/**
 * find_function - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_function(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_funtion(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		errors(3, ln, opcode);
}
