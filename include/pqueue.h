#ifndef PQUEUE_H
#define PQUEUE_H

// System headers
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// My headers
#include <mymem.h>

// Node data structure for the priority queue
typedef struct pq_node_t {
	void* data;
	double prio;
	struct pq_node_t *next;
} pq_node_t;

// Priority queue data structure
typedef struct pqueue_t {
	pq_node_t *head;
} pqueue_t;

///	Create an empty prioty queue
/// @param errnum error number
/// @return pointer to priority queue
pqueue_t* create_pq(int *errnum);

/// Determines whether the priority queue is empty
/// @param pq pointer to priority queue
/// @param errnum error number
/// @return 1 if pq is empty and 0 if it's not
uint8_t is_pq_empty(pqueue_t *pq, int *errnum);

/// Push an element to priority queue
/// @param pq pointer to priority queue
/// @param data data that is going to be stored
/// @param size size of data
/// @param prio priority value of this element
/// @param errnum error number
/// @return nothing
void pq_push(pqueue_t *pq, void *data, size_t size, double prio, int *errnum);

/// Pop the element with the highest priority from priority queue
/// @param pq pointer to priority queue
/// @param errnum error number
/// @return data of the element (must be freed manually)
void* pq_pop(pqueue_t *pq, int *errnum);

/// Peek an element with the highest priority in a priority queue
/// @param pq pointer to priority queue
/// @param errnum error number
/// @return data of the element
void* pq_peek(pqueue_t *pq, int *errnum);

/// Get the number of elements in a priority queue
/// @param pq pointer to priority queue
/// @param errnum error number
/// @return number of elements
size_t pq_elem_count(pqueue_t *pq, int *errnum);

/// Free memory allocated by priority queue
/// @param pq pointer to priority queue
/// @param errnum error number
/// @return nothing
void free_pq(pqueue_t *pq, int *errnum);

// error codes
// 1 - malloc failed
// 2 - param passed as NULL
// 3 - pqueue is empty

#endif /* PQUEUE_H */