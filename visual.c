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
  set_color(GRAY, BLACK);
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

void print_all_groups(group *groups, int groupCount, int debug) {
    int i;
    /* print criteria-header for group generation if debug-flag is set */
    if (debug) {
      set_color(YELLOW, BLACK);
      printf("%-30s", "Criteria defined:");
      /* printing criteria name, weight and separator if not last criteria */
      for (i = 0; i < _CriteriaCount; i++) {
        printf("C%d: %10s = %.2f %s\t", i+1, _Criteria[i].name, _Criteria[i].weight, (i<_CriteriaCount-1)?"|":"");
      } printf("\n");
      reset_color();
    }
    /* invoking group-print function for i group */
    for (i = 0; i < groupCount; i++) {
        if (i != 0) printf("\n");
        print_group(groups + i, debug);
    }
}

/* Print a group and it's members */
void print_group(group *g, int debug) {
    int i, n;

    /* if debug-flag is set, print groups verbosely with all criteria for each member */
    if (debug) {
      printf("Group %d has %d members with collective fitness = %.2lf):\n", g->groupNumber + 1, g->memberCount, g->fitnessValue);
      for (i = 0; i < g->memberCount; i++) {
          printf("%-30s", g->members[i].name);
          for (n = 0; n < _CriteriaCount; n++) {
            printf("C%d:", n+1);

            /* printing criteria colorized for an easier overview */
            if (g->members[i].criteria[n] == 0) {
              set_color(RED, BLACK);
            } else {
              set_color(BLUE, BLACK);
            }
            printf("%18.2f", g->members[i].criteria[n]);
            reset_color();
            /* printing separator */
            printf(" %s\t", (n<_CriteriaCount-1)?"|":"");
          }
          printf("\n");
      }

    } else {
      printf("Group %d (fitness = %.2lf):\n", g->groupNumber + 1, g->fitnessValue);
      for (i = 0; i < g->memberCount; i++) {
          printf("%s\n", g->members[i].name);
      }
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
        set_color(GREEN, BLACK);
    else
        set_color(RED, BLACK);
    printf("avg: %.2lf\t", avg);

    /* Set color for median and print */
    if (med >= prevMed)
        set_color(LIGHTGREEN, BLACK);
    else
        set_color(LIGHTRED, BLACK);
    printf("med: %.2lf\t", med);

    /* Set color for best and print */
    if (best >= prevBest)
        set_color(GREEN, BLACK);
    else
        set_color(RED, BLACK);
    printf("best: %.2lf\t", best);

    /* Set color for worst and print */
    if (worst >= prevWorst)
        set_color(GREEN, BLACK);
    else
        set_color(RED, BLACK);
    printf("worst: %.2lf\n", worst);

    /* Reset color */
    reset_color();

    /* Save this average as prev average */
    prevAvg = avg;
    prevBest = best;
    prevWorst = worst;
}
