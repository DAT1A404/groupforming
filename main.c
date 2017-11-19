#include <stdio.h>
#include <stdlib.h>

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

int main(void) {

    /* Read.read_datafile(); */
    genetic_setup();

    return EXIT_SUCCESS;
}

/* Initializing genetic variables before running the algorithm */
int genetic_setup() {
    
    int groups = _PersonCount / 7;
    int popsize = 50;
    int generations = 200;
    float mutationrate = 0.04f;

    do {
        float newValue = 0;
        char option = '0';
        
        clear_screen();
        
        /* Show current settings */
        printf("== Current settings for genetic algorithm:\n(1) Number of groups: %d\n(2) Population size: %d\n(3) Generations: %d\n(4) Mutation rate: %f\n",
            groups, popsize, generations, mutationrate);
        
        /* Instruct how to change */
        printf("To change a variable, please write the number next to the setting you wanna change.\nIf ready, write '0' instead!\n");
        scanf(" %c ", &option);
        
        /* Continue if option = 0 */
        if (option = '0') break;
        
        /* Read new value */
        printf("New value: \n");
        scanf(" %f ", newValue);
        
        /* Save new value */
        switch (option) {
            case '1': groups = (int)newValue; break;
            case '2': popsize = (int)newValue; break;
            case '3': generations = (int)newValue; break;
            case '4': mutationrate = newValue; break;
        }
        
    } while (1);
    
    clear_screen();
    
    /* Run algorithm */
    printf("Running algorithm...\n");
    genetic_algorithm(popsize, generations, mutationrate);
}