/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:57 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:37:57 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
#define EVALUATOR_H

# include "distance.h"
# include <sys/types.h>

t_distance	evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size);

#endif
