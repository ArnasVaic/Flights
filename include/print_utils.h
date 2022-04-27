#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#define TAB_SIZE 4

#include <stdio.h>
#include <list.h>
#include <graph.h>
#include <flights.h>

typedef void (*print_func_t)(FILE *, const void *, size_t);

void print_tabs(FILE *os, size_t n);

void print_flight(FILE *os, const void *data, size_t ident);
void print_gnode(FILE *os, const void *data, size_t ident);

void print_list(FILE *os, list_t list, print_func_t f, size_t ident, char end);

void print_graph(FILE *os, graph_t *g);

#endif /* PRINT_UTILS_H */