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

cet_t* setDifference(cet_t *a, cet_t *b) {
    const char *i = 0;
    while(i = cet_Iterate(b, i)) {
	if(cet_Contains(a, i)) {
            cet_Remove(a, i);
        }
    }
    return a;
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
    setPrint("A \\ B", setDifference(A, B));
    cet_Destroy(A);
    cet_Destroy(B);
    return 0;
}
