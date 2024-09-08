#include <stdio.h>
#include "set.h"

size_t charHash(const void *c) {
    return *(const char*) c;
}

int charCompare(const void *l, const void *r) {
    return *(const char*) l - *(const char*) r;
}

void setPrint(const char *name, set_t *a) {
    printf("%s = {", name);
    const char *i = 0;
    while(i = set_Iterate(a, i)) {
        printf(" %c ", *i);
    }
    printf("}\n");
}

set_t* setUnion(set_t *a, set_t *b) {
    set_t *c = set_Create(set_Length(a) + set_Length(b), sizeof(char), charHash, charCompare);
    const char *i = 0;
    while(i = set_Iterate(a, i)) {
        set_Insert(c, i);
    }
    while(i = set_Iterate(b, i)) {
        set_Insert(c, i);
    }
    return c;
}

int main(void) {
    set_t *A = set_Create(4, sizeof(char), charHash, charCompare);
    set_Insert(A, "a");
    set_Insert(A, "b");
    set_Insert(A, "c");
    set_Insert(A, "d");
    setPrint("A", A);
    set_t *B = set_Create(4, sizeof(char), charHash, charCompare);
    set_Insert(B, "c");
    set_Insert(B, "d");
    set_Insert(B, "e");
    set_Insert(B, "f");
    setPrint("B", B);
    set_t *C = setUnion(A, B);
    setPrint("A u B", C);
    set_Destroy(A);
    set_Destroy(B);
    set_Destroy(C);
    return 0;
}
