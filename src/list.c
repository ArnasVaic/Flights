#include <list.h>

list_node_t* create_list_node(void *data, size_t size) {
    assert(data);
    assert(size > 0);

    list_node_t *node = (list_node_t*) __malloc(sizeof(list_node_t));
    assert(node);

    node->data = __malloc(size);
    assert(node->data);

    memcpy(node->data, data, size);
    node->next = NULL;

    return node;
}

void free_list_node(list_node_t *node, free_func_t f) {
    f(node->data);
    __free(node->data);
    __free(node);
}

list_t* create_list() {
    list_t *list = __malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void push_back(list_t *list, void *data, size_t size) {
    assert(list);
    list_node_t *node = create_list_node(data, size);
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
    list_node_t *next = list->head->next;
    __free(list->head);
    // Change tail if this was the last node
    if(list->head == list->tail) list->tail = NULL; 
    list->head = next;
    list->size--;
    return data;
}

void* list_get(list_t* list, int index) {
    assert(index >= 0);
    assert(index < list->size);

    list_node_t *it = list->head;
    for(int i = 0; i < index; ++i) {
        it = it->next;
    }
    return it->data;
}

void free_list(list_t *list, free_func_t f) {
    assert(list);
    if(list->size != 0) { 
        list_node_t *it = list->head;
        while(it) {
            list_node_t *temp = it;
            it = it->next;
            free_list_node(temp, f);
        }
    }
    __free(list);
}