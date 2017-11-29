#include <windows.h>
#include <stdio.h>
#include "utility.h"

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
    double low = min(a, b), high = max(a, b);
    return min(max(low, v), high);
}

/* Returns value v as a time between a to b */
double inverse_lerp(double a, double b, double v) {
    if (a == b) return a;
    return (v - a) / (b - a);
}

/* Clears the terminal */
void clear_screen() {
    system("@cls||clear");
    printf("\033c");
}