/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   distance.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:20 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:38:20 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
