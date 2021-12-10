/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:39:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 11:59:21 by dmeijer       ########   odam.nl         */
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
	ret->m_Top = NULL;
	ret->m_Bottom = NULL;
	return (ret);
}

ft_bool push_top_content(t_stack *stack, void *content)
{
	t_stack_element	*element;

	element = create_element(content);
	if (element == NULL)
		return (FALSE);
	if (!push_top(stack, element))
	{
		free(element);
		return (FALSE);
	}
	return (TRUE);
}

ft_bool push_bottom_content(t_stack *stack, void *content)
{
	t_stack_element	*element;

	element = create_element(content);
	if (element == NULL)
		return (FALSE);
	if (!push_bottom(stack, element))
	{
		free(element);
		return (FALSE);
	}
	return (TRUE);
}

ft_bool push_top(t_stack *stack, t_stack_element *element)
{
	add_before(&stack->m_Top, element);
	stack->m_Top = element;
	if (stack->m_Bottom == NULL)
		stack->m_Bottom = element;
	return (TRUE);
}

ft_bool push_bottom(t_stack *stack, t_stack_element *element)
{
	add_after(&stack->m_Bottom, element);
	stack->m_Bottom = element;
	if (stack->m_Top == NULL)
		stack->m_Top = element;
	return (TRUE);
}

t_stack_element *pop_top(t_stack *stack)
{
	t_stack_element	*ret;
	
	ret = top(stack);
	if (ret == NULL)
		return (NULL);
	if (ret->m_Head)
		ret->m_Head->m_Tail = NULL;
	else
		stack->m_Bottom = NULL;
	stack->m_Top = ret->m_Head;
	return (ret);
}

t_stack_element *pop_bottom(t_stack *stack)
{
	t_stack_element	*ret;
	
	ret = bottom(stack);
	if (ret == NULL)
		return (NULL);
	if (ret->m_Tail)
		ret->m_Tail->m_Head = NULL;
	else
		stack->m_Top = NULL;
	stack->m_Bottom = ret->m_Tail;
	return (ret);
}

t_stack_element *top(const t_stack *stack)
{
	return (stack->m_Top);
}

t_stack_element *bottom(const t_stack *stack)
{
	return (stack->m_Bottom);
}

void rotate(t_stack *stack)
{
	t_stack_element	*temp;
	
	temp = pop_top(stack);
	if (temp)
		push_bottom(stack, temp);
}

void rrotate(t_stack *stack)
{
	t_stack_element	*temp;
	
	temp = pop_bottom(stack);
	if (temp)
		push_top(stack, temp);
}

void swap_top(t_stack *stack)
{
	t_stack_element	*first;
	t_stack_element	*second;

	first = pop_top(stack);
	second = pop_top(stack);
	if (first)
		push_top(stack, first);
	if (second)
		push_top(stack, second);
}
