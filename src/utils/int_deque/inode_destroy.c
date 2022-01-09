#include "inode.h"

#include <stdlib.h>

void
	inode_destroy(t_inode *node)
{
	free(node);
}
