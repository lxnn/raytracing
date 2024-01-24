#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct Interval Interval;
struct Interval {double min, max;};

bool interval_contains(Interval interval, double value);
bool interval_surrounds(Interval interval, double value);
double interval_clamp(Interval interval, double value);

#endif // INTERVAL_H