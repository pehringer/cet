#include <stdio.h>
#include "cet.h"

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
    cet_t *m = cet_Create(1024, sizeof(pair), pairHash, pairCompare);
    while(*string) {
        pair k = {*string, 0};
        pair *p = cet_Insert(m, &k);
        p->value++;
        string++;
    }
    const pair *i = 0;
    printf("Unique Characters: %d\n", cet_Length(m));
    while(i = cet_Iterate(m, i)) {
        printf("Key: '%c' Value: %d\n", i->key, i->value);
    }
}

int main(void) {
    printf("\"the quick brown fox jumps over the lazy dog\"\n");
    charaterCount("the quick brown fox jumps over the lazy dog");
}
