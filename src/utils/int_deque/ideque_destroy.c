/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_destroy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:15 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:47:24 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

#include <stdlib.h>

static void
	_ideque_destroy_nodes(t_ideque *deque)
{
	t_inode	*node;
	t_inode	*next;

	node = deque->m_front;
	while (node)
	{
		next = node->m_head;
		inode_destroy(node);
		node = next;
	}
}

void
	ideque_destroy(t_ideque *deque, ft_bool free_self)
{
	_ideque_destroy_nodes(deque);
	if (free_self)
		free(deque);
}
