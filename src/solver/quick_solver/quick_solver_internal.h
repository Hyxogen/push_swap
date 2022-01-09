#ifndef QUICK_SOLVER_INTERNAL_H
#define QUICK_SOLVER_INTERNAL_H

# include "../instruction.h"
# include "../../ps_object.h"

t_instruction	*_quick_solve(t_ps_object *object, const int *arr, size_t len, size_t *instr_count);

#endif
