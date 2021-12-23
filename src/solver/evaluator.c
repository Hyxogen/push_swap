/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:56:48 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/16 09:27:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "evaluator.h"
#include "instruction.h"
#include <stdlib.h>
#include <limits.h>
#include <ft_string.h>

size_t get_position(const t_stack *stack, int number)
{
	size_t			position, highest_pos;
	t_stack_element	*element;
	int				current, previous, highest;

	element = stack->m_Top;
	if (element == NULL)
		return (0);
	position = 0;
	highest_pos = 0;
	highest = INT_MIN;
	previous = *((int*)stack->m_Bottom->m_Content);
	while (element)
	{
		current = *((int*)element->m_Content);
		if (current == previous)
			return (position);
		else if ((number < previous) && (number > current))
			return (position);
		if (current > highest)
		{
			highest_pos = position;
			highest = current;
		}
		position++;
		previous = current;
		element = element->m_Head;
	}
	return (highest_pos);
}

t_distance get_distance(const t_stack *stack, int number)
{
	return (get_distance_exact(get_position(stack, number), get_size(top(stack))));
}

t_evaluation	evaluate_single_exact(t_stack *origin, t_stack *des, int num, size_t position, size_t size)
{
	t_distance	a_dis;
	t_distance	b_dis;

	(void)origin;
	(void)des;
	a_dis = get_distance_exact(position, size);
	b_dis = get_distance(des, num);
	return (generate_instructions(a_dis, b_dis));
}

void execute_evaluation(t_ps_object *object, const t_evaluation *eval)
{
	size_t	index;

	for (index = 0; index < eval->m_Count; index++)
		execute_instruction(eval->m_Instructions[index], object);
}

int	cmp_evaluation(const t_evaluation *a, const t_evaluation *comp)
{
	if (comp->m_Count < a->m_Count)
		return (1);
	else if (comp->m_Count > a->m_Count)
		return (-1);
	return (0);
}

t_evaluation	generate_put_pack(t_stack *a, t_stack *b)
{
	t_evaluation	ret;
	t_distance		distance;
	t_stack_element	*element;
	size_t 			size, position, highest_pos;
	int 			highest, number;
	size_t			i;
	size_t 			temp;

	element = top(b);
	size = get_size(element);
	highest = INT_MIN;
	highest_pos = 0;
	position = 0;
	(void)a;
	while (element)
	{
		number = *((int*)element->m_Content);
		if (number > highest)
		{
			highest = number;
			highest_pos = position;
		}
		position++;
		element = element->m_Head;
	}

	distance = get_distance_exact(highest_pos, size);
	ret = generate_instructions(g_EmptyDistance, distance);
	temp = ret.m_Count;
	ret.m_Instructions = realloc(ret.m_Instructions, (temp + size + 1) * sizeof(int));
	ret.m_Count += size - 1;
	for (i = 0; i < size; i++)
		ret.m_Instructions[(temp - 1) + i] = ips_pa;
	ret.m_Instructions[temp + size] = ips_empty;
	return (ret);
}

t_evaluation evaluate(t_stack *origin, t_stack *des, int depth)
{
	t_evaluation	*evaluations;
	int				number;
	int				best_evaluation;
	size_t			position;
	size_t			origin_size;
	t_stack_element	*element;
	t_evaluation	temp1;

	(void)depth;
	element = top(origin);
	origin_size = get_size(element);
	if (origin_size == 0)
		return (g_EmptyEval);
	position = 0;
	best_evaluation = -1;
	evaluations = malloc(sizeof(t_evaluation) * origin_size);
	while (element)
	{
		number = *((int*)element->m_Content);
		temp1 = evaluate_single_exact(origin, des, number, position, origin_size);
		evaluations[position] = temp1;
		/*if (depth > 0)
		{
			temp2 = evaluate(origin, des, depth - 1);
			evaluations[position] = join_evaluations(&evaluations[position], &temp2);
		}*/
		if (best_evaluation < 0 || (cmp_evaluation(&evaluations[position], &evaluations[best_evaluation]) < 0))
			best_evaluation = position;
		position++;
		element = element->m_Head;
	}
	return (evaluations[best_evaluation]);
}

void print_evaluation(t_evaluation eval)
{
	size_t i;

	for (i = 0; i < eval.m_Count; i++)
	{
		printf("%s\n", get_instr_name(eval.m_Instructions[i]));
	}
}

void print_distance(const t_distance *distance)
{
	printf("(%zu, %zu)", distance->m_Up, distance->m_Down);
}
