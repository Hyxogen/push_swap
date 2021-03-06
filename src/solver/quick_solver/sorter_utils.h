/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sorter_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:36 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTER_UTILS_H
# define SORTER_UTILS_H

# include "sorter.h"
# include "distance.h"
# include <sys/types.h>

t_bool			sort_info_applies(const t_sort_info *info, int val);

long			_sorter_get_position(int val, const t_sort_info *sort_info);
t_distance		_sorter_get_distance(size_t left_pos,
					size_t left_size, size_t right_pos, size_t right_size);
t_instruction	*_sorter_generate_put(const t_sort_info *info,
					const t_distance *distance, size_t *instr_count);
t_instruction	*_sorter_put(t_sort_info *info,
					const t_distance *distance, size_t *instr_count);

#endif
