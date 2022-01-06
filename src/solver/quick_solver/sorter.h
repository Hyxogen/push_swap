#ifndef SORTER_H
#define SORTER_H

#include "../instruction.h"
#include "../../int_deque.h"

t_instruction* rough_sort_optimized(t_ideque* from, t_ideque* to, t_instruction put_instr, const int* from_sorted, size_t block_size, size_t* instrs);

t_instruction* sort(t_ideque* from, t_ideque* to, t_instruction put_instr, size_t* instrs);

#endif
