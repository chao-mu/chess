#include <stdlib.h>
#include <string.h>

#include "fen.h"
#include "gc.h"
#include "square.h"
#include "test.h"

int main(void) {
    test_start("fen.h");

    const char* fen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    gc_graph_t* graph = fen_parse(fen);

    // Kings on their rightful squares and of the rightful color.
    assert_true(gc_graph_get_piece(graph, SQUARE_E1) == GC_PIECE_KING);
    assert_true(gc_graph_get_color(graph, SQUARE_E1) == GC_NODE_COLOR_WHITE);
    assert_true(gc_graph_get_piece(graph, SQUARE_E8) == GC_PIECE_KING);
    assert_true(gc_graph_get_color(graph, SQUARE_E8) == GC_NODE_COLOR_BLACK);

    // Convert back to FEN and compare
    char* built_fen = NULL;
    fen_build(graph, &built_fen);
    assert_true(strcmp(fen, built_fen) == 0);
    free(built_fen);

    gc_graph_free(graph);

    test_end();
}
