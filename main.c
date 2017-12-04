#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32 || _WIN64
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

#define GROUP_STD (_PersonCount / 6.)
#define GROUP_MIN 2
#define GROUP_MAX (_PersonCount / 2.)
#define POPSIZE_STD 60
#define POPSIZE_MIN 10
#define POPSIZE_MAX 500
#define GENERATIONS_STD 400
#define GENERATIONS_MIN 1
#define GENERATIONS_MAX 10000
#define MUTATION_RATE_STD 0.05f
#define MUTATION_RATE_MIN 0
#define MUTATION_RATE_MAX 1

group* genetic_setup();
void print_setup_settings(int groups, int popsize, int generations, float mutationrate);

int main(int argc, char *argv[]) {

    group *grps;
    int debug = 0;
    
    if (argc >= 2 && strequal(argv[1], "--test")) debug = 1;

    srand(time(NULL));

    read_data();

#if POSTREADPRINT
    print_all_persons(_AllPersons, _PersonCount);
#endif
    
#if GENETIC_SETUP_DIALOG
    grps = genetic_setup(debug);
    if (!debug) {
        show_commands(grps);
    }
#endif
    
    free(_AllPersons);
    free(_Criteria);
    free(grps);

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
group* genetic_setup(int debug) {

    group *grps;
    int groups = GROUP_STD;
    int popsize = POPSIZE_STD;
    int generations = GENERATIONS_STD;
    float mutationrate = MUTATION_RATE_STD;

    do {
        float newValue = 0;
        char option = '0';

        clear_screen();

        /* Show current settings */
        print_setup_settings(groups, popsize, generations, mutationrate);

        /* Instruct how to change */
        set_color(COLOR_INFO, BLACK);
        printf("To change a variable, write the letter next to the setting you wanna change.\nIf ready, write (x) to start algorithm. Write (q) to cancel.\n");
        reset_color();
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

    clear_screen();

    _GroupCount = groups;

    if (debug) {
        run_tests();
    } else {
        /* Run algorithm */
        printf("Running algorithm...\n");
#if DO_GENETIC_ALGORITHM
        grps = genetic_algorithm(popsize, generations, mutationrate);
        printf("Complete!\n\n\n");
#endif
    }

    return grps;
}

/* Prints the users options nicely formatted */
void print_setup_settings(int groups, int popsize, int generations, float mutationrate) {
    
    /* Header */
    set_color(LIGHTGREEN, BLACK);
    printf("== Current settings for genetic algorithm:\n");
    
    /* print group count setting */
    set_color(YELLOW, BLACK);
    printf("(a)");
    reset_color();
    printf(" Number of groups: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d (%.1f in each)\n", groups, _PersonCount / (float)groups);
    
    /* print population size setting */
    set_color(YELLOW, BLACK);
    printf("(b)");
    reset_color();
    printf(" Population size: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d\n", popsize);
    
    /* print generation count setting */
    set_color(YELLOW, BLACK);
    printf("(c)");
    reset_color();
    printf(" Generations: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%d\n", generations);
    
    /* print mutation rate setting */
    set_color(YELLOW, BLACK);
    printf("(d)");
    reset_color();
    printf(" Mutation rate: ");
    set_color(LIGHTMAGENTA, BLACK);
    printf("%.3f\n", mutationrate);
    
    reset_color();
}
