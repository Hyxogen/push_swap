#include "distance.h"

int cmp_dist(const t_distance *a, const t_distance *cmp)
{
	if ((a->m_Down + a->m_Up) < (cmp->m_Up + cmp->m_Down))
		return (-1);
	else if ((a->m_Down + a->m_Up) > (cmp->m_Up + cmp->m_Down))
		return (1);
	return (0);
}


t_distance subtract_dist(const t_distance *a, const t_distance *b) {
	t_distance ret;

	if (a->m_Up < b->m_Up)
		ret.m_Up = b->m_Up - a->m_Up;
	else
		ret.m_Up = a->m_Up - b->m_Up;
	if (a->m_Down < b->m_Down)
		ret.m_Down = b->m_Down - a->m_Down;
	else
		ret.m_Down = a->m_Down - b->m_Down;
	return (ret);
}

t_distance add_dist(const t_distance *a, const t_distance *b) {
	t_distance ret;

	ret.m_Up = a->m_Up + b->m_Down;
	ret.m_Down = a->m_Down + b->m_Down;
	return (ret);
}

t_distance get_distance_exact(size_t position, size_t size)
{
	t_distance	ret;

	ret.m_Up = position;
	ret.m_Down = size - position;
	return (ret);
}

t_distance optimal_dist(const t_distance *a) {
	t_distance	ret;

	ret.m_Up = 0;
	ret.m_Down = 0;
	if (a->m_Up < a->m_Down)
		ret.m_Up = ret.m_Up;
	else
		ret.m_Down = a->m_Down;
}
