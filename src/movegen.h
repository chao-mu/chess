#ifndef GC_SUBGRAPH_H
#define GC_SUBGRAPH_H

#include <stddef.h>
#include <stdio.h>

#include "gc.h"

// The max number of legal moves a single piece can make in a move
#define MOVEGEN_MAX_MOVES 32

// How deep to calculate
#define MOVEGEN_MAX_DEPTH 12

// Wildly pesimistic estimate of maximum todo count
#define MOVEGEN_TODO_CAPACITY 64 * 64

typedef struct todo_item {
    int from_file;
    int from_rank;
    int to_file;
    int to_rank;
    int depth;  //  required jumps to reach from_file/rank
} todo_item_t;

typedef struct todo {
    todo_item_t items[MOVEGEN_TODO_CAPACITY];
    size_t size;
} todo_t;

typedef void (*movegen_t)(gc_graph_t* graph, gc_node_color_t color,
                          todo_t* todo, int rank, int file, int depth);

void movegen_walk(gc_graph_t* graph, movegen_t movegen, gc_node_color_t color,
                  uint8_t square_from);

void movegen_queen(gc_graph_t* graph, gc_node_color_t color, todo_t* todo,
                   int file, int rank, int depth);

void movegen_knight(gc_graph_t* graph, gc_node_color_t color, todo_t* todo,
                    int file, int rank, int depth);

void movegen_rook(gc_graph_t* graph, gc_node_color_t color, todo_t* todo,
                  int file, int rank, int depth);

void movegen_bishop(gc_graph_t* graph, gc_node_color_t color, todo_t* todo,
                    int file, int rank, int depth);

void movegen_king(gc_graph_t* graph, gc_node_color_t color, todo_t* todo,
                  int file, int rank, int depth);

#endif
