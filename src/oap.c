#include "map.h"

struct Map {
    size_t cap;
    size_t inc;
    size_t key;
    size_t len;
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
    memset(m->end, 0, m->inc);
    memcpy(m->end + m->dis, key, m->key);
    char *cur = m->beg + (djb2(key, m->key) % m->cap) * m->inc;
    while(*(int*) cur >= *(int*) m->end) {
        if(memcmp(cur + m->dis, m->end + m->dis, m->key) == 0) {
            return cur + m->dis + m->key;
        }
        *(int*) m->end += 1;
        cur += m->inc;
        if(cur == m->end) {
            cur = m->beg;
        }
    }
    if(m->len == m->cap) {
        return 0;
    }
    void *ret = cur + m->dis + m->key;
    m->len++1;
    do {
        if(*(int*) cur < *(int*) m->end) {
            for(size_t i = 0; i < m->inc; i++) {
               cur[i] = cur[i] ^ m->end[i];
               m->end[i] = cur[i] ^ m->end[i];
               cur[i] = cur[i] ^ m->end[i];
            }
        }
        *(int*) m->end += 1;
        cur += m->inc;
        if(cur == m->end) {
            cur = m->beg;
        }
    } while(*(int*) m->end > 0);
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
