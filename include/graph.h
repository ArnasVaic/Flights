// This graph structure is stored with neighbour adjacency lists
#ifndef GRAPH_H
#define GRAPH_H

// My headers
#include <list.h>
#include <mem.h>

typedef struct gnode_t {
    void *data;
    list_t adj;
} gnode_t;

typedef struct graph_t {
    list_t nodes;
    size_t size;
} graph_t;

/// Create and empty graph
/// @return pointer to graph
graph_t* create_graph();

/// Get node that has matching data
/// @param g pointer to graph
/// @param data data to match
/// @param size size of data in bytes
/// @return pointer to node (NULL if such node does not exist)
gnode_t* get_node(graph_t *g, const void *data, size_t size);

/// Check whether a node exists 
/// @param g pointer to graph
/// @param data data to match
/// @param size size of data in bytes
/// @return boolean value - 1 if exists, 0 otherwise
uint8_t node_exists(graph_t *g, const void *data, size_t size);

/// Add a node to the graph (identical nodes are allowed)
/// @param g pointer to graph
/// @param data data to be asociated with a node
/// @param size size of data in bytes
/// @return nothing
void add_node(graph_t *g, const void *data, size_t size);

/// Free the memory of a graph
/// @param g pointer to graph
/// @param f1 function that knows how to free data asociated with each graph node
/// @param f2 function that knows how to free each element of each graph node list
/// @return nothing
void free_graph(graph_t *g, free_func_t f1, free_func_t f2);

#endif /* GRAPH_H */