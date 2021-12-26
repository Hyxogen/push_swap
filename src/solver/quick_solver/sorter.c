#include "sorter.h"

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
	best.m_Count = ULONG_MAX;
	while (element) {
		val = *((int*)element->m_Content);
		if (val >= low || val <= high) {
			current = evaluate(position, 0);
			if (evaluation_cmp(&current, &best) < 0) {
				destroy_evaluation(&best, FALSE);
				best = current;
			} else
				destroy_evaluation(&current, FALSE);
		}
		position++;
		element = stack_get_next(element);
	}
	*count = best.m_Count;

	execute_instructions(from, to, best.m_Instructions, count);
	return (best.m_Instructions);
}

static t_instruction* dump_range(t_stack* from, t_stack* to, int low, int high, size_t* count) {
	t_instruction* instructions, *temp;
	size_t instr_count;

	*count = 0;
	instructions = NULL;

	while (TRUE) {
		temp = dump_single(from, to, low, high, &instr_count);

		if (instr_count == 0)
			break;
		
		join_instructions(instructions, *count, temp, instr_count);
		*count += instr_count;
		free(temp);
	}
	
	return (instructions);
}

t_instruction* rough_sort_optimized(t_stack* from, t_stack* to, int* from_sorted, size_t block_size, size_t* instrs) {
	t_instruction* instructions, temp;
	size_t block_index;
	size_t instr_count;
	size_t size;
	int low, high;

	*instrs = 0;
	instructions = NULL;
	size = stack_size(from);
	for (block_index = 0; block_index < size; block_index += block_size) {
		low = from_sorted[block_index];
		high = from_sorted[min(block_index + block_size - 1, size)];

		temp = dump_range(from, to, low, high, &instr_count);

		if (instr_count == 0)
			break;
		join_instructions(instructions, instrs, temp, instr_count);
		free(temp);
	}
	return (instructions);
}

static size_t get_sorted_pos(t_stack* stack, int i) {
	t_stack_element* previous, *current;
	int previous_val, current_val;

	if (stack_size(stack) <= 1)
		return (0);
	previous = stack_bottom(stack);
	current = stack_top(stack);
	while (current) {
		previous_val = *((int*)previous->m_Content);
		current_val = *((int*)current->m_Content);
		if ((i > previous_val) && (i < current_val))
			return (position);
		previous = current;
		current = stack_get_next(current);
	}
	return (0); /*The only chance of this happening is when you try to get the sorted position in an unsorted stack. This is undefined behavior*/
}

static t_instruction* move_best(t_stack* from, t_stack* to, size_t* instrs) {
	t_evaluation best, current;
	t_stack_element* element;
	size_t from_pos, to_pos;

	element = stack_top(from);
	from_pos = 0;
	best = worst_evaluation();
	while (element) {
		to_pos = get_sorted_pos(to, *((int*)element->m_Content));
		current = evaluate(from_pos, to_pos);

		if (evaluation_cmp(&current, &best) < 0) {
			destroy_evaluation(&best, FALSE);
			best = current;
		} else
			destroy_evaluation(&current, FALSE);
		element = stack_get_next(element);
	}
	execute_instructions(from, to, best.m_Instructions, best.m_Count);
	*instrs = best.m_Count;
	return (best.m_Instructions);
}

t_instruction* sort(t_stack* from, t_stack* to, size_t* instrs) {
	t_instruction* instructions, temp;
	size_t index;
	size_t instr_count;

	size = stack_size(from);
	instructions = NULL;
	for (index = 0; index < size; index++) {
		temp = move_best(from, to, &instr_count);

		if (instr_count == 0)
			break; /*This should never happen*/
		join_instructions(instructions, instrs, temp, instr_count);
		free(temp);
	}
	return (instructions);
}
