#include <stdio.h>
#include <stdlib.h>

/* holds structs for the whole program */
#include <datastruct.c>

/* holds void read_control() and read_data(FILE *f) */
#include <read.c>

/* holds functions for genetic algorithm */
#include <genetic.c>

int main(void) {
    
    /* Read.read_datafile(); */
    genetic_setup();
    
    return EXIT_SUCCESS;
}
