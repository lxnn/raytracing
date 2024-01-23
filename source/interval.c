#include "interval.h"

bool interval_contains(Interval interval, double value) {
    return value >= interval.min && value <= interval.max;
}

bool interval_surrounds(Interval interval, double value) {
    return value > interval.min && value < interval.max;
}
