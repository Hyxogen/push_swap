#ifndef SORTER_H
#define SORTER_H

#include "../instruction.h"

t_instruction* rough_sort_optimized(t_stack* from, t_stack* to, int* from_sorted, size_t block_size, size_t* instrs);

t_instruction* sort(t_stack* from, t_stack* to, size_t* instrs);

#endif
