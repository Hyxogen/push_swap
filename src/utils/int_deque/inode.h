/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inode.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:45:07 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INODE_H
# define INODE_H

typedef struct s_inode
{
	struct s_inode	*m_tail;
	struct s_inode	*m_head;
	int				m_content;
}	t_inode;

void	inode_init(t_inode *node, t_inode *tail, t_inode *head, int val);
void	inode_destroy(t_inode *node);

/*MALLOC SAFE*/
t_inode	*inode_create(int val);

#endif
