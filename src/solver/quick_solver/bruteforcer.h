/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bruteforcer.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:38:26 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 12:04:30 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRUTEFORCER_H
# define BRUTEFORCER_H

# include "../instruction.h"

t_instruction	*brute_force(t_ps_object *object,
					int depth, size_t *instr_count);

#endif
