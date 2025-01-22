#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "gc_io.h"
#include "movegen.h"

#define RANK_COUNT 8
#define FILE_COUNT 8

gc_graph_t* graph_fen_parse(const char* fen) {
    gc_graph_t* graph = gc_graph_new();

    int square_id = 0;
    while (*fen != '\0') {
        char c = *(fen++);
        if (c == ' ') {
            break;
        }

        if (c == '/') {
            continue;
        }

        if (isdigit(c)) {
            int empties = c - '0';
            for (int i = 0; i < empties; i++) {
                square_id++;
            }
        } else {
            gc_node_t node = {0};
            node.color = isupper(c) ? GC_NODE_COLOR_WHITE : GC_NODE_COLOR_BLACK;
            switch (c) {
                case 'r':
                case 'R':
                    node.piece = GC_PIECE_ROOK;
                    break;
                case 'b':
                case 'B':
                    node.piece = GC_PIECE_BISHOP;
                    break;
                case 'n':
                case 'N':
                    node.piece = GC_PIECE_KNIGHT;
                    break;
                case 'q':
                case 'Q':
                    node.piece = GC_PIECE_QUEEN;
                    break;
                case 'k':
                case 'K':
                    node.piece = GC_PIECE_KING;
                    break;
                case 'p':
                case 'P':
                    node.piece = GC_PIECE_PAWN;
                    break;
            }

            gc_graph_insert_node(graph, square_id, node);
            square_id++;
        }
    }

    return graph;
}

int main(int argc, const char** argv) {
    FILE* out_fp = stdout;

    if (argc != 2) {
        printf("Usage: %s <FEN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* fen = argv[1];

    gc_graph_t* graph = graph_fen_parse(fen);
    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        gc_node_color_t color = gc_graph_get_color(graph, id);
        gc_piece_t piece = gc_graph_get_piece(graph, id);

        if (piece == GC_PIECE_KNIGHT) {
            movegen_walk(graph, movegen_knight, color, id);
        }
    }

    gc_io_fprint(out_fp, graph);

    gc_graph_free(graph);

    return EXIT_SUCCESS;
}
