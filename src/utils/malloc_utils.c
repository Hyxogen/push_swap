#include "malloc_utils.h"

#include <stdlib.h>

void* ft_malloc(size_t size) {
	void* ret;

	ret = malloc(size);
	if (ret == NULL) {
		exit(EXIT_FAILURE);
		return (NULL);
	}
	return (ret);
}
