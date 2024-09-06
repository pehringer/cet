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
        int error = tests[index].function();
        if(error) {
            printf("FAILED: %d\n", error);
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

int unique_hashes(void) {
    int i = 42;
    const int *p = 0;
    set_t *s = set_Create(10, sizeof(int), intHash, intCompare);
    if(s == 0) return 1;
    i = 1;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 2;
    i = 2;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 3;
    i = 6;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 4;
    i = 7;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 5;
    i = 8;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 6;
    i = 9;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 7;
    i = 10;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 8;
    i = 13;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 9;
    i = 14;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 10;
    i = 15;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 11;
    i = 0;
    set_Remove(s, &i);
    i = 1;
    set_Remove(s, &i);
    i = 2;
    set_Remove(s, &i);
    i = 3;
    set_Remove(s, &i);
    i = 4;
    set_Remove(s, &i);
    i = 5;
    set_Remove(s, &i);
    i = 6;
    set_Remove(s, &i);
    i = 7;
    set_Remove(s, &i);
    i = 8;
    set_Remove(s, &i);
    i = 9;
    set_Remove(s, &i);
    i = 0;
    if(set_Contains(s, &i) != 0) return 12;
    i = 1;
    if(set_Contains(s, &i) != 0) return 13;
    i = 2;
    if(set_Contains(s, &i) != 0) return 14;
    i = 3;
    if(set_Contains(s, &i) != 0) return 15;
    i = 4;
    if(set_Contains(s, &i) != 0) return 16;
    i = 5;
    if(set_Contains(s, &i) != 0) return 17;
    i = 6;
    if(set_Contains(s, &i) != 0) return 18;
    i = 7;
    if(set_Contains(s, &i) != 0) return 19;
    i = 8;
    if(set_Contains(s, &i) != 0) return 20;
    i = 9;
    if(set_Contains(s, &i) != 0) return 21;
    i = 10;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 22;
    i = 11;
    if(set_Contains(s, &i) != 0) return 23;
    i = 12;
    if(set_Contains(s, &i) != 0) return 24;
    i = 13;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 25;
    i = 14;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 26;
    i = 15;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 27;
    i = 16;
    if(set_Contains(s, &i) != 0) return 28;
    i = 17;
    if(set_Contains(s, &i) != 0) return 29;
    i = 18;
    if(set_Contains(s, &i) != 0) return 30;
    i = 19;
    if(set_Contains(s, &i) != 0) return 31;
    if(set_Capacity(s) != 10) return 32;
    if(set_Length(s) != 4) return 33;
    if((p = set_Iterate(s, 0)) == 0 || *p != 10) return 34;
    if((p = set_Iterate(s, p)) == 0 || *p != 13) return 35;
    if((p = set_Iterate(s, p)) == 0 || *p != 14) return 36;
    if((p = set_Iterate(s, p)) == 0 || *p != 15) return 37;
    if(set_Iterate(s, p) != 0) return 38;
    i = 11;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 39;
    i = 12;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 40;
    i = 16;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 41;
    i = 17;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 42;
    i = 18;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 43;
    i = 19;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 44;
    i = 0;
    if(set_Insert(s, &i) != 0) return 45;
    i = 3;
    if(set_Insert(s, &i) != 0) return 46;
    i = 4;
    if(set_Insert(s, &i) != 0) return 47;
    i = 5;
    if(set_Insert(s, &i) != 0) return 48;
    i = 10;
    set_Remove(s, &i);
    i = 11;
    set_Remove(s, &i);
    i = 12;
    set_Remove(s, &i);
    i = 13;
    set_Remove(s, &i);
    i = 14;
    set_Remove(s, &i);
    i = 15;
    set_Remove(s, &i);
    i = 16;
    set_Remove(s, &i);
    i = 17;
    set_Remove(s, &i);
    i = 18;
    set_Remove(s, &i);
    i = 19;
    set_Remove(s, &i);
    i = 0;
    if(set_Contains(s, &i) != 0) return 49;
    i = 1;
    if(set_Contains(s, &i) != 0) return 50;
    i = 2;
    if(set_Contains(s, &i) != 0) return 51;
    i = 3;
    if(set_Contains(s, &i) != 0) return 52;
    i = 4;
    if(set_Contains(s, &i) != 0) return 53;
    i = 5;
    if(set_Contains(s, &i) != 0) return 54;
    i = 6;
    if(set_Contains(s, &i) != 0) return 55;
    i = 7;
    if(set_Contains(s, &i) != 0) return 56;
    i = 8;
    if(set_Contains(s, &i) != 0) return 57;
    i = 9;
    if(set_Contains(s, &i) != 0) return 58;
    i = 10;
    if(set_Contains(s, &i) != 0) return 59;
    i = 11;
    if(set_Contains(s, &i) != 0) return 60;
    i = 12;
    if(set_Contains(s, &i) != 0) return 61;
    i = 13;
    if(set_Contains(s, &i) != 0) return 62;
    i = 14;
    if(set_Contains(s, &i) != 0) return 63;
    i = 15;
    if(set_Contains(s, &i) != 0) return 64;
    i = 16;
    if(set_Contains(s, &i) != 0) return 65;
    i = 17;
    if(set_Contains(s, &i) != 0) return 66;
    i = 18;
    if(set_Contains(s, &i) != 0) return 67;
    i = 19;
    if(set_Contains(s, &i) != 0) return 68;
    if(set_Capacity(s) != 10) return 69;
    if(set_Length(s) != 0) return 70;
    if(set_Iterate(s, p) != 0) return 71;
    set_Destroy(s);
    return 0;
}

int identical_hashes(void) {
    return 0;
}

int duplicate_hashes(void) {
    return 0;
}

int maximum_distance(void) {
    return 0;
}

int main() {
    RunTests(1, (struct Test[1]) {
        (struct Test) {unique_hashes, "unique_hashes"},
    });
    return 0;
}

