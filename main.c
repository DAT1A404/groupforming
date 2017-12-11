#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "datastructs.c"
#include "read.h"
#include "genetic.h"
#include "commands.h"
#include "visual.h"
#include "export.h"
#include "utility.h"
#include "ctest.h"

#define DEBUG_POST_READ_PRINT 0
#define DO_GENETIC_SETUP_DIALOG 1
#define DO_GENETIC_ALGORITHM 1

#define GROUP_MEMBERS_STD 6
#define GROUP_MIN 2
#define GROUP_MEMBERS_MIN 2
#define POPSIZE_STD 60
#define POPSIZE_MIN 10
#define POPSIZE_MAX 500
#define GENERATIONS_STD 400
#define GENERATIONS_MIN 1
#define GENERATIONS_MAX 10000
#define MUTATION_RATE_STD 0.05f
#define MUTATION_RATE_MIN 0
#define MUTATION_RATE_MAX 1

Group* genetic_setup(DataSet data, int *groupCount, int debug);
double calculate_max_min(DataSet data);
void print_setup_settings(int groupCount, GASettings settings, int personCount, double maxMinCriteria);

int main(int argc, char *argv[]) {

    /* Main data variables */
    DataSet data;
    Group *grps;
    int groupCount;

    /* Debug flags */
    int test = 0, debug = 0;
    char dummy[40];

    srand(time(NULL));

    /* Test for arguments */
    if (argc >= 2 && strequal(argv[1], "--test")) test = 1;
    else if (argc >= 2 && strequal(argv[1], "-v")) debug = 1;

    /* Printing welcome-message for user */
    set_color(COLOR_INFO, BLACK);
    printf("GroupForming-project, please follow on-screen instructions when prompted.\n");
    reset_color();

    /* Read datafile */
    data = read_data();

#if DEBUG_POST_READ_PRINT
    print_all_persons(data.allPersons, data.personCount);
#endif

#if DO_GENETIC_SETUP_DIALOG
    grps = genetic_setup(data, &groupCount, debug);
    if (!test) {
        set_color(COLOR_INFO, BLACK);
        printf("Press ANY key to continue. The screen will be cleared.");
        reset_color();
        scanf(" %s", dummy);
        clear_screen();
        show_commands(grps, groupCount, data, debug);
    }
#endif

    free(data.allPersons);
    free(data.allCriteria);
    free(grps);

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
Group* genetic_setup(DataSet data, int *groupCount, int test) {

    Group *grps;
    GASettings settings;

    /* Set settings to default values */
    settings.popsize = POPSIZE_STD;
    settings.generations = GENERATIONS_STD;
    settings.mutationrate = MUTATION_RATE_STD;

    *groupCount = data.personCount / GROUP_MEMBERS_STD;

    do {
        float newValue = 0;
        char option = '0';

        clear_screen();

        /* Show current settings - and pass largest minimum
        printf("PENIS: %lf\n", calculate_max_min(data)); */
        print_setup_settings(*groupCount, settings, data.personCount, calculate_max_min(data));
        /* Instruct how to change */
        set_color(COLOR_INFO, BLACK);
        printf("To change a variable, write the letter next to the setting you wanna change.\nIf ready, write (x) to start algorithm. Write (q) to cancel.\n");
        reset_color();
        scanf(" %c", &option);

        /* Continue if option == x. Abort if option == q */
        if (option == 'x') break;
        if (option == 'q') exit(0);

        /* Change a variable */
        if (option >= 'a' && option <= 'd') {

            /* Read new value */
            printf("New value: \n");
            scanf(" %f", &newValue);

            /* Save new value */
            switch (option) {
                case 'a': *groupCount = (int)clamp(newValue, GROUP_MIN, data.personCount / GROUP_MEMBERS_MIN); break;
                case 'b': settings.popsize = (int)clamp(newValue, POPSIZE_MIN, POPSIZE_MAX); break;
                case 'c': settings.generations = (int)clamp(newValue, GENERATIONS_MIN, GENERATIONS_MAX); break;
                case 'd': settings.mutationrate = clamp(newValue, MUTATION_RATE_MIN, MUTATION_RATE_MAX); break;
            }
        }

    } while (1);

    clear_screen();

    if (test) {
        /* run_tests(settings, data, *groupCount); */
    } else {
        /* Run algorithm */
        printf("Running algorithm...\n");
#if DO_GENETIC_ALGORITHM
        grps = genetic_algorithm(settings, data, *groupCount);
        printf("Complete!\n\n");
#endif
    }

    return grps;
}

double calculate_max_min(DataSet data) {
  int i;
  double maxMin = 0;
  for (i=0; i < data.criteriaCount; i++) {
    if (maxMin < data.allCriteria[i].minimum) {
      maxMin = data.allCriteria[i].minimum;
    }
  }
  return maxMin;
}

/* Prints the users options nicely formatted */
void print_setup_settings(int groupCount, GASettings settings, int personCount, double maxMinCriteria) {

    /* Header */
    set_color(GREEN, BLACK);
    printf("== Current settings for genetic algorithm:\n");
    reset_color();

    /* print group count setting */
    printf("(a) Number of groups: ");
    if (maxMinCriteria <= personCount / groupCount) {
      set_color(MAGENTA, BLACK);
      printf("%d (%.1f in each)\n", groupCount, personCount / (float)groupCount);
    } else {
      set_color(RED, BLACK);
      printf("%d (%.1f in each) minimum criteria is %.2lf!\n", groupCount, personCount / (float)groupCount, maxMinCriteria);
    }
    reset_color();

    /* print population size setting */
    printf("(b) Population size: ");
    set_color(MAGENTA, BLACK);
    printf("%d\n", settings.popsize);
    reset_color();

    /* print generation count setting */
    printf("(c) Generations: ");
    set_color(MAGENTA, BLACK);
    printf("%d\n", settings.generations);
    reset_color();

    /* print mutation rate setting */
    printf("(d) Mutation rate: ");
    set_color(MAGENTA, BLACK);
    printf("%.3f\n", settings.mutationrate);
    reset_color();
}
