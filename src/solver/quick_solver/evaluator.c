#include "evaluator.h"
#include "../../utils/vector2.h"
#include "../../utils/malloc_utils.h"
#include <limits.h>
#include <ft_stdlib.h>
#include <ft_math.h>
#include <signal.h>

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

	if (both_up->m_X < both_down->m_X)
		vec->m_X = both_up->m_X;
	else
		vec->m_X = both_down->m_X;

	if (both_up->m_Y < both_down->m_Y)
		vec->m_Y = both_up->m_Y;
	else
		vec->m_Y = both_down->m_Y;
	instr_count = ft_min(ft_labs(vec->m_X), ft_labs(vec->m_Y)) + ft_labs(vec->m_X - vec->m_Y);
	return (instr_count);
}

static t_evaluation generate_eval(const t_vec2* vec, t_instruction put_instr, size_t instr_count) {
	t_vec2 cpy;
	t_evaluation ret;
	t_instruction* instructions;

	vector_cpy(vec, &cpy);
	ret.m_Count = instr_count + 1;
	instructions = ft_malloc(sizeof(int) * ret.m_Count);
	ret.m_Instructions = instructions;

	while (cpy.m_X > 0 && cpy.m_Y > 0) {
		*instructions++ = ips_rr;
		cpy.m_X--;
		cpy.m_Y--;
	}
	while (cpy.m_X > 0) {
		*instructions++ = ips_ra;
		cpy.m_X--;
	}
	while (cpy.m_Y > 0) {
		*instructions++ = ips_rb;
		cpy.m_Y--;
	}

	while (cpy.m_X < 0 && cpy.m_Y < 0) {
		*instructions++ = ips_rrr;
		cpy.m_X++;
		cpy.m_Y++;
	}
	while (cpy.m_X < 0) {
		*instructions++ = ips_rra;
		cpy.m_X++;
	}
	while (cpy.m_Y < 0) {
		*instructions++ = ips_rrb;
		cpy.m_Y++;
	}
	*instructions = put_instr;
	if (!is_valid(ret.m_Instructions, ret.m_Count))
		raise(SIGTRAP);
	return (ret);
}

t_evaluation evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size, t_instruction put_instr) {
	t_vec2 up, down, fastest;
	size_t up_count, down_count, fastest_count;

	up_count = get_count_both_up(from_pos, to_pos, &up);
	down_count = get_count_both_down(from_pos, from_size, to_pos, to_size, &down);
	fastest_count = get_count_both_fastest(&up, &down, &fastest); /*Probaby beter name is something like exclusive_count*/

	if (up_count < down_count && up_count < fastest_count)
		return (generate_eval(&up, put_instr, up_count));
	else if (fastest_count > down_count)
		return (generate_eval(&down, put_instr, down_count));
	else
		return (generate_eval(&fastest, put_instr, fastest_count));
}

t_evaluation worst_evaluation() {
	t_evaluation ret;

	ret.m_Count = ULONG_MAX;
	return (ret);
}