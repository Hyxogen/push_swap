/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:21 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:21 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
#define SOLVER_H

# include "instruction.h"
# include <sys/types.h>

t_instruction	*solve(int *arr, size_t len, size_t *instrs);

#endif
