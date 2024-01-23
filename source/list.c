#include "list.h"

#include <stdlib.h>

bool list_hit(Hittable *self, Ray r, double tmin, double tmax, Hit *record) {
    List *list = (List *) self;
    for (size_t i = 0; i < list->length; i++) {
        Hittable *object = list->elements[i];
        if (object->hit(object, r, tmin, tmax, record)) {
            return true;
        }
    }
    return false;
}

void list_init(List *self, size_t capacity) {
    self->length = 0;
    self->capacity = capacity;
    self->elements = calloc(capacity, sizeof(Hittable *));
}

void list_destroy(List *self) {
    free(self->elements);
}

void list_append(List *self, Hittable *hittable) {
    if (self->length == self->capacity) {
        self->capacity *= 2;
        self->elements = realloc(self->elements, self->capacity * sizeof(Hittable *));
    }
    self->elements[self->length++] = hittable;
}
