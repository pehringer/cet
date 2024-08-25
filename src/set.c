#include "set.h"

struct Set {
    size_t capacity;
    size_t length;
    size_t size;
    size_t (*hash)(const void*);
    int (*compare)(const void*, const void*);
    char *begin;
    char *end;
    char *target;
};

const unsigned char EMPTY_ELEMENT = 0;
const unsigned char MIN_DISTANCE = 1;
const unsigned char MAX_DISTANCE = 255;

/*

 Header   Data                      Swap      Traversal
|--------|-------------------------|---------|---------|
________________________________________________________
| MAP    | ELEMENT | ... | ELEMENT | ELEMENT | ELEMENT |
| STRUCT | 0       |     | N       | END     | TARGET  |
|________|_________|_____|_________|_________|_________|

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
    s->target = s->end + size + 1;
    char *i = s->begin;
    while(i != s->end) {
        *i = EMPTY_ELEMENT;
        i += s->size + 1;
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

const void* set_Contains(Set *s, const void *element) {
    *s->target = MIN_DISTANCE;
    memcpy(s->target + 1, element, s->size);
    char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(1) {
        if(*s->target > *i) {
            break;
        }
        if(s->compare(s->target + 1, i + 1) == 0) {
            return i + 1;
        }
        *s->target += 1;
        i += s->size + 1;
        if(i == s->end) {
            i = s->begin;
        }
    }
    return 0;
}

void* set_Insert(Set *s, const void *element) {
    *s->target = MIN_DISTANCE;
    memcpy(s->target + 1, element, s->size);
    char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(1) {
        if(*s->target == MAX_DISTANCE) {
            return 0;
        }
        if(*s->target > *i) {
            break;
        }
        if(s->compare(s->target + 1, i + 1) == 0) {
            return i + 1;
        }
        *s->target += 1;
        i += s->size + 1;
        if(i == s->end) {
            i = s->begin;
        }
    }
    if(s->length == s->capacity) {
        return 0;
    }
    void *j = i + 1;
    while(1) {
        if(*s->target > *i) {
            memcpy(s->end, i, s->size + 1);
            memcpy(i, s->target, s->size + 1);
            memcpy(s->target, s->end, s->size + 1);
        }
        if(*s->target == EMPTY_ELEMENT) {
            break;
        }
        *s->target += 1;
        i += s->size + 1;
        if(i == s->end) {
            i = s->begin;
        }
    }
    s->length++;
    //printf("Inserted %c (Hash %d):\n", *(char*) element, s->hash(element) % s->capacity);
    //i = s->begin;
    //while(i != s->end) {
    //    printf("%d\t%c\t%d\n", *i, *(i + 1));
    //    i += s->size + 1;
    //}
    //printf("\n");
    return j;
}

void set_Remove(Set *s, const void *element) {
    *s->target = MIN_DISTANCE;
    memcpy(s->target + 1, element, s->size);
    char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(1) {
        if(*s->target > *i) {
            return;
        }
        if(s->compare(s->target + 1, i + 1) == 0) {
            break;
        }
        *s->target += 1;
        i += s->size + 1;
        if(i == s->end) {
            i = s->begin;
        }
    }
    *i = EMPTY_ELEMENT;
    char *j = i;
    while(1) {
        j += s->size + 1;
        if(j == s->end) {
            j = s->begin;
        }
        if(*j <= MIN_DISTANCE) {
            break;
        }
        memcpy(s->end, i, s->size + 1);
        memcpy(i, j, s->size + 1);
        memcpy(j, s->end, s->size + 1);
        *i -= 1;
        i = j;
    }
    s->length--;
    //printf("Removed %c:\n", *(char*) element);
    //i = s->begin;
    //while(i != s->end) {
    //    printf("%d\t%c\n", *i, *(i + 1));
    //    i += s->size + 1;
    //}
    //printf("\n");
}

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
    const char *r = set_Contains(s, "A");
    if(r) printf("found: %c\n", *r); else printf("missing: A\n");
    r = set_Contains(s, "B");
    if(r) printf("found: %c\n", *r); else printf("missing: B\n");
    r = set_Contains(s, "C");
    if(r) printf("found: %c\n", *r); else printf("missing: C\n");
    r = set_Contains(s, "D");
    if(r) printf("found: %c\n", *r); else printf("missing: D\n");
    r = set_Contains(s, "E");
    if(r) printf("found: %c\n", *r); else printf("missing: E\n");
    r = set_Contains(s, "F");
    if(r) printf("found: %c\n", *r); else printf("missing: F\n");
    r = set_Contains(s, "L");
    if(r) printf("found: %c\n", *r); else printf("missing: L\n");
    r = set_Contains(s, "M");
    if(r) printf("found: %c\n", *r); else printf("missing: M\n");
    r = set_Contains(s, "S");
    if(r) printf("found: %c\n", *r); else printf("missing: S\n");
}
