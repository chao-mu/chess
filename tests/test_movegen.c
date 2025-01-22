#include <stdint.h>
#include <stdio.h>

#include "gc.h"
#include "gc_io.h"
#include "movegen.h"
#include "square.h"
#include "test.h"

//  From starting square in bottom right.
static int expected_knight_weights[GC_GRAPH_NODES] = {
    // A8 .. H8
    5, 4, 5, 4, 5, 4, 5, 4,
    // A7 ..
    4, 5, 4, 3, 4, 3, 4, 3,
    // A6 ..
    5, 4, 3, 4, 3, 4, 3, 4,
    // A5 ..
    4, 3, 4, 3, 2, 3, 2, 3,
    // A4 ..
    3, 4, 3, 2, 3, 2, 3, 2,
    // A3 ..
    4, 3, 2, 3, 4, 1, 2, 1,
    // A2 ..
    3, 4, 3, 2, 1, 2, 3, 2,
    // A1 ..
    4, 3, 2, 3, 2, 3, 0, 3};

void assert_weights(gc_graph_t* graph, uint8_t from_id,
                    int expected[GC_GRAPH_NODES]) {
    gc_edge_t* edges = graph->edges[from_id];
    assert_true(edges != NULL);

    int edge_count = 0;
    // Iterate and assert
    for (gc_edge_t* edge = edges; edge != NULL; edge = edge->next) {
        edge_count++;
        uint8_t to_id = edge->to_id;
        assert_true(expected[to_id] == edge->weight);
    }

    assert_true(edge_count == GC_GRAPH_NODES);
}

void assert_knight_walk(void) {
    gc_graph_t* graph = gc_graph_new();

    uint8_t from_id = SQUARE_G1;
    movegen_walk(graph, movegen_knight, GC_NODE_COLOR_WHITE, from_id);

    assert_weights(graph, from_id, expected_knight_weights);

    gc_graph_free(graph);
}

int main(void) {
    test_start("movegen.h");

    assert_knight_walk();

    test_end();

    return 0;
}
