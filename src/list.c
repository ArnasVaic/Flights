#include <list.h>

node_t* create_node(void *data, size_t size) {
    assert(data);
    assert(size > 0);

    node_t *node = (node_t*) __malloc(sizeof(node_t));
    assert(node);

    node->data = __malloc(size);
    assert(node->data);

    memcpy(node->data, data, size);
    node->next = NULL;

    return node;
}

void free_node(node_t *node, free_func_t f) {
    f(node->data);
    __free(node);
}

list_t create_list() {
    list_t list = {NULL, NULL, 0};
    return list;
}

void push_back(list_t *list, void *data, size_t size) {
    assert(list);
    node_t *node = create_node(data, size);
    if(!list->head && !list->tail) {
        // Set head if this is the first node
        list->head = node; 
    } else {
        // Add node to tail
        list->tail->next = node;
    }
    // Set new tail
    list->tail = node;
    list->size++;
}

void* pop_front(list_t *list) {
    assert(list);
    if(list->size == 0) return NULL;
    // Save head fields
    void *data = list->head->data;
    node_t *next = list->head->next;
    __free(list->head);
    // Change tail if this was the last node
    if(list->head == list->tail) list->tail = NULL; 
    list->head = next;
    list->size--;
    return data;
}

void* list_get(list_t list, int index) {
    assert(index >= 0);
    assert(index < list.size);

    node_t *it = list.head;
    for(int i = 0; i < index; ++i) {
        it = it->next;
    }
    return it->data;
}

void free_list(list_t *list, free_func_t f) {
    assert(list);
    if(list->size == 0) return;
    node_t *it = list->head;
    while(it) {
        node_t *temp = it;
        it = it->next;
        free_node(temp, f);
    }
}