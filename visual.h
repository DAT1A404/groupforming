#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

/* Color constants for Windows */
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15
#endif

#ifdef __unix__
/* Color ANSI escape sequences */
#define BLACK           "\x1b[30m"
#define BLUE            "\x1b[34m"
#define GREEN           "\x1b[32m"
#define CYAN            "\x1b[36m"
#define RED             "\x1b[31m"
#define MAGENTA         "\x1b[35m"
#define BROWN           "\x1b[31m" /* RED fallback */
#define LIGHTGRAY       "\x1b[37m" /* WHITE fallback */
#define DARKGRAY        "\x1b[37m" /* WHITE fallback */
#define LIGHTBLUE       "\x1b[34m" /* BLUE fallback */
#define LIGHTGREEN      "\x1b[32m" /* GREEN fallback */
#define LIGHTCYAN       "\x1b[36m" /* CYAN fallback */
#define LIGHTRED        "\x1b[31m" /* RED fallback */
#define LIGHTMAGENTA    "\x1b[35m" /* MAGENTA fallback */
#define YELLOW          "\x1b[33m"
#define WHITE           "\x1b[37m"
#define RESET           "\x1b[0m"
#endif

#define COLOR_INFO LIGHTCYAN
#define COLOR_WARN YELLOW
#define COLOR_ERROR LIGHTRED

#ifdef _WIN32
void set_color(int ForgC, int BackC);
#endif
#ifdef __unix__
void set_color(char *ForgC, char *BackC);
#endif

void reset_color();
void print_all_groups(Group *groups, int groupCount);
void print_group(Group *g);
void print_all_persons(Person *all, int personCount, int criteriaCount);
void print_chromosome(Person **chromosome);
void print_generation(int gen, double avg, double med, double best, double worst);
