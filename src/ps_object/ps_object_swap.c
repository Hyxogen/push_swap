/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_swap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:39 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:39 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

static void
	_ps_object_sx(t_ideque *deque)
{
	t_inode *first;
	t_inode *second;

	first = ideque_pop_front(deque);
	second = ideque_pop_front(deque);
	ideque_push_front(deque, first);
	ideque_push_front(deque, second);
}

static void
	ps_object_sx(t_ideque *deque)
{
	if (ideque_get_size(deque) <= 1)
		return;
	_ps_object_sx(deque);
}

void
	ps_object_sa(t_ps_object *object)
{
	ps_object_sx(object->m_stack_a);
}

void
	ps_object_sb(t_ps_object *object)
{
	ps_object_sx(object->m_stack_b);
}

void
	ps_object_ss(t_ps_object *object)
{
	ps_object_sa(object);
	ps_object_sb(object);
}
