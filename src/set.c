#include "set.h"

struct set_t {
    size_t capacity;
    size_t length;
    size_t size;
    size_t (*hash)(const void*);
    int (*compare)(const void*, const void*);
    unsigned char *begin;
    unsigned char *end;
};

const unsigned char EMPTY_ELEMENT = 0;
const unsigned char MIN_DISTANCE = 1;
const unsigned char MAX_DISTANCE = 255;

/*

 header   begin                     end
|--------|-------------------------|---------|
______________________________________________
| set_t  | element | ... | element | element |
| struct | 0       |     | n       | swap    |
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

set_t* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*)) {
    set_t *s = malloc(sizeof(set_t) + (capacity + 1) * (size + 1));
    if(s == 0) {
        return 0;
    }
    s->capacity = capacity;
    s->length = 0;
    s->size = size;
    s->hash = hash;
    s->compare = compare;
    s->begin = (unsigned char*) (s + 1);
    s->end = s->begin + capacity * (size + 1);
    memset(s->begin, EMPTY_ELEMENT, (capacity + 1) * (size + 1));
    return s;
}

void set_Destroy(set_t *s) {
    free(s);
}

size_t set_Capacity(set_t *s) {
    return s->capacity;
}

size_t set_Length(set_t *s) {
    return s->length;
}

const void* set_Contains(set_t *s, const void *element) {
    unsigned char d = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(d <= *i) {
        if(s->compare(element, i + 1) == 0) {
            return i + 1;
        }
        d += 1;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    return 0;
}

void* set_Insert(set_t *s, const void *element) {
    unsigned char d = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    while(d <= *i) {
        if(s->compare(element, i + 1) == 0) {
            return i + 1;
        }
        d += 1;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    if(d == MAX_DISTANCE) {
        return 0;
    }
    if(s->length == s->capacity) {
        return 0;
    }
    unsigned char *j = i;
    while(*i != EMPTY_ELEMENT) {
        *i += 1;
        j += s->size + 1;
        if(j >= s->end) {
            j = s->begin;
        }
        if(*i > *j) {
            memcpy(s->end, j, s->size + 1);
            memcpy(j, i, s->size + 1);
            memcpy(i, s->end, s->size + 1);
        }
    }
    *i = d;
    memcpy(i + 1, element, s->size);
    s->length++;
    printf("Inserted %c (Hash %d):\n", *(char*) element, s->hash(element) % s->capacity);
    j = s->begin;
    while(j != s->end) {
        printf("%d\t%c\n", *j, *(j + 1));
        j += s->size + 1;
    }
    printf("\n");
    return i + 1;
}

void set_Remove(set_t *s, const void *element) {
    unsigned char d = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    if(d > *i) {
        return;
    }
    while(s->compare(element, i + 1) != 0) {
        d += 1;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
        if(d > *i) {
            return;
        }
    }
    unsigned char *j = i + s->size + 1;
    if(j >= s->end) {
        j = s->begin;
    }
    while(*j > MIN_DISTANCE) {
        memcpy(i, j, s->size + 1);
        *i -= 1;
        i = j;
        j += s->size + 1;
        if(j >= s->end) {
            j = s->begin;
        }
    }
    memset(i, EMPTY_ELEMENT, s->size + 1);
    s->length--;
    printf("Removed %c:\n", *(char*) element);
    i = s->begin;
    while(i != s->end) {
        printf("%d\t%c\n", *i, *(i + 1));
        i += s->size + 1;
    }
    printf("\n");
}

const void* set_Iterate(set_t *s, const void *element) {
    unsigned char d = MIN_DISTANCE;
    unsigned char *i = s->begin;
    if(element != 0) {
        i += (s->hash(element) % s->capacity) * (s->size + 1);
    }
    while(element != 0) {
        if(d > *i) {
            return 0;
        }
        if(s->compare(element, i + 1) == 0) {
            i += s->size + 1;
            break;
        }
        d += 1;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    while(i < s->end) {
        if(*i > EMPTY_ELEMENT) {
            return i + 1;
        }
        i += s->size + 1;
    }
    return 0;
}

void main(void) {
    const char *i = 0;
    set_t *s = set_Create(6, sizeof(char), djb2, cmpr);


    set_Insert(s, "A");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "B");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "C");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "G");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "M");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "S");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "G");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "C");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "F");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Insert(s, "L");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "A");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "B");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "S");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "F");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "L");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


    set_Remove(s, "M");
    i = 0;
    while((i = set_Iterate(s, i))) {
        printf("iteration: %c\n", *i);
    }
    printf("\n");


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
    r = set_Contains(s, "G");
    if(r) printf("found: %c\n", *r); else printf("missing: G\n");
    r = set_Contains(s, "L");
    if(r) printf("found: %c\n", *r); else printf("missing: L\n");
    r = set_Contains(s, "M");
    if(r) printf("found: %c\n", *r); else printf("missing: M\n");
    r = set_Contains(s, "S");
    if(r) printf("found: %c\n", *r); else printf("missing: S\n");
}
