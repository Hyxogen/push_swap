#ifndef QUICK_SOLVER_UTILS_H
#define QUICK_SOLVER_UTILS_H

# include <sys/types.h>

size_t			 quick_get_rough_sorted_pos(int val, t_ideque *deque);
size_t			 quick_get_full_sorted_pos(int val, t_ideque *deque);

size_t			 _quick_get_full_sorted_pos(int val, const t_inode *current, const t_inode *previous);
t_instruction	 *_quick_rough_sort_block(t_ps_object *object, int min, int max, size_t *instr_count);
t_instruction	 *_quick_full_sort_block(t_ps_object *object, int min, int max, size_t *instr_count);

#endif
