#ifndef FEN_H
#define FEN_H

#include "gc.h"

void fen_build(gc_graph_t* graph, char** fen_out);
gc_graph_t* fen_parse(const char* fen);
#endif
