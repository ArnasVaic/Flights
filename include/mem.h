#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

/// These are my custom memory allocation/deallocation functions
/// The purpose of these function is to help find memory leaks

typedef void (*free_func_t)(void*);

extern size_t malloc_cnt;
extern size_t calloc_cnt;
extern size_t realloc_cnt;
extern size_t free_cnt;

void* __malloc(size_t);
void* __calloc(size_t, size_t);
void* __realloc(void*, size_t);
void __free(void*);

#endif /* MEMORY_H */