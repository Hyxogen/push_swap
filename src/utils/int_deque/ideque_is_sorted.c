/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_is_sorted.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:55 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:46:36 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

ft_bool
	ideque_is_sorted(const t_ideque *deque)
{
	t_inode	*node;

	node = ideque_front(deque);
	while (node && node->m_head)
	{
		if (node->m_content > node->m_head->m_content)
			return (FALSE);
		node = node->m_head;
	}
	return (TRUE);
}
