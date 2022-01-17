/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_rrotate.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:41 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:41 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

void
	ps_object_rra(t_ps_object *object)
{
	ideque_rotate(object->m_stack_a, -1);
}

void
	ps_object_rrb(t_ps_object *object)
{
	ideque_rotate(object->m_stack_b, -1);
}

void
	ps_object_rrr(t_ps_object *object)
{
	ps_object_rra(object);
	ps_object_rrb(object);
}
