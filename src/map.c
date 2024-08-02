#include "map.h"

struct Map {
    size_t cap;
    size_t inc;
    size_t key;
    size_t len;
    size_t val;
};

/*

 Header   Data                      Swap
|--------|-------------------------|---------|
______________________________________________
| MAP    | ELEMENT | ... | ELEMENT | ELEMENT |
| STRUCT | 0       |     | N       | END     |
|________|_________|_____|_________|_________|

*/

unsigned long djb2(const char *src, size_t len) {
    unsigned long hsh = 5381;
    for (size_t i = 0; i < len; ++i) {
        hsh = ((hsh << 5) + hsh) + src[i];
    }
    return hsh;
}

Map* map_Init(const size_t key, const size_t val, const size_t cap) {
    size_t inc = (sizeof(int) + key + val);
    Map *m = malloc(sizeof(Map) + (cap + 1) * inc);
    if(m == 0) {
        return 0;
    }
    m->cap = cap;
    m->inc = inc;
    m->key = key;
    m->len = 0;
    m->val = val;
    int* cur = (int*) (m + 1);
    int *end = (int*) ((char*) (m + 1) + m->cap * m->inc);
    while(cur != end) {
        *cur = -1;
        cur = (int*) ((char*) cur + m->inc);
    }
    return m;
}

void map_Free(Map *m) {
    free(m);
}

size_t map_Cap(Map *m) {
    return m->cap;
}

size_t map_Len(Map *m) {
    return m->len;
}

void map_Del(Map *m, const void *key) {
}

void* map_Set(Map *m, const void *key) {
    int *end = (int*) ((char*) (m + 1) + m->cap * m->inc);
    memset(end, 0, m->inc);
    memcpy(end + 1, key, m->key);
    //printf("Hash %d\n", djb2(key, m->key) % m->cap);
    int *cur = (int*) ((char*) (m + 1) + (djb2(key, m->key) % m->cap) * m->inc);
    while(*cur >= *end && memcmp(cur + 1, end + 1, m->key) != 0) {
        //printf("Searching\n");
        *end += 1;
        cur = (int*) ((char*) cur + m->inc);
        if(cur == end) {
            cur = (int*) (m + 1);
        }
    }
    int *ret = (int*) ((char*) (cur + 1) + m->key);
    if(memcmp(cur + 1, end + 1, m->key) == 0) {
        //printf("Found\n");
        return ret;
    }
    if(m->len == m->cap) {
        //printf("Full\n");
        return 0;
    }
    //printf("Not Found\n");
    m->len += 1;
    do {
        //printf("Inserting\n");
        if(*cur < *end) {
            for(size_t i = 0; i < m->inc; i += 1) {
               ((char*) cur)[i] = ((char*) cur)[i] ^ ((char*) end)[i];
               ((char*) end)[i] = ((char*) cur)[i] ^ ((char*) end)[i];
               ((char*) cur)[i] = ((char*) cur)[i] ^ ((char*) end)[i];
            }
        }
        *end += 1;
        cur = (int*) ((char*) cur + m->inc);
        if(cur == end) {
            cur = (int*) (m + 1);
        }
    } while(*end > 0);
    return ret;
}

const void* map_Get(Map *m, const void *key) {
    return 0;
}

const void* map_Iter(Map *m, const void *key) {
    return 0;
}

void main(void) {
    Map *m = map_Init(sizeof(char), sizeof(int), 6);
    printf("%ld\n", map_Len(m));
    *(int*)map_Set(m, "A") = 1;
    *(int*)map_Set(m, "B") = 22;
    *(int*)map_Set(m, "C") = 333;
    *(int*)map_Set(m, "G") = 4444;
    *(int*)map_Set(m, "M") = 55555;
    *(int*)map_Set(m, "S") = 666666;
    printf("S = %d\n", *(int*)map_Set(m, "S"));
    printf("M = %d\n", *(int*)map_Set(m, "M"));
    printf("G = %d\n", *(int*)map_Set(m, "G"));
    printf("C = %d\n", *(int*)map_Set(m, "C"));
    printf("B = %d\n", *(int*)map_Set(m, "B"));
    printf("A = %d\n", *(int*)map_Set(m, "A"));
    printf("%ld\n", map_Len(m));
}
