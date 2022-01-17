/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generator.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:37:52 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 12:02:10 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include "../instruction.h"

/*instr_count will contain the amount of generated instructions without extra*/
t_instruction	*generate_instructions(long a_mov, long b_mov,
					size_t extra, size_t *instr_count);

#endif
