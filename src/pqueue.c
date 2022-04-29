#include <pqueue.h>

pq_node_t* create_node(void *data, size_t size, int64_t prio, int *errnum) {
	pq_node_t *node = (pq_node_t*) __malloc(sizeof(pq_node_t));
	++malloc_cnt;

	if(node == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	
	node->data = __malloc(size);
	++malloc_cnt;
	
	if(node->data == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	
	memcpy(node->data, data, size);
	
	node->next = NULL;
	node->prio = prio;
	
	return node;
}

void free_pq_node(pq_node_t **node, int* errnum) {
	if((node == NULL) || (*node == NULL)) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	if((*node)->data != NULL) {
		__free((*node)->data);
		++free_cnt;
	}
	__free(*node);
	++free_cnt;

	*node = NULL;
}

pqueue_t* create_pq(int *errnum) {
	pqueue_t *pq = (pqueue_t*) __malloc(sizeof(pqueue_t));
	++malloc_cnt;

	if(pq == NULL) {
		if(errnum != NULL) *errnum = 1;
		return NULL;
	}
	pq->head = NULL;
	return pq;
}

uint8_t is_pq_empty(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return 0;
	}
	return (pq->head == NULL);
}

void pq_push(pqueue_t *pq, void* data, size_t size, int64_t prio, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	
	if((pq->head == NULL) || (pq->head->prio < prio)) {
		pq_node_t *temp = pq->head;
		pq->head = create_node(data, size, prio, errnum);
		pq->head->next = temp;
		return;
	}
	
	pq_node_t *iter = pq->head;
	while(iter->next && (iter->next->prio > prio)) {
		iter = iter->next;
	}
	pq_node_t *node = create_node(data, size, prio, errnum);
	if(node == NULL) return;
	pq_node_t* temp = iter->next;
	iter->next = node;
	node->next = temp;
}

void* pq_pop(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return NULL;
	}
	if(pq->head == NULL) {
		if(errnum != NULL) *errnum = 3;
		return NULL;
	}
	
	pq_node_t *temp = pq->head;
	void* data = temp->data;
	pq->head = pq->head->next;
	__free(temp);
	++free_cnt;
	return data;
}

void* pq_peek(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return NULL;
	}
	if(pq->head == NULL) {
		if(errnum != NULL) *errnum = 3;
		return NULL;
	}
	return pq->head->data;
}

size_t pq_elem_count(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return 0;
	}
	size_t i;
	pq_node_t *iter = pq->head;
	for(i = 0; iter; ++i) {
		iter = iter->next;
	}
	return i;
}

void free_pq(pqueue_t *pq, int *errnum) {
	if(pq == NULL) {
		if(errnum != NULL) *errnum = 2;
		return;
	}
	pq_node_t *iter = pq->head;
	while(iter) {
		pq_node_t *temp = iter;
		iter = iter->next;
		free_pq_node(&temp, errnum);
	}
	__free(pq);
	++free_cnt;
}