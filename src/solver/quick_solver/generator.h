#ifndef GENERATOR_H
#define GENERATOR_H

# include "../instruction.h"

/*instr_count will contain the amount of generated instructions without extra*/
t_instruction	*generate_instructions(long a_mov, long b_mov, size_t extra, size_t *instr_count);

#endif
