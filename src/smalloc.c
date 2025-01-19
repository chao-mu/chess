#include "smalloc.h"

#include <assert.h>
#include <stdlib.h>

void* smalloc(size_t size) {
    void* ptr = calloc(1, size);
    assert(ptr != NULL && "Out of Memory");

    return ptr;
}
