/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object_destroy.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"

#include <stdlib.h>

void
	ps_object_destroy(t_ps_object *object, t_bool free_self)
{
	ideque_destroy(object->m_stack_a, TRUE);
	ideque_destroy(object->m_stack_b, TRUE);
	if (free_self)
		free(object);
}
