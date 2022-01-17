/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_front_back.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:12 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:13 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

t_inode
	*ideque_back(const t_ideque *deque)
{
	return (deque->m_back);
}

t_inode
	*ideque_front(const t_ideque *deque)
{
	return (deque->m_front);
}
