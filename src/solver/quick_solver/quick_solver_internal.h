/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_solver_internal.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:48 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 16:02:01 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUICK_SOLVER_INTERNAL_H
# define QUICK_SOLVER_INTERNAL_H

# include "../instruction.h"
# include "../../ps_object/ps_object.h"

typedef struct s_block_restraints {
	size_t	m_block_size;
	size_t	m_block_max;
}	t_block_restraints;

t_instruction	*_quick_solve(t_ps_object *object,
					const int *arr, size_t len, size_t *instr_count);

#endif
