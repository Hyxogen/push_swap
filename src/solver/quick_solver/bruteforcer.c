/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bruteforcer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:30 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bruteforcer.h"

#include <stdlib.h>
#include <ft_string.h>
#include "../../utils/malloc_utils.h"
#include "../../utils/array_utils.h"
#include <stdio.h>

static int	_brute_force(t_ps_object *object, t_instruction *instructions, int depth, int instr_count);

static const t_instruction g_inverse_instructions[] = {
		ips_empty,
		ips_pb,
		ips_pa,
		ips_rra,
		ips_rrb,
		ips_rrr,
		ips_sa,
		ips_sb,
		ips_ss,
		ips_ra,
		ips_rb,
		ips_rr,
		ips_stop,
		ips_err
};

static void
	apply_instruction(t_ps_object *object, t_instruction instr)
{
	execute_instructions(object->m_stack_a, object->m_stack_b, &instr, 1);
}

static void
	undo_instruction(t_ps_object *object, t_instruction instr)
{
	translate_instructions(&instr, 1, g_inverse_instructions);
	execute_instructions(object->m_stack_a, object->m_stack_b, &instr, 1);
}

static int
	_brute_force_loop(t_ps_object *object, t_instruction *instructions, int depth, int instr_count)
{
	t_instruction	*best;
	t_instruction	instruction;
	int				count;

	best = NULL;
	instruction = ips_pb + 1;
	while (instruction < ips_stop)
	{
		*instructions = instruction;
		apply_instruction(object, instruction);
		count = _brute_force(object, instructions + 1, depth, instr_count + 1);
		if (count >= 0)
		{
			free(best);
			depth = count + 1;
			best = iarray_cpy(instructions, depth);
		}
		undo_instruction(object, instruction);
		instruction++;
	}
	if (best == NULL)
		return (-1);
	ft_memcpy(instructions, best, sizeof(t_instruction) * depth);
	free(best);
	return (depth);
}

static int
	_brute_force(t_ps_object *object, t_instruction *instructions, int depth, int instr_count)
{
	if (ps_object_is_sorted(object))
		return (0);
	if (instr_count >= depth)
		return (-1);
	return (_brute_force_loop(object, instructions, depth, instr_count));
}

t_instruction
	*brute_force(t_ps_object *object, int depth, size_t *instr_count)
{
	t_instruction	*instructions;
	int				count;

	instructions = ft_safe_malloc(sizeof(t_instruction) * depth);
	count = _brute_force(object, instructions, depth, 0);
	if (count < 0)
	{
		free(instructions);
		return (NULL);
	}
	*instr_count = (size_t)count;
	return (instructions);
}
