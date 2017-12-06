#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

/* Color constants for Windows */
#define BLACK           0
#define DARKBLUE        1
#define DARKGREEN       2
#define DARKCYAN        3
#define DARKRED         4
#define DARKMAGENTA     5
#define BROWN           6
#define GRAY            7
#define DARKGRAY        8
#define BLUE            9
#define GREEN           10
#define CYAN            11
#define RED             12
#define MAGENTA         13
#define YELLOW          14
#define WHITE           15
#endif

#ifdef __unix__
/* Color ANSI escape sequences */
#define BLACK           "\x1b[30m"
#define DARKBLUE        "\x1b[34m"
#define DARKGREEN       "\x1b[32m"
#define DARKCYAN        "\x1b[36m"
#define DARKRED         "\x1b[31m"
#define DARKMAGENTA     "\x1b[35m"
#define BROWN           "\x1b[31m" /* RED fallback */
#define GRAY            "\x1b[37m" /* WHITE fallback */
#define DARKGRAY        "\x1b[37m" /* WHITE fallback */
#define BLUE            "\x1b[34m" /* BLUE fallback */
#define GREEN           "\x1b[32m" /* GREEN fallback */
#define CYAN            "\x1b[36m" /* CYAN fallback */
#define RED             "\x1b[31m" /* RED fallback */
#define MAGENTA         "\x1b[35m" /* MAGENTA fallback */
#define YELLOW          "\x1b[33m"
#define WHITE           "\x1b[37m"
#define RESET           "\x1b[0m"
#endif

#define COLOR_INFO CYAN
#define COLOR_WARN YELLOW
#define COLOR_ERROR RED

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
void print_chromosome(Chromosome chromosome);
void print_generation(int gen, double avg, double med, double best, double worst);
