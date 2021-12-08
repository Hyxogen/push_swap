/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:45:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/07 15:18:22 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"
#include <stdlib.h>
#include <limits.h>

t_ps_object *create_ps_object() {
	t_ps_object	*ret;

	ret = malloc(sizeof(t_ps_object));
	if (!ret)
		return (NULL);
	ret->m_StackA = create_stack();
	ret->m_StackB = create_stack();
	if (!ret->m_StackA || !ret->m_StackB)
		return (NULL);
	return (ret);
}

void fill_psa(t_ps_object *object, int *arr, size_t size)
{
	while (size)
	{
		push(object->m_StackA, arr);
		arr++;
		size--;
	}
}

void print_ps_object(const t_ps_object *object)
{
	t_dlinked_list	*tempA;
	t_dlinked_list	*tempB;

	tempA = object->m_StackA->m_Begin;
	tempB = object->m_StackB->m_Begin;
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
		if (tempA == object->m_StackA->m_Begin)
			tempA = NULL;
		if (tempB)
			tempB = tempB->m_Head;
		if (tempB == object->m_StackB->m_Begin)
			tempB = NULL;
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
	push(object->m_StackA, pop(object->m_StackB));
}

void ps_pb(t_ps_object *object)
{
	push(object->m_StackB, pop(object->m_StackA));
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
	t_dlinked_list	*temp;
	int				last;

	if (object->m_StackB->m_Begin)
		return (FALSE);
	temp = object->m_StackA->m_Begin;
	last = INT_MIN;
	while (temp)
	{
		if (*((int*)temp->m_Content) < last)
			return (FALSE);
		last = *((int*)temp->m_Content);
		temp = temp->m_Head;
		if (temp == object->m_StackA->m_Begin)
			break;
	}
	return (TRUE);
}