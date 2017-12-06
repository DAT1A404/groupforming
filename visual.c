#include "datastructs.c"
#include "genetic.h"
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
#ifdef __unix__
void set_color(char *ForgC, char *BackC) {
  printf(ForgC);
}

void reset_color() {
  printf(RESET);
}
#endif

/* Prints all groups */
void print_all_groups(Group *groups, int groupCount) {
    int i;
    for (i = 0; i < groupCount; i++) {
        if (i != 0) printf("\n");
        print_group(groups + i);
    }
}

/* Print a group and it's members */
void print_group(Group *g) {
    int i;
    printf("Gruppe %d (f = %.2lf):\n", g->groupNumber, g->fitnessValue);
    for (i = 0; i < g->memberCount; i++) {
        printf("%s\n", g->members[i].name);
    }
}

/* Prints an array of persons */
void print_all_persons(Person *all, int personCount, int criteriaCount) {
    int i, j;
    for (i = 0; i < personCount; i++) {
        printf("Person | n: %s c: ", all[i].name);
        for (j = 0; j < criteriaCount; j++) {
            printf("%.1lf, ", all[i].criteria[j]);
        }
        printf("\n");
    }
}

void print_chromosome(Chromosome chromosome) {
    int i;
    for (i = 0; i < chromosome.personCount; i++) {
        printf("chromo person: %s\n", chromosome.persons[i].name);
    }
}

/* Prints details about a generation */
void print_generation(int gen, double avg, double med, double best, double worst) {

    /* Keeps track of last printed */
    static double prevAvg = 0;
    static double prevMed = 0;
    static double prevBest = 0;
    static double prevWorst = 0;

    /* Print status of generation */
    printf("GA generation ");
    set_color(CYAN, BLACK); printf("%04d", gen);
    reset_color(); printf(" fitness:\t");

    /* Set color for avg and print */
    if (avg >= prevAvg)
        set_color(LIGHTGREEN, BLACK);
    else
        set_color(LIGHTRED, BLACK);
    printf("avg: %.2lf\t", avg);

    /* Set color for median and print */
    if (med >= prevMed)
        set_color(LIGHTGREEN, BLACK);
    else
        set_color(LIGHTRED, BLACK);
    printf("med: %.2lf\t", med);

    /* Set color for best and print */
    if (best >= prevBest)
        set_color(LIGHTGREEN, BLACK);
    else
        set_color(LIGHTRED, BLACK);
    printf("best: %.2lf\t", best);

    /* Set color for worst and print */
    if (worst >= prevWorst)
        set_color(LIGHTGREEN, BLACK);
    else
        set_color(LIGHTRED, BLACK);
    printf("worst: %.2lf\n", worst);

    /* Reset color */
    reset_color();

    /* Save this average as prev average */
    prevAvg = avg;
    prevBest = best;
    prevWorst = worst;
}
