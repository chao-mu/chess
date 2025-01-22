#ifndef GC_IO_H
#define GC_IO_H

#include <stdio.h>

#include "gc.h"

// Writes graph to file handle in the DOT format. Exclusively meant for
// debugging.
void gc_io_fprint(FILE *out_fp, gc_graph_t *graph);

#endif
