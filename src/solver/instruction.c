/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   instruction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:26 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:26 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "instruction.h"

#include <ft_string.h>
#include <ft_stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_stdio.h>

static const char *g_DefaultNames[] = {
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
		"",
		"err",
		NULL
};

static const t_object_func g_Functions[] = {
		NULL,
		ps_object_pa,
		ps_object_pb,
		ps_object_ra,
		ps_object_rb,
		ps_object_rr,
		ps_object_sa,
		ps_object_sb,
		ps_object_ss,
		ps_object_rra,
		ps_object_rrb,
		ps_object_rrr,
		NULL,
		NULL
};

const char
	*get_instr_name(t_instruction instr)
{
	if (instr <= 0 || instr >= ips_err)
		return (g_DefaultNames[ips_err]);
	return (g_DefaultNames[instr]);
}

void
	execute_instructions(t_ideque *a, t_ideque *b, t_instruction *instructions, size_t count)
{
	t_ps_object	object;

	ps_object_init(&object, a, b);
	while (count)
	{
		if (*instructions > 0 && *instructions < ips_err)
			g_Functions[*instructions](&object);
		instructions++;
		count--;
	}
}

void
	print_instructions(t_instruction *instructions, size_t count)
{
	while (count)
	{
		ft_putendl_fd(1, get_instr_name(*instructions));
		count--;
		instructions++;
	}
}

void
	join_instructions(t_instruction **a, size_t a_len, t_instruction *b, size_t b_len)
{
	t_instruction	*ptr;

	ptr = ft_realloc(*a, a_len * sizeof(t_instruction), (a_len + b_len) * sizeof(t_instruction));
	if (ptr == NULL)
		exit(EXIT_FAILURE);
	ft_memcpy(ptr + a_len, b, b_len * sizeof(t_instruction));
	*a = ptr;
}

void
	translate_instructions(t_instruction *instructions, size_t count, const t_instruction *translation)
{
	while (count)
	{
		if (*instructions >= 0 && *instructions <= ips_err)
			*instructions = translation[*instructions];
		else
			*instructions = ips_err;
		count--;
		instructions++;
	}
}
