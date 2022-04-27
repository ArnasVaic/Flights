#include <graph.h>

gnode_t* create_gnode(const void *data, size_t size) {
    assert(data);
    assert(size > 0);
    gnode_t *node = (gnode_t*) __malloc(sizeof(gnode_t));
    assert(node);
    node->data = __malloc(size);
    assert(node->data);
    memcpy(node->data, data, size);
    node->adj = create_list(); 
    return node;
}

void free_gnode(
    gnode_t *node, 
    free_func_t f1 /* knows how to free data asociated with the node itself */, 
    free_func_t f2 /* knows how to free node list elements */
) {
    f1(node->data);
    free_list(&(node->adj), f2);
    __free(node);
}

graph_t* create_graph() {
    graph_t *g = __malloc(sizeof(graph_t));
    g->nodes = create_list();
    g->size = 0;
    return g;
}

gnode_t* get_node(graph_t *g, const void *data, size_t size) {
    node_t *head = g->nodes.head;
    node_t *tail = g->nodes.tail;
    for(node_t *it = head; it; it = it->next) {
        gnode_t *node = (gnode_t*)it->data;
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
    gnode_t *node = create_gnode(data, size);
    push_back(&(g->nodes), node, sizeof(gnode_t));
    g->size++;
}

void free_graph(graph_t *g, free_func_t f1, free_func_t f2) {
    list_t list = g->nodes;
    if(list.size == 0) return;
    node_t *it = list.head;
    while(it) {
        node_t *temp = it;
        it = it->next;

        // improv free_node()
        free_gnode(temp->data, f1, f2);
        __free(temp);
    }
    // each element in list has been freed
    __free(g);
}