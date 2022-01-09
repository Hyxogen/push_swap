#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "distance.h"
#include <sys/types.h>

t_distance	evaluate(size_t from_pos, size_t from_size, size_t to_pos, size_t to_size);

#endif
