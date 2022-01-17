/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_solver_internal.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:50 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "quick_solver_internal.h"
#include "evaluator.h"
#include "generator.h"
#include "quick_solver_utils.h"
#include "../../utils/array_utils.h"
#include <stdlib.h>
#include <ft_math.h>

static const t_instruction g_swapped_instructions[] = {
		ips_empty,
		ips_pb,
		ips_pa,
		ips_rb,
		ips_ra,
		ips_rr,
		ips_sb,
		ips_sa,
		ips_ss,
		ips_rrb,
		ips_rra,
		ips_rrr,
		ips_stop,
		ips_err
};

static size_t
	quick_get_blocksize(size_t len)
{
	if (len <= 10)
		return (5);
	if (len <= 50)
		return (25);
	if (len <= 100)
		return (50);
	if (len <= 200)
		return (75);
	if (len <= 500)
		return (100);
	else
		return (250);
}

static t_instruction
	*_quick_rough_sort(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction	 *instructions;
	t_instruction	 *block_instrs;
	size_t			 block_instrs_count;
	size_t			 block_index;
	size_t			 block_size;
	size_t			 block_max;

	*instr_count = 0;
	block_index = 0;
	block_size = quick_get_blocksize(len);
	instructions = NULL;
	while (block_index < len)
	{
		block_max = ft_stmin((block_index + block_size) - 1, len - 1);
		block_instrs = _quick_rough_sort_block(object, sorted_arr[block_index], sorted_arr[block_max], &block_instrs_count);

		join_instructions(&instructions, *instr_count, block_instrs, block_instrs_count);
		*instr_count += block_instrs_count;
		free(block_instrs);
		block_index += block_size;
	}
	return (instructions);
}

static t_instruction
	*_quick_align(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction	*align_instrs;
	t_distance		align_eval;
	size_t			lowest_pos;

	lowest_pos = quick_get_full_sorted_pos(sorted_arr[0], object->m_stack_a);

	align_eval = evaluate(lowest_pos, len, 0, 0);
	align_instrs = generate_instructions(align_eval.m_left_dist, 0, 0, instr_count);
	execute_instructions(object->m_stack_a, object->m_stack_b, align_instrs, *instr_count);
	return (align_instrs);
}

static t_instruction
	*_quick_sort(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction	*rough_instrs;
	t_instruction	*sort_instrs;
	size_t			rough_count;
	size_t			sort_count;

	rough_instrs = _quick_rough_sort(object, sorted_arr, len, &rough_count);

	sort_instrs = _quick_full_sort_block(object, sorted_arr[0], sorted_arr[len - 1], &sort_count);
	translate_instructions(sort_instrs, sort_count, g_swapped_instructions);

	join_instructions(&rough_instrs, rough_count, sort_instrs, sort_count);
	*instr_count = rough_count + sort_count;

	free(sort_instrs);
	return (rough_instrs);
}

t_instruction
	*_quick_solve(t_ps_object *object, const int *arr, size_t len, size_t *instr_count)
{
	t_instruction	 *sort_instrs;
	t_instruction	 *align_instrs;
	size_t			 sort_count;
	size_t			 align_count;
	int				 *sorted_arr;

	sorted_arr = iarray_cpy_quick_sort(arr, len);

	sort_instrs = _quick_sort(object, sorted_arr, len, &sort_count);
	align_instrs = _quick_align(object, sorted_arr, len, &align_count);

	join_instructions(&sort_instrs, sort_count, align_instrs, align_count);
	*instr_count = sort_count + align_count;

	free(align_instrs);
	free(sorted_arr);
	return (sort_instrs);
}
