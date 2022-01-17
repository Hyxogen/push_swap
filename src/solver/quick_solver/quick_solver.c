/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_solver.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:41 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:41 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../solver.h"

#include "quick_solver_internal.h"
#include "bruteforcer.h"
#include "../../ps_object/ps_object.h"
#include <stdlib.h>

t_instruction
	*solve(int *arr, size_t len, size_t *instrs)
{
	t_instruction	*solve_instructions;
	t_ps_object		*object;

	object = ps_object_create_empty();
	ps_object_fill(object, arr, len);

	solve_instructions = brute_force(object, 7, instrs);
	if (solve_instructions)
	{
		ps_object_destroy(object, TRUE);
		return (solve_instructions);
	}
	free(solve_instructions);

	solve_instructions = _quick_solve(object, arr, len, instrs);

	ps_object_destroy(object, TRUE);
	return (solve_instructions);
}
