#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "fen.h"
#include "gc.h"
#include "move.h"
#include "movegen.h"

// Shows number of hops to given square per opposite colored piece
int main(int argc, const char** argv) {
    FILE* out_fp = stdout;

    if (argc != 2) {
        printf("Usage: %s <FEN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* fen = argv[1];

    board_t* board = board_new(WHITE);
    fen_parse(fen, board);
    gc_graph_t* graph = gc_graph_new(board);

    movelist_t* moves = movelist_new();
    movegen(moves, board);

    // Add edges to graph
    gc_graph_insert_edges(graph, moves);

    gc_node_color_t perspective = GC_NODE_COLOR_BLACK;
    square_t center = SQUARE_COUNT;

    // Find our king
    for (gc_edge_t* edge = graph->edges; edge != NULL; edge = edge->next) {
        if ((board->squares[edge->a->id] == SQUARE_KING_BLACK &&
             perspective == GC_NODE_COLOR_BLACK) ||
            (board->squares[edge->a->id] == SQUARE_KING_WHITE &&
             perspective == GC_NODE_COLOR_WHITE)) {
            center = edge->a->id;
        }
    }

    assert(center < SQUARE_COUNT && "Enemy King Not Found");

    // Get squares around king
    board_t* sub_board = board_new(WHITE);

    // Populate king moves while board is empty.
    movelist_t* king_moves = movelist_new();
    movegen_king(king_moves, sub_board, center);

    // Populate the board with the opposite player's pieces
    for (gc_edge_t* edge = graph->edges; edge != NULL; edge = edge->next) {
        if (edge->a->color != perspective) {
            sub_board->squares[edge->a->id] = board->squares[edge->a->id];
        }
    }

    // Populate with our king
    sub_board->squares[center] = perspective == GC_NODE_COLOR_WHITE
                                     ? SQUARE_KING_WHITE
                                     : SQUARE_KING_BLACK;

    gc_graph_t* subgraph = gc_graph_new(sub_board);
    for (gc_edge_t* edge = graph->edges; edge != NULL; edge = edge->next) {
        // Does the edge threaten our zone?
        for (move_t* king_move = king_moves->head; king_move != NULL;
             king_move = king_move->next) {
            if (edge->b->id == king_move->from ||
                edge->b->id == king_move->to) {
                gc_graph_insert_edge(subgraph, edge->a->id, edge->b->id);
                break;
            }
        }
    }

    // Print graph
    gc_fprint_graph(out_fp, subgraph);

    // Free resources
    movelist_free(king_moves);
    movelist_free(moves);
    gc_graph_free(graph);
    board_free(board);
    board_free(sub_board);

    return EXIT_SUCCESS;
}
