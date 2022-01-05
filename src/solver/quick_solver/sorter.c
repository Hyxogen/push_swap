#include "sorter.h"

#include "evaluator.h"
#include "../../utils/math_utils.h"
#include "generator.h"
#include <limits.h>
#include <stdlib.h>
#include <ft_math.h>
#include <signal.h>

/** Dumps the first best number from low to high from the from stack to the to stack */
static t_instruction* dump_single(t_stack* from, t_stack* to, t_instruction put_instr, int low, int high, size_t* count) {
	t_instruction* instructions;
	t_evaluation best, current;
	t_stack_element* element;
	size_t position;
	size_t from_size, to_size;
	int val;
	ft_bool first_pass;

	element = stack_top(from);
	position = 0;
	from_size = stack_size(from);
	to_size = stack_size(to);
	first_pass = TRUE;
	init_evaluation(&best);
	while (element) {
		val = *((int*)element->m_Content);
		if (val >= low && val <= high) {
			current = evaluate(position, from_size, 0, to_size);
			if (first_pass || cmp_evaluation(&current, &best) < 0) {
				destroy_evaluation(&best, FALSE);
				best = current;
			} else
				destroy_evaluation(&current, FALSE);
			first_pass = FALSE;
		}
		position++;
		element = stack_get_next(element);
	}

	if (first_pass) {
		*count = 0;
		return (0);
	}

	instructions = generate_instructions_e(&best, 1);
	instructions[best.m_Count] = put_instr;
	best.m_Count += 1;

	destroy_evaluation(&best, FALSE);

	execute_instructions(from, to, instructions, best.m_Count);
	*count = best.m_Count;
	return (instructions);
}

/** Dumps all the numbers from low to high from the from stack to the to stack */
static t_instruction* dump_range(t_stack* from, t_stack* to, t_instruction put_instr, int low, int high, size_t* count) {
	t_instruction* instructions, *temp;
	size_t instr_count;

	*count = 0;
	instructions = NULL;

	while (TRUE) {
		temp = dump_single(from, to, put_instr, low, high, &instr_count);

		if (instr_count == 0)
			break;
		
		join_instructions(&instructions, *count, temp, instr_count);
		*count += instr_count;
		free(temp);
	}
	
	return (instructions);
}

t_instruction* rough_sort_optimized(t_stack* from, t_stack* to, t_instruction put_instr, const int* from_sorted, size_t block_size, size_t* instrs) {
	t_instruction* instructions, *temp;
	size_t block_index;
	size_t instr_count;
	size_t size;
	int low, high;

	*instrs = 0;
	instructions = NULL;
	size = stack_size(from);
	instructions = NULL;
	for (block_index = 0; block_index < size; block_index += block_size) {
		low = from_sorted[block_index];
		high = from_sorted[ft_stmin(block_index + block_size - 1, size)]; /*Possible overflow when block_size = 0 or block_index and size are both zero, should I fix this?*/

		temp = dump_range(from, to, put_instr, low, high, &instr_count);

		if (instr_count == 0)
			break;
		join_instructions(&instructions, *instrs, temp, instr_count);
		*instrs += instr_count;
		free(temp);
	}
	return (instructions);
}

static size_t get_sorted_pos(t_stack* stack, int i) {
	t_stack_element* previous, *current;
	int previous_val, current_val, position;
	int lowest_val, lowest_pos;

	if (stack_size(stack) <= 1)
		return (0);
	previous = stack_bottom(stack);
	current = stack_top(stack);
	position = 0;
	lowest_pos = 0;
	lowest_val = INT_MAX;
	while (current) {
		previous_val = *((int*)previous->m_Content);
		current_val = *((int*)current->m_Content);
		if ((i > previous_val) && (i < current_val))
			return (position);
		else if (current_val < lowest_val) {
			lowest_val = current_val;
			lowest_pos = position;
		}
		previous = current;
		current = stack_get_next(current);
		position++;
	}
	return (lowest_pos);
}

static t_instruction* move_best(t_stack* from, t_stack* to, t_instruction put_instr, size_t* instrs) {
	t_evaluation best, current;
	t_instruction* instructions;
	t_stack_element* element;
	size_t from_pos, to_pos;
	size_t from_size, to_size;
	ft_bool first_pass;

	element = stack_top(from);
	from_pos = 0;
	init_evaluation(&best);
	from_size = stack_size(from);
	to_size = stack_size(to);
	first_pass = TRUE;
	while (element) {
		to_pos = get_sorted_pos(to, *((int*)element->m_Content));
		current = evaluate(from_pos, from_size, to_pos, to_size);

		if (first_pass || cmp_evaluation(&current, &best) < 0) {
			destroy_evaluation(&best, FALSE);
			best = current;
		} else
			destroy_evaluation(&current, FALSE);
		element = stack_get_next(element);
		from_pos++;
		first_pass = FALSE;
	}

	instructions = generate_instructions_e(&best, 1);
	instructions[best.m_Count] = put_instr;
	best.m_Count += 1;

	destroy_evaluation(&best, FALSE);

	execute_instructions(from, to, instructions, best.m_Count);
	*instrs = best.m_Count;
	return (instructions);
}

t_instruction* sort(t_stack* from, t_stack* to, t_instruction put_instr, size_t* instrs) {
	t_instruction* instructions, *temp;
	size_t index;
	size_t instr_count;
	size_t size;

	size = stack_size(from);
	instructions = NULL;
	*instrs = 0;
	for (index = 0; index < size; index++) {
		temp = move_best(from, to, put_instr, &instr_count);

		if (instr_count == 0)
			break; /*This should never happen*/
		join_instructions(&instructions, *instrs, temp, instr_count);
		*instrs += instr_count;
		free(temp);
	}
	return (instructions);
}
