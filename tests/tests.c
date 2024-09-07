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
    int i;
    const int *p;
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
    int i;
    const int *p;
    set_t *s = set_Create(10, sizeof(int), intHash, intCompare);
    if(s == 0) return 1;
    i = 5;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 2;
    i = 15;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 3;
    i = 25;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 4;
    i = 35;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 5;
    i = 45;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 6;
    i = 55;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 7;
    i = 65;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 8;
    i = 75;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 9;
    i = 85;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 10;
    i = 95;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 11;
    i = 5;
    set_Remove(s, &i);
    i = 25;
    set_Remove(s, &i);
    i = 45;
    set_Remove(s, &i);
    i = 65;
    set_Remove(s, &i);
    i = 85;
    set_Remove(s, &i);
    i = 105;
    set_Remove(s, &i);
    i = 125;
    set_Remove(s, &i);
    i = 145;
    set_Remove(s, &i);
    i = 165;
    set_Remove(s, &i);
    i = 185;
    set_Remove(s, &i);
    i = 95;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 12;
    i = 85;
    if(set_Contains(s, &i) != 0) return 13;
    i = 75;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 14;
    i = 65;
    if(set_Contains(s, &i) != 0) return 15;
    i = 55;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 16;
    i = 45;
    if(set_Contains(s, &i) != 0) return 17;
    i = 35;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 18;
    i = 25;
    if(set_Contains(s, &i) != 0) return 19;
    i = 15;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 20;
    i = 5;
    if(set_Contains(s, &i) != 0) return 21;
    if(set_Capacity(s) != 10) return 22;
    if(set_Length(s) != 5) return 23;
    if((p = set_Iterate(s, 0)) == 0 || *p != 15) return 24;
    if((p = set_Iterate(s, p)) == 0 || *p != 35) return 25;
    if((p = set_Iterate(s, p)) == 0 || *p != 55) return 26;
    if((p = set_Iterate(s, p)) == 0 || *p != 75) return 27;
    if((p = set_Iterate(s, p)) == 0 || *p != 95) return 28;
    if(set_Iterate(s, p) != 0) return 29;
    i = 105;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 30;
    i = 115;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 31;
    i = 125;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 32;
    i = 135;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 33;
    i = 145;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 34;
    i = 155;
    if(set_Insert(s, &i) != 0) return 35;
    i = 165;
    if(set_Insert(s, &i) != 0) return 36;
    i = 175;
    if(set_Insert(s, &i) != 0) return 37;
    i = 185;
    if(set_Insert(s, &i) != 0) return 38;
    i = 195;
    if(set_Insert(s, &i) != 0) return 39;
    i = 15;
    set_Remove(s, &i);
    i = 35;
    set_Remove(s, &i);
    i = 55;
    set_Remove(s, &i);
    i = 75;
    set_Remove(s, &i);
    i = 95;
    set_Remove(s, &i);
    i = 105;
    set_Remove(s, &i);
    i = 115;
    set_Remove(s, &i);
    i = 125;
    set_Remove(s, &i);
    i = 135;
    set_Remove(s, &i);
    i = 145;
    set_Remove(s, &i);
    i = 5;
    if(set_Contains(s, &i) != 0) return 40;
    i = 15;
    if(set_Contains(s, &i) != 0) return 41;
    i = 25;
    if(set_Contains(s, &i) != 0) return 42;
    i = 35;
    if(set_Contains(s, &i) != 0) return 43;
    i = 45;
    if(set_Contains(s, &i) != 0) return 44;
    i = 55;
    if(set_Contains(s, &i) != 0) return 45;
    i = 65;
    if(set_Contains(s, &i) != 0) return 46;
    i = 75;
    if(set_Contains(s, &i) != 0) return 47;
    i = 85;
    if(set_Contains(s, &i) != 0) return 48;
    i = 95;
    if(set_Contains(s, &i) != 0) return 49;
    i = 105;
    if(set_Contains(s, &i) != 0) return 50;
    i = 115;
    if(set_Contains(s, &i) != 0) return 51;
    i = 125;
    if(set_Contains(s, &i) != 0) return 52;
    i = 135;
    if(set_Contains(s, &i) != 0) return 53;
    i = 145;
    if(set_Contains(s, &i) != 0) return 54;
    i = 155;
    if(set_Contains(s, &i) != 0) return 55;
    i = 165;
    if(set_Contains(s, &i) != 0) return 56;
    i = 175;
    if(set_Contains(s, &i) != 0) return 57;
    i = 185;
    if(set_Contains(s, &i) != 0) return 58;
    i = 195;
    if(set_Contains(s, &i) != 0) return 59;
    if(set_Capacity(s) != 10) return 60;
    if(set_Length(s) != 0) return 61;
    if(set_Iterate(s, p) != 0) return 62;
    set_Destroy(s);
    return 0;
}

/*
#0 #1 #2 #3 #4 #5 #6 #7 #8 #9
----------------------------- i 7
                      1
                      7
----------------------------- i 8
                      1  1
                      7  8
----------------------------- i 18
                      1  1  2
                      7  8 18
----------------------------- i 28
 3                    1  1  2
28                    7  8 18
----------------------------- i 38
 3  4                 1  1  2
28 38                 7  8 18
----------------------------- i 1
 3  4  2              1  1  2
28 38  1              7  8 18
----------------------------- i 5
 3  4  2        1     1  1  2
28 38  1        5     7  8 18
----------------------------- i 17
 3  4  5  3     1     1  2  2
28 38  8  1     5     7 17 18
----------------------------- i 0
 3  4  5  4  4  1     1  2  2
28 38  8  0  1  5     7 17 18
----------------------------- i 27
 3  4  5  6  5  5  2  1  2  3
28 38  8 18  0  1  5  7 17 27
-----------------------------
ALL GOOD
----------------------------- r 5
 3  4  5  6  5  5     1  2  3
28 38  8 18  0  1     7 17 27
----------------------------- r 7
 3  4  5  4  4        1  2  2
38  8 18  0  1       17 27 28
----------------------------- r 8
 3  4  3  3           1  2  2
38 18  0  1          17 27 28
----------------------------- r 0
 3  4  2              1  2  2
38 18  1             17 27 28
----------------------------- r 1
 3  4                 1  2  2
38 18                17 27 28
-----------------------------
ALL GOOD
----------------------------- i 15
 3  4           1     1  2  2
38 18          15    17 27 28
----------------------------- i 25
 3  4           1  2  1  2  2
38 18          15 25 17 27 28
----------------------------- i 26
 3  4  5        1  2  2  2  3
38 18 28       15 25 26 27 17
----------------------------- i 16
 4  4  5  6     1  2  2  3  3
27 18 28 38    15 25 26 16 17
----------------------------- i 14
 4  4  5  6  1  1  2  2  3  3
27 18 28 38 14 15 25 26 16 17
-----------------------------
ALL GOOD
----------------------------- r 15
 3  4  5     1  1  1  2  2  3
18 28 38    14 25 26 16 17 27
----------------------------- r 16
 3  4        1  1  1  1  2  2
28 38       14 25 26 17 27 18
----------------------------- r 27
 3           1  1  1  1  1  2
38          14 25 26 17 18 28
----------------------------- r 17
 3           1  1  1     1  2
38          14 25 26    18 28
----------------------------- r 18
             1  1  1     1  2
            14 25 26    28 38
-----------------------------
*/

int duplicate_hashes(void) {
    int i;
    const int *p;
    set_t *s = set_Create(10, sizeof(int), intHash, intCompare);
    if(s == 0) return 1;
    if(set_Capacity(s) != 10) return 2;
    if(set_Length(s) != 0) return 3;
    i = 7;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 4;
    i = 8;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 5;
    i = 18;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 6;
    i = 28;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 7;
    i = 38;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 8;
    i = 1;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 9;
    i = 5;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 10;
    i = 17;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 11;
    i = 0;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 12;
    i = 27;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 13;
    if(set_Capacity(s) != 10) return 14;
    if(set_Length(s) != 10) return 15;
    if((p = set_Iterate(s, 0)) == 0 || *p != 28) return 16;
    if((p = set_Iterate(s, p)) == 0 || *p != 38) return 17;
    if((p = set_Iterate(s, p)) == 0 || *p != 8) return 18;
    if((p = set_Iterate(s, p)) == 0 || *p != 18) return 19;
    if((p = set_Iterate(s, p)) == 0 || *p != 0) return 20;
    if((p = set_Iterate(s, p)) == 0 || *p != 1) return 21;
    if((p = set_Iterate(s, p)) == 0 || *p != 5) return 22;
    if((p = set_Iterate(s, p)) == 0 || *p != 7) return 23;
    if((p = set_Iterate(s, p)) == 0 || *p != 17) return 24;
    if((p = set_Iterate(s, p)) == 0 || *p != 27) return 25;
    if(set_Iterate(s, p) != 0) return 26;
    i = 5;
    set_Remove(s, &i);
    i = 7;
    set_Remove(s, &i);
    i = 8;
    set_Remove(s, &i);
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
    i = 6;
    set_Remove(s, &i);
    i = 9;
    set_Remove(s, &i);
    i = 27;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 27;
    i = 17;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 28;
    i = 7;
    if(set_Contains(s, &i) != 0) return 29;
    i = 5;
    if(set_Contains(s, &i) != 0) return 30;
    i = 1;
    if(set_Contains(s, &i) != 0) return 31;
    i = 0;
    if(set_Contains(s, &i) != 0) return 32;
    i = 18;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 33;
    i = 8;
    if(set_Contains(s, &i) != 0) return 34;
    i = 38;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 35;
    i = 28;
    if((p = set_Contains(s, &i)) != set_Insert(s, &i) || *p != i) return 36;
    i = 5;
    if(set_Contains(s, &i) != 0) return 37;
    if(set_Capacity(s) != 10) return 38;
    if(set_Length(s) != 5) return 39;
    if((p = set_Iterate(s, 0)) == 0 || *p != 38) return 40;
    if((p = set_Iterate(s, p)) == 0 || *p != 18) return 41;
    if((p = set_Iterate(s, p)) == 0 || *p != 17) return 42;
    if((p = set_Iterate(s, p)) == 0 || *p != 27) return 43;
    if((p = set_Iterate(s, p)) == 0 || *p != 28) return 44;
    if(set_Iterate(s, p) != 0) return 45;
    i = 15;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 46;
    i = 25;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 47;
    i = 26;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 48;
    i = 16;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 49;
    i = 14;
    if((p = set_Insert(s, &i)) == 0 | *p != i) return 50;
    i = 13;
    if(set_Insert(s, &i) != 0) return 51;
    i = 12;
    if(set_Insert(s, &i) != 0) return 52;
    i = 11;
    if(set_Insert(s, &i) != 0) return 53;
    i = 10;
    if(set_Insert(s, &i) != 0) return 54;
    i = 19;
    if(set_Insert(s, &i) != 0) return 55;
    if(set_Capacity(s) != 10) return 56;
    if(set_Length(s) != 10) return 57;
    if((p = set_Iterate(s, 0)) == 0 || *p != 27) return 58;
    if((p = set_Iterate(s, p)) == 0 || *p != 18) return 59;
    if((p = set_Iterate(s, p)) == 0 || *p != 28) return 60;
    if((p = set_Iterate(s, p)) == 0 || *p != 38) return 61;
    if((p = set_Iterate(s, p)) == 0 || *p != 14) return 62;
    if((p = set_Iterate(s, p)) == 0 || *p != 15) return 63;
    if((p = set_Iterate(s, p)) == 0 || *p != 25) return 64;
    if((p = set_Iterate(s, p)) == 0 || *p != 26) return 65;
    if((p = set_Iterate(s, p)) == 0 || *p != 16) return 66;
    if((p = set_Iterate(s, p)) == 0 || *p != 17) return 67;
    if(set_Iterate(s, p) != 0) return 68;
    i = 15;
    set_Remove(s, &i);
    i = 16;
    set_Remove(s, &i);
    i = 27;
    set_Remove(s, &i);
    i = 17;
    set_Remove(s, &i);
    i = 18;
    set_Remove(s, &i);
    i = 19;
    set_Remove(s, &i);
    i = 20;
    set_Remove(s, &i);
    i = 21;
    set_Remove(s, &i);
    i = 22;
    set_Remove(s, &i);
    i = 23;
    set_Remove(s, &i);
    if(set_Capacity(s) != 10) return 69;
    if(set_Length(s) != 5) return 70;
    if((p = set_Iterate(s, 0)) == 0 || *p != 14) return 71;
    if((p = set_Iterate(s, p)) == 0 || *p != 25) return 72;
    if((p = set_Iterate(s, p)) == 0 || *p != 26) return 73;
    if((p = set_Iterate(s, p)) == 0 || *p != 28) return 74;
    if((p = set_Iterate(s, p)) == 0 || *p != 38) return 75;
    if(set_Iterate(s, p) != 0) return 76;
    i = 14;
    set_Remove(s, &i);
    i = 25;
    set_Remove(s, &i);
    i = 26;
    set_Remove(s, &i);
    i = 28;
    set_Remove(s, &i);
    i = 38;
    set_Remove(s, &i);
    if(set_Capacity(s) != 10) return 77;
    if(set_Length(s) != 0) return 78;
    if(set_Iterate(s, 0) != 0) return 79;
    set_Destroy(s);
    return 0;
}

size_t intHashZero(const void *i) {
    return 0;
}

int maximum_distance(void) {
    int i;
    const int *p;
    set_t *s = set_Create(256, sizeof(int), intHashZero, intCompare);
    if(s == 0) return 1;
    for(int n = 1; n < 255; n++) {
        if((p = set_Insert(s, &n)) == 0 || *p != n) return 2;
        if(set_Capacity(s) != 256) return 3;
        if(set_Length(s) != n) return 4;
    }
    i = 255;
    if(set_Insert(s, &i) != 0) return 5;
    set_Destroy(s);
    return 0;
}

int main() {
    RunTests(4, (struct Test[4]) {
        (struct Test) {unique_hashes, "unique_hashes"},
        (struct Test) {identical_hashes, "identical_hashes"},
        (struct Test) {duplicate_hashes, "duplicate_hashes"},
        (struct Test) {maximum_distance, "maximum_distance"},
    });
    return 0;
}

