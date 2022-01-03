#ifndef SORTER_H
#define SORTER_H

#include "../instruction.h"

t_instruction* rough_sort_optimized(t_stack* from, t_stack* to, t_instruction put_instr, const int* from_sorted, size_t block_size, size_t* instrs);

size_t get_sorted_pos(t_stack* stack, int i);

t_instruction* sort(t_stack* from, t_stack* to, t_instruction put_instr, size_t* instrs);

#endif
