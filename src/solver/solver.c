/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:56:44 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 10:33:37 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"
#include "evaluator.h"

typedef struct s_move {
	size_t	m_AUp;
	size_t	m_ADown;
	size_t	m_BUp;
	size_t	m_BDown;
}	t_move;

static t_move generate_move(const t_distance_pair *pair)
{
	t_move	ret;

	ret.m_ADown = 0;
	ret.m_BDown = 0;
	ret.m_AUp = 0;
	ret.m_BUp = 0;
	if (pair->m_TDis.m_Down < pair->m_TDis.m_Up)
	{
		ret.m_ADown = pair->m_ADis.m_Down;
		ret.m_BDown = pair->m_BDis.m_Down;
	}
	else
	{
		ret.m_AUp = pair->m_ADis.m_Up;
		ret.m_BUp = pair->m_BDis.m_Up;
	}
	return (ret);
}

void execute_next_move(t_ps_object *object)
{
	t_move			next_move;
	t_distance_pair	pair;
	
	pair = evaluate_ps(object);
	next_move = generate_move(&pair);
	printf("Aup=%zu Adown=%zu ", next_move.m_AUp, next_move.m_ADown);
	printf("Bup=%zu Bdown=%zu\n", next_move.m_BUp, next_move.m_BDown);
	if (next_move.m_AUp && next_move.m_BUp)
	{
		next_move.m_AUp--;
		next_move.m_BUp--;
		printf("rrr\n");
	}
	else if (next_move.m_AUp)
	{
		next_move.m_AUp--;
		printf("rra\n");
	}
	else if (next_move.m_BUp)
	{
		next_move.m_AUp--;
		printf("rrb\n");
	}
	else if (next_move.m_ADown && next_move.m_BDown)
	{
		next_move.m_ADown--;
		next_move.m_BDown--;
		printf("rr\n");
	}
	else if (next_move.m_ADown)
	{
		next_move.m_ADown--;
		printf("ra\n");
	}
	else if (next_move.m_BDown)
	{
		next_move.m_BDown--;
		printf("rb\n");
	}
	else
		printf("pb\n");
}

void
	solve_ps(t_ps_object *object)
{
	t_move			next_move;
	t_distance_pair	pair;

	while (object->m_StackA->m_Top)
	{
		pair = evaluate_ps(object);
		next_move = generate_move(&pair);
		while (next_move.m_AUp && next_move.m_BUp)
		{
			ps_rrr(object);
			next_move.m_AUp--;
			next_move.m_BUp--;
			printf("rrr\n");
		}
		while (next_move.m_AUp)
		{
			ps_rra(object);
			next_move.m_AUp--;
			printf("rra\n");
		}
		while (next_move.m_BUp)
		{
			ps_rrb(object);
			next_move.m_BUp--;
			printf("rrb\n");
		}
		while (next_move.m_ADown && next_move.m_BDown)
		{
			ps_rr(object);
			next_move.m_ADown--;
			next_move.m_BDown--;
			printf("rr\n");
		}
		while (next_move.m_ADown)
		{
			ps_ra(object);
			next_move.m_ADown--;
			printf("ra\n");
		}
		while (next_move.m_BDown)
		{
			ps_rb(object);
			next_move.m_BDown--;
			printf("rb\n");
		}
		ps_pb(object);
		printf("pb\n");
	}
}
