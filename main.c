#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#if 0
/* holds structs for the whole program */
#include "datastructs.h"

/* holds void read_control() and read_data(FILE *f) */
#include "read.h"

/* holds functions for genetic algorithm */
#include "genetic.h"

/* holds functions for print, export an exit-commands */
#include "commands.h"

/* holds functions that print person, persons and groups nicely */
#include "visual.h"

/* holds functions that export generated data into different file-formats */
#include "export.h"

/* holds functions that aren't applicable to above categories */
#include "utility.h"
#endif

void clear_screen() {
    system("@cls||clear");
}

int genetic_setup();

int main(void) {

    /* Read.read_datafile(); */
    genetic_setup();

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
int genetic_setup() {
    
    int groups = 10;
    int popsize = 50;
    int generations = 200;
    float mutationrate = 0.04f;

    do {
        float newValue = 0;
        char option = '0';
        
        clear_screen();
        
        /* Show current settings */
        printf("== Current settings for genetic algorithm:\n(a) Number of groups: %d\n(b) Population size: %d\n(c) Generations: %d\n(d) Mutation rate: %f\n",
            groups, popsize, generations, mutationrate);
        
        /* Instruct how to change */
        printf("To change a variable, write the letter next to the setting you wanna change.\nIf ready, write (x) to start algorithm. Write (q) to cancel.\n");
        scanf(" %c", &option);
        
        /* Continue if option = 0 */
        if (option == 'x') break;
        if (option == 'q') return -1;
        
        /* Change a variable */
        if (option >= 'a' && option <= 'd') {
            
            /* Read new value */
            printf("New value: \n");
            scanf(" %f", &newValue);
            
            /* Save new value */
            switch (option) {
                case 'a': groups = (int)newValue; break;
                case 'b': popsize = (int)newValue; break;
                case 'c': generations = (int)newValue; break;
                case 'd': mutationrate = newValue; break;
            }
        }
        
    } while (1);
    
    clear_screen();
    
    /* Run algorithm */
    printf("Running algorithm...\n");
#if 0
    genetic_algorithm(popsize, generations, mutationrate);
#endif
    
    return 0;
}