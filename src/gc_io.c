#include "gc_io.h"

#include <stdio.h>

#include "gc.h"
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

const char* get_edge_color(gc_graph_t* graph, gc_edge_t* edge) {
    gc_node_color_t from_color = gc_graph_get_color(graph, edge->from_id);
    gc_node_color_t to_color = gc_graph_get_color(graph, edge->to_id);

    if (from_color == to_color) {
        return "green";
    } else if (from_color != GC_NODE_COLOR_EMPTY &&
               to_color != GC_NODE_COLOR_EMPTY) {
        return "red";
    } else {
        return "black";
    }
}

void gc_io_fprint(FILE* out_fp, gc_graph_t* graph) {
    fprintf(out_fp, "digraph {\n");

    // Good for showing defense?
    // fprintf(out_fp, "\tlayout=\"circo\";\n");

    fprintf(out_fp, "\toverlap=false;\n");

    bool from_seen[GC_GRAPH_NODES] = {false};
    bool to_seen[GC_GRAPH_NODES] = {false};
    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        for (gc_edge_t* edge = graph->edges[id]; edge != NULL;
             edge = edge->next) {
            from_seen[edge->from_id] = true;
            to_seen[edge->to_id] = true;
            const char* color = get_edge_color(graph, edge);
            if (edge->weight != 1) {
                fprintf(out_fp, "\t%d -> %d [label=\"%d\" color=\"%s\"]\n",
                        edge->from_id, edge->to_id, edge->weight, color);
            } else {
                fprintf(out_fp, "\t%d -> %d [color=\"%s\"]\n", edge->from_id,
                        edge->to_id, color);
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

            // Feature - Exclude unseen nodes
            if (!from_seen[id] && !to_seen[id]) {
                continue;
            }

            const char* piece_symbol = gc_io_get_piece_symbol(color, piece);
            fprintf(out_fp, "\t%d [label=\"%s%s%c%c\"]\n", id, piece_symbol,
                    sep, square_getc_file(id), square_getc_rank(id));
        }
    }

    fprintf(out_fp, "}\n");
}
