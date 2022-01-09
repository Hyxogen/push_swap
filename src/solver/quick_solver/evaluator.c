#include "evaluator.h"
#include "../../utils/vector2.h"
#include "../../utils/malloc_utils.h"
#include <limits.h>
#include <ft_stdlib.h>
#include <ft_math.h>


/*TODO replace size_t with long in the entire project*/
static t_distance
	evaluator_get_distance_up(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size)
{
	t_distance	distance;

	(void)from_size;
	(void)to_size;
	distance.m_left_dist = (long)from_pos;
	distance.m_right_dist = (long)to_pos;
	return (distance);
}

static t_distance
	evaluator_get_distance_down(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size)
{
	t_distance	distance;

	distance.m_left_dist = -((long)(from_size - from_pos));
	distance.m_right_dist = -((long)(to_size - to_pos));
	return (distance);
}

static t_distance
	evaluator_get_distance_ex(const t_distance *up_distance, const t_distance *down_distance)
{
	t_distance	distance;

	if (up_distance->m_left_dist < ft_labs(down_distance->m_left_dist))
		distance.m_left_dist = up_distance->m_left_dist;
	else
		distance.m_left_dist = down_distance->m_left_dist;

	if (up_distance->m_right_dist < ft_labs(down_distance->m_right_dist))
		distance.m_right_dist = up_distance->m_right_dist;
	else
		distance.m_right_dist = down_distance->m_right_dist;
	return (distance);
}

t_distance
	evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size)
{
	t_distance	 up_distance;
	t_distance	 down_distance;
	t_distance	 ex_distance;

	up_distance = evaluator_get_distance_up(from_pos, from_size, to_pos, to_size);
	down_distance = evaluator_get_distance_down(from_pos, from_size, to_pos, to_size);
	ex_distance = evaluator_get_distance_ex(&up_distance, &down_distance);

	if (distance_cmp(&up_distance, &down_distance) < 0 &&
		distance_cmp(&up_distance, &ex_distance) < 0)
		return (up_distance);
	if (distance_cmp(&down_distance, &ex_distance) < 0)
		return (down_distance);
	return (ex_distance);
}
