#ifndef SORTER_UTILS_H
#define SORTER_UTILS_H

#include "sorter.h"
#include "distance.h"
#include <sys/types.h>

ft_bool			sort_info_applies(const t_sort_info *info, int val);

long			_sorter_get_position(int val, const t_sort_info *sort_info);
t_distance		_sorter_get_distance(size_t left_pos, size_t left_size, size_t right_pos, size_t right_size);
t_instruction	 *_sorter_generate_put(const t_sort_info *info, const t_distance *distance, size_t *instr_count);
t_instruction	 *_sorter_put(t_sort_info *info, const t_distance *distance, size_t *instr_count);

#endif
