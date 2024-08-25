#include "set.h"

struct Set {
    size_t capacity;
    size_t length;
    size_t size;
    size_t (*hash)(const void*);
    int (*compare)(const void*, const void*);
    char *begin;
    char *end;
    char *swap;
};

/*

 Header   Data                      Swap
|--------|-------------------------|---------|
______________________________________________
| MAP    | ELEMENT | ... | ELEMENT | ELEMENT |
| STRUCT | 0       |     | N       | END     |
|________|_________|_____|_________|_________|

*/

size_t djb2(const void *source) {
    size_t hsh = 5381;
    hsh = ((hsh << 5) + hsh) + *(char*) source;
    return hsh;
}

int cmpr(const void *left, const void *right) {
    return *(char*) left - *(char*) right;
}

Set* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*)) {
    Set *s = malloc(sizeof(Set) + (capacity + 2) * (size + 1));
    if(s == 0) {
        return 0;
    }
    s->capacity = capacity;
    s->length = 0;
    s->size = size;
    s->hash = hash;
    s->compare = compare;
    s->begin = (char*) (s + 1);
    s->end = s->begin + capacity * (size + 1);
    s->swap = s->end + size + 1;
    char *ptr = s->begin;
    while(ptr != s->end) {
        *ptr = -1;
        ptr += s->size + 1;
    }
    return s;
}

void set_Destroy(Set *s) {
    free(s);
}

size_t set_Capacity(Set *s) {
    return s->capacity;
}

size_t set_Length(Set *s) {
    return s->length;
}

void set_Remove(Set *s, const void *element) {
    *s->end = 0;
    memcpy(s->end + 1, element, s->size);
    char *ptr = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(s->compare(ptr + 1, s->end + 1) != 0) {
        if(*ptr > *s->end) {
            return;
        }
        *s->end += 1;
        ptr += s->size + 1;
        if(ptr == s->end) {
            ptr = s->begin;
        }
    }
    *ptr = -1;
    char *nxt = ptr + s->size + 1;
    if(nxt == s->end) {
        nxt = s->begin;
    }
    while(*nxt > 0) {
        memcpy(ptr, nxt, s->size + 1);
        *ptr -= 1;
        *nxt = -1;
        ptr = nxt;
        nxt += s->size + 1;
        if(nxt == s->end) {
            nxt = s->begin;
        }
    }
    s->length--;
    printf("Removed %c:\n", *(char*) element);
    ptr = s->begin;
    while(ptr != s->end) {
        printf("%d\t%c\n", *ptr, *(ptr + 1));
        ptr += s->size + 1;
    }
    printf("\n");
}

void* set_Insert(Set *s, const void *element) {
    *s->end = 0;
    memcpy(s->end + 1, element, s->size);
    char *ptr = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(*ptr >= *s->end) {
        if(s->compare(ptr + 1, s->end + 1) == 0) {
            return ptr + 1;
        }
        *s->end += 1;
        ptr += s->size + 1;
        if(ptr == s->end) {
            ptr = s->begin;
        }
    }
    if(s->length == s->capacity) {
        return 0;
    }
    void *ret = ptr + 1;
    do {
        if(*ptr < *s->end) {
            memcpy(s->swap, ptr, s->size + 1);
            memcpy(ptr, s->end, s->size + 1);
            memcpy(s->end, s->swap, s->size + 1);
        }
        *s->end += 1;
        ptr += s->size + 1;
        if(ptr == s->end) {
            ptr = s->begin;
        }
    } while(*s->end > 0);
    s->length++;
    printf("Inserted %c (Hash %d):\n", *(char*) element, s->hash(element) % s->capacity);
    ptr = s->begin;
    while(ptr != s->end) {
        printf("%d\t%c\t%d\n", *ptr, *(ptr + 1));
        ptr += s->size + 1;
    }
    printf("\n");
    return ret;
}





/*
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

*/


void main(void) {
    Set *s = set_Create(6, sizeof(char), djb2, cmpr);
    set_Insert(s, "A");
    set_Insert(s, "B");
    set_Insert(s, "C");
    set_Insert(s, "G");
    set_Insert(s, "M");
    set_Insert(s, "S");
    set_Remove(s, "G");
    set_Remove(s, "C");
    set_Insert(s, "F");
    set_Insert(s, "L");
    set_Remove(s, "A");
}
