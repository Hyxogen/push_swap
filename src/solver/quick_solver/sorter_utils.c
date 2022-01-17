/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sorter_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:38 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:39 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sorter_utils.h"
#include "generator.h"
#include "../instruction.h"
#include "evaluator.h"

long
	_sorter_get_position(int val, const t_sort_info *sort_info)
{
	return (sort_info->m_pos_func(val, sort_info->m_to_deque));
}

t_distance
	_sorter_get_distance(size_t left_pos, size_t left_size, size_t right_pos, size_t right_size)
{
	t_distance	distance;

	distance = evaluate(left_pos, left_size, right_pos, right_size);
	return (distance);
}

t_instruction
	*_sorter_generate_put(const t_sort_info *info, const t_distance *distance, size_t *instr_count)
{
	t_instruction	*put_instrs;

	put_instrs = generate_instructions(distance->m_left_dist, distance->m_right_dist, 1, instr_count);
	put_instrs[*instr_count] = info->m_put_instr;
	*instr_count += 1;
	return (put_instrs);
}

t_instruction
	*_sorter_put(t_sort_info *info, const t_distance *distance, size_t *instr_count)
{
	t_instruction	*instructions;

	instructions = _sorter_generate_put(info, distance, instr_count);
	execute_instructions(info->m_from_deque, info->m_to_deque, instructions, *instr_count);
	return (instructions);
}

ft_bool
	sort_info_applies(const t_sort_info *info, int val)
{
	return (info->m_min <= val && val <= info->m_max);
}
