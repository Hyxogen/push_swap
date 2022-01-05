#include "../solver.h"

#include "../../ps_object.h"
#include "../../utils/array_utils.h"
#include "../../utils/malloc_utils.h"
#include "sorter.h"
#include <stdlib.h>
#include <ft_string.h>
#include <stdio.h>

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

static void make_ps_object(int* arr, size_t len, t_ps_object* object) {
	init_ps_object(object);
	fill_psa(object, arr, len);
}

static t_instruction* quick_rough_sort(t_ps_object* object, int* arr, size_t len, size_t block_size, size_t* count) {
	t_instruction* instrs;
	int* arr_cpy;

	arr_cpy = ft_malloc(len * sizeof(int));
	ft_memcpy(arr_cpy, arr, len * sizeof(int));
	quick_sort(arr_cpy, len);

	instrs = rough_sort_optimized(object->m_StackA, object->m_StackB, ips_pb, arr_cpy, block_size, count);
	free(arr_cpy);
	return (instrs);
}

static t_instruction* quick_full_sort(t_ps_object* object, size_t* count) {
	t_instruction* instrs;

	instrs = sort(object->m_StackB, object->m_StackA, ips_pb, count);
	translate_instructions(instrs, *count, g_InverseInstructions);
	return (instrs);
}

t_instruction* solve(int* arr, size_t len, size_t* instrs) {
	t_ps_object object;
	t_instruction* solve_instructions, * temp_instr;
	size_t rough_count, sort_count;

	make_ps_object(arr, len, &object);

	solve_instructions = quick_rough_sort(&object, arr, len, 100, &rough_count);
	temp_instr = quick_full_sort(&object, &sort_count);
	join_instructions(&solve_instructions, rough_count, temp_instr, sort_count);

	*instrs = rough_count + sort_count;
	free(temp_instr);

	print_ps_object(&object);
	destroy_ps_object(&object, FALSE);
	return (solve_instructions);
}
