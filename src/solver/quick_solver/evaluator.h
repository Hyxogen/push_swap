#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "../instruction.h"
#include <ft_stdbool.h>

typedef struct s_evaluation {
	size_t m_Count;
	t_instruction* m_Instructions;
}	t_evaluation;

/**
 * Evaluates the best instructions to get from stack position from_pos to other stack position to_pos
 */
t_evaluation evaluate(size_t from_pos, size_t to_pos);

t_evaluation worst_evaluation();

int evaluation_cmp(const t_evaluation* a, const t_evaluation* b);

#endif
