#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

/* Color constants for Windows */
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             12
#define MAGENTA         5
#define YELLOW          14
#define WHITE           15
#endif

#ifdef linux
/* Color ANSI escape sequences */
#define BLACK           "\x1b[30m"
#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"
#define YELLOW          "\x1b[33m"
#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define WHITE           "\x1b[37m"
#define RESET           "\x1b[0m"
#endif

#define COLOR_INFO BLUE
#define COLOR_WARN YELLOW
#define COLOR_ERROR RED

#ifdef _WIN32
void set_color(int ForgC, int BackC);
#endif
#ifdef linux
void set_color(char *ForgC, char *BackC);
#endif

void reset_color();
void print_all_groups(group *groups, int groupCount);
void print_group(group *g);
void print_all_persons(person *all, int count);
void print_chromosome(person **chromosome);
void print_generation(int gen, person ***population, int popsize);
