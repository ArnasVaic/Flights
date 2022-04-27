#include <mem.h>

size_t malloc_cnt = 0;
size_t calloc_cnt = 0;
size_t realloc_cnt = 0;
size_t free_cnt = 0;

void* __malloc(size_t size) {
    ++malloc_cnt;
    return malloc(size);
}

void* __calloc(size_t size, size_t nmemb) {
    ++calloc_cnt;
    return calloc(size, nmemb);
}

void* __realloc(void *ptr, size_t size) {
    ++realloc_cnt;
    return realloc(ptr, size);
}

void __free(void *ptr) {
    ++free_cnt;
    free(ptr);
}