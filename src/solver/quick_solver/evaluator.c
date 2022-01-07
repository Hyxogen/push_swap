#include "evaluator.h"
#include "../../utils/vector2.h"
#include "../../utils/malloc_utils.h"
#include <limits.h>
#include <ft_stdlib.h>
#include <ft_math.h>

static size_t get_count_both_up(size_t from_pos, size_t to_pos, t_vec2* vec) {
	size_t instr_count;

	instr_count = ft_stmax(from_pos, to_pos);
	vec->m_X = (long) from_pos;
	vec->m_Y = (long) to_pos;
	return (instr_count);
}

/*Downwards instructions do not get calculated properly see ./push_swap 3 6 1 5 where it doesn't calculate the proper value for putting back 3*/
static size_t get_count_down(size_t pos, size_t size, long* mov) {
	size_t instr_count;

	instr_count = size - pos;
	*mov = -((long)(size - pos));
	return (instr_count);
}

static size_t get_count_both_down(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size, t_vec2* vec) {
	size_t instr_count;

	instr_count = get_count_down(to_pos, to_size, &(vec->m_Y));
	instr_count += get_count_down(from_pos, from_size, &(vec->m_X));
	return (instr_count);
}

/*TODO ervoor zorgen dat conversies tussen long en size_t niet fout gaan (Heel het project)*/
static size_t get_count_both_fastest(const t_vec2* both_up, const t_vec2* both_down, t_vec2* vec) {
	size_t instr_count;
	
	if (both_up->m_X < ft_labs(both_down->m_X))
		vec->m_X = both_up->m_X;
	else
		vec->m_X = both_down->m_X;

	if (both_up->m_Y < ft_labs(both_down->m_Y))
		vec->m_Y = both_up->m_Y;
	else
		vec->m_Y = both_down->m_Y;
	instr_count = ft_min(ft_labs(vec->m_X), ft_labs(vec->m_Y)) + ft_labs(vec->m_X - vec->m_Y);
	return (instr_count);
}

t_evaluation evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size) {
	t_evaluation ret;
	t_vec2 up, down, fastest;
	size_t up_count, down_count, fastest_count;

	up_count = get_count_both_up(from_pos, to_pos, &up);
	down_count = get_count_both_down(from_pos, from_size, to_pos, to_size, &down);
	fastest_count = get_count_both_fastest(&up, &down, &fastest); /*Probaby beter name is something like exclusive_count*/

	if (up_count < down_count && up_count < fastest_count) {
		ret.m_Count = up_count;
		ret.m_MoveVec = up;
	}
	else if (fastest_count > down_count) {
		ret.m_Count = down_count;
		ret.m_MoveVec = down;
	}
	else {
		ret.m_Count = fastest_count;
		ret.m_MoveVec = fastest;
	}
	return (ret);
}
