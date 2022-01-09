#include "distance.h"

#include <ft_stdlib.h>
#include <ft_math.h>

int distance_cmp(const t_distance *a, const t_distance *cmp)
{
	size_t a_len;
	size_t cmp_len;

	a_len = distance_get_len(a);
	cmp_len = distance_get_len(cmp);
	if (a_len < cmp_len)
		return (-1);
	else if (a_len > cmp_len)
		return (1);
	return (0);
}

size_t distance_get_len(const t_distance *distance)
{
	long left_mov;
	long right_mov;

	left_mov = distance->m_left_dist;
	right_mov = distance->m_right_dist;

	if ((left_mov <= 0 && right_mov >= 0) || (right_mov <= 0 && left_mov >= 0))
		return (ft_labs(left_mov) + ft_labs(right_mov));
	else if (left_mov > 0)
		return (ft_lmax(left_mov, right_mov));
	return (ft_labs(ft_lmin(left_mov, right_mov)));
}
