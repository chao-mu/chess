#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "gc_io.h"
#include "movegen.h"
#include "square.h"

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

    square_t center = SQUARE_E1;

    gc_graph_t* graph = graph_fen_parse(fen);
    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        gc_node_color_t color = gc_graph_get_color(graph, id);
        gc_piece_t piece = gc_graph_get_piece(graph, id);

        switch (piece) {
            case GC_PIECE_KNIGHT:
                // printf("Walkgen for knight %d %d\n", color, id);
                movegen_walk(graph, movegen_knight, color, id);
                break;
            case GC_PIECE_QUEEN:
                // printf("Walkgen for queen %d %d\n", color, id);
                movegen_walk(graph, movegen_queen, color, id);
                break;
            case GC_PIECE_ROOK:
                // printf("Walkgen for rook %d %d\n", color, id);
                movegen_walk(graph, movegen_rook, color, id);
                break;
            case GC_PIECE_BISHOP:
                // printf("Walkgen for bishop %d %d\n", color, id);
                movegen_walk(graph, movegen_bishop, color, id);
                break;
            case GC_PIECE_KING:
                // printf("Walkgen for king %d %d\n", color, id);
                movegen_walk(graph, movegen_king, color, id);
                break;
            case GC_PIECE_NONE:
                break;
        }
    }

    gc_graph_t* subgraph = graph_fen_parse(fen);
    for (gc_edge_t* edge = graph->edges_reverse[center]; edge != NULL;
         edge = edge->next) {
        uint8_t from_id = edge->from_id;
        uint8_t to_id = edge->to_id;
        int weight = edge->weight;
        gc_node_color_t from_color = gc_graph_get_color(graph, edge->from_id);
        gc_node_color_t to_color = gc_graph_get_color(graph, edge->to_id);

        if (from_color != to_color) {
            gc_graph_insert_edge(subgraph, from_id, to_id, weight);
        }
    }

    gc_io_fprint(out_fp, subgraph);

    gc_graph_free(graph);

    return EXIT_SUCCESS;
}
