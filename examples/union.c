#include <stdio.h>
#include "cet.h"

size_t charHash(const void *c) {
    return *(const char*) c;
}

int charCompare(const void *l, const void *r) {
    return *(const char*) l - *(const char*) r;
}

void setPrint(const char *name, cet_t *a) {
    printf("%s = {", name);
    const char *i = 0;
    while(i = cet_Iterate(a, i)) {
        printf(" %c ", *i);
    }
    printf("}\n");
}

cet_t* setUnion(cet_t *a, cet_t *b) {
    cet_t *c = cet_Create(cet_Length(a) + cet_Length(b), sizeof(char), charHash, charCompare);
    const char *i = 0;
    while(i = cet_Iterate(a, i)) {
        cet_Insert(c, i);
    }
    while(i = cet_Iterate(b, i)) {
        cet_Insert(c, i);
    }
    return c;
}

int main(void) {
    cet_t *A = cet_Create(4, sizeof(char), charHash, charCompare);
    cet_Insert(A, "a");
    cet_Insert(A, "b");
    cet_Insert(A, "c");
    cet_Insert(A, "d");
    setPrint("A", A);
    cet_t *B = cet_Create(4, sizeof(char), charHash, charCompare);
    cet_Insert(B, "c");
    cet_Insert(B, "d");
    cet_Insert(B, "e");
    cet_Insert(B, "f");
    setPrint("B", B);
    cet_t *C = setUnion(A, B);
    setPrint("A u B", C);
    cet_Destroy(A);
    cet_Destroy(B);
    cet_Destroy(C);
    return 0;
}
