# ***set***
Are you looking for a versatile set implementation written in C? Look no further. This library offers a hash table that utilizes Robin Hood hashing, a technique that dynamically rearranges elements to keep them close to their ideal hash locations, resulting in a fast and reliable set.
- Easy to use (library only has eight functions)
  + [```Set* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```](#set_t-set_createsize_t-capacity-size_t-size-size_t-hashconst-void-int-compareconst-void-const-void)
  + [```void set_Destroy(Set *s)```](#void-set_destroyset_t-s)
  + [```size_t set_Capacity(Set *s)```](#size_t-set_capacityset_t-s)
  + [```size_t set_Length(Set *s)```](#size_t-set_lengthset_t-s)
  + [```const void* set_Contains(Set *s, const void *element)```](#const-void-set_containsset_t-s-const-void-element)
  + [```void* set_Insert(Set *s, const void *element)```](#void-set_insertset_t-s-const-void-element)
  + [```void set_Remove(Set *s, const void *element)```](#void-set_removeset_t-s-const-void-element)
  + [```const void* set_Iterate(Set *s, const void *element)```](#const-void-set_iterateset_t-s-const-void-element)
- Generic (can hold any kind of data)
- Lightweight (less than XXX lines of source code)
- Performant (Robin Hood hashing dynamically rearranges elements)
- Portable (only uses the C standard library)
  + ```stdlib.h```
  + ```string.h```
# Example Code
# Library Functions
---
### ```set_t* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```
Allocates set with specified element size and capacity.  
- ```capacity``` capacity of set.
- ```size``` size of element type.
- ```hash``` hashes element. Returns hash of element.
- ```compare``` compares elements. Returns zero if equal, otherwise non zero.

---
### ```void set_Destroy(set_t *s)```
Deallocates set.  
- ```s``` set returned by set_Create.
---
### ```size_t set_Capacity(set_t *s)```
Returns the total number of elements in the set.  
- ```s``` set returned by set_Create.
---
### ```size_t set_Length(set_t *s)```
Returns the current number of elements being used in the set.  
- ```s``` set returned by set_Create.
---
### ```const void* set_Contains(set_t *s, const void *element)```
Returns a pointer to the element in the set if the element is present.  
Otherwise, returns NULL (not in set).  
- ```s``` set returned by set_Create.
- ```element``` key to lookup.
---
### ```void* set_Insert(set_t *s, const void *element)```
Inserts the element into the set if the element is not present.  
Returns NULL if the insert fails (set is too full).  
Otherwise, returns a pointer to the element in the set.  
- ```s``` set returned by set_Create.
- ```element``` element to insert.
---
### ```void set_Remove(set_t *s, const void *element)```
Removes the element in the set if the element is present.  
- ```s``` set returned by set_Create.
- ```element``` element to remove.
---
### ```const void* set_Iterate(set_t *s, const void *element)```
Returns a pointer to the first element in the set if the element is NULL.  
Returns NULL if the element was the last element in the set or not present.  
Otherwise, returns a pointer to the next element in the set.  
- ```s``` set returned by set_Create.
- ```element``` current element iteration.
---
