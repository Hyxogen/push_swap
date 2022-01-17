/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sorter.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:32 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:52:21 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sorter.h"
#include "sorter_utils.h"
#include "distance.h"
#include <stdlib.h>
#include <ft_stdlib.h>
#include <ft_math.h>

static ft_bool
	_sorter_get_best_next(t_sort_info *info, t_distance *out)
{
	t_distance	cmp_distance;
	t_inode		*node;
	size_t		node_pos;
	ft_bool		found;

	node = ideque_front(info->m_from_deque);
	found = FALSE;
	node_pos = 0;
	while (node)
	{
		if (sort_info_applies(info, node->m_content))
		{
			cmp_distance = _sorter_get_distance(node_pos,
					ideque_get_size(info->m_from_deque),
					_sorter_get_position(node->m_content, info),
					ideque_get_size(info->m_to_deque));
			if (!found || distance_cmp(&cmp_distance, &*out) < 0)
				*out = cmp_distance;
			found = TRUE;
		}
		node_pos++;
		node = node->m_head;
	}
	return (found);
}

static t_instruction
	*_sorter_sort_next(t_sort_info *info, size_t *instr_count)
{
	t_instruction	*next_instrs;
	t_distance		next_dist;

	*instr_count = 0;
	if (!_sorter_get_best_next(info, &next_dist))
		return (NULL);
	next_instrs = _sorter_put(info, &next_dist, instr_count);
	return (next_instrs);
}

static t_instruction
	*_sorter_sort(t_sort_info *info, size_t *total_count)
{
	t_instruction	*sort_instrs;
	t_instruction	*next_instrs;
	size_t			next_count;

	sort_instrs = NULL;
	while (TRUE)
	{
		next_instrs = _sorter_sort_next(info, &next_count);
		if (next_instrs == NULL)
			break ;
		join_instructions(&sort_instrs, *total_count, next_instrs, next_count);
		free(next_instrs);
		*total_count += next_count;
	}
	return (sort_instrs);
}

t_instruction
	*sorter_sort(t_sort_info *info, size_t *count)
{
	*count = 0;
	if (ideque_is_empty(info->m_from_deque))
		return (NULL);
	return (_sorter_sort(info, count));
}
