/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   instruction.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:23 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:49:13 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_H
# define INSTRUCTION_H

# include "../ps_object/ps_object.h"

typedef int		t_instruction;

typedef void	(*t_object_func)(t_ps_object *object);

enum e_instruction
{
	ips_empty = 0,
	ips_pa,
	ips_pb,
	ips_ra,
	ips_rb,
	ips_rr,
	ips_sa,
	ips_sb,
	ips_ss,
	ips_rra,
	ips_rrb,
	ips_rrr,
	ips_stop,
	ips_err
};

void		execute_instructions(t_ideque *a, t_ideque *b,
				t_instruction *instructions, size_t count);
void		print_instructions(t_instruction *instructions, size_t count);
void		join_instructions(t_instruction **a, size_t a_len,
				t_instruction *b, size_t b_len);
void		translate_instructions(t_instruction *instructions,
				size_t count, const t_instruction *translation);
const char	*get_instr_name(t_instruction instr);

#endif
