#ifndef GC_H
#define GC_H

#include <stdbool.h>
#include <stdint.h>

#define GC_GRAPH_NODES 64
#define GC_RANK_COUNT 8
#define GC_FILE_COUNT 8

/**
 * Represents the chess pieces independent of color. A special piece
"GC_PIECE_NONE"
 * is included to indicate an empty square on the board.
 */
typedef enum gc_piece {
    GC_PIECE_NONE = 0,
    GC_PIECE_ROOK,
    GC_PIECE_BISHOP,
    GC_PIECE_KNIGHT,
    GC_PIECE_QUEEN,
    GC_PIECE_KING,
    GC_PIECE_PAWN,
} gc_piece_t;

typedef enum gc_node_color {
    GC_NODE_COLOR_EMPTY = 0,
    GC_NODE_COLOR_BLACK,
    GC_NODE_COLOR_WHITE,
} gc_node_color_t;

typedef struct gc_node {
    gc_node_color_t color;
    gc_piece_t piece;
} gc_node_t;

typedef struct gc_edge {
    uint8_t from_id;
    uint8_t to_id;
    int weight;
    struct gc_edge *next;
} gc_edge_t;

/**
 * Represents a weighted, directed graph of 64 nodes
 * each having a color of black, white, or empty.
 */
typedef struct gc_graph {
    gc_node_t *nodes[GC_GRAPH_NODES];
    gc_edge_t *edges[GC_GRAPH_NODES];
    gc_edge_t *edges_reverse[GC_GRAPH_NODES];
    int weights[GC_GRAPH_NODES][GC_GRAPH_NODES];
    bool edge_exists[GC_GRAPH_NODES][GC_GRAPH_NODES];
} gc_graph_t;

/**
 * Constructs a graph suitable for representing a chessboard
 */
gc_graph_t *gc_graph_new(void);

/**
 * Frees the graph along with its edges and nodes.
 */
void gc_graph_free(gc_graph_t *graph);

/**
 * Insert an edge into the graph with the given weight.
 */
void gc_graph_insert_edge(gc_graph_t *graph, uint8_t from_id, uint8_t to_id,
                          int weight);

/**
 * Insert a node of the given description into the graph.
 * If there is an existing node, that node is de-allocated and replaced
 */
void gc_graph_insert_node(gc_graph_t *graph, uint8_t node_id, gc_node_t node);

/**
 * Get the node's color at the given position. asserts node_id is not out of
 * bounds.
 */
gc_node_color_t gc_graph_get_color(gc_graph_t *graph, uint8_t node_id);

/**
 * Get the node's piece at the given position. asserts node_id is not out of
 * bounds.
 */
gc_piece_t gc_graph_get_piece(gc_graph_t *graph, uint8_t node_id);

#endif
