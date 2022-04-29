// This graph structure is stored with neighbour adjacency lists
#ifndef GRAPH_H
#define GRAPH_H

// My headers
#include <pqueue.h>
#include <list.h>
#include <mymem.h>

typedef int (*cmp_func_t)(const void*, const void*);

typedef struct graph_node_t {
    void *data;
    list_t *adj;
} graph_node_t;

typedef struct graph_t {
    list_t *nodes;
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
graph_node_t* get_node(graph_t *g, const void *data, size_t size);

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

/// Get the shortest path between two nodes p and q
/// @param g pointer to graph
/// @param p origin node
/// @param q destination node
/// @param func function that can compare two edges
/// @return list of edges that lead from p to q in the shortest ammount of something
list_t* shortest_path(graph_t *g , const void *p, const void *q, cmp_func_t func);

/// Free the memory of a graph
/// @param g pointer to graph
/// @param free_node_data function that knows how to free data asociated with each graph node
/// @param free_list_elem function that knows how to free each element (inside only, itself will be freed automatically) of each graph node list
/// @return nothing
void free_graph(
    graph_t *g, 
    free_func_t free_node_data, 
    free_func_t free_list_elem
);

#endif /* GRAPH_H */