#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "datastructs.c"
#include "read.h"
#include "genetic.h"
#include "commands.h"
#include "visual.h"
/* #include "export.h" */
#include "utility.h"
#include "ctest.h"

#define POSTREADPRINT 0
#define GENETIC_SETUP_DIALOG 1
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
void print_setup_settings(int groupCount, GASettings settings, int personCount);

int main(int argc, char *argv[]) {

    /* Main data variables */
    DataSet data;
    Group *grps;
    int groupCount;
    
    /* Debug flags */
    int debug = 0;
    
    /* Test for arguments */
    if (argc >= 2 && strequal(argv[1], "--test")) debug = 1;

    srand(time(NULL));

    /* Read datafile */
    data = read_data();

#if POSTREADPRINT
    print_all_persons(data.allPersons, data.personCount);
#endif

#if GENETIC_SETUP_DIALOG
    grps = genetic_setup(data, &groupCount, debug);
    if (!debug) {
        show_commands(grps, groupCount);
    }
#endif

    free(data.allPersons);
    free(data.allCriteria);
    free(grps);

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
Group* genetic_setup(DataSet data, int *groupCount, int debug) {

    Group *grps;
    GASettings settings;
    
    
    settings.popsize = POPSIZE_STD;
    settings.generations = GENERATIONS_STD;
    settings.mutationrate = MUTATION_RATE_STD;

    *groupCount = data.personCount / GROUP_MEMBERS_STD;

    do {
        float newValue = 0;
        char option = '0';

        clear_screen();

        /* Show current settings */
        print_setup_settings(*groupCount, settings, data.personCount);

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

    if (debug) {
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

/* Prints the users options nicely formatted */
void print_setup_settings(int groupCount, GASettings settings, int personCount) {

    /* Header */
    set_color(LIGHTGREEN, BLACK);
    printf("== Current settings for genetic algorithm:\n");

    /* print group count setting */
    set_color(YELLOW, BLACK);
    printf("(a)");
    reset_color();
    printf(" Number of groups: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d (%.1f in each)\n", groupCount, personCount / (float)groupCount);

    /* print population size setting */
    set_color(YELLOW, BLACK);
    printf("(b)");
    reset_color();
    printf(" Population size: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d\n", settings.popsize);

    /* print generation count setting */
    set_color(YELLOW, BLACK);
    printf("(c)");
    reset_color();
    printf(" Generations: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d\n", settings.generations);

    /* print mutation rate setting */
    set_color(YELLOW, BLACK);
    printf("(d)");
    reset_color();
    printf(" Mutation rate: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%.3f\n", settings.mutationrate);

    reset_color();
}
