/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 13:20:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/16 09:28:38 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"
#include "parser/argument_parser.h"
#include "solver/solver.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef PS_ERROR_MESSAGE
#define PS_ERROR_MESSAGE "Error\n"
#endif

int main(int argc, char **argv)
{
	t_instruction *solve_instr;
	size_t instr_count;
	int *lst;

	if (argc <= 1)
		return (EXIT_SUCCESS);

	lst = read_arguments(argc, argv);

	if (lst == NULL)
	{
		printf("%s\n", PS_ERROR_MESSAGE);
		return (EXIT_FAILURE);
	}

	solve_instr = solve(lst, argc - 1, &instr_count);
	print_instructions(solve_instr, instr_count);

	destroy_instruction(solve_instr, TRUE);
	free(lst);
	return (EXIT_SUCCESS);
}
