#ifndef DISTANCE_H
#define DISTANCE_H

# include <sys/types.h>

typedef struct s_distance
{
	long m_left_dist;
	long m_right_dist;
}	t_distance;

int		distance_cmp(const t_distance *a, const t_distance *cmp);
size_t	distance_get_len(const t_distance *disance);

#endif
