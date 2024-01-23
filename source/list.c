#include "list.h"

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
