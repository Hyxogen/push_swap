#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "../instruction.h"
#include <sys/types.h>
#include <ft_stdbool.h>
#include "evaluation.h"


/**
 * Evaluates the best instructions to get from stack position from_pos to other stack position to_pos
 * 
 * TODO change this to get the best instructions to rotate a x times and b y times. There should probably be another functions that gets the best evualuation for an placement
 */
t_evaluation evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size);

#endif
