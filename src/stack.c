/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:39:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/07 15:30:19 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

t_stack *create_stack()
{
	t_stack	*ret;
	
	ret = malloc(sizeof(t_stack));
	if (!ret)
		return (NULL);
	ret->m_Begin = NULL;
	return (ret);
}

t_bool push(t_stack *stack, void *content)
{
	t_dlinked_list	*element;

	element = create_element(content);
	if (!element)
		return (FALSE);
	add_before(&stack->m_Begin, element);
	if (element->m_Head == NULL)
	{
		element->m_Head = element;
		element->m_Tail = element;
	}
	stack->m_Begin = element;
	return (TRUE);
}

void *pop(t_stack *stack)
{
	void			*content;
	t_dlinked_list	*temp;

	if (!stack->m_Begin)
		return (NULL);
	content = stack->m_Begin->m_Content;
	if (stack->m_Begin->m_Tail != stack->m_Begin)
	{
		stack->m_Begin->m_Tail->m_Head = stack->m_Begin->m_Head;
		stack->m_Begin->m_Head->m_Tail = stack->m_Begin->m_Tail;
		temp = stack->m_Begin->m_Head;
		free(stack->m_Begin);
		stack->m_Begin = temp;
	}
	else
	{
		free(stack->m_Begin);
		stack->m_Begin = NULL;
	}	
	return (content);
}

void *top(const t_stack *stack)
{
	if (stack->m_Begin == NULL)
		return (NULL);
	return (stack->m_Begin->m_Content);
}

void rotate(t_stack *stack)
{
	if (stack->m_Begin == NULL)
		return;
	stack->m_Begin = stack->m_Begin->m_Tail;
}

void rrotate(t_stack *stack)
{
	if (stack->m_Begin == NULL)
		return;
	stack->m_Begin = stack->m_Begin->m_Head;
}

void swap_top(t_stack *stack)
{
	if (stack->m_Begin == NULL)
		return;
	stack->m_Begin->m_Tail->m_Head = stack->m_Begin->m_Head;
	stack->m_Begin->m_Head->m_Head->m_Tail = stack->m_Begin;

	stack->m_Begin->m_Head->m_Tail = stack->m_Begin->m_Tail;
	stack->m_Begin->m_Head = stack->m_Begin->m_Head->m_Head;

	stack->m_Begin->m_Tail = stack->m_Begin->m_Tail->m_Head;
	stack->m_Begin->m_Tail->m_Head = stack->m_Begin;

	stack->m_Begin = stack->m_Begin->m_Tail;
}

void print_stack(const t_stack *stack)
{
	t_dlinked_list	*temp;

	temp = stack->m_Begin;
	printf("Top -> ");
	while (temp)
	{
		printf("%p ", (void*) temp);
		temp = temp->m_Head;
		if (temp == stack->m_Begin)
			break;
	}
	printf(" <- Bottom\n");
}