#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fen.h"
#include "gc.h"
#include "movegen.h"

#define RANK_COUNT 8
#define FILE_COUNT 8

int main(int argc, const char** argv) {
    FILE* out_fp = stdout;

    if (argc != 2) {
        printf("Usage: %s <FEN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* fen = argv[1];

    uint8_t white_king_id = GC_GRAPH_NODES;
    uint8_t black_king_id = GC_GRAPH_NODES;

    gc_graph_t* graph = fen_parse(fen);
    movegen_all(graph);

    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        gc_node_color_t color = gc_graph_get_color(graph, id);
        gc_piece_t piece = gc_graph_get_piece(graph, id);

        switch (piece) {
            case GC_PIECE_KING:
                if (color == GC_NODE_COLOR_WHITE) {
                    white_king_id = id;
                } else if (color == GC_NODE_COLOR_BLACK) {
                    black_king_id = id;
                }

                // printf("Walkgen for king %d %d\n", color, id);
                movegen_walk(graph, movegen_king, color, id);
                break;
            default:
                break;
        }
    }

    assert(white_king_id != GC_GRAPH_NODES && "White king not found");
    assert(black_king_id != GC_GRAPH_NODES && "Black king not found");

    return EXIT_SUCCESS;
}
