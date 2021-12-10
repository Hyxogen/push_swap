/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slow_solver.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/10 13:02:49 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 13:13:22 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "slow_solver.h"
#include <limits.h>


static int get_lowest(t_stack *stack)
{
	t_stack_element	*temp;
	int				lowest;

	temp = stack->m_Top;
	lowest = INT_MAX;
	while (temp)
	{
		if (*((int*)temp->m_Content) < lowest)
			lowest = *((int*)temp->m_Content);
		temp = temp->m_Head;
	}
	return (lowest);
}


/*
static int get_highest(t_stack *stack)
{
	t_stack_element	*temp;
	int				highest;

	temp = stack->m_Top;
	highest = INT_MIN;
	while (temp)
	{
		if (*((int*)temp->m_Content) > highest)
			highest = *((int*)temp->m_Content);
		temp = temp->m_Head;
	}
	return (highest);
}
*/

void slow_solve(t_ps_object *object)
{
	int	highest;

	highest = get_lowest(object->m_StackA);
	while (object->m_StackA->m_Top)
	{
		while (*((int*)object->m_StackA->m_Top->m_Content) != highest)
		{
			printf("ra\n");
			ps_ra(object);
		}
		ps_pb(object);
		printf("pb\n");
		if (object->m_StackA->m_Top)
			highest = get_lowest(object->m_StackA);
	}
	while (object->m_StackB->m_Top)
	{
		ps_pa(object);
		printf("pa\n");
	}
}
/*
ra
ra
pb
pb
pb
pa
pa
pa
*/
