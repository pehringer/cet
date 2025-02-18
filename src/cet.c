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
    cet_t *s = malloc(sizeof(cet_t) + (capacity + 1) * (size + 1));
    if(s == 0) {
        return 0;
    }
    s->capacity = capacity;
    s->length = 0;
    s->size = size;
    s->hash = hash;
    s->compare = compare;
    s->begin = (unsigned char*) (s + 1);
    s->end = s->begin + capacity * (size + 1);
    memset(s->begin, EMPTY_ELEMENT, (capacity + 1) * (size + 1));
    return s;
}

void cet_Destroy(cet_t *s) {
    free(s);
}

size_t cet_Capacity(cet_t *s) {
    return s->capacity;
}

size_t cet_Length(cet_t *s) {
    return s->length;
}

const void* cet_Contains(cet_t *s, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    // Search until a slot with a smaller distance is encountered.
    while(distance <= *i) {
        // Slot contains the element.
        if(s->compare(element, i + 1) == 0) {
            return i + 1;
        }
        // Move to the next slot and update distance.
        distance++;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    // Element not found.
    return 0;
}

void* cet_Insert(cet_t *s, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    // Search until a slot with a smaller distance is encountered.
    while(distance <= *i) {
        // Slot contains the element.
        if(s->compare(element, i + 1) == 0) {
            return i + 1;
        }
        // Move to the next slot and update distance.
        distance++;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    // Slot is too far away from the initial position.
    if(distance == MAX_DISTANCE) {
        return 0;
    }
    // There are no empty slots.
    if(s->length == s->capacity) {
        return 0;
    }
    // Maintain Robin Hood ordering.
    // Shift slots rightward until a empty slot is encountered
    unsigned char *j = i;
    while(*i != EMPTY_ELEMENT) {
        // Move to the next slot and update distance.
        (*i)++;
        j += s->size + 1;
        if(j >= s->end) {
            j = s->begin;
        }
        // Swap if the slot has a smaller distance.
        if(*i > *j) {
            memcpy(s->end, j, s->size + 1);
            memcpy(j, i, s->size + 1);
            memcpy(i, s->end, s->size + 1);
        }
    }
    // Insert the element into its Robin Hood slot position.
    *i = distance;
    memcpy(i + 1, element, s->size);
    (s->length)++;
    return i + 1;
}

void cet_Remove(cet_t *s, const void *element) {
    // Compute initial position from hash.
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = s->begin + (s->hash(element) % s->capacity) * (s->size + 1);
    // Slot has a smaller distance.
    if(distance > *i) {
        return;
    }
    // Search until a slot containing the element is encountered.
    while(s->compare(element, i + 1) != 0) {
        // Move to the next slot and update distance.
        distance++;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
        // Slot has a smaller distance.
        if(distance > *i) {
            return;
        }
    }
    // Maintain Robin Hood ordering.
    // Get the next slot for shifting leftward.
    unsigned char *j = i + s->size + 1;
    if(j >= s->end) {
        j = s->begin;
    }
    // Shift slots leftward until a empty or in place slot is encountered.
    while(*j > MIN_DISTANCE) {
	// Shift slot and update its distance.
        memcpy(i, j, s->size + 1);
        (*i)--;
        // Move to the next slot.
        i = j;
        j += s->size + 1;
        if(j >= s->end) {
            j = s->begin;
        }
    }
    // Mark last shifted slot as empty.
    memset(i, EMPTY_ELEMENT, s->size + 1);
    (s->length)--;
}

const void* cet_Iterate(cet_t *s, const void *element) {
    unsigned char distance = MIN_DISTANCE;
    unsigned char *i = s->begin;
    if(element != 0) {
        i += (s->hash(element) % s->capacity) * (s->size + 1);
    }
    while(element != 0) {
        if(distance > *i) {
            return 0;
        }
        if(s->compare(element, i + 1) == 0) {
            i += s->size + 1;
            break;
        }
        distance++;
        i += s->size + 1;
        if(i >= s->end) {
            i = s->begin;
        }
    }
    while(i < s->end) {
        if(*i > EMPTY_ELEMENT) {
            return i + 1;
        }
        i += s->size + 1;
    }
    return 0;
}
