#include "fen.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "gc.h"
#include "smalloc.h"
#include "square.h"

char from_piece(gc_piece_t piece, gc_node_color_t color) {
    switch (piece) {
        case GC_PIECE_PAWN:
            return color == GC_NODE_COLOR_BLACK ? 'p' : 'P';
        case GC_PIECE_KNIGHT:
            return color == GC_NODE_COLOR_BLACK ? 'n' : 'N';
        case GC_PIECE_BISHOP:
            return color == GC_NODE_COLOR_BLACK ? 'b' : 'B';
        case GC_PIECE_ROOK:
            return color == GC_NODE_COLOR_BLACK ? 'r' : 'R';
        case GC_PIECE_QUEEN:
            return color == GC_NODE_COLOR_BLACK ? 'q' : 'Q';
        case GC_PIECE_KING:
            return color == GC_NODE_COLOR_BLACK ? 'k' : 'K';
        default:
            return '\0';
    }
}

void fen_build(gc_graph_t* graph, char** fen_out) {
    char* fen = smalloc(100);
    size_t pos = 0;

    for (int rank = SQUARE_RANK_COUNT - 1; rank >= 0; rank--) {
        if (rank < SQUARE_RANK_COUNT - 1) {
            fen[pos++] = '/';
        }

        int empties = 0;
        for (int file = 0; file < SQUARE_FILE_COUNT; file++) {
            uint8_t node_id = square_from(file, rank);
            gc_piece_t piece = gc_graph_get_piece(graph, node_id);
            gc_node_color_t color = gc_graph_get_color(graph, node_id);

            char symbol = from_piece(piece, color);
            if (symbol != '\0') {
                if (empties > 0) {
                    fen[pos++] = '0' + empties;
                    empties = 0;
                }
                fen[pos++] = symbol;
            } else {
                empties++;
            }
        }
        if (empties > 0) {
            fen[pos++] = '0' + empties;
            empties = 0;
        }
    }

    // Turn
    pos += sprintf(&fen[pos], " %c",
                   graph->turn == GC_NODE_COLOR_WHITE ? 'w' : 'b');

    // Castling rights
    pos += sprintf(&fen[pos], " KQkq");

    // e.p. target square
    pos += sprintf(&fen[pos], " -");

    // Move/ply
    pos += sprintf(&fen[pos], " %d %d", graph->ply / 2, graph->ply);

    fen[pos++] = '\0';

    *fen_out = fen;
}

gc_graph_t* fen_parse(const char* fen) {
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
