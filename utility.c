
/* Liniar lerp from a to b with time t */
double lerp(double a, double b, double t) {
    return t * (b - a) + a;
}

/* Returns the lowest of a and b */
double min(double a, double b) {
    return a < b ? a : b;
}

/* Returns the greatest of a and b */
double max(double a, double b) {
    return a > b ? a : b;
}

/* Clamps value v so it is between a and b */
double clamp(double v, double a, double b) {
    double low = min(a, b), high = max(a, b);
    return min(max(low, v), high);
}