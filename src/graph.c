#include <graph.h>

graph_node_t* create_graph_node(const void *data, size_t size) {
    assert(data);
    assert(size > 0);
    graph_node_t *node = (graph_node_t*) __malloc(sizeof(graph_node_t));
    assert(node);
    node->data = __malloc(size);
    assert(node->data);
    memcpy(node->data, data, size);
    node->adj = create_list(); 
    return node;
}

void free_graph_node(
    graph_node_t *node, 
    free_func_t free_node_data /* knows how to free data asociated with the node itself */, 
    free_func_t free_list_elem /* knows how to free node list elements */
) {
    free_node_data(node->data);
    free_list(node->adj, free_list_elem);
}

graph_t* create_graph() {
    graph_t *g = __malloc(sizeof(graph_t));
    g->nodes = create_list();
    g->size = 0;
    return g;
}

graph_node_t* get_node(graph_t *g, const void *data, size_t size) {
    list_node_t *head = g->nodes->head;
    list_node_t *tail = g->nodes->tail;
    for(list_node_t *it = head; it; it = it->next) {
        graph_node_t *node = (graph_node_t*)it->data;
        if(memcmp(node->data, data, size) == 0) {
            return node;
        }
    }
    return NULL;
}

uint8_t node_exists(graph_t *g, const void *data, size_t size) {
    return get_node(g, data, size)? 1 : 0;
}

void add_node(graph_t *g, const void *data, size_t size) {
    // fields of this node do not live inside and get
    // copied while `node` is only a shell to give to push_back.
    // after push_back the ownership is transfered to g->nodes 
    // so it can be freed while insides live on 
    graph_node_t *node = create_graph_node(data, size);
    push_back(g->nodes, node, sizeof(graph_node_t));
    __free(node); 
    g->size++;
}

list_t* shortest_path(graph_t *g , const void *p, const void *q, cmp_func_t func) {
    /// Implementation based on Dijkstra's algorithm:
    /// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    list_t *path = create_list();
    pqueue_t *pq = create_pq(NULL);

    // TODO: figure out how to implement this algorithm


    free_pq(pq, NULL);
    return path;
}

void free_graph(
    graph_t *g, 
    free_func_t free_node_data, 
    free_func_t free_list_elem
) {
    // can't use list_free() because free_graph_node 
    // requires more args than free_func_t
    list_t *list = g->nodes;
    if(list->size != 0) {
        list_node_t *it = list->head;
        while(it) {
            list_node_t *temp = it;
            it = it->next;

            // can't use free_list_node() for the same reason
            graph_node_t *gn = (graph_node_t*) temp->data;
            free_graph_node(gn, free_node_data, free_list_elem); // frees whats inside of gnode

            __free(gn);
            __free(temp);
        }
    }

    __free(g->nodes);
    __free(g);
}