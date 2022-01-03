#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "../instruction.h"
#include <sys/types.h>
#include <ft_stdbool.h>
#include "evaluation.h"


/**
 * Evaluates the best instructions to get from stack position from_pos to other stack position to_pos
 */
t_evaluation evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size, t_instruction put_instr);

t_evaluation worst_evaluation();
#endif
