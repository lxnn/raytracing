#include "interval.h"

bool interval_contains(Interval interval, double value) {
    return value >= interval.min && value <= interval.max;
}

bool interval_surrounds(Interval interval, double value) {
    return value > interval.min && value < interval.max;
}

double interval_clamp(Interval interval, double value) {
    if (value <= interval.min) return interval.min;
    if (value >= interval.max) return interval.max;
    return value;
}