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

t_instruction* solve(int* arr, size_t len, size_t* instrs) {
	t_ps_object object;
	t_instruction* solve_instructions, * temp_instr;
	size_t rough_count, sort_count;
	int* arr_cpy;

	arr_cpy = ft_malloc(len * sizeof(int));
	ft_memcpy(arr_cpy, arr, len * sizeof(int));
	quick_sort(arr_cpy, len);

	make_ps_object(arr, len, &object);

	solve_instructions = rough_sort_optimized(object.m_StackA, object.m_StackB, ips_pb, arr_cpy, 100, &rough_count);


	temp_instr = sort(object.m_StackB, object.m_StackA, ips_pb, &sort_count);
	translate_instructions(temp_instr, sort_count, g_InverseInstructions);
	join_instructions(&solve_instructions, rough_count, temp_instr, sort_count);
	free(temp_instr);

	*instrs = rough_count + sort_count;

	destroy_ps_object(&object, FALSE);
	free(arr_cpy);
	return (solve_instructions);
}
