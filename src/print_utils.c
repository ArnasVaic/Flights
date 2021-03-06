#include <print_utils.h>

void print_tabs(FILE *os, size_t n) {
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < TAB_SIZE; ++j) {
            putc(' ', os);
        }
    }
}

void print_flight(FILE *os, const void *data, size_t ident) {
    flight_t *f = (flight_t*) data; 

    print_tabs(os, ident);
    fputs("{", os);//fputs("{\n", os);

    //print_tabs(os, ident + 1);
    //fprintf(os, "orig:%s\n", f->orig);

    //print_tabs(os, ident + 1);
    fprintf(os, "dest:\"%s\", ", f->dest);

    //print_tabs(os, ident + 1);
    //fprintf(os, "leave:%.0lf\n", f->leave);

    //print_tabs(os, ident + 1);
    fprintf(os, "dur:%.0lf", f->duration);

    //print_tabs(os, ident);
    fputs("}", os);
}

void print_graph(FILE *os, graph_t *g) {
    fprintf(os, "Number of nodes: %zu\n", g->size);
    print_list(os, g->nodes, print_gnode, 0, ',', 1, '\n');
}

void print_gnode(FILE *os, const void *data, size_t ident) {
    graph_node_t *node = (graph_node_t*) data;

    print_tabs(os, ident);
    fputs("{\n", os);

    print_tabs(os, ident + 1);
    fprintf(os, "data:%s,\n", node->data);

    print_tabs(os, ident + 1);
    fprintf(os, "adj:\n");
    print_list(os, node->adj, print_flight, ident + 1, ',', 1, '\n');

    print_tabs(os, ident);
    fprintf(os, "}");
}

void print_int(FILE *os, const void *data) {
    fprintf(os, "%d", *(int*)data);
}

void print_list(
    FILE *os, 
    list_t* list, 
    void (*print_func_t)(FILE *, const void *, size_t), 
    size_t ident, 
    char sep,
    uint8_t nl,
    char end
) {
    if(list->size == 0) {
        fprintf(os, "[empty]%c", end);
        return;
    }
    if(nl) print_tabs(os, ident);
    fprintf(os, "[");
    if(nl) putc('\n', os);
    for(list_node_t *it = list->head; it; it = it->next) {
        print_func_t(os, it->data, nl?ident + 1:0);
        if(it != list->tail) putc(sep, os);
        if(nl) putc('\n', os);
    }
    if(nl) print_tabs(os, ident);
    fprintf(os, "]%c", end);
}