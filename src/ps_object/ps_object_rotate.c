/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_rotate.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:43 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:43 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

void
	ps_object_ra(t_ps_object *object)
{
	ideque_rotate(object->m_stack_a, 1);
}

void
	ps_object_rb(t_ps_object *object)
{
	ideque_rotate(object->m_stack_b, 1);
}

void
	ps_object_rr(t_ps_object *object)
{
	ps_object_ra(object);
	ps_object_rb(object);
}
