# ***map***
Are you looking for a versatile set implementation for C? Look no further. This library offers a hash table that utilizes Robin Hood hashing, a technique that dynamically rearranges elements to keep them close to their ideal hash locations, resulting in a fast and reliable set.
- Easy to use (library only has eight functions)
  + [```Set* set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```]()
  + [```void set_Destroy(Set *s)```]()
  + [```size_t set_Capacity(Set *s)```]()
  + [```size_t set_Length(Set *s)```]()
  + [```void set_Remove(Set *s, const void *element)```]()
  + [```void* set_Insert(Set *s, const void *element)```]()
  + [```const void* set_Contains(Set *s, const void *element)```]()
  + [```const void* set_Iterate(Set *s, const void *element)```]()
- Generic (can hold any kind of data)
- Lightweight (less than XXX lines of source code)
- Performant (Robin Hood hashing dynamically rearranges elements)
- Portable (only uses the C standard library)
  + ```stdlib.h```
  + ```string.h```
# Example Code
# Library Functions
---
### ```set_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*))```
Allocates set with specified element size and capacity.  
- ```key``` size of key type.
- ```val``` size of value type.
- ```cap``` capacity of map.
---
### ```void set_Destroy(Set *s)```
Deallocates set.  
- ```m``` map returned by map_Init.
---
### ```size_t set_Capacity(Set *s)```
Returns the total number of elements.  
- ```m``` map returned by map_Init.
---
### ```size_t set_Length(Set *s)```
Returns the current number of elements being used.  
- ```m``` map returned by map_Init.
---
### ```void set_Remove(Set *s, const void *element)```
Removes the element if the element is present.  
- ```m``` map returned by map_Init.
- ```key``` key to delete.
---
### ```void* set_Insert(Set *s, const void *element)```
Inserts the element if the element is not present.  
Returns NULL if the insert fails (set is too full).  
Otherwise, returns a pointer to the element.  
- ```m``` map returned by map_Init.
- - ```key``` key to update or insert.
---
### ```const void* set_Contains(Set *s, const void *element)```
Returns a pointer to the element if the element is present.  
Otherwise, returns NULL (not in set).  
- ```m``` map returned by map_Init.
- ```key``` key to lookup.
---
### ```const void* set_Iterate(Set *s, const void *element)```
Returns a pointer to the first element if the element is NULL.  
Returns NULL if the element was the last element or not present.  
Otherwise, returns a pointer to the next element.  
- ```m``` map returned by map_Init.
- ```key``` current key iteration.
---
