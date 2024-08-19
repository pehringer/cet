#include "map.h"

struct Map {
    char *beg;
    char *end;
    size_t cap;
    size_t dis;
    size_t ele;
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

void* memswp(char *des, char *src, size_t len) {
        for(size_t i = 0; i < len; i++) {
           des[i] = des[i] ^ src[i];
           src[i] = des[i] ^ src[i];
           des[i] = des[i] ^ src[i];
        }
    return des;
}

unsigned long djb2(const char *src, size_t len) {
    unsigned long hsh = 5381;
    for (size_t i = 0; i < len; ++i) {
        hsh = ((hsh << 5) + hsh) + src[i];
    }
    return hsh;
}

Map* map_Init(const size_t key, const size_t val, const size_t cap) {
    size_t dis = sizeof(int);
    size_t ele = dis + key + val;
    Map *m = malloc(sizeof(Map) + (cap + 1) * ele);
    if(m == 0) {
        return 0;
    }
    m->beg = (char*) (m + 1);
    m->end = m->beg + cap * ele;
    m->cap = cap;
    m->dis = dis;
    m->ele = ele;
    m->key = key;
    m->len = 0;
    char* cur = m->beg;
    while(cur != m->end) {
        *(int*) cur = -1;
        cur += ele;
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
    memset(m->end, 0, m->ele);
    memcpy(m->end + m->dis, key, m->key);
    char *cur = m->beg + (djb2(key, m->key) % m->cap) * m->ele;
    while(memcmp(cur + m->dis, m->end + m->dis, m->key) != 0) {
        if(*(int*) cur < *(int*) m->end) {
            return;
        }
        *(int*) m->end += 1;
        cur += m->ele;
        if(cur == m->end) {
            cur = m->beg;
        }
    }
    memset(cur, 0, m->ele);
    *(int*) cur = -1;
    char *nxt = cur + m->ele;
    if(nxt == m->end) {
        nxt = m->beg;
    }
    while(*(int*) nxt > 0) {
        memswp(cur, nxt, m->ele);
        *(int*) cur -= 1;
        cur = nxt;
        nxt += m->ele;
        if(nxt == m->end) {
            nxt = m->beg;
        }
    }
    m->len--;
    printf("Removed %c:\n", *(char*) key);
    cur = m->beg;
    while(cur != m->end) {
        printf("%d\t%c\t%d\n", *(int*) cur, *(char*) (cur + m->dis), *(int*) (cur + m->dis + m->key));
        cur += m->ele;
    }
    printf("\n");
}

void* map_Set(Map *m, const void *key) {
    memset(m->end, 0, m->ele);
    memcpy(m->end + m->dis, key, m->key);
    char *cur = m->beg + (djb2(key, m->key) % m->cap) * m->ele;
    while(*(int*) cur >= *(int*) m->end) {
        if(memcmp(cur + m->dis, m->end + m->dis, m->key) == 0) {
            return cur + m->dis + m->key;
        }
        *(int*) m->end += 1;
        cur += m->ele;
        if(cur == m->end) {
            cur = m->beg;
        }
    }
    if(m->len == m->cap) {
        return 0;
    }
    void *ret = cur + m->dis + m->key;
    do {
        if(*(int*) cur < *(int*) m->end) {
            memswp(cur, m->end, m->ele);
        }
        *(int*) m->end += 1;
        cur += m->ele;
        if(cur == m->end) {
            cur = m->beg;
        }
    } while(*(int*) m->end > 0);
    m->len++;
    printf("Inserted %c (Hash %d):\n", *(char*) key, djb2(key, m->key) % m->cap);
    cur = m->beg;
    while(cur != m->end) {
        printf("%d\t%c\t%d\n", *(int*) cur, *(char*) (cur + m->dis), *(int*) (cur + m->dis + m->key));
        cur += m->ele;
    }
    printf("\n");
    return ret;
}

const void* map_Get(Map *m, const void *key) {
    memset(m->end, 0, m->ele);
    memcpy(m->end + m->dis, key, m->key);
    char *cur = m->beg + (djb2(key, m->key) % m->cap) * m->ele;
    while(*(int*) cur >= *(int*) m->end) {
        if(memcmp(cur + m->dis, m->end + m->dis, m->key) == 0) {
            return cur + m->dis + m->key;
        }
        *(int*) m->end += 1;
        cur += m->ele;
        if(cur == m->end) {
            cur = m->beg;
        }
    }
    return 0;
}

const void* map_Iter(Map *m, const void *key) {
    return 0;
}

void main(void) {
    Map *m = map_Init(sizeof(char), sizeof(int), 6);
    *(int*)map_Set(m, "A") = 1;
    *(int*)map_Set(m, "B") = 22;
    *(int*)map_Set(m, "C") = 333;
    *(int*)map_Set(m, "G") = 4444;
    *(int*)map_Set(m, "M") = 55555;
    *(int*)map_Set(m, "S") = 666666;
    map_Del(m, "G");
    map_Del(m, "C");
    *(int*)map_Set(m, "F") = 7777777;
    *(int*)map_Set(m, "L") = 88888888;
    map_Del(m, "A");
}
