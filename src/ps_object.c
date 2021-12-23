/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:45:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 12:28:13 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

t_ps_object *create_ps_object() {
	t_ps_object	*ret;

	ret = malloc(sizeof(t_ps_object));
	if (!ret)
		return (NULL);
	if (!initialize_ps_object(ret))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

void destroy_ps_object(t_ps_object* object, ft_bool free_self) {
	destroy_stack(object->m_StackA, TRUE);
	destroy_stack(object->m_StackB, TRUE);
	if (free_self)
		free(object);
}

t_ps_object	*initialize_ps_object(t_ps_object *object)
{
	object->m_StackA = create_stack();
	object->m_StackB = create_stack();
	if (!object->m_StackA || !object->m_StackB)
	{
		free(object->m_StackA);
		free(object->m_StackB);
		return (NULL);
	}
	return (object);
}

void fill_psa(t_ps_object *object, int *arr, size_t size)
{
	while (size)
	{
		if (!push_top_content(object->m_StackA, arr))
			printf("Something went terribly wrong!\n");
		arr++;
		size--;
	}
}

void print_ps_object(const t_ps_object *object)
{
	t_stack_element	*tempA;
	t_stack_element	*tempB;

	tempA = top(object->m_StackA);
	tempB = top(object->m_StackB);
	printf("%20c|%-2c\n", 'A', 'B');
	printf("----------------------------------------\n");
	while (1)
	{
		if (tempA)
			printf("%20d", *((int*)tempA->m_Content));
		else
			printf("%20.0d", 0);
		if (tempB)
			printf("|%-20d\n", *((int*)tempB->m_Content));
		else
			printf("|%-20.00d\n", 0);
		if (tempA)
			tempA = tempA->m_Head;
		if (tempB)
			tempB = tempB->m_Head;
		if (!tempA && !tempB)
			break;
	}
}

void ps_sa(t_ps_object *object)
{
	swap_top(object->m_StackA);
}

void ps_sb(t_ps_object *object)
{
	swap_top(object->m_StackB);
}

void ps_ss(t_ps_object *object)
{
	ps_sa(object);
	ps_sb(object);
}

void ps_pa(t_ps_object *object)
{
	if (object->m_StackB->m_Top)
		push_top(object->m_StackA, pop_top(object->m_StackB));
}

void ps_pb(t_ps_object *object)
{
	if (object->m_StackA->m_Top)
		push_top(object->m_StackB, pop_top(object->m_StackA));
}

void ps_ra(t_ps_object *object)
{
	rotate(object->m_StackA);
}

void ps_rb(t_ps_object *object)
{
	rotate(object->m_StackB);
}

void ps_rr(t_ps_object *object)
{
	ps_ra(object);
	ps_rb(object);
}

void ps_rra(t_ps_object *object)
{
	rrotate(object->m_StackA);
}

void ps_rrb(t_ps_object *object)
{
	rrotate(object->m_StackB);
}

void ps_rrr(t_ps_object *object)
{
	ps_rra(object);
	ps_rrb(object);
}

t_bool is_sorted(t_ps_object *object)
{
	t_stack_element	*temp;

	if (top(object->m_StackB))
		return (FALSE);
	temp = top(object->m_StackA);
	while (temp)
	{
		if (temp->m_Tail && *((int*)temp->m_Tail->m_Content) > *((int*)temp->m_Content))
			return (FALSE);
		temp = temp->m_Head;
	}
	return (TRUE);
}
