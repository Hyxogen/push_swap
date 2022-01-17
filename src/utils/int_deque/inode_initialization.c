/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inode_initialization.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:34 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:36:34 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inode.h"

#include "../malloc_utils.h"
#include <stddef.h>

void
	inode_init(t_inode *node, t_inode *tail, t_inode *head, int val)
{
	node->m_tail = tail;
	node->m_head = head;
	node->m_content = val;
}

t_inode
	*inode_create(int val)
{
	t_inode	*node;

	node = ft_safe_malloc(sizeof(t_inode));
	inode_init(node, NULL, NULL, val);
	return (node);
}
