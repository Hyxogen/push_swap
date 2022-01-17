/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ideque_size.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:40 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:36:40 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "int_deque.h"

ft_bool
	ideque_is_empty(const t_ideque *deque)
{
	return (ideque_get_size(deque) == 0);
}

size_t
	ideque_get_size(const t_ideque *deque)
{
	return (deque->m_size);
}
