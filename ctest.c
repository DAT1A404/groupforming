#include "datastructs.h"
#include "genetic.h"
#include "visual.h"
#include "ctest.h"

/* Runs all test */
void run_tests() {
#if 0
    person **chromosome;
    
    /* Set seed to 0 so we always get the same results */
    srand(0);
    
    /* Setup a chromosome */
    chromosome = *(genetic_get_memory_for_pop(1));
    genetic_generate_chromosome(chromosome);
    
    /* Make tests */
    test_fitness(chromosome);
    
    /* End test */
    free(chromosome);
    printf("Test complete!\n");
#endif
}

/* Test fitness functions */
void test_fitness(Chromosome chromosome) {
#if 0
    int i;
    
    /* Test if fitness function always returns the same */
    for (i = 0; i < 10; i++) {
        assert(fitness_chromosome(chromosome) == fitness_chromosome(chromosome));
    }
#endif
}