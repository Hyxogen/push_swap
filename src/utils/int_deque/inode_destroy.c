/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inode_destroy.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:37 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:36:37 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "inode.h"

#include <stdlib.h>

void
	inode_destroy(t_inode *node)
{
	free(node);
}
