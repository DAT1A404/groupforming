#include "datastructs.c"
#include "utility.h"
#include "genetic.h"
#include "visual.h"

/* Local struct containing data about chromosomes.
    personCount and groupCount are nessary when sending
    a Chromosome to a function like qsort */
typedef struct {
    Person *persons;
    int personCount
    int groupCount;
} Chromosome;

/* Starts the genetic algorithm
    - popsize       : the number of chromosomes in the populations
    - generations   : how many iterations the algorithm should run
    - mutationrate  : how likely a mutations is to happen. Between [0..1]
    Returns a pointer to an array of groups
*/
group* genetic_algorithm(GASettings settings, DataSet data, int groupCount) {

    FILE *lgf; /* Log file */
    int gen;
    group *result;

    /* Open log file */
    lgf = fopen("genlog.csv", "w");
    assert(lgf != NULL);
    log_make_header(lgf, data, settings, groupCount);

    /* Setting up array of Chromosomes by allocating memory.
        Also generates first generation of random chromosomes */
    Chromosome *population = genetic_generate_initial_population(popsize, data, groupCount);
    
    /* Similarly, allocate memory to generate a new population */
    Chromosome *nextGeneration = genetic_get_empty_population(popsize, data, groupCount);
    
    printf("Population initialized...\n");

    for (gen = 0; gen < generations; gen++) {
        int i;
        person ***temp;

        /* Sort according to fitness */
        qsort(population, popsize, sizeof(person**), genetic_q_compare);
        
        /* Analyse how the algorithm is doing */
        genetic_analyse(lgf, gen, population, popsize);
        
        /* Create new population */
        for (i = 0; i < popsize / 2; i++) {
            
            person **par1, **par2, **chi1, **chi2;
            
            /* Make child pointers point to the next positions in nextGeneration */
            chi1 = nextGeneration[2 * i];
            chi2 = nextGeneration[2 * i + 1];
            
            /* Selection. Make par1 and par2 point to two chromosomes */
            genetic_selection(population, popsize, &par1, &par2);
            
            /* Crossover. Merge par1 and par2 into two children */
            genetic_crossover(par1, par2, chi1, chi2);
            
            /* Mutation. A small chance to make a small change in the chromosomes */
            genetic_mutation(chi1, mutationrate);
            genetic_mutation(chi2, mutationrate);
        }
        
        /* If popsize is odd, we have to add another chromosome. We just
            copy the one with highest fitness */
        if (popsize % 2 == 1) {
            genetic_copy_chromosome(nextGeneration[popsize - 1], population[0]);
        }
        
        /* Set population to next generation, by swapping current and next */
        temp = population;
        population = nextGeneration;
        nextGeneration = temp;
    }
    
    /* Sort according to fitness, then make the BEST chromosome into groups */
    qsort(population, popsize, sizeof(person**), genetic_q_compare);
    result = genetic_chromosome_to_groups(population[0]);
    
    /* Calc the fitness in the final groups */
    fitness_groups(result);

    free(*population); /* Pointer to the array of memberpointers */
    free(population); /* Pointer to the array of pointers, that points at array of memberpointers */
    
    free(*nextGeneration); /* Pointer to the array of memberpointers */
    free(nextGeneration); /* Pointer to the array of pointers, that points at array of memberpointers */
    
    /* Close log file */
    fclose(lgf);
    
    /* Return an array with groups */
    return result;
}

/* Make the header of the log file */
void log_make_header(FILE *lgf, DataSet data, GASettings settings, int groupCount) {
    fprintf(lgf, "Person Count:;%d\n", data.ersonCount);
    fprintf(lgf, "Group Count:;%d\n", groupCount);
    fprintf(lgf, "Population size:;%d\n", settings.popsize);
    fprintf(lgf, "Generations:;%d\n", settings.generations);
    fprintf(lgf, "Mutation rate:;%f\n", settings.mutationrate);
    fprintf(lgf, "Generation;Avg;Median;Best;worst\n");
}

/* Analyse a generation. Calculates interesting numbers, prints some of them
    but stores everything in the log file. Population must be sorted */
void genetic_analyse(FILE *lgf, int gen, person*** population, int popsize) {
    
    /* Calculate interesting numbers */
    double avg = genetic_average_fitness(population, popsize);
    double med = genetic_median_fitness(population, popsize);
    double best = fitness_chromosome(population[0]);
    double worst = fitness_chromosome(population[popsize - 1]);
    
    /* Write the numbers into the log file */
    fprintf(lgf, "%d;%lf;%lf;%lf;%lf\n", gen, avg, med, best, worst);
    
    /* Show how the algorithm is doing every 10'th generation */
    if (gen % 10 == 0)
        print_generation(gen, avg, med, best, worst);
}

/* Copy the content of one chromosome to another */
void genetic_copy_chromosome(person **to, person **from) {
    int i;
    for (i = 0; i < _PersonCount; i++) {
        to[i] = from[i];
    }
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

/* Returns the median fitness of the population */
double genetic_median_fitness(person ***population, int popsize) {
    int median = popsize / 2;
    return fitness_chromosome(population[median]);
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
        
        /* Setup some data about the group */
        groups[i].groupNumber = i;
        groups[i].fitnessValue = -1;

        /* Add persons to group */
        for (j = 0; j < personPerGroup; j++) {
            groups[i].members[j] = **(chromosome + currentPerson);
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
    person ***a = (person***)i;
    person ***b = (person***)j;
    
    double fa = fitness_chromosome(*a);
    double fb = fitness_chromosome(*b);
    
    /* Return -1 if A is best, returns 1 if B is best */
    if (fa > fb) return -1;
    if (fb > fa) return 1;
    return 0;
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
double fitness_groups(group *groups) {
    double result = 0;
    int i;
    /* Calls the fitness_group function as many times as the number of groups */
    for (i = 0; i < _GroupCount; i++) {
        result += fitness_group(groups + i);
    }
    return result;
}

/* Returns the total fitness of a single group */
double fitness_group(group *g) {
    double result = 0, average, criteriaMin, criteriaMax, t;
    int i, j;
    
    /* Goes through all criteria */
    for (i = 0; i < _CriteriaCount; i++) {
        
        /*Finds the average value of specific criteria */
        average = average_criteria(g, i);
        
        /*Finds min and max values of specific criteria in group */
        for (j = 0; j < g->memberCount; j++) {

            double a = g->members[j].criteria[i];
            
            /* If min/max is not set yet, set them to a */
            if (j == 0) {
                criteriaMin = a;
                criteriaMax = a;
            } else {
                
                /* Calls min/max function and finds min/max */
                criteriaMin = _min(criteriaMin, a);
                criteriaMax = _max(criteriaMax, a);
            }
        }
        
        /* t is the average compared to min and max */
        t = inverse_lerp(criteriaMin, criteriaMax, average);
        
        /* Adds the fitness of the specific criteria in the single group to result */
        result += fitness_of_criteria(t, _Criteria[i].weight);
    }
    
    /* Save fitness in the group struct */
    g->fitnessValue = result;
    
    return result;
}

/* Returns fitness of specific criteria */
double fitness_of_criteria(double t, double weight) {
    return (-4 * weight * pow(t, 2)) + (4 * weight * t) ;
}

/* Finds average of one criteria */
double average_criteria(group *g, int i) {
    double result = 0;
    int j;
    
    /* Find sum of group's criteria */
    for (j = 0; j < g->memberCount; j++) {
        result += g->members[j].criteria[i];
    }
    return result / g->memberCount; 
}

/* Selects two random parents from the upper half of population */
void genetic_selection(person ***population, int popsize, person ***par1, person ***par2) {

    int a = rand() % (popsize / 2);
    int b = rand() % (popsize / 2);

    *par1 = population[a];
    *par2 = population[b];
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
        int indexInPar2;
        
        /* Mark index i */
        bitstring[i] = 1;
        
        /* Find index of element par1[i] in par2 */
        for (indexInPar2 = 0; indexInPar2 < _PersonCount; indexInPar2++) {
            if (par1[i] == par2[indexInPar2]) {
                /* Set index i to indexInPar2 */
                i = indexInPar2;
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
    if (rn <= mutationrate) {
        
        person *temp;
        
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

/* Returns a pointer to an array of initialized chromosomes. Remeber to call free */
Chromosome * genetic_get_empty_population(int popsize, DataSet data, int groupCount) {
    int i;
    
    /* Get memory for population */
    Chromosome *population = genetic_get_memory_for_pop(popsize, data.personCount);
    
    /* Init each population */
    for (i = 0; i < popsize; i++) {
        population[i].personCount = data.personCount;
        population[i].groupCount = groupCount;
    }
    
    return population;
}

/* Returns a pointer to an array of new chromosomes. Remember to call free */
Chromosome * genetic_get_memory_for_pop(int popsize, int personCount) {
    int i;

    /* Create an array of chromosomes */
    Chromosome *population = (Chromosome*)malloc(popsize * sizeof(Chromosome));

    /* Create each chromosome's array of persons */
    for (i = 0; i < popsize; i++) {
        population[i].persons = (Person*)malloc(personCount * sizeof(Person));
    }
    
    return population;
}

/* Generates initial population by allocating memory and 
    setting chromosomes to random permutations */
Chromosome * genetic_generate_initial_population(int popsize, DataSet data, int groupCount) {

    int i;

    /* Allocate memory to the population */
    Chromosome *population = genetic_get_empty_population(popsize, data, groupCount);

    /* Generate chromosomes */
    for (i = 0; i < popsize; i++) {    
        genetic_generate_chromosome(population + i, data);
    }

    return population;
}

/* Put members randomly into the chromosome array */
void genetic_generate_chromosome(Chromosome *chromosome, DataSet data) {
    
    Person temp;
    int i, n;

    /* Fill chromosome with all persons systematically */
    for (i = 0; i < data.personCount; i++) {
        chromosome->persons[i] = data.allPersons[i];
    }

    /* Do Fisher Yates-algorithm for shuffling array */
    for (i = 0; i < data.personCount; i++) {
        n = rand() % (personCount - i) + i;
        
        /* Swap index i and n */
        temp = chromosome[n];
        chromosome[n] = chromosome[i];
        chromosome[i] = temp;
    }
}