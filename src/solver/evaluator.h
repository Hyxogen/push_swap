#ifndef EVALUATOR_H
# define EVALUATOR_H

# include "../ps_object.h"

typedef struct s_distance {
	size_t	m_Up;
	size_t	m_Down;
}	t_distance;

typedef struct s_distance_pair {
	t_distance	m_ADis;
	t_distance	m_BDis;
	t_distance	m_TDis;
}	t_distance_pair;

/*returns number that should be sorted next*/
t_distance_pair evaluate(t_stack *origin, t_stack *des);

/*returns number that should be sorted next*/
t_distance_pair evaluate_ps(t_ps_object *object);

#endif
