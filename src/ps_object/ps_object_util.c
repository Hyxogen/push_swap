/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_util.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:36 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

void
	ps_object_fill(t_ps_object *object, int *int_arr, size_t arr_len)
{
	while (arr_len--)
	{
		ideque_push_front(object->m_stack_a, inode_create(*int_arr));
		int_arr++;
	}
}

t_bool
	ps_object_is_sorted(const t_ps_object *object)
{
	if (!ideque_is_empty(object->m_stack_b))
		return (FALSE);
	return (ideque_is_sorted(object->m_stack_a));
}
