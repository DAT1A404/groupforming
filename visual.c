#include "visual.h"

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
    printf("Gruppe %d:\n", g->groupNumber);
    for (i = 0; i < g->memberCount; i++) {
        printf("%s\n", g->members[i].name);
    }
}