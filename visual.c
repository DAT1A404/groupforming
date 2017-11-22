
#include <windows.h>

/* Color constants */
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

/* Set the terminals printing colors. Remember to reset */
void set_color(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

/* Reset terminals printing colors */
void reset_color() {
    set_color(LIGHTGRAY, BLACK);
}

/* Prints all groups */
void print_all_groups(group **groups, int groupCount) {
    int i;
    for (i = 0; i < groupCount; i++) {
        if (i != 0) printf("\n");
        print_group(groups[i]);
    }
}

/* Print a group and it's members */
void print_group(group *g) {
    int i;
    printf("Gruppe %d:\n");
    for (i = 0; i < g->memberCount; i++) {
        printf("%s\n", g->members[i].name);
    }
}