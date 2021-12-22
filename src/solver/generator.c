#include "generator.h"

#include <stdlib.h>

const static char *g_InstructionNames[] = {
		"empty",
		"pa",
		"pb",
		"ra",
		"rb",
		"rr",
		"sa",
		"sb",
		"ss",
		"rra",
		"rrb",
		"rrr",
		"err",
		NULL
};

const char *get_instr_name(t_instruction instr)
{
	if (instr < 0 || instr >= ips_err)
		return g_InstructionNames[ips_err];
	return g_InstructionNames[instr];
}

static t_evaluation generate_instructions_internal(t_distance a, t_distance b) {
	int				*ret;
	int				*ret_cpy;
	t_evaluation	eval;

	ret = malloc((a.m_Up + b.m_Up + a.m_Down + b.m_Down + 2) * sizeof(int));
	ret_cpy = ret;
	while (a.m_Up && b.m_Up)
	{
		*ret_cpy = ips_rr;
		a.m_Up--;
		b.m_Up--;
		ret_cpy++;
	}
	while (a.m_Up)
	{
		*ret_cpy = ips_ra;
		a.m_Up--;
		ret_cpy++;
	}
	while (b.m_Up)
	{
		*ret_cpy = ips_rb;
		b.m_Up--;
		ret_cpy++;
	}

	while (a.m_Down && b.m_Down)
	{
		*ret_cpy = ips_rrr;
		a.m_Down--;
		b.m_Down--;
		ret_cpy++;
	}
	while (a.m_Down)
	{
		*ret_cpy = ips_rra;
		a.m_Down--;
		ret_cpy++;
	}
	while (b.m_Down)
	{
		*ret_cpy = ips_rrb;
		b.m_Down--;
		ret_cpy++;
	}
	*ret_cpy = ips_pb;
	*(ret_cpy + 1) = ips_empty;
	eval.m_Instructions = ret;
	eval.m_Count = (ret_cpy - ret) + 1;
	return (eval);
}

t_evaluation
	generate_instructions(t_distance a, t_distance b)
{
	t_distance	total_in;
	t_distance	total_ex;
	t_distance	diff;
	int			cmp;

	total_ex.m_Up = 0;
	total_ex.m_Down = 0;
	diff = subtract_dist(&a, &b);
	total_in = add_dist(&a, &diff);
	if (a.m_Up < a.m_Down)
		total_ex.m_Up += a.m_Up;
	else
		total_ex.m_Down += a.m_Down;
	if (b.m_Up < b.m_Down)
		total_ex.m_Up += b.m_Up;
	else
		total_ex.m_Down += b.m_Down;
	cmp = cmp_dist(&total_in, &total_ex);
	if (cmp <= 0)
	{
		if (total_in.m_Up < total_in.m_Down)
		{
			a.m_Down = 0;
			b.m_Down = 0;
			return (generate_instructions_internal(a, b));
		}
		a.m_Up = 0;
		b.m_Up = 0;
		return (generate_instructions_internal(a, b));
	}
	if (a.m_Up < a.m_Down)
		a.m_Down = 0;
	else
		a.m_Up = 0;
	if (b.m_Up < b.m_Down)
		b.m_Down = 0;
	else
		b.m_Up = 0;
	return (generate_instructions_internal(a, b));
}
