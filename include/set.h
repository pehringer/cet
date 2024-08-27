#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct set_t set_t;

set_t* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*));

void set_Destroy(set_t *s);

size_t set_Capacity(set_t *s);

size_t set_Length(set_t *s);

const void* set_Contains(set_t *s, const void *element);

void* set_Insert(set_t *s, const void *element);

void set_Remove(set_t *s, const void *element);

const void* set_Iterate(set_t *s, const void *element);

#endif
