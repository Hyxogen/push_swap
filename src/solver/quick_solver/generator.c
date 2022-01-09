#include "generator.h"
#include <ft_math.h>
#include <ft_stdlib.h>
#include "../../utils/malloc_utils.h"

static size_t
	get_instruction_count(long a_mov, long b_mov)
{
	if ((a_mov <= 0 && b_mov >= 0) || (b_mov <= 0 && a_mov >= 0))
		return (ft_labs(a_mov) + ft_labs(b_mov));
	else if (a_mov > 0)
		return (ft_lmax(a_mov, b_mov));
	return (ft_labs(ft_lmin(a_mov, b_mov)));
}

static size_t
	generate_up_internal(t_instruction *instructions, long *a_mov, long *b_mov)
{
	size_t	count;

	count = 0;
	while (*a_mov > 0 && *b_mov > 0)
	{
		*instructions++ = ips_rr;
		*a_mov -= 1;
		*b_mov -= 1;
		count++;
	}
	while (*a_mov > 0)
	{
		*instructions++ = ips_ra;
		*a_mov -= 1;
		count++;
	}
	while (*b_mov > 0)
	{
		*instructions++ = ips_rb;
		*b_mov -= 1;
		count++;
	}
	return (count);
}

static size_t
	generate_down_internal(t_instruction *instructions, long *a_mov, long *b_mov)
{
	size_t	count;

	count = 0;
	while (*a_mov < 0 && *b_mov < 0)
	{
		*instructions++ = ips_rrr;
		*a_mov += 1;
		*b_mov += 1;
		count++;
	}
	while (*a_mov < 0)
	{
		*instructions++ = ips_rra;
		*a_mov += 1;
		count++;
	}
	while (*b_mov < 0)
	{
		*instructions++ = ips_rrb;
		*b_mov += 1;
		count++;
	}
	return (count);
}

t_instruction
	*generate_instructions(long a_mov, long b_mov, size_t extra, size_t *instr_count)
{
	t_instruction	*instructions;
	size_t			temp;

	*instr_count = get_instruction_count(a_mov, b_mov);
	instructions = ft_malloc(sizeof(t_instruction) * (*instr_count + extra));

	temp = generate_up_internal(instructions, &a_mov, &b_mov);
	generate_down_internal(instructions + temp, &a_mov, &b_mov);

	return (instructions);
}
