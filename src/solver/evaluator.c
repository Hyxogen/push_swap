/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:56:48 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 16:38:19 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "evaluator.h"
#include <stdlib.h>
#include <limits.h>
#include <ft_string.h>

int ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int cmp_distance(const t_distance *a, const t_distance *cmp)
{
	if ((a->m_Down + a->m_Up) < (cmp->m_Up + cmp->m_Down))
		return (-1);
	else if ((a->m_Down + a->m_Up) > (cmp->m_Up + cmp->m_Down))
		return (1);
	return (0);
}
/*TODO new get_position schrijven*/
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
		{
			printf("current == previous (%d, %d)\n", current, previous);
			return (position);
		}
		else if ((number > previous) && (number < current))
		{
			printf("number > previous\n");
			return (position - 1);
		}
		if (current > highest)
		{
			highest_pos = position;
			highest = current;
		}
		position++;
		previous = current;
		element = element->m_Head;
	}
	printf("Highest pos:%zu\n", highest_pos);
	return (highest_pos);
}

t_distance get_distance_exact(size_t position, size_t size)
{
	t_distance	ret;

	ret.m_Up = position;
	ret.m_Down = size - position;
	return (ret);
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
	printf("num:%d a (%zu, %zu) b (%zu, %zu)\n", num, a_dis.m_Up, a_dis.m_Down, b_dis.m_Up, b_dis.m_Down);
	return (generate_instructions(&a_dis, &b_dis));
}

t_evaluation	generate_instructions_internal(t_distance a, t_distance b)
{
	int				*ret;
	int				*ret_cpy;
	t_evaluation	eval;

	/*todo, uitozeken waarom hier +2 is*/
	ret = malloc((a.m_Up + b.m_Up + a.m_Down + b.m_Down + 1) * sizeof(int));
	ret_cpy = ret;
	while (a.m_Up && b.m_Up)
	{
		*ret_cpy = ips_rr;
		a.m_Up--;
		b.m_Up--;
		ret_cpy++;
	}
	while (a.m_Up)
	{
		*ret_cpy = ips_ra;
		a.m_Up--;
		ret_cpy++;
	}
	while (b.m_Up)
	{
		*ret_cpy = ips_rb;
		b.m_Up--;
		ret_cpy++;
	}

	while (a.m_Down && b.m_Down)
	{
		*ret_cpy = ips_rrr;
		a.m_Down--;
		b.m_Down--;
		ret_cpy++;
	}
	while (a.m_Down)
	{
		*ret_cpy = ips_rra;
		a.m_Down--;
		ret_cpy++;
	}
	while (b.m_Down)
	{
		*ret_cpy = ips_rrb;
		b.m_Down--;
		ret_cpy++;
	}
	*ret_cpy = ips_empty;
	eval.m_Instructions = ret;
	eval.m_Count = ret_cpy - ret;
	return (eval);
}

t_evaluation	generate_instructions(const t_distance *a, const t_distance *b)
{
	t_distance	total_in;
	t_distance	total_ex;
	t_distance	a_cpy, b_cpy;
	int			cmp;

	total_ex.m_Up = 0;
	total_ex.m_Down = 0;
	a_cpy = *a;
	b_cpy = *b;
	if (a->m_Up > b->m_Up)
		total_in.m_Up = a->m_Up - b->m_Up;/*dit klopt niet, als beide 3 omhoog moeten gaan gaat ie 0 omhoog*/
	else
		total_in.m_Up = b->m_Up - a->m_Up;
	if (a->m_Down > b->m_Down)
		total_in.m_Down = a->m_Down - b->m_Down;
	else
		total_in.m_Down = b->m_Down - a->m_Down;
	if (a->m_Up < a->m_Down)
		total_ex.m_Up += a->m_Up;
	else
		total_ex.m_Down += a->m_Down;
	if (b->m_Up < b->m_Down)
		total_ex.m_Up += b->m_Up;
	else
		total_ex.m_Down += b->m_Down;
	cmp = cmp_distance(&total_in, &total_ex);
	if (cmp <= 0)
	{
		if (total_in.m_Up < total_in.m_Down)
		{
			a_cpy.m_Down = 0;
			b_cpy.m_Down = 0;
			return (generate_instructions_internal(a_cpy, b_cpy));
		}
		a_cpy.m_Up = 0;
		a_cpy.m_Down = 0;
		return (generate_instructions_internal(a_cpy, b_cpy));
	}
	if (a->m_Up < a->m_Down)
		a_cpy.m_Down = 0;
	else
		a_cpy.m_Up = 0;
	if (b->m_Up < b->m_Down)
		b_cpy.m_Down = 0;
	else
		b_cpy.m_Up = 0;
	return (generate_instructions_internal(a_cpy, b_cpy));
}

void execute_evaluation(t_stack *a, t_stack *b, const t_evaluation *eval)
{
	(void)a;
	(void)b;
	(void)eval;
}

void execute_evaluation_r(t_stack *a, t_stack *b, const t_evaluation *eval)
{
	(void)a;
	(void)b;
	(void)eval;
}

t_evaluation	join_evaluations(const t_evaluation *a, const t_evaluation *b)
{
	t_evaluation	join;
	size_t i;

	join.m_Count = a->m_Count + b->m_Count;
	join.m_Instructions = malloc((join.m_Count + 1) * sizeof(int));
	ft_memset(join.m_Instructions, 0, (join.m_Count + 1) * sizeof(int));
	ft_memcpy(join.m_Instructions, a->m_Instructions, a->m_Count);
	ft_memcpy(join.m_Instructions + a->m_Count, b->m_Instructions, b->m_Count);
	printf("aptr:%p, bptr:%p\n", (void*)a->m_Instructions, (void*)b->m_Instructions);
	printf("\n\n--[");
	for (i = 0; i < a->m_Count; i++)
		printf("%s;", g_InstructionNames[a->m_Instructions[i]]);
	for (i = 0; i < b->m_Count; i++)
		printf("%s'", g_InstructionNames[b->m_Instructions[i]]);
	printf("]--\n\n");
	print_evaluation(join);
	/*possible segfault with underflow*/
	return (join);
}

int	cmp_evaluation(const t_evaluation *a, const t_evaluation *comp)
{
	if (comp->m_Count < a->m_Count)
		return (1);
	else if (comp->m_Count > a->m_Count)
		return (-1);
	return (0);
}


t_evaluation evaluate(t_stack *origin, t_stack *des, int depth)
{
	t_evaluation	*evaluations;
	int				number;
	int				best_evaluation;
	size_t			position;
	size_t			origin_size;
	t_stack_element	*element;
	t_evaluation	temp1, temp2;
	
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
		/*printf("number: %d eval:", number);*/
		print_evaluation(temp1);
		/*execute_evaluation(origin, des, &temp1);*/
		if (depth > 0)
		{
			temp2 = evaluate(origin, des, depth - 1);
			evaluations[position] = join_evaluations(&evaluations[position], &temp2);
		}
		/*execute_evaluation_r(origin, des, &temp1);*/
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

	printf("[");
	for (i = 0; i < eval.m_Count; i++)
	{
		printf("%s;", g_InstructionNames[eval.m_Instructions[i]]);
	}
	printf("]\n");
}

void print_distance(const t_distance *distance)
{
	printf("(%zu, %zu)", distance->m_Up, distance->m_Down);
}
