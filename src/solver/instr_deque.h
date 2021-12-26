#ifndef DEQUE_H
#define DEQUE_H

#include "../../utils/dlinked_list.h"
#include "instruction.h"
#include <ft_stdbool.h>

typedef struct s_instr_deque {
	t_dlinked_list* m_Front;
	t_dlinked_list* m_Back;
}	t_instr_deque;

void deque_init(t_instr_deque* deque);
void deque_destroy(t_instr_deque* deque, ft_bool free_self);

int deque_pop_front(t_instr_deque* deque);
int deque_pop_back(t_instr_deque* deque);

void deque_push_front(t_instr_deque* deque, t_instruction instr);
void deque_push_back(t_instr_deque* deque, t_instruction instr);

void deque_push_front_arr(t_instr_deque* deque, t_instruction* arr, size_t count);
void deque_push_back_arr(t_instr_deque* deque, t_instruction* arr, size_t count);

void deque_append_front(t_instruction* deque, const t_instr_deque* to_append);
void deque_append_back(t_instruction* deque, const t_instr_deque* to_append);

t_instruction* deque_join_all(const t_instr_deque* deque);

#endif
