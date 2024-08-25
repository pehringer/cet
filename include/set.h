#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Set Set;

Set* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*));

void set_Destroy(Set *s);

size_t set_Capacity(Set *s);

size_t set_Length(Set *s);

const void* set_Contains(Set *s, const void *element);

void* set_Insert(Set *s, const void *element);

void set_Remove(Set *s, const void *element);

const void* set_Iterate(Set *s, const void *element);

#endif
