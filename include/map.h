#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Map Map;

Map* map_Init(const size_t key, const size_t val, const size_t cap);

void map_Free(Map *m);

size_t map_Cap(Map *m);

size_t map_Len(Map *m);

void map_Del(Map *m, const void *key);

void* map_Set(Map *m, const void *key);

const void* map_Get(Map *m, const void *key);

const void* map_Iter(Map *m, const void *key);

#endif
