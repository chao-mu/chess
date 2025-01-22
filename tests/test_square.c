#include "square.h"
#include "test.h"

int main(void) {
    test_start("square.h");

    printf("%d\n", SQUARE_G1);

    // Corners of the chessboard.
    assert_true(SQUARE_A8 == 0);
    assert_true(SQUARE_H8 == 7);
    assert_true(SQUARE_A1 == 56);
    assert_true(SQUARE_H1 == 63);

    // Previously troublesome square.
    // assert_true(SQUARE_G1 == 63);

    assert_true(SQUARE_A1 == square_from(SQUARE_FILE_A, SQUARE_RANK_1));
    assert_true(SQUARE_B1 == square_from(SQUARE_FILE_B, SQUARE_RANK_1));
    assert_true(SQUARE_C1 == square_from(SQUARE_FILE_C, SQUARE_RANK_1));
    assert_true(SQUARE_D1 == square_from(SQUARE_FILE_D, SQUARE_RANK_1));
    assert_true(SQUARE_E1 == square_from(SQUARE_FILE_E, SQUARE_RANK_1));
    assert_true(SQUARE_F1 == square_from(SQUARE_FILE_F, SQUARE_RANK_1));
    assert_true(SQUARE_G1 == square_from(SQUARE_FILE_G, SQUARE_RANK_1));
    assert_true(SQUARE_H1 == square_from(SQUARE_FILE_H, SQUARE_RANK_1));

    assert_true(SQUARE_A2 == square_from(SQUARE_FILE_A, SQUARE_RANK_2));
    assert_true(SQUARE_B2 == square_from(SQUARE_FILE_B, SQUARE_RANK_2));
    assert_true(SQUARE_C2 == square_from(SQUARE_FILE_C, SQUARE_RANK_2));
    assert_true(SQUARE_D2 == square_from(SQUARE_FILE_D, SQUARE_RANK_2));
    assert_true(SQUARE_E2 == square_from(SQUARE_FILE_E, SQUARE_RANK_2));
    assert_true(SQUARE_F2 == square_from(SQUARE_FILE_F, SQUARE_RANK_2));
    assert_true(SQUARE_G2 == square_from(SQUARE_FILE_G, SQUARE_RANK_2));
    assert_true(SQUARE_H2 == square_from(SQUARE_FILE_H, SQUARE_RANK_2));

    assert_true(SQUARE_A3 == square_from(SQUARE_FILE_A, SQUARE_RANK_3));
    assert_true(SQUARE_B3 == square_from(SQUARE_FILE_B, SQUARE_RANK_3));
    assert_true(SQUARE_C3 == square_from(SQUARE_FILE_C, SQUARE_RANK_3));
    assert_true(SQUARE_D3 == square_from(SQUARE_FILE_D, SQUARE_RANK_3));
    assert_true(SQUARE_E3 == square_from(SQUARE_FILE_E, SQUARE_RANK_3));
    assert_true(SQUARE_F3 == square_from(SQUARE_FILE_F, SQUARE_RANK_3));
    assert_true(SQUARE_G3 == square_from(SQUARE_FILE_G, SQUARE_RANK_3));
    assert_true(SQUARE_H3 == square_from(SQUARE_FILE_H, SQUARE_RANK_3));

    assert_true(SQUARE_A4 == square_from(SQUARE_FILE_A, SQUARE_RANK_4));
    assert_true(SQUARE_B4 == square_from(SQUARE_FILE_B, SQUARE_RANK_4));
    assert_true(SQUARE_C4 == square_from(SQUARE_FILE_C, SQUARE_RANK_4));
    assert_true(SQUARE_D4 == square_from(SQUARE_FILE_D, SQUARE_RANK_4));
    assert_true(SQUARE_E4 == square_from(SQUARE_FILE_E, SQUARE_RANK_4));
    assert_true(SQUARE_F4 == square_from(SQUARE_FILE_F, SQUARE_RANK_4));
    assert_true(SQUARE_G4 == square_from(SQUARE_FILE_G, SQUARE_RANK_4));
    assert_true(SQUARE_H4 == square_from(SQUARE_FILE_H, SQUARE_RANK_4));

    assert_true(SQUARE_A5 == square_from(SQUARE_FILE_A, SQUARE_RANK_5));
    assert_true(SQUARE_B5 == square_from(SQUARE_FILE_B, SQUARE_RANK_5));
    assert_true(SQUARE_C5 == square_from(SQUARE_FILE_C, SQUARE_RANK_5));
    assert_true(SQUARE_D5 == square_from(SQUARE_FILE_D, SQUARE_RANK_5));
    assert_true(SQUARE_E5 == square_from(SQUARE_FILE_E, SQUARE_RANK_5));
    assert_true(SQUARE_F5 == square_from(SQUARE_FILE_F, SQUARE_RANK_5));
    assert_true(SQUARE_G5 == square_from(SQUARE_FILE_G, SQUARE_RANK_5));
    assert_true(SQUARE_H5 == square_from(SQUARE_FILE_H, SQUARE_RANK_5));

    assert_true(SQUARE_A6 == square_from(SQUARE_FILE_A, SQUARE_RANK_6));
    assert_true(SQUARE_B6 == square_from(SQUARE_FILE_B, SQUARE_RANK_6));
    assert_true(SQUARE_C6 == square_from(SQUARE_FILE_C, SQUARE_RANK_6));
    assert_true(SQUARE_D6 == square_from(SQUARE_FILE_D, SQUARE_RANK_6));
    assert_true(SQUARE_E6 == square_from(SQUARE_FILE_E, SQUARE_RANK_6));
    assert_true(SQUARE_F6 == square_from(SQUARE_FILE_F, SQUARE_RANK_6));
    assert_true(SQUARE_G6 == square_from(SQUARE_FILE_G, SQUARE_RANK_6));
    assert_true(SQUARE_H6 == square_from(SQUARE_FILE_H, SQUARE_RANK_6));

    assert_true(SQUARE_A7 == square_from(SQUARE_FILE_A, SQUARE_RANK_7));
    assert_true(SQUARE_B7 == square_from(SQUARE_FILE_B, SQUARE_RANK_7));
    assert_true(SQUARE_C7 == square_from(SQUARE_FILE_C, SQUARE_RANK_7));
    assert_true(SQUARE_D7 == square_from(SQUARE_FILE_D, SQUARE_RANK_7));
    assert_true(SQUARE_E7 == square_from(SQUARE_FILE_E, SQUARE_RANK_7));
    assert_true(SQUARE_F7 == square_from(SQUARE_FILE_F, SQUARE_RANK_7));
    assert_true(SQUARE_G7 == square_from(SQUARE_FILE_G, SQUARE_RANK_7));
    assert_true(SQUARE_H7 == square_from(SQUARE_FILE_H, SQUARE_RANK_7));

    assert_true(SQUARE_A8 == square_from(SQUARE_FILE_A, SQUARE_RANK_8));
    assert_true(SQUARE_B8 == square_from(SQUARE_FILE_B, SQUARE_RANK_8));
    assert_true(SQUARE_C8 == square_from(SQUARE_FILE_C, SQUARE_RANK_8));
    assert_true(SQUARE_D8 == square_from(SQUARE_FILE_D, SQUARE_RANK_8));
    assert_true(SQUARE_E8 == square_from(SQUARE_FILE_E, SQUARE_RANK_8));
    assert_true(SQUARE_F8 == square_from(SQUARE_FILE_F, SQUARE_RANK_8));
    assert_true(SQUARE_G8 == square_from(SQUARE_FILE_G, SQUARE_RANK_8));
    assert_true(SQUARE_H8 == square_from(SQUARE_FILE_H, SQUARE_RANK_8));

    assert_true(square_geti_file(SQUARE_A1) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A2) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A3) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A4) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A5) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A6) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A7) == SQUARE_FILE_A);
    assert_true(square_geti_file(SQUARE_A8) == SQUARE_FILE_A);

    assert_true(square_geti_rank(SQUARE_A1) == SQUARE_RANK_1);
    assert_true(square_geti_rank(SQUARE_A2) == SQUARE_RANK_2);
    assert_true(square_geti_rank(SQUARE_A3) == SQUARE_RANK_3);
    assert_true(square_geti_rank(SQUARE_A4) == SQUARE_RANK_4);
    assert_true(square_geti_rank(SQUARE_A5) == SQUARE_RANK_5);
    assert_true(square_geti_rank(SQUARE_A6) == SQUARE_RANK_6);
    assert_true(square_geti_rank(SQUARE_A7) == SQUARE_RANK_7);
    assert_true(square_geti_rank(SQUARE_A8) == SQUARE_RANK_8);

    assert_true(square_geti_file(SQUARE_B1) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B2) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B3) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B4) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B5) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B6) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B7) == SQUARE_FILE_B);
    assert_true(square_geti_file(SQUARE_B8) == SQUARE_FILE_B);

    assert_true(square_geti_rank(SQUARE_B1) == SQUARE_RANK_1);
    assert_true(square_geti_rank(SQUARE_B2) == SQUARE_RANK_2);
    assert_true(square_geti_rank(SQUARE_B3) == SQUARE_RANK_3);
    assert_true(square_geti_rank(SQUARE_B4) == SQUARE_RANK_4);
    assert_true(square_geti_rank(SQUARE_B5) == SQUARE_RANK_5);
    assert_true(square_geti_rank(SQUARE_B6) == SQUARE_RANK_6);
    assert_true(square_geti_rank(SQUARE_B7) == SQUARE_RANK_7);
    assert_true(square_geti_rank(SQUARE_B8) == SQUARE_RANK_8);

    assert_true(square_geti_file(SQUARE_C1) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C2) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C3) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C4) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C5) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C6) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C7) == SQUARE_FILE_C);
    assert_true(square_geti_file(SQUARE_C8) == SQUARE_FILE_C);

    assert_true(square_geti_rank(SQUARE_C1) == SQUARE_RANK_1);
    assert_true(square_geti_rank(SQUARE_C2) == SQUARE_RANK_2);
    assert_true(square_geti_rank(SQUARE_C3) == SQUARE_RANK_3);
    assert_true(square_geti_rank(SQUARE_C4) == SQUARE_RANK_4);
    assert_true(square_geti_rank(SQUARE_C5) == SQUARE_RANK_5);
    assert_true(square_geti_rank(SQUARE_C6) == SQUARE_RANK_6);
    assert_true(square_geti_rank(SQUARE_C7) == SQUARE_RANK_7);
    assert_true(square_geti_rank(SQUARE_C8) == SQUARE_RANK_8);

    test_end();

    return 0;
}
