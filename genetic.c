#include <math.h>
/* Starts the genetic algorithm
    - popsize       : the number of chromosomes in the populations
    - generations   : how many iterations the algorithm should run
    - murationrate  : how likely a mutations is to happen. Between [0..1]
*/
void genetic_algorithm(int popsize, int generations, float mutationrate) {

    int gen;

    /* Setting up multi-dimensional array of pointers to persons.
        This way no unnersasary data is copied. It's all pointers, baby.
        Also generates the some random chromosomes */
    person ***population = genetic_generate_initial_population(popsize);
    
    /* Similarly, allocate memory to generate a new population */
    person ***nextGeneration = genetic_get_memory_for_pop(popsize);

    for (gen = 0; gen < generations; gen++) {
        int i;
        person ***temp;

        /* Algorithm ... */

        /* Sort according to fitness */
        qsort(population, popsize, sizeof(person**), genetic_q_compare);
        
        /* Show how the algorithm is doing */
        printf("GA generation %d fitness|:\tavg: %.2lf\tbest: %.2lf\t worst: %.2lf\n", gen, genetic_average_fitness(population), population[0], population[popsize - 1]);

        /* Create new population */
        for (i = 0; i < popsize; i += 2) {
            
            
            person **par1, **par2, **chi1, **chi2;

            /* Selection */
            genetic_selection(population, popsize, &par1, &par2);
            
            /* Crossover */
            genetic_crossover(par1, par2, chi1, chi2);
            
            /* Mutation */
            genetic_mutation(chi1, murationrate);
            genetic_mutation(chi2, murationrate);
            
            /* Add children to next generation */
            nextGeneration[i] = chi1;
            nextGeneration[i + 1] = chi2;
            
            /* TODO: Currently we assume popsize is an even number! */
        }
        
        /* Set population to next generation, by swapping current and next */
        temp = population;
        population = nextGeneration;
        nextGeneration = temp;
    }

    free(*population); /* Pointer to the array of memberpointers */
    free(population); /* Pointer to the array of pointers, that points at array of memberpointers */
    
    free(*nextGeneration);
    free(nextGeneration);
    
    /* TODO: Return the best chromosome? */
}

/* Returns the average fitness of the population of chromosomes */
double genetic_average_fitness(person ***population, int popsize) {
    int i;
    double total = 0;
    for (i = 0; i < popsize; i++) {
        total += fitness_chromosome(population[i]);
    }
    return total / popsize;
}

/* This function takes a chromosome from the genetic algorithm and splits
    it into groups. It returns an array to the formed groups. Remember to free */
group* genetic_chromosome_to_groups(person **chromosome) {
    
    int i, j, currentPerson;
    
    /* personPerGroup is the minimum size of each group. leftoverPerons
        is the amount of groups, which have an extra member */
    int personPerGroup = _PersonCount / _GroupCount;
    int leftoverPersons = _PersonCount % personPerGroup;
    
    /* Allocate memory */
    group *groups = (group*)malloc(_GroupCount * sizeof(group));
    
    currentPerson = 0;
    for (i = 0; i < _GroupCount; i++) {
        /* TODO: Optimize group memory use. Allocate memory to groups
            members instead of fixed length which it currently is */
        
        /* Add persons to group */
        for (j = 0; j < personPerGroup; j++) {
            groups[i].members[j] = *(chromosome[currentPerson]);
            currentPerson++;
        }
        
        /* Add another person if i < leftoverPersons.
            Now that we know the size of the group let's set
            the memberCount variable in the group struct */
        if (i < leftoverPersons) {
            groups[i].members[j] = *(chromosome[currentPerson]);
            currentPerson++;
            
            groups[i].memberCount = personPerGroup + 1;
        } else {
            groups[i].memberCount = personPerGroup;
        }
    }
    
    return groups;
}

/* Compare function used to sort chromosomes. Will sort in descending order */
int genetic_q_compare(const void * i, const void * j) {
    person **a = (person**)i;
    person **b = (person**)j;

    return fitness_chromosome(b) - fitness_chromosome(a);
}

/* Returns the fitness of a chromosome */
double fitness_chromosome(person **chromosome) {
    
    /* Split chromosome into groups, then calculate fitness */
    group *groups = genetic_chromosome_to_groups(chromosome);
    double fitness = fitness_groups(groups);
    
    free (groups);
    
    return fitness;
}

/* Returns the total fitness of all groups */
double fitness_groups(group **groups, int groupCount) {
    double result = 0;
    int i;
    /* Calls the fitness_group function as many times as the number of groups */
    for (i = 0; i <= _GroupCount; i++) {
        result += fitness_group(groups[i])
    }
    return result;
}

/* Returns the total fitness of a single group */
double fitness_group(group *group) {
    double result = 0, average, criteriaMin, criteriaMax, t;
    int i, j;
    /* Goes through all criteria */
    for (i = 0; i <= _CriteriaCount; i++) {
        /*Finds the average value of specific criteria */
        average = average_criteria(group, i);
        /*Finds min and max values of specific criteria in group */
        for (j = 0; <= group->memberCount; j++) {
            double a;
            a = group.members[j].criteria[i];
            if (j == 0) {
                criteriaMin = a;
                criteriaMax = a;
            }
            /* Calls min/max function and assigns min/max */
            criteriaMin = min(criteriaMin, a);
            criteriaMax = max(criteriaMax, a);
        }
        t = inverse_lerp(criteriaMin, criteriaMax, average);
        /* Adds the fitness of the specific criteria in the single group to result */
        result += fitness_of_criteria(t, (_Criteria[i])->weight );
    }
    return result;
}

/* Returns fitness of specific criteria */
double fitness_of_criteria(double t, double weight){
    return (-4 * weight * pow(t, 2)) + (4 * weight * t) ;
}

/* Finds average of one criteria */
double average_criteria(group *group, int i){
    double result = 0;
    int j;
    for (j = 0; j <= persons_pr_group; j++) {
        result += group.members[j].criteria[i]
    }
    result = result / persons_pr_group;

    return result;
}

/* Selects two random parents from the upper half of population */
void genetic_selection(person ***population, int popsize, person **par1, person **par2) {

    int a = rand() % (popsize / 2);
    int b = rand() % (popsize / 2);

    par1 = population[a];
    par2 = population[b];
}

/* Takes two pointers to parent chromosome and creates two children, which are stored at child pointers */
void genetic_crossover(person **par1, person **par2, person **child1, person **child2) {
    
    /* The bitstring is used to determine which parent genes is taken from */
    int *bitstring = (int*) calloc(_PersonCount, sizeof(int));
    int i, limit = _PersonCount + 1;
    
    /* Reset children */
    genetic_reset_chromosome(child1);
    genetic_reset_chromosome(child2);
    
    /* Do cycle */
    i = 0;
    do {
        int indexInPar2, j;
        person* p = par1[i]
        
        /* Mark index i */
        bitstring[i] = 1;
        
        /* Find index j of element par1[i] in par2 */
        for (j = 0; j < _PersonCount; j++) {
            if (par1[i] == par2[indexInPar2]) {
                /* Set index i to j */
                i = j;
                break;
            }
        }
        
        limit--;
    } while (i != 0 && limit > 0);
    assert(limit > 0);
    
    /* Copy flagged genes from the other chromosome */
    for (i = 0; i < _PersonCount; i++) {
        if (bitstring[i]) {
            child1[i] = par1[i];
            child2[i] = par2[i];
        } else {
            child1[i] = par2[i];
            child2[i] = par1[i];
        }
    }
    
    free(bitstring);
}

/* Sets all person pointers in a chromosome to NULL */
void genetic_reset_chromosome(person **chromosome) {
    int i;
    for (i = 0; i < _PersonCount; i++) {
        chromosome[i] = NULL;
    }
}

/* Takes a pointer to chromosome and slighty alter it */
void genetic_mutation(person **child, float mutationrate) {
    
    /* Small chance of mutation */
    float rn = (rand() % 1000) / 1000.;
    if (rn <= murationrate) {
        
        person **temp;
        
        /* Find two random indexes */
        int i = 0, j = 0;
        while (i == j && _PersonCount > 0) {
            i = rand() % _PersonCount;
            j = rand() % _PersonCount;
        }
        
        /* Swaps two random elements */
        temp = child[i];
        child[i] = child[j];
        child[j] = temp;
    }
}

person*** genetic_get_memory_for_pop(int popsize) {
    int i;

    /* Create an array of pointers to persons,
        AND an array of pointers to parts of that other array */
    person *chromosomes = (person*)malloc(_PersonCount * popsize * sizeof(person));
    person **population = (person**)malloc(popsize * sizeof(person*));

    for (i = 0; i < popsize; i++) {
        /* Setup populations pointers to the right spots.
            They shall not be moved again. Only their content should change */
        population[i] = chromosomes + i * _PersonCount;
    }
    
    return population;
}

person*** genetic_generate_initial_population(int popsize) {

    int i;

    /* Allocate memory to the population */
    person ***population = genetic_get_memory_for_pop(popsize);

    /* Generate chromosomes */
    for (i = 0; i < popsize; i++) {    
        genetic_generate_chromosome(population[i]);
    }

    return population;
}

/* Put members randomly into the chromosome array */
void genetic_generate_chromosome(person **chromosome) {

    int i;

    person *temp;
    int i, n;

    /* Fill chromosome with all persons systematically */
    for (i = 0; i < _PersonCount; i++) {
        chromosome[i] = _AllPersons[i];
    }

    /* Do Fisher Yates-algorithm for shuffling array */
    for (i = 0; i < _PersonCount; i++) {
        n = rand() % (_PersonCount - i) + i;
        
        /* Swap index i and n */
        temp = chromosome[n];
        chromosome[n] = chromosome[i];
        chromosome[i] = temp;
    }
}