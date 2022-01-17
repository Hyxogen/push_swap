/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quick_solver_utils.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:43 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:55:59 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUICK_SOLVER_UTILS_H
# define QUICK_SOLVER_UTILS_H

# include <sys/types.h>

size_t			quick_get_rough_sorted_pos(int val, t_ideque *deque);
size_t			quick_get_full_sorted_pos(int val, t_ideque *deque);

size_t			_quick_get_full_sorted_pos(int val,
					const t_inode *current, const t_inode *previous);
t_instruction	*_quick_rough_sort_block(t_ps_object *object,
					int min, int max, size_t *instr_count);
t_instruction	*_quick_full_sort_block(t_ps_object *object,
					int min, int max, size_t *instr_count);

#endif
