/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_rotate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:42 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:36:43 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

static void
	_ideque_rotate_forward(t_ideque *deque, unsigned long val)
{
	while (val--)
		ideque_push_back(deque, ideque_pop_front(deque));
}

static void
	_deque_rotate_backward(t_ideque *deque, unsigned long val)
{
	while (val--)
		ideque_push_front(deque, ideque_pop_back(deque));
}

static void
	_ideque_rotate(t_ideque *deque, int val)
{
	if (val < 0)
		_deque_rotate_backward(deque, -((long)val));
	else
		_ideque_rotate_forward(deque, val);
}

void
	ideque_rotate(t_ideque *deque, int val)
{
	if (ideque_get_size(deque) <= 1)
		return;
	_ideque_rotate(deque, val);
}
