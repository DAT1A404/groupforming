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
