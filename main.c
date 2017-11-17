#include <stdio.h>
#include <stdlib.h>

/* holds structs for the whole program */
#include <datastructs.c>

/* holds void read_control() and read_data(FILE *f) */
#include <read.c>

/* holds functions for genetic algorithm */
#include <genetic.c>

/* holds functions for print, export an exit-commands */
#include <commands.c>

/* holds functions that print person, persons and groups nicely */
#include <visual.c>

/* holds functions that export generated data into different file-formats */
#include <export.c>

/* holds functions that aren't applicable to above categories */
#include <utility.c>

int main(void) {

    /* Read.read_datafile(); */
    genetic_setup();

    return EXIT_SUCCESS;
}
