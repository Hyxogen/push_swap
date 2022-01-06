#include "../solver.h"

#include "../../ps_object.h"
#include "../../utils/array_utils.h"
#include "../../utils/malloc_utils.h"
#include "sorter.h"
#include <stdlib.h>
#include <ft_string.h>
#include <stdio.h>

/*
static const t_instruction g_InverseInstructions[] = {
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

static t_instruction* quick_rough_sort(t_ps_object* object, int* arr, size_t len, size_t block_size, size_t* count) {
	t_instruction* instrs;
	int* arr_cpy;

	arr_cpy = ft_malloc(len * sizeof(int));
	ft_memcpy(arr_cpy, arr, len * sizeof(int));
	quick_sort(arr_cpy, len);

	instrs = rough_sort_optimized(object->m_stack_a, object->m_stack_b, ips_pb, arr_cpy, block_size, count);
	free(arr_cpy);
	return (instrs);
}

static t_instruction* quick_full_sort(t_ps_object* object, size_t* count) {
	t_instruction* instrs;

	instrs = sort(object->m_stack_b, object->m_stack_a, ips_pb, count);
	translate_instructions(instrs, *count, g_InverseInstructions);
	return (instrs);
}*/

size_t always_top(int val, t_ideque* deque) {
	(void)val;
	(void)deque;
	return (0);
}

t_instruction* solve(int* arr, size_t len, size_t* instrs) {
	t_ps_object* object;
	t_instruction* solve_instructions;
	t_sort_info info;

	object = ps_object_create_empty();
	ps_object_fill(object, arr, len);
	ps_object_debug_print(object);

	info.m_from_deque = object->m_stack_a;
	info.m_to_deque = object->m_stack_b;
	info.m_put_instr = ips_pb;
	info.m_min = 0;
	info.m_max = 5;
	info.m_pos_func = always_top;

	solve_instructions = sorter_sort(&info, instrs);

	ps_object_debug_print(object);
	ps_object_destroy(object, TRUE);
	return (solve_instructions);
}
