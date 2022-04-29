#ifndef LIST_H
#define LIST_H

// System headers
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>

// My headers
#include <mymem.h>

typedef struct list_node_t {
    void *data;
    struct list_node_t *next;
} list_node_t;

typedef struct list_t {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

/// Creates a list
/// @return list object
list_t* create_list();

/// Adds an element to the list_t
/// @param list pointer to list_t object
/// @param data data you want to store
/// @param size size of data in bytes
/// @return nothing
void push_back(list_t *list, void *data, size_t size);

/// Removes an element from the list_t
/// Note: memory returned by pop_front needs to be freed manually
/// @param list pointer to list_t object
/// @return pointer to the element
void* pop_front(list_t *list);

// Get element from list by index
/// @param list pointer to list_t object
/// @param index index of desired element
/// @return pointer to the element
void* list_get(list_t *list, int index);

/// Frees elements contained by list_t
/// @param list pointer to list_t object
/// @param f this function will be used to free list elements
/// @return nothing
void free_list(list_t *list, free_func_t f);

#endif /* LIST_H */