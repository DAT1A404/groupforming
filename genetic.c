
void genetic_algorithm(person *all[], int personCount, int popsize, int generations, double mutationrate) {
    
    int gen;
    
    person ***population genetic_generate_initial_population(all, personCount, popsize);
    
    for (gen = 0; gen < generations; gen++) {
        
        /* Algorithm ... */
    }
    
    free(*population); /* Pointer to the array of memberpointers */
    free(population); /* Pointer to the array of pointers, that points at array of memberpointers */
}

person*** genetic_generate_initial_population(person *all[], int personCount, int popsize) {
    
    int i;
    
    person *chromosomes = (person*)malloc(personCount * popsize * sizeof(person));
    person **population = (person**)malloc(popsize * sizeof(person*));
    
    for (i = 0; i < popsize; i++) {
        genetic_generate_chromosome(population[i], all, personCount);
    }
    
    return population;
}

void genetic_generate_chromosome(person **chromosome, person *all[], int personCount) {
    
    /* Put members randomly into the chromosome array */
}
