#include <stdio.h>
#include "set.h"

typedef struct pair {
    char key;
    int value;
} pair;

size_t pairHash(const void *p) {
    return ((const pair*) p)->key;
}

int pairCompare(const void *l, const void *r) {
    return ((const pair*) l)->key - ((const pair*) r)->key;
}

void charaterCount(const char *string) {
    set_t *m = set_Create(1024, sizeof(pair), pairHash, pairCompare);
    while(*string) {
        pair k = {*string, 0};
        pair *p = set_Insert(m, &k);
        p->value++;
        string++;
    }
    const pair *i = 0;
    while(i = set_Iterate(m, i)) {
        printf("Key: '%c' Value: %d\n", i->key, i->value);
    }
}

int main(void) {
    printf("\"the quick brown fox jumps over the lazy dog\"\n");
    charaterCount("the quick brown fox jumps over the lazy dog");
}
