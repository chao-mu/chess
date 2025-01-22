#include "square.h"

#include <assert.h>
#include <stdbool.h>

int square_geti_file(int id) { return id % SQUARE_FILE_COUNT; }

int square_geti_rank(int id) { return 7 - (id / SQUARE_RANK_COUNT); }

bool square_is_valid(int file, int rank) {
    return file >= 0 && file < SQUARE_FILE_COUNT && rank >= 0 &&
           rank < SQUARE_RANK_COUNT;
}

int square_from(int file, int rank) {
    assert(square_is_valid(file, rank));

    int file_contribution = file;
    int rank_contribution = (7 - rank) * SQUARE_RANK_COUNT;

    return file_contribution + rank_contribution;
}

char square_getc_file(int id) { return 'A' + square_geti_file(id); }

char square_getc_rank(int id) { return '1' + square_geti_rank(id); }
