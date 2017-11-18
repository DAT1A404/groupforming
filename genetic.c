/* Starts the genetic algorithm
    - person **all  : a pointer to an array with size personCount
    - personCount   : the number of persons in the datafile
    - popsize       : the number of chromosomes in the populations
    - generations   : how many iterations the algorithm should run
    - murationrate  : how likely a mutations is to happen. Between [0..1]
*/
void genetic_algorithm(person **all, int personCount, int popsize, int generations, double mutationrate) {

    int gen;

    /* Setting up multi-dimensional array of pointers to persons.
        This way no unnersasary data is copied. It's all pointers, baby */
    person ***population genetic_generate_initial_population(all, personCount, popsize);

    for (gen = 0; gen < generations; gen++) {
        int i;

        /* Algorithm ... */

        /* Sort according to fitness */
        qsort(population, popsize, sizeof(person**), genetic_q_compare);

        /* Create new population */
        for (i = 0; i < popsize; i += 2) {

            person **par1, **par2, **chi1, **chi2;

            /* Selection */
            genetic_selection(population, popsize, &par1, &par2);
        }
    }

    free(*population); /* Pointer to the array of memberpointers */
    free(population); /* Pointer to the array of pointers, that points at array of memberpointers */
}

/* Compare function used to sort chromosomes. Will sort in descending order */
int genetic_q_compare(const void * i, const void * j) {
    person **a = (person**)i;
    person **b = (person**)j;

    return fitness_chromosome(b) - fitness_chromosome(a);
}

/* Selects two random parents from the upper half of population */
void genetic_selection(person ***population, int popsize, person ***par1, person ***par2) {

    int a = rand() % (popsize / 2);
    int b = rand() % (popsize / 2);

    *par1 = &(population[a]);
    *par2 = &(population[b]);
}

person*** genetic_generate_initial_population(person **all, int personCount, int popsize) {

    int i;

    /* Create an array of pointers to persons,
        AND an array of pointers to parts of that other array */
    person *chromosomes = (person*)malloc(personCount * popsize * sizeof(person));
    person **population = (person**)malloc(popsize * sizeof(person*));

    for (i = 0; i < popsize; i++) {
        /* Setup populations pointers to the right spots.
            They shall not be moved again. Only their content should change */
        population[i] = chromosomes + i * personCount;

        /* Generate chromosome */
        genetic_generate_chromosome(population[i], all, personCount);
    }

    return population;
}

/* Put members randomly into the chromosome array */
void genetic_generate_chromosome(person **chromosome, person **all, int personCount) {

    int i;

    /* g_rand() returns an array with all integers between 0 and the argument,
        where each values occurs exactly once. */
    int *rn_idx = g_rand(personCount);

    for (i = 0; i < personCount; i++) {
        /* Fill chromosome systematically with pointers to members */
        chromosome[i] = all[rn_idx[i]];
    }

    free(rn_idx);
}

int * g_rand(int personCount) {

    /* declaring and filling array from 0 to personCount */
    int *arrRand = (int *) malloc(sizeof(int) * personCount);
    int i, n, temp;
    
    for (i=0; i < personCount; i++) {
        arrRand[i] = i;
    }

    /* implementing Fisher Yates-algorithm for shuffling array */
    for (i=0; i < personCount; i++) {
        n = rand() % (personCount - i) + i;
        temp = arrRand[n];
        arrRand[n] = arrRand[i];
        arrRand[i] = temp;
    }

    return arrRand;
}
