#include "../solver.h"

#include "../../ps_object.h"
#include "../instr_deque.h"
#include "sorter.h"
#include <stdlib.h>

static void make_ps_object(int* arr, size_t len, t_ps_object* object) {
	fill_psa(object, arr, len);
}

t_instruction* solve(int* arr, size_t len) {
	t_ps_object object;
	t_instr_deque instr_deque;
	t_instruction* temp_instructions;
	int count;

	make_ps_object(arr, len, &object);

	temp_instructions = rough_sort(&object.m_StackA, &object.m_StackB, len / 2, &count);
	deque_push_back_arr(&instr_deque, temp_instructions, count);
	
	free(temp_instructions);
	
	temp_instructions = sort(&object.m_StackA, &object.m_StackB, &count);
	deque_push_back_arr(&instr_deque, temp_instructions, count);
	
	free(temp_instructions);
	
	temp_instructions = deque_join_all(&instr_deque);
	deque_destroy(&instr_deque, FALSE);
	
	return (temp_instructions);
}
