/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 11:02:42 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 16:03:42 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
# define EVALUATOR_H

# include "../ps_object.h"
# include <sys/types.h>

typedef struct s_evaluation {
	size_t	m_Count;
	int		*m_Instructions;
}	t_evaluation;

typedef struct s_distance {
	size_t	m_Up;
	size_t	m_Down;
}	t_distance;

const static char *g_InstructionNames[] = {
	"empty",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"sa",
	"sb",
	"ss",
	"rra",
	"rrb",
	"rrr",
	NULL	
};

enum instruction {
	ips_empty,
	ips_pa,
	ips_pb,
	ips_ra,
	ips_rb,
	ips_rr,
	ips_sa,
	ips_sb,
	ips_ss,
	ips_rra,
	ips_rrb,
	ips_rrr
};

const static t_evaluation g_EmptyEval = { 0, (void*) 0};

/*
Makkelijke manier om reverse instructie uit te voeren


0
2
3

rra rrb pb kan beter met dat de vorige instructe een sa was
*/

int ft_abs(int num);

t_distance get_distance_exact(size_t position, size_t size);
t_distance get_distance(const t_stack *stack, int number);

int cmp_distance(const t_distance *a, const t_distance *cmp);

size_t get_position(const t_stack *stack, int number);
/*
void execute_instruction(t_stack *a, t_stack *b, int instruction);
void execute_instruction_r(t_stack *a, t_stack *b, int instruction);
*/

void execute_evaluation(t_stack *a, t_stack *b, const t_evaluation *eval);
void execute_evaluation_r(t_stack *a, t_stack *b, const t_evaluation *eval);

t_evaluation	generate_instructions_internal(t_distance a, t_distance b);
t_evaluation	join_evaluations(const t_evaluation *a, const t_evaluation *b);

t_evaluation	generate_instructions(const t_distance *a, const t_distance *b);
t_evaluation	evaluate_single_exact(t_stack *origin, t_stack *des, int num, size_t position, size_t size);
t_evaluation	evaluate_single(t_stack *origin, t_stack *des, int number);
t_evaluation	evaluate(t_stack *origin, t_stack *des, int depth);

int	cmp_evaluation(const t_evaluation *a, const t_evaluation *comp);

void print_evaluation(t_evaluation eval);
void print_distance(const t_distance *distance);

#endif
