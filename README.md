# ***cet***
Are you looking for a versatile set implementation written in C?
Look no further.
This library offers a hash table that utilizes Robin Hood hashing,
a technique that dynamically rearranges elements to keep them close to their ideal hash locations,
resulting in a fast and reliable set.
- Easy to use (library only has eight functions)
  + [```cet_t* cet_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```](#cet_t-cet_createsize_t-capacity-size_t-size-size_t-hashconst-void-int-compareconst-void-const-void)
  + [```void cet_Destroy(cet_t *s)```](#void-cet_destroycet_t-s)
  + [```size_t cet_Capacity(cet_t *s)```](#size_t-cet_capacitycet_t-s)
  + [```size_t cet_Length(cet_t *s)```](#size_t-cet_lengthcet_t-s)
  + [```const void* cet_Contains(cet_t *s, const void *element)```](#const-void-cet_containscet_t-s-const-void-element)
  + [```void* cet_Insert(cet_t *s, const void *element)```](#void-cet_insertcet_t-s-const-void-element)
  + [```void cet_Remove(cet_t *s, const void *element)```](#void-cet_removecet_t-s-const-void-element)
  + [```const void* cet_Iterate(cet_t *s, const void *element)```](#const-void-cet_iteratecet_t-s-const-void-element)
- Generic (can hold any kind of data)
- Lightweight (less than 175 lines of source code)
- Performant (Robin Hood hashing dynamically rearranges elements)
- Portable (only uses the C standard library)
  + ```stdlib.h```
  + ```string.h```
# Example Code
---
Compute set union:
```
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
```
```
set$ make union
gcc -fPIC -shared -I ./include ./src/cet.c -o ./cet.so
gcc -I ./include ./cet.so ./examples/union.c -o ./union.bin
./union.bin
A = { d  a  b  c }
B = { d  e  f  c }
A u B = { a  b  c  d  e  f }
rm ./union.bin
```
---
Compute set intersection:
```
cet_t* setIntersection(cet_t *a, cet_t *b) {
    cet_t *c = cet_Create(cet_Length(a), sizeof(char), charHash, charCompare);
    const char *i = 0;
    while(i = cet_Iterate(a, i)) {
        if(cet_Contains(b, i)) {
            cet_Insert(c, i);
        }
    }
    return c;
}
```
```
set$ make intersection
gcc -fPIC -shared -I ./include ./src/cet.c -o ./cet.so
gcc -I ./include ./cet.so ./examples/intersection.c -o ./intersection.bin
./intersection.bin
A = { d  a  b  c }
B = { d  e  f  c }
A n B = { d  c }
rm ./intersection.bin
```
---
Compute set difference:
```
cet_t* setDifference(cet_t *a, cet_t *b) {
    const char *i = 0;
    while(i = cet_Iterate(b, i)) {
        if(cet_Contains(a, i)) {
            cet_Remove(a, i);
        }
    }
    return a;
}
```
```
set$ make difference 
gcc -fPIC -shared -I ./include ./src/cet.c -o ./cet.so
gcc -I ./include ./cet.so ./examples/difference.c -o ./difference.bin
./difference.bin
A = { d  a  b  c }
B = { d  e  f  c }
A \ B = { a  b }
rm ./difference.bin
```
---
Custom hash/comapare functions combined with cet_Contains/cet_Insert returning pointers to set elements allows the set to function as a map.
For example character counting using a map (set holding key-value pairs):
```
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
```
```
set$ make map
gcc -fPIC -shared -I ./include ./src/cet.c -o ./cet.so
gcc -I ./include ./cet.so ./examples/map.c -o ./map.bin
./map.bin
"the quick brown fox jumps over the lazy dog"
Unique Characters: 27
Key: ' ' Value: 8
Key: 'a' Value: 1
Key: 'b' Value: 1
Key: 'c' Value: 1
Key: 'd' Value: 1
Key: 'e' Value: 3
Key: 'f' Value: 1
Key: 'g' Value: 1
Key: 'h' Value: 2
Key: 'i' Value: 1
Key: 'j' Value: 1
Key: 'k' Value: 1
Key: 'l' Value: 1
Key: 'm' Value: 1
Key: 'n' Value: 1
Key: 'o' Value: 4
Key: 'p' Value: 1
Key: 'q' Value: 1
Key: 'r' Value: 2
Key: 's' Value: 1
Key: 't' Value: 2
Key: 'u' Value: 2
Key: 'v' Value: 1
Key: 'w' Value: 1
Key: 'x' Value: 1
Key: 'y' Value: 1
Key: 'z' Value: 1
rm ./map.bin
```
---
# Library Functions
---
### ```cet_t* cet_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```
Allocates set with specified element size and capacity.  
- ```capacity``` capacity of set. Non zero value.
- ```size``` size of element type. Non zero value.
- ```hash``` hashes element. Returns hash of element.
- ```compare``` compares elements. Returns zero if equal, otherwise non zero.

---
### ```void cet_Destroy(cet_t *s)```
Deallocates set.  
- ```s``` set returned by cet_Create. Non null value.
---
### ```size_t cet_Capacity(cet_t *s)```
Returns the total number of elements in the set.  
- ```s``` set returned by cet_Create. Non null value.
---
### ```size_t cet_Length(cet_t *s)```
Returns the current number of elements being used in the set.  
- ```s``` set returned by cet_Create. Non null value.
---
### ```const void* cet_Contains(cet_t *s, const void *element)```
Returns a pointer to the element in the set if the element is present.  
Otherwise, returns NULL (not in set).  
<<<<<<< HEAD
- ```s``` set returned by cet_Create. Non null value.
- ```element``` key to lookup. Non null value.
=======
- ```s``` set returned by set_Create. Non null value.
- ```element``` element to lookup. Non null value.
>>>>>>> d0eb47db8bc1d1a9d5b7208510680d5b4b0ac231
---
### ```void* cet_Insert(cet_t *s, const void *element)```
Inserts the element into the set if the element is not present.  
Returns NULL if the insert fails (set is too full).  
Otherwise, returns a pointer to the element in the set.  
- ```s``` set returned by cet_Create. Non null value.
- ```element``` element to insert. Non null value.
---
### ```void cet_Remove(cet_t *s, const void *element)```
Removes the element in the set if the element is present.  
- ```s``` set returned by cet_Create. Non null value.
- ```element``` element to remove. Non null value.
---
### ```const void* cet_Iterate(cet_t *s, const void *element)```
Returns a pointer to the first element in the set if the element is NULL.  
Returns NULL if the element was the last element in the set or not present.  
Otherwise, returns a pointer to the next element in the set.  
- ```s``` set returned by cet_Create. Non null value.
- ```element``` current element iteration.
---
