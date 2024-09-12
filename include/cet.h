#ifndef CET_H
#define CET_H

#include <stdlib.h>
#include <string.h>

typedef struct cet_t cet_t;

cet_t* cet_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*));

void cet_Destroy(cet_t *s);

size_t cet_Capacity(cet_t *s);

size_t cet_Length(cet_t *s);

const void* cet_Contains(cet_t *s, const void *element);

void* cet_Insert(cet_t *s, const void *element);

void cet_Remove(cet_t *s, const void *element);

const void* cet_Iterate(cet_t *s, const void *element);

#endif
