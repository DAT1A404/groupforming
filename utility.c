#include <stdio.h>
#include <string.h>
#include "datastructs.c"
#include "utility.h"

#if _WIN32
#include <windows.h>
#endif

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
#if _WIN32
    system("cls||clear");
#endif
#endif
}

/* Compare if strings are equal */
int strequal(const char * a, const char * b) {
    return strcmp(a, b) == 0;
}

/* Returns the max posible fitness a solution can have.
    Only works if criteria is [0..1] */
double get_max_fitness_overall(DataSet data, int groupCount) {
    return get_max_fitness_group(data) * groupCount;
}

/* Returns the max posible fitness a group can have.
    Only works if criteria is [0..1] */
double get_max_fitness_group(DataSet data) {
    int i;
    double maxFit = 0;
    
    /* Assuming all criteria is binary for each person, max
        fitness will be equal to the sum of all weights or
        0 if 0 is greater */
    for (i = 0; i < data.criteriaCount; i++) {
        maxFit = _max(0, data.allCriteria[i].weight);
    }
    return maxFit;
}