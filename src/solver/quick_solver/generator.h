#ifndef GENERATOR_H

#include "../instruction.h"
#include "evaluation.h"

/**
 * DEPRECATED
 */
t_instruction* generate_instructions(long a_mov, long b_mov, size_t extra, size_t* count);

t_instruction* generate_instructions_e(const t_evaluation* eval, size_t extra);

#endif
