/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   int_deque.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:28 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_DEQUE_H
# define INT_DEQUE_H

# include "inode.h"
# include <sys/types.h>
# include <ft_stdbool.h>

typedef struct s_deque
{
	t_inode	*m_front;
	t_inode	*m_back;
	size_t	m_size;
}	t_ideque;

void		ideque_init(t_ideque *deque, t_inode *front,
				t_inode *back, size_t size);
void		ideque_destroy(t_ideque *deque, t_bool free_self);

/*MALLOC SAFE*/
t_ideque	*ideque_create_empty(void);

t_bool		ideque_is_empty(const t_ideque *deque);
size_t		ideque_get_size(const t_ideque *deque);

void		ideque_push_back(t_ideque *deque, t_inode *node);
void		ideque_push_front(t_ideque *deque, t_inode *node);

/*Undefined behavior when popping empty ideque*/
t_inode		*ideque_pop_back(t_ideque *deque);
/*Undefined behavior when popping empty ideque*/
t_inode		*ideque_pop_front(t_ideque *deque);

t_inode		*ideque_back(const t_ideque *deque);
t_inode		*ideque_front(const t_ideque *deque);

t_bool		ideque_is_sorted(const t_ideque *deque);

void		ideque_rotate(t_ideque *deque, int val);
#endif
