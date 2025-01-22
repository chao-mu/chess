#include "gc_io.h"

#include <stdio.h>

#include "gc.h"
#include "movegen.h"
#include "square.h"

const char* gc_io_get_piece_symbol(gc_node_color_t color, gc_piece_t piece) {
    switch (piece) {
        case GC_PIECE_ROOK:
            return color == GC_NODE_COLOR_BLACK ? "♖" : "♜";
        case GC_PIECE_BISHOP:
            return color == GC_NODE_COLOR_BLACK ? "♗" : "♝";
        case GC_PIECE_KNIGHT:
            return color == GC_NODE_COLOR_BLACK ? "♘" : "♞";
        case GC_PIECE_QUEEN:
            return color == GC_NODE_COLOR_BLACK ? "♕" : "♛";
        case GC_PIECE_KING:
            return color == GC_NODE_COLOR_BLACK ? "♔" : "♚";
        case GC_PIECE_PAWN:
            return color == GC_NODE_COLOR_BLACK ? "♙" : "♟";
        case GC_PIECE_NONE:
            return "";
    }
}

void gc_io_fprint(FILE* out_fp, gc_graph_t* graph) {
    fprintf(out_fp, "digraph {\n");
    fprintf(out_fp, "\tlayout=\"fdp\";\n");
    fprintf(out_fp, "\toverlap=\"prism\";\n");
    fprintf(out_fp, "\tsep=\"1\";\n");

    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        for (gc_edge_t* edge = graph->edges[id]; edge != NULL;
             edge = edge->next) {
            if (edge->weight < MOVEGEN_MAX_DEPTH) {
                fprintf(out_fp, "\t%d -> %d [label=\"%d\"]\n", edge->from_id,
                        edge->to_id, edge->weight);
            }
        }
    }

    for (size_t rank = 0; rank < SQUARE_RANK_COUNT; rank++) {
        for (size_t file = 0; file < SQUARE_FILE_COUNT; file++) {
            square_t id = square_from(file, rank);
            gc_node_color_t color = gc_graph_get_color(graph, id);
            gc_piece_t piece = gc_graph_get_piece(graph, id);
            const char* sep = "";
            if (piece != GC_PIECE_NONE) {
                sep = " ";
            }

            const char* piece_symbol = gc_io_get_piece_symbol(color, piece);

            fprintf(out_fp, "%d [label=\"%s%s%c%c\"]\n", id, piece_symbol, sep,
                    square_getc_file(id), square_getc_rank(id));
        }
    }

    fprintf(out_fp, "}\n");
}
