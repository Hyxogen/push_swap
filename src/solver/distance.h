#ifndef DISTANCE_H
#define DISTANCE_H

#include <sys/types.h>
#include "../stack.h"

typedef struct s_distance {
	size_t	m_Up;
	size_t	m_Down;
}	t_distance;

int cmp_dist(const t_distance *a, const t_distance *cmp);

t_distance subtract_dist(const t_distance *a, const t_distance *b);
t_distance add_dist(const t_distance *a, const t_distance *b);

t_distance get_distance_exact(size_t position, size_t size);
t_distance get_distance(const t_stack *stack, int number);

void get_abs_difference(const t_distance *a, const t_distance *b, t_distance *out);

#endif
