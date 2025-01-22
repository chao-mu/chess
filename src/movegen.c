#include "movegen.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gc.h"
#include "smalloc.h"
#include "square.h"

void todo_push(todo_t* todo, todo_item_t item) {
    assert(todo->size < MOVEGEN_TODO_CAPACITY);
    todo->items[todo->size++] = item;
}

todo_item_t todo_shift(todo_t* todo) {
    assert(todo->size > 0 && "Attempted to pop empty todo queue");

    todo_item_t item = todo->items[0];
    for (size_t i = 1; i < todo->size; i++) {
        todo->items[i - 1] = todo->items[i];
    }

    todo->size--;

    return item;
}

void movegen_walk(gc_graph_t* graph, movegen_t movegen, gc_node_color_t color,
                  uint8_t orig_square) {
    todo_t* todo = smalloc(sizeof(*todo));
    int depths[GC_RANK_COUNT][GC_FILE_COUNT];
    memset(depths, MOVEGEN_MAX_DEPTH,
           GC_RANK_COUNT * GC_RANK_COUNT * sizeof(int));

    int orig_file = square_geti_file(orig_square);
    int orig_rank = square_geti_rank(orig_square);

    todo_item_t item = {
        .depth = 0,
        .from_file = orig_file,
        .from_rank = orig_rank,
        .to_file = orig_file,
        .to_rank = orig_rank,
    };

    todo_push(todo, item);

    while (todo->size > 0) {
        item = todo_shift(todo);

        int to_file = item.to_file;
        int to_rank = item.to_rank;
        int depth = item.depth;

        // Ignore moves that went offboard.
        if (!square_is_valid(to_file, to_rank)) {
            continue;
        }

        if (depths[to_file][to_rank] < depth) {
            continue;
        }

        depths[to_file][to_rank] = depth;

        // Collides  with a same color piece? Stop.
        uint8_t to_id = square_from(to_file, to_rank);
        if (gc_graph_get_color(graph, to_id) == color && depth != 0) {
            continue;
        }

        if (++depth > MOVEGEN_MAX_DEPTH) {
            continue;
        }

        (*movegen)(todo, to_file, to_rank, depth);
    }

    // Insert the depth edges
    for (size_t file = 0; file < SQUARE_FILE_COUNT; file++) {
        for (size_t rank = 0; rank < SQUARE_RANK_COUNT; rank++) {
            uint8_t to_id = square_from(file, rank);
            int depth = depths[file][rank];
            gc_graph_insert_edge(graph, orig_square, to_id, depth);
        }
    }

    free(todo);
}

void movegen_knight(todo_t* todo, int file, int rank, int depth) {
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file + 1,
                                  .to_rank = rank + 2,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file - 1,
                                  .to_rank = rank + 2,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file + 1,
                                  .to_rank = rank - 2,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file - 1,
                                  .to_rank = rank - 2,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file + 2,
                                  .to_rank = rank + 1,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file - 2,
                                  .to_rank = rank + 1,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file + 2,
                                  .to_rank = rank - 1,
                                  .depth = depth});
    todo_push(todo, (todo_item_t){.from_file = file,
                                  .from_rank = rank,
                                  .to_file = file - 2,
                                  .to_rank = rank - 1,
                                  .depth = depth});
}
