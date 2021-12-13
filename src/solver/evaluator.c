/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:56:48 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 10:56:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "evaluator.h"
#include <stdlib.h>
#include <limits.h>

static t_distance get_distance_size(size_t position, size_t size)
{
	t_distance	ret;

	ret.m_Up = position;
	ret.m_Down = size - position;
	return (ret);
}

static t_distance get_distance(size_t position, t_stack *stack)
{
	return (get_distance_size(position, get_size(top(stack))));
}

static t_distance get_total_distance(const t_distance *a, const t_distance *b)
{
	t_distance	ret;

	if (a->m_Down > b->m_Down)
		ret.m_Down = a->m_Down - b->m_Down;
	else
		ret.m_Down = b->m_Down - a->m_Down;
	if (a->m_Up > b->m_Up)
		ret.m_Up = a->m_Up - b->m_Up;
	else
		ret.m_Up = b->m_Up - a->m_Up;
	return (ret);
}

static size_t get_pos(int number, t_stack *stack)
{
	size_t			distance;
	size_t			pos, current_pos;
	t_stack_element	*temp;
	int				temp_number;

	pos = 0;
	distance = ULONG_MAX;
	temp = top(stack);
	current_pos = 0;
	while (temp)
	{
		temp_number = *((int*)temp->m_Content);
		if (temp_number > number)
		{
			if ((size_t) (temp_number - number) < distance)
			{
				pos = current_pos + 1;
				distance = temp_number - number;
			}
		}
		else
		{
			if ((size_t) (number - temp_number) < distance)
			{
				if (current_pos)
					pos = current_pos - 1;
				else
					pos = 0;
				distance = number - temp_number;
			}
		}
		current_pos++;
		temp = temp->m_Head;
	}
	return (pos);
}

t_distance_pair evaluate(t_stack *origin, t_stack *des)
{
	t_distance_pair		best;
	t_stack_element		*element;
	size_t				size, i;
	t_distance			closest;
	t_distance			origin_distance, destination_distance, total;
	int					number;

	closest.m_Up = ULONG_MAX;
	closest.m_Down = ULONG_MAX;
	element = top(origin);
	size = get_size(element);
	for (i = 0; i < size; i++)
	{
		number = *((int*)element->m_Content);
		origin_distance = get_distance_size(i, size);
		destination_distance = get_distance(get_pos(number, des), des);
		total = get_total_distance(&origin_distance, &destination_distance);
		if ((total.m_Up < closest.m_Up) && (total.m_Down < closest.m_Down))
		{
			closest = total;
			best.m_ADis = origin_distance;
			best.m_BDis = destination_distance;
			best.m_TDis = total;
		}
		element = element->m_Head;
	}
	return (best);
}

t_distance_pair evaluate_ps(t_ps_object *object)
{
	return (evaluate(object->m_StackA, object->m_StackB));
}
