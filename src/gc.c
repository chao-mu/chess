#include "gc.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smalloc.h"

gc_graph_t *gc_graph_new(void) {
    gc_graph_t *graph = smalloc(sizeof(*graph));

    return graph;
}

void gc_graph_free(gc_graph_t *graph) {
    for (uint8_t id = 0; id < GC_GRAPH_NODES; id++) {
        gc_node_t *node = graph->nodes[id];
        free(node);

        while (graph->edges[id] != NULL) {
            gc_edge_t *next = graph->edges[id]->next;

            free(graph->edges[id]);

            graph->edges[id] = next;
        }

        while (graph->edges_reverse[id] != NULL) {
            gc_edge_t *next = graph->edges_reverse[id]->next;

            free(graph->edges_reverse[id]);

            graph->edges_reverse[id] = next;
        }
    }

    free(graph);
}

void gc_graph_insert_edge(gc_graph_t *graph, uint8_t from_id, uint8_t to_id,
                          int weight) {
    assert(from_id < GC_GRAPH_NODES);
    assert(to_id < GC_GRAPH_NODES);

    gc_edge_t *edge = smalloc(sizeof(*edge));
    edge->weight = weight;
    edge->from_id = from_id;
    edge->to_id = to_id;

    if (graph->edges[from_id] == NULL) {
        graph->edges[from_id] = edge;
    } else {
        edge->next = graph->edges[from_id];
        graph->edges[from_id] = edge;
    }

    gc_edge_t *edge_copy = smalloc(sizeof(*edge));
    memcpy(edge_copy, edge, sizeof(*edge_copy));
    edge_copy->next = NULL;

    if (graph->edges_reverse[to_id] == NULL) {
        graph->edges_reverse[to_id] = edge_copy;
    } else {
        edge_copy->next = graph->edges_reverse[to_id];
        graph->edges_reverse[to_id] = edge_copy;
    }
}

void gc_graph_insert_node(gc_graph_t *graph, uint8_t node_id, gc_node_t node) {
    assert(node_id < GC_GRAPH_NODES);

    gc_node_t *existing = graph->nodes[node_id];
    if (existing != NULL) {
        free(existing);
    }

    gc_node_t *node_copy = smalloc(sizeof(node));
    *node_copy = node;

    graph->nodes[node_id] = node_copy;
}

gc_node_color_t gc_graph_get_color(gc_graph_t *graph, uint8_t node_id) {
    assert(node_id < GC_GRAPH_NODES);

    if (graph->nodes[node_id] == NULL) {
        return GC_NODE_COLOR_EMPTY;
    }

    return graph->nodes[node_id]->color;
}

gc_piece_t gc_graph_get_piece(gc_graph_t *graph, uint8_t node_id) {
    assert(node_id < GC_GRAPH_NODES);

    if (graph->nodes[node_id] == NULL) {
        return GC_PIECE_NONE;
    }

    return graph->nodes[node_id]->piece;
}
