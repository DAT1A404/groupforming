#include "datastructs.c"
#include "visual.h"

/* Set the terminals printing colors for Windows-platform. Remember to reset */
#ifdef _WIN32
void set_color(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

/* Reset terminals printing colors */
void reset_color() {
  set_color(LIGHTGRAY, BLACK);
}
#endif

/* Set the terminal printing colors for Linux-platform. Remember to reset */
#ifdef linux
void set_color(char *ForgC, char *BackC) {
  printf(ForgC);
}

void reset_color() {
  printf(RESET);
}
#endif

/* Prints all groups */
void print_all_groups(group *groups, int groupCount) {
    int i;
    for (i = 0; i < groupCount; i++) {
        if (i != 0) printf("\n");
        print_group(groups + i);
    }
}

/* Print a group and it's members */
void print_group(group *g) {
    int i;
    printf("Gruppe %d (f = %.2lf):\n", g->groupNumber, g->fitnessValue);
    for (i = 0; i < g->memberCount; i++) {
        printf("%s\n", g->members[i].name);
    }
}

/* Prints an array of persons */
void print_all_persons(person *all, int count) {
    int i, j;
    for (i = 0; i < count; i++) {
        printf("Person | n: %s c: ", all[i].name);
        for (j = 0; j < _CriteriaCount; j++) {
            printf("%.1lf, ", all[i].criteria[j]);
        }
        printf("\n");
    }
}

void print_chromosome(person **chromosome) {
    int i;
    for (i = 0; i < _PersonCount; i++) {
        printf("chromo person: %s\n", chromosome[i]->name);
    }
}
