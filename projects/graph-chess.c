#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fen.h"
#include "gc.h"
#include "gc_io.h"
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

    gc_graph_t* graph = fen_parse(fen);
    movegen_all(graph);

    gc_graph_t* subgraph = fen_parse(fen);
    for (uint8_t from_id = 0; from_id < GC_GRAPH_NODES; from_id++) {
        for (gc_edge_t* edge = graph->edges[from_id]; edge != NULL;
             edge = edge->next) {
            int weight = edge->weight;
            if (weight != 1) {
                continue;
            }

            uint8_t to_id = edge->to_id;
            gc_piece_t from_piece = gc_graph_get_piece(graph, from_id);
            gc_piece_t to_piece = gc_graph_get_piece(graph, to_id);
            gc_node_color_t from_color = gc_graph_get_color(graph, from_id);
            gc_node_color_t to_color = gc_graph_get_color(graph, to_id);

            //  Feature: Attack only
            // if (from_color != to_color) {
            //    continue;
            //}

            if (from_piece == GC_PIECE_PAWN || from_piece == GC_PIECE_NONE ||
                to_piece == GC_PIECE_NONE) {
                continue;
            }

            gc_graph_insert_edge(subgraph, from_id, to_id, weight);
        }
    }

    gc_io_fprint(out_fp, subgraph);

    gc_graph_free(graph);

    return EXIT_SUCCESS;
}
