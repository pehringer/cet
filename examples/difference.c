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

set_t* setDifference(set_t *a, set_t *b) {
    const char *i = 0;
    while(i = set_Iterate(b, i)) {
	if(set_Contains(a, i)) {
            set_Remove(a, i);
        }
    }
    return a;
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
    setPrint("A \\ B", setDifference(A, B));
    set_Destroy(A);
    set_Destroy(B);
    return 0;
}
