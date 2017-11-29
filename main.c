#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "datastructs.c"

/* holds void read_control() and read_data(FILE *f) */
#include "read.h"

/* holds functions for genetic algorithm */
#include "genetic.h"

/* holds functions for print, export an exit-commands */
/* #include "commands.h" */

/* holds functions that print person, persons and groups nicely */
#include "visual.h"

/* holds functions that export generated data into different file-formats */
/* #include "export.h" */

/* holds functions that aren't applicable to above categories */
#include "utility.h"

#define POSTREADPRINT 0
#define GENSETUP 1
#define GEN 1
#define GENPRINT 1

#define GROUP_STD (_PersonCount / 6.)
#define GROUP_MIN 2
#define GROUP_MAX (_PersonCount / 2.)
#define POPSIZE_STD 50
#define POPSIZE_MIN 10
#define POPSIZE_MAX 500
#define GENERATIONS_STD 200
#define GENERATIONS_MIN 1
#define GENERATIONS_MAX 10000
#define MUTATION_RATE_STD 0.04f
#define MUTATION_RATE_MIN 0
#define MUTATION_RATE_MAX 1

group* genetic_setup();

int main(void) {

    group *grps;

    read_data();
#if POSTREADPRINT
    print_all_persons(_AllPersons, _PersonCount);
#endif
#if GENSETUP
    grps = genetic_setup();
#endif
    /*
    print_all_groups(grps, _GroupCount);
    */
    free(_AllPersons);
    free(_Criteria);

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
group* genetic_setup() {

    group *grps;
    int groups = GROUP_STD;
    int popsize = POPSIZE_STD;
    int generations = GENERATIONS_STD;
    float mutationrate = MUTATION_RATE_STD;

    do {
        float newValue = 0;
        char option = '0';

        /* clear_screen(); */

        /* Show current settings */
        printf("== Current settings for genetic algorithm:\n(a) Number of groups: %d (%.1f in each)\n(b) Population size: %d\n(c) Generations: %d\n(d) Mutation rate: %f\n",
            groups, _PersonCount / (float)groups,  popsize, generations, mutationrate);

        /* Instruct how to change */
        printf("To change a variable, write the letter next to the setting you wanna change.\nIf ready, write (x) to start algorithm. Write (q) to cancel.\n");
        scanf(" %c", &option);

        /* Continue if option = x. Abort if option = q */
        if (option == 'x') break;
        if (option == 'q') exit(0);

        /* Change a variable */
        if (option >= 'a' && option <= 'd') {

            /* Read new value */
            printf("New value: \n");
            scanf(" %f", &newValue);

            /* Save new value */
            switch (option) {
                case 'a': groups = (int)clamp(newValue, GROUP_MIN, GROUP_MAX); break;
                case 'b': popsize = (int)clamp(newValue, POPSIZE_MIN, POPSIZE_MAX); break;
                case 'c': generations = (int)clamp(newValue, GENERATIONS_MIN, GENERATIONS_MAX); break;
                case 'd': mutationrate = clamp(newValue, MUTATION_RATE_MIN, MUTATION_RATE_MAX); break;
            }
        }

    } while (1);

    /* clear_screen(); */

    _GroupCount = groups;

    /* Run algorithm */
    printf("Running algorithm...\n");
#if GEN && GENSETUP
    grps = genetic_algorithm(popsize, generations, mutationrate);
#endif

    return grps;
}
