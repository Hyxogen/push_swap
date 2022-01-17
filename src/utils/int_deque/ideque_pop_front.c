/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_pop_front.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:46:11 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

#include <stddef.h>

static void
	_ideque_pop_front_last(t_ideque *deque)
{
	deque->m_front = NULL;
	deque->m_back = NULL;
	deque->m_size = 0;
}

static void
	_ideque_pop_front_nlast(t_ideque *deque)
{
	deque->m_front->m_head->m_tail = NULL;
	deque->m_front = deque->m_front->m_head;
	deque->m_size -= 1;
}

static void
	_ideque_pop_front(t_ideque *deque)
{
	if (ideque_get_size(deque) == 1)
		_ideque_pop_front_last(deque);
	else
		_ideque_pop_front_nlast(deque);
}

t_inode
	*ideque_pop_front(t_ideque *deque)
{
	t_inode	*ret;

	ret = ideque_front(deque);
	_ideque_pop_front(deque);
	ret->m_head = NULL;
	return (ret);
}
