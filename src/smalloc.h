#ifndef SMALLOC_H
#define SMALLOC_H

#include <stddef.h>

/**
 * Allocate zeroed memory, assert not out of memory
 */
void* smalloc(size_t size);

#endif
