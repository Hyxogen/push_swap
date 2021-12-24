#include "sorter.h"

#include "../instr_deque.h"
#include "evaluator.h"
#include "../../utils/math_utils.h"
#include <limits.h>
#include <stdlib.h>

static t_instruction* dump_single(t_stack* from, t_stack* to, int low, int high, size_t* count) {
	t_evaluation best, current;
	t_instruction* best_instr;
	t_stack_element* element;
	size_t position;
	int val;

	element = stack_top(from);
	position = 0;
	while (element) {
		val = *((int*)element->m_Content);
		if (val >= low || val <= high) {
			current = evaluate(position, 0);
			if (evaluation_cmp(&current, &best) < 0) {
				destroy_evaluation(&best, FALSE);
				best = current;
			}
		}
		position++;
		element = stack_get_next(element);
	}
	*count = best.m_Count;

	execute_instructions(from, to, best.m_Instructions, count);
	return (best.m_Instructions);
}

static t_instruction* dump_range(t_stack* from, t_stack* to, int low, int high, size_t* count) {
	t_instr_deque deque;
	t_instruction* instructions;
	size_t instr_count;

	*count = 0;
	deque_init(&deque);
	
	while (TRUE) {
		instructions = dump_single(from, to, low, high, &instr_count);

		if (instr_count == 0)
			break;
		
		*count += instr_count;
		deque_push_back_arr(&deque, instructions, count);
		free(instructions);
	}
	
	instructions = deque_join_all(&deque);
	deque_destroy(&deque, FALSE);
	return (instructions);
}

t_instruction* rough_sort_optimized(t_stack* from, t_stack* to, int* from_sorted, size_t block_size, size_t* instrs) {
	t_instruction* instructions;
	t_instr_deque* instr_deque;
	size_t block_index;
	size_t instr_count;
	size_t size;
	int low, high;

	size = stack_size(from);
	for (block_index = 0; block_index < size; block_index += block_size) {
		low = from_sorted[block_index];
		high = from_sorted[min(block_index + block_size - 1, size)];

		instructions = dump_range(from, to, low, high, &instr_count);

		if (instr_count == 0)
			break;
		deque_push_back_arr(&instr_deque, instructions, instr_count);
		free(instructions);
	}
	instructions = deque_join_all(&instr_deque);
	deque_destroy(&instr_deque);
	return (instructions);
}

t_instruction* sort(t_stack* from, t_stack* to, size_t* instrs) {
	/*TODO Get sort working*/
}
