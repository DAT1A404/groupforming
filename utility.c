#include <stdio.h>
#include "utility.h"

#define CLEARSCREENALLOWED 1

/* Liniar lerp from a to b with time t */
double lerp(double a, double b, double t) {
    return t * (b - a) + a;
}

/* Returns the lowest of a and b */
double _min(double a, double b) {
    return a < b ? a : b;
}

/* Returns the greatest of a and b */
double _max(double a, double b) {
    return a > b ? a : b;
}

/* Clamps value v so it is between a and b */
double clamp(double v, double a, double b) {
    double low = _min(a, b), high = _max(a, b);
    return _min(_max(low, v), high);
}

/* Returns value v as a time between a to b */
double inverse_lerp(double a, double b, double v) {
    if (a == b) return a;
    return (v - a) / (b - a);
}

/* Clears the terminal */
void clear_screen() {
#if CLEARSCREENALLOWED
    printf("\033c");
#endif
}
