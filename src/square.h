#ifndef SQUARE_H
#define SQUARE_H

#include <stdbool.h>

typedef enum square_rank {
    SQUARE_RANK_1 = 0,
    SQUARE_RANK_2,
    SQUARE_RANK_3,
    SQUARE_RANK_4,
    SQUARE_RANK_5,
    SQUARE_RANK_6,
    SQUARE_RANK_7,
    SQUARE_RANK_8,
    SQUARE_RANK_COUNT,
} square_rank_t;

typedef enum square_file {
    SQUARE_FILE_A = 0,
    SQUARE_FILE_B,
    SQUARE_FILE_C,
    SQUARE_FILE_D,
    SQUARE_FILE_E,
    SQUARE_FILE_F,
    SQUARE_FILE_G,
    SQUARE_FILE_H,
    SQUARE_FILE_COUNT,
} square_file_t;

typedef enum square {
    SQUARE_A8,
    SQUARE_B8,
    SQUARE_C8,
    SQUARE_D8,
    SQUARE_E8,
    SQUARE_F8,
    SQUARE_G8,
    SQUARE_H8,

    SQUARE_A7,
    SQUARE_B7,
    SQUARE_C7,
    SQUARE_D7,
    SQUARE_E7,
    SQUARE_F7,
    SQUARE_G7,
    SQUARE_H7,

    SQUARE_A6,
    SQUARE_B6,
    SQUARE_C6,
    SQUARE_D6,
    SQUARE_E6,
    SQUARE_F6,
    SQUARE_G6,
    SQUARE_H6,

    SQUARE_A5,
    SQUARE_B5,
    SQUARE_C5,
    SQUARE_D5,
    SQUARE_E5,
    SQUARE_F5,
    SQUARE_G5,
    SQUARE_H5,

    SQUARE_A4,
    SQUARE_B4,
    SQUARE_C4,
    SQUARE_D4,
    SQUARE_E4,
    SQUARE_F4,
    SQUARE_G4,
    SQUARE_H4,

    SQUARE_A3,
    SQUARE_B3,
    SQUARE_C3,
    SQUARE_D3,
    SQUARE_E3,
    SQUARE_F3,
    SQUARE_G3,
    SQUARE_H3,

    SQUARE_A2,
    SQUARE_B2,
    SQUARE_C2,
    SQUARE_D2,
    SQUARE_E2,
    SQUARE_F2,
    SQUARE_G2,
    SQUARE_H2,

    SQUARE_A1,
    SQUARE_B1,
    SQUARE_C1,
    SQUARE_D1,
    SQUARE_E1,
    SQUARE_F1,
    SQUARE_G1,
    SQUARE_H1,

    SQUARE_COUNT,
} square_t;

typedef enum square_piece {
    SQUARE_EMPTY = 0,
    SQUARE_PAWN_WHITE,
    SQUARE_PAWN_BLACK,
    SQUARE_KNIGHT_WHITE,
    SQUARE_KNIGHT_BLACK,
    SQUARE_BISHOP_WHITE,
    SQUARE_BISHOP_BLACK,
    SQUARE_ROOK_WHITE,
    SQUARE_ROOK_BLACK,
    SQUARE_QUEEN_WHITE,
    SQUARE_QUEEN_BLACK,
    SQUARE_KING_WHITE,
    SQUARE_KING_BLACK,
    SQUARE_PIECE_COUNT
} square_piece_t;

typedef square_piece_t squares_t[SQUARE_COUNT];

square_rank_t square_get_rank(square_t square);

square_file_t square_get_file(square_t square);

int square_geti_file(int id);

int square_geti_rank(int id);

bool square_is_valid(int file, int rank);

int square_from(int file, int rank);

char square_getc_file(int id);

char square_getc_rank(int id);

#endif
