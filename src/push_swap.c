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

#include "stack.h"
#include "ps_object.h"
#include "parser/argument_parser.h"
#include "solver/solver.h"
#include <stdlib.h>

int main(int argc, char** argv) {
	int* lst;
	t_instruction* solve_instr;
	size_t instr_count;

	if (argc <= 1)
		return (EXIT_SUCCESS);

	lst = read_arguments(argc, argv);
	
	solve_instr = solve(lst, argc - 1, &instr_count);
	destroy_instruction(solve_instr, TRUE);

	return (EXIT_SUCCESS);
}
