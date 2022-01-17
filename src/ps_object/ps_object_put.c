/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_put.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:45 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:45 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

static void
	_ps_object_px(t_ideque *from, t_ideque *to)
{
	t_inode *pop_node;

	pop_node = ideque_pop_front(from);
	ideque_push_front(to, pop_node);
}

static void
	ps_object_px(t_ideque *from, t_ideque *to)
{
	if (ideque_is_empty(from))
		return;
	_ps_object_px(from, to);
}

void
	ps_object_pa(t_ps_object *object)
{
	ps_object_px(object->m_stack_b, object->m_stack_a);
}

void
	ps_object_pb(t_ps_object *object)
{
	ps_object_px(object->m_stack_a, object->m_stack_b);
}
