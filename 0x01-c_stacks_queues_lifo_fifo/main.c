#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "monty.h"

/**
 * main - main crossroad in processing monty opcodes.
 * @ac: Amount of args passed (int).
 * @av: Array of strings containing args passed.
 *
 * Return: 0.
 */
int main(int ac, char **av)
{
	FILE *fp;
	char buf[101];
	unsigned int line_number;
	char *tokens[3] = { NULL, NULL, NULL };

	/* Initialization of the stack */
	stack_t *stack = NULL;

	if (ac != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* open file */
	fp = fopen(av[1], "r");
	if (!fp)
	{
		printf("Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	/* retrieve every line from file until EOF */
	for (line_number = 1; fgets(buf, sizeof(buf), fp); line_number++)
	{
		/* parse opcode command */
		parse(buf, tokens);

		/* ignore comments */
		if (!tokens[0] || tokens[0][0] == '#')
			continue;

		/* process opcodes */
		manage_stack(&stack, tokens, line_number);
	}
	fclose(fp);
	if (stack)
		free_stack(&stack);

	return (0);
}
