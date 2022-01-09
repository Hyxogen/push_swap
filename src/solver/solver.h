#ifndef SOLVER_H
#define SOLVER_H

# include "instruction.h"
# include <sys/types.h>

t_instruction	*solve(int *arr, size_t len, size_t *instrs);

#endif
