#include <rendering/hittable/list.h>

bool list_hit(Hittable *self, Ray r, Interval in, Hit *record) {
    List *list = (List *) self;
    bool hit = false;
    Hit temp_record;
    for (size_t i = 0; i < list->count; i++) {
        Hittable *object = list->objects[i];
        if (object->hit(object, r, in, &temp_record)) {
            hit = true;
            in.max = temp_record.time;
            *record = temp_record;
        }
    }
    return hit;
}
