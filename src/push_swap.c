/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 13:20:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:42:37 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object/ps_object.h"

#include "locale.h"
#include "parser/argument_parser.h"
#include "solver/solver.h"
#include "utils/array_utils.h"
#include <stdlib.h>
#include <ft_stdio.h>

int
	main(int argc, char **argv)
{
	t_instruction	*solve_instr;
	size_t			instr_count;
	int				*lst;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	lst = read_arguments(argc, argv);
	if (lst == NULL || iarray_has_duplicates(lst, argc - 1))
	{
		free(lst);
		ft_putendl_fd(2, PS_ERROR_MESSAGE);
		return (EXIT_FAILURE);
	}
	solve_instr = solve(lst, argc - 1, &instr_count);
	print_instructions(solve_instr, instr_count);
	free(solve_instr);
	free(lst);
	return (EXIT_SUCCESS);
}
