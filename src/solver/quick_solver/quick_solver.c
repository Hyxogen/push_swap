#include "../solver.h"

#include "../../ps_object.h"
#include "../../utils/array_utils.h"
#include "../../utils/malloc_utils.h"
#include "bruteforcer.h"
#include "sorter.h"
#include "evaluator.h"
#include "generator.h"
#include <stdlib.h>
#include <ft_string.h>
#include <ft_math.h>
#include <stdio.h>
#include <limits.h>


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


size_t quick_get_rough_sorted_pos(int val, t_ideque *deque)
{
	(void)val;
	(void)deque;
	return (0);
}

size_t _quick_get_full_sorted_pos(int val, const t_inode *current, const t_inode *previous)
{
	size_t node_pos;
	size_t lowest_pos;
	int lowest_val;

	node_pos = 0;
	lowest_pos = 0;
	lowest_val = INT_MAX;
	while (current)
	{
		if (previous->m_content < val && val < current->m_content)
			return (node_pos);
		if (current->m_content < lowest_val)
		{
			lowest_val = current->m_content;
			lowest_pos = node_pos;
		}
		node_pos += 1;
		previous = current;
		current = current->m_head;
	}
	return (lowest_pos);
}

size_t quick_get_full_sorted_pos(int val, t_ideque *deque)
{
	if (ideque_get_size(deque) <= 1)
		return (0);
	return (_quick_get_full_sorted_pos(val, ideque_front(deque), ideque_back(deque)));
}

static size_t quick_get_blocksize(size_t len)
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

static t_instruction *_quick_rough_sort_block(t_ps_object *object, int min, int max, size_t *instr_count)
{
	t_sort_info info;

	info.m_from_deque = object->m_stack_a;
	info.m_to_deque = object->m_stack_b;
	info.m_min = min;
	info.m_max = max;
	info.m_pos_func = quick_get_rough_sorted_pos;
	info.m_put_instr = ips_pb;
	return (sorter_sort(&info, instr_count));
}

static t_instruction *_quick_full_sort_block(t_ps_object *object, int min, int max, size_t *instr_count)
{
	t_sort_info info;

	info.m_from_deque = object->m_stack_b;
	info.m_to_deque = object->m_stack_a;
	info.m_min = min;
	info.m_max = max;
	info.m_pos_func = quick_get_full_sorted_pos;
	info.m_put_instr = ips_pb;
	return (sorter_sort(&info, instr_count));
}

static t_instruction *_quick_rough_sort(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction *instructions;
	t_instruction *block_instrs;
	size_t block_instrs_count;
	size_t block_index;
	size_t block_size;
	size_t block_max;

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

static t_instruction *_quick_align(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction *align_instrs;
	t_evaluation align_eval;
	size_t lowest_pos;

	lowest_pos = quick_get_full_sorted_pos(sorted_arr[0], object->m_stack_a);

	align_eval = evaluate(lowest_pos, len, 0, 0);
	align_instrs = generate_instructions(align_eval.m_MoveVec.m_X, 0, 0, instr_count);
	execute_instructions(object->m_stack_a, object->m_stack_b, align_instrs, *instr_count);
	return (align_instrs);
}

static t_instruction *_quick_sort(t_ps_object *object, const int *sorted_arr, size_t len, size_t *instr_count)
{
	t_instruction *rough_instrs;
	size_t rough_count;
	t_instruction *sort_instrs;
	size_t sort_count;


	rough_instrs = _quick_rough_sort(object, sorted_arr, len, &rough_count);

	sort_instrs = _quick_full_sort_block(object, sorted_arr[0], sorted_arr[len - 1], &sort_count);

	translate_instructions(sort_instrs, sort_count, g_swapped_instructions);

	join_instructions(&rough_instrs, rough_count, sort_instrs, sort_count);
	*instr_count = rough_count + sort_count;

	free(sort_instrs);
	return (rough_instrs);
}

static t_instruction *_quick_solve(t_ps_object *object, const int *arr, size_t len, size_t *instr_count)
{
	t_instruction *sort_instrs;
	size_t sort_count;
	t_instruction *align_instrs;
	size_t align_count;
	int *sorted_arr;

	sorted_arr = iarray_cpy_quick_sort(arr, len);

	sort_instrs = _quick_sort(object, sorted_arr, len, &sort_count);
	align_instrs = _quick_align(object, sorted_arr, len, &align_count);

	join_instructions(&sort_instrs, sort_count, align_instrs, align_count);
	*instr_count = sort_count + align_count;

	free(align_instrs);
	free(sorted_arr);
	return (sort_instrs);
}

t_instruction *solve(int *arr, size_t len, size_t *instrs)
{
	t_ps_object *object;
	t_instruction *solve_instructions;


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

	/*ps_object_debug_print(object);*/
	ps_object_destroy(object, TRUE);
	return (solve_instructions);
}
