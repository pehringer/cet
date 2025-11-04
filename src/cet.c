#include "cet.h"

/*

Cet memory layout:

          cet_t.begin         cet_t.end
         /                   /
____________________________________
| cet_t | slot | ... | slot | slot |
|       | 0    |     | n    | swap |
|_______|______|_____|______|______|


element memory layout:

  distance   data
 /          /
_______________________
| unsigned | unsigned |
| char     | char(s)  |
|__________|__________|

*/

struct cet_t {
    size_t capacity;
    size_t length;
    size_t size;
    size_t (*hash)(const void*);
    int (*compare)(const void*, const void*);
    unsigned char *begin;
    unsigned char *end;
};

const unsigned char EMPTY_ELEMENT = 0;
const unsigned char MIN_DISTANCE = 1;
const unsigned char MAX_DISTANCE = UCHAR_MAX;

cet_t* cet_Create(size_t capacity, size_t size, size_t (*hash)(const void*), int (*compare)(const void*, const void*)) {
    cet_t *p = malloc(sizeof(cet_t) + (capacity + 1) * (size + 1));
    if(p == 0) {
        return 0;
    }
    p->capacity = capacity;
    p->length = 0;
    p->size = size;
    p->hash = hash;
    p->compare = compare;
    p->begin = (unsigned char*) (p + 1);
    p->end = p->begin + capacity * (size + 1);
    memset(p->begin, EMPTY_ELEMENT, (capacity + 1) * (size + 1));
    return p;
}

void cet_Destroy(cet_t *p) {
    free(p);
}

size_t cet_Capacity(cet_t *p) {
    return p->capacity;
}

size_t cet_Length(cet_t *p) {
    return p->length;
}

const void* cet_Contains(cet_t *p, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = p->begin + (p->hash(element) % p->capacity) * (p->size + 1);
    // Search until a slot with a smaller distance is encountered.
    while(distance <= *i) {
        // Slot contains the element.
        if(p->compare(element, i + 1) == 0) {
            return i + 1;
        }
        // Move to the next slot and update distance.
        distance++;
        i += p->size + 1;
        if(i >= p->end) {
            i = p->begin;
        }
    }
    // Element not found.
    return 0;
}

const void* cet_Insert(cet_t *p, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = p->begin + (p->hash(element) % p->capacity) * (p->size + 1);
    // Search until a slot with a smaller distance is encountered.
    while(distance <= *i) {
        // Slot contains the element.
        if(p->compare(element, i + 1) == 0) {
            memcpy(i + 1, element, p->size);
            return i + 1;
        }
        // Move to the next slot and update distance.
        distance++;
        i += p->size + 1;
        if(i >= p->end) {
            i = p->begin;
        }
    }
    // Slot is too far away from the initial position.
    if(distance == MAX_DISTANCE) {
        return 0;
    }
    // There are no empty slots.
    if(p->length == p->capacity) {
        return 0;
    }
    // Maintain Robin Hood ordering.
    // Shift slots rightward until a empty slot is encountered
    unsigned char *j = i;
    while(*i != EMPTY_ELEMENT) {
        // Move to the next slot and update distance.
        (*i)++;
        j += p->size + 1;
        if(j >= p->end) {
            j = p->begin;
        }
        // Swap if the slot has a smaller distance.
        if(*i > *j) {
            memcpy(p->end, j, p->size + 1);
            memcpy(j, i, p->size + 1);
            memcpy(i, p->end, p->size + 1);
        }
    }
    // Insert the element into its Robin Hood slot position.
    *i = distance;
    memcpy(i + 1, element, p->size);
    (p->length)++;
    return i + 1;
}

void cet_Remove(cet_t *p, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = p->begin + (p->hash(element) % p->capacity) * (p->size + 1);
    // Slot has a smaller distance.
    if(distance > *i) {
        return;
    }
    // Search until a slot containing the element is encountered.
    while(p->compare(element, i + 1) != 0) {
        // Move to the next slot and update distance.
        distance++;
        i += p->size + 1;
        if(i >= p->end) {
            i = p->begin;
        }
        // Slot has a smaller distance.
        if(distance > *i) {
            return;
        }
    }
    // Maintain Robin Hood ordering.
    // Get the next slot for shifting leftward.
    unsigned char *j = i + p->size + 1;
    if(j >= p->end) {
        j = p->begin;
    }
    // Shift slots leftward until a empty or in place slot is encountered.
    while(*j > MIN_DISTANCE) {
	// Shift slot and update its distance.
        memcpy(i, j, p->size + 1);
        (*i)--;
        // Move to the next slot.
        i = j;
        j += p->size + 1;
        if(j >= p->end) {
            j = p->begin;
        }
    }
    // Mark last shifted slot as empty.
    memset(i, EMPTY_ELEMENT, p->size + 1);
    (p->length)--;
}

const void* cet_Iterate(cet_t *p, const void *element) {
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = p->begin;
    if(element != 0) {
        i += (p->hash(element) % p->capacity) * (p->size + 1);
    }
    while(element != 0) {
        if(distance > *i) {
            return 0;
        }
        if(p->compare(element, i + 1) == 0) {
            i += p->size + 1;
            break;
        }
        distance++;
        i += p->size + 1;
        if(i >= p->end) {
            i = p->begin;
        }
    }
    while(i < p->end) {
        if(*i > EMPTY_ELEMENT) {
            return i + 1;
        }
        i += p->size + 1;
    }
    return 0;
}
