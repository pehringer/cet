#include <stdio.h>
#include "set.h"

struct Test {
    int (*function)(void);
    char *name;
};

void RunTests(int number, struct Test *tests) {
    int failed = 0;
    int passed = 0;
    printf("--------------------------------------\n");
    for(int index = 0; index < number; index++) {
        printf("%s: ", tests[index].name);
        fflush(stdout);
        if(tests[index].function()) {
            printf("FAILED\n");
            failed++;
        } else {
            printf("PASSED\n");
            passed++;
        }
    }
    printf("--------------------------------------\n");
    printf("Tests Failed: %d Tests Passed: %d\n", failed, passed);
    printf("--------------------------------------\n");
}

size_t intHash(const void *i) {
    return *(int*) i;
}

int intCompare(const void *l, const void *r) {
    return *(int*) l - *(int*) r;
}

int zero_cap_set(void) {
    set_t *s = set_Create(0, sizeof(int), intHash, intCompare);
    if(s == 0) return 1;
    set_Destroy(s);
    return 0;
}


int main() {
    RunTests(1, (struct Test[1]) {
        (struct Test) {zero_cap_set, "zero_cap_set"},
    });
    return 0;
}

