#include <flights.h>

void free_flight(void *ptr) {
    flight_t *f = (flight_t*) ptr;
    __free(f->orig);
    __free(f->dest);
}

graph_t* read_flights(const char* file) {
    FILE *is = fopen(file, "rb");
    graph_t *g = create_graph();
    
    size_t cnt = 0;
    while(!feof(is)) {
        flight_t f;
        f.orig = __malloc(MAX_CITY_NAME_LEN * sizeof(char));
        f.dest = __malloc(MAX_CITY_NAME_LEN * sizeof(char));
        fscanf(is, "%s %s %lf %lf", f.orig, f.dest, &f.leave, &f.duration);
        const size_t len = (strlen(f.orig) + 1) * sizeof(char);
        
        if(!node_exists(g, f.orig, len)) {
            add_node(g, f.orig, len);
            ++cnt;
        }
        
        graph_node_t *node = get_node(g, f.orig, len);
        push_back(node->adj, &f, sizeof(flight_t));
    }
    
    fclose(is);
    return g;
}

flight_t* get_shortest_flight(graph_t *g, const char *c1, const char *c2) {
    assert(c1);
    assert(c2);

    size_t size = (strlen(c1) + 1) * sizeof(char);
    graph_node_t *node = get_node(g, c1, size);
    if(node == NULL) return NULL;
    list_t *list = node->adj;
    double min_time = __DBL_MAX__;
    list_node_t *min_it = NULL;
    for(list_node_t *it = list->head; it; it = it->next) {
        const double t = ((flight_t*)it->data)->duration;
        if(min_time > t) {
            min_time = t;
            min_it = it;
        }
    }
    return min_it->data;
}