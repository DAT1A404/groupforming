#include "datastructs.c"
#include "utility.h"
#include "genetic.h"
#include "visual.h"

/* Starts the genetic algorithm
    - popsize       : the number of chromosomes in the populations
    - generations   : how many iterations the algorithm should run
    - mutationrate  : how likely a mutations is to happen. Between [0..1]
    Returns a pointer to an array of groups
*/
Group* genetic_algorithm(GASettings settings, DataSet data, int groupCount) {

    FILE *lgf; /* Log file */
    int gen;
    Group *result;

    /* Open log file */
    lgf = fopen("genlog.csv", "w");
    assert(lgf != NULL);
    log_make_header(lgf, data, settings, groupCount);

    /* Setting up array of Chromosomes by allocating memory.
        Also generates first generation of random chromosomes */
    Chromosome *population = genetic_generate_initial_population(settings.popsize, data, groupCount);

    /* Similarly, allocate memory to generate a new population */
    Chromosome *nextGeneration = genetic_get_empty_population(settings.popsize, data, groupCount);

    printf("Population initialized...\n");

    for (gen = 0; gen < settings.generations; gen++) {
        int i;
        Chromosome *tempPop;

        /* Sort according to fitness */
        qsort(population, settings.popsize, sizeof(Chromosome), genetic_q_compare);

        /* Analyse how the algorithm is doing */
        genetic_analyse(lgf, gen, population, settings.popsize);

        /* Create new population */
        for (i = 0; i < settings.popsize / 2; i++) {

            Chromosome parent1, parent2, *child1, *child2;

            /* Make child pointers point to the next positions in nextGeneration */
            child1 = &(nextGeneration[2 * i]);
            child2 = &(nextGeneration[2 * i + 1]);

            /* Selection. Make parent1 and parent2 point to two chromosomes */
            genetic_selection(population, settings.popsize, &parent1, &parent2);

            /* Crossover. Merge parent1 and parent2 into two children */
            genetic_crossover(parent1, parent2, child1, child2);

            /* Mutation. A small chance to make a small change in the chromosomes */
            genetic_mutation(child1, settings.mutationrate);
            genetic_mutation(child2, settings.mutationrate);
        }

        /* If popsize is odd, we have to add another chromosome. We just
            copy the one with highest fitness */
        if (settings.popsize % 2 == 1) {
            nextGeneration[settings.popsize - 1] = population[0];
        }

        /* Set population to next generation, by swapping current and next */
        tempPop = population;
        population = nextGeneration;
        nextGeneration = tempPop;
    }

    /* Sort according to fitness, then make the BEST chromosome into groups */
    qsort(population, settings.popsize, sizeof(Chromosome), genetic_q_compare);
    result = genetic_chromosome_to_groups(population[0]);

    /* Calc the fitness in the final groups */
    fitness_groups(result, groupCount, data.allCriteria, data.criteriaCount);

    /* Clean up memory */
    genetic_kill_population(population, settings.popsize);
    genetic_kill_population(nextGeneration, settings.popsize);

    /* Close log file */
    fclose(lgf);

    /* Return an array with groups */
    return result;
}

/* Make the header of the log file */
void log_make_header(FILE *lgf, DataSet data, GASettings settings, int groupCount) {
    fprintf(lgf, "Person Count:;%d\n", data.personCount);
    fprintf(lgf, "Group Count:;%d\n", groupCount);
    fprintf(lgf, "Population size:;%d\n", settings.popsize);
    fprintf(lgf, "Generations:;%d\n", settings.generations);
    fprintf(lgf, "Mutation rate:;%f\n", settings.mutationrate);
    fprintf(lgf, "Generation;Avg;Median;Best;worst\n");
}

/* Analyse a generation. Calculates interesting numbers, prints some of them
    but stores everything in the log file. Population must be sorted */
void genetic_analyse(FILE *lgf, int gen, Chromosome *population, int popsize) {

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

/* Returns the average fitness of the population of chromosomes */
double genetic_average_fitness(Chromosome *population, int popsize) {
    int i;
    double total = 0;
    for (i = 0; i < popsize; i++) {
        total += fitness_chromosome(population[i]);
    }
    return total / popsize;
}

/* Returns the median fitness of the population */
double genetic_median_fitness(Chromosome *population, int popsize) {
    int median = popsize / 2;
    return fitness_chromosome(population[median]);
}

/* This function takes a chromosome from the genetic algorithm and splits
    it into groups. It returns an array to the formed groups. Remember to free */
Group* genetic_chromosome_to_groups(Chromosome chromo) {

    int i, j, currentPerson;

    /* personPerGroup is the minimum size of each group. leftoverPerons
        is the amount of groups, which have an extra member */
    int personPerGroup = chromo.personCount / chromo.groupCount;
    int leftoverPersons = chromo.personCount % personPerGroup;

    /* Allocate memory */
    Group *groups = (Group*)malloc(chromo.groupCount * sizeof(Group));

    currentPerson = 0;
    for (i = 0; i < chromo.groupCount; i++) {

        /* Setup some data about the group */
        groups[i].groupNumber = i;
        groups[i].fitnessValue = -1;

        /* Add persons to group */
        for (j = 0; j < personPerGroup; j++) {
            groups[i].members[j] = chromo.persons[currentPerson];
            currentPerson++;
        }

        /* Add another person if i < leftoverPersons.
            set the memberCount variable in the group struct */
        if (i < leftoverPersons) {
            groups[i].members[j] = chromo.persons[currentPerson];
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
    Chromosome *a = (Chromosome*)i;
    Chromosome *b = (Chromosome*)j;

    double fa = fitness_chromosome(*a);
    double fb = fitness_chromosome(*b);

    /* Return -1 if A is best, returns 1 if B is best */
    if (fa > fb) return -1;
    if (fb > fa) return 1;
    return 0;
}

/* Returns the fitness of a chromosome */
double fitness_chromosome(Chromosome chromo) {

    /* Split chromosome into groups, then calculate fitness */
    Group *groups = genetic_chromosome_to_groups(chromo);
    double fitness = fitness_groups(groups, chromo.groupCount, chromo.criteria, chromo.criteriaCount);

    free(groups);

    return fitness;
}

/* Returns the total fitness of all groups */
double fitness_groups(Group *groups, int groupCount, Criteria *criteria, int criteriaCount) {
    double result = 0;
    int i;
    /* Calls the fitness_group function as many times as the number of
        groups and summerize the fitness */
    for (i = 0; i < groupCount; i++) {
        result += fitness_group(groups + i, criteria, criteriaCount);
    }
    return result;
}

/* Returns the total fitness of a single group */
double fitness_group(Group *group, Criteria *criteria, int criteriaCount) {
    double result = 0, average, criteriaMin, criteriaMax, t;
    int i, j;

    /* Goes through all criteria */
    for (i = 0; i < criteriaCount; i++) {

        /* Finds the average value of specific criteria */
        average = average_criteria(group, i);

        /* Finds min and max values of specific criteria in group */
        for (j = 0; j < group->memberCount; j++) {

            double a = group->members[j].criteria[i];

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
        result += fitness_of_criteria(t, criteria[i].weight, fitness_alpha(group->memberCount, criteria->minimum));
    }

    /* Save fitness in the group struct */
    group->fitnessValue = result;

    return result;
}

/* Returns fitness of specific criteria, if minimum isn't satisfied, return 0 */
double fitness_of_criteria(double t, double weight, double alpha) {
  if (alpha <= t && t <= 1 - alpha) {
    return (-4 * weight * pow(t, 2)) + (4 * weight * t) ;
  } else {
    return 0;
  }
}

/* returns alpha from groupsize and miminum specified */
double fitness_alpha(int groupSize, double minimum) {
  return _min((minimum / groupSize), 1 - (minimum / groupSize));
}

/* Finds average of one criteria */
double average_criteria(Group *g, int i) {
    double result = 0;
    int j;

    /* Find sum of group's criteria */
    for (j = 0; j < g->memberCount; j++) {
        result += g->members[j].criteria[i];
    }
    return result / g->memberCount;
}

/* Selects two random parents from the upper half of population */
void genetic_selection(Chromosome *population, int popsize, Chromosome *par1, Chromosome *par2) {

    int a = rand() % (popsize / 2);
    int b = rand() % (popsize / 2);

    *par1 = population[a];
    *par2 = population[b];
}

/* Takes two parent chromosome and creates two children, which are stored at child pointers */
void genetic_crossover(Chromosome parent1, Chromosome parent2, Chromosome *child1, Chromosome *child2) {

    int personCount = parent1.personCount;

    /* The bitstring is used to determine which parent genes is taken from */
    int *bitstring = (int*) calloc(personCount, sizeof(int));
    int i, limit = personCount + 1;

    /* Do cycle */
    i = 0;
    do {
        int indexInPar2;

        /* Mark index i */
        bitstring[i] = 1;

        /* Find index of element parent1.person[i] in parent2 */
        for (indexInPar2 = 0; indexInPar2 < personCount; indexInPar2++) {
            if (parent1.persons[i].personID == parent2.persons[indexInPar2].personID) {
                /* Set index i to indexInPar2 */
                i = indexInPar2;
                break;
            }
        }

        limit--;
    } while (i != 0 && limit > 0);
    assert(limit > 0);

    /* Copy flagged genes from the other chromosome */
    for (i = 0; i < personCount; i++) {
        if (bitstring[i]) {
            child1->persons[i] = parent1.persons[i];
            child2->persons[i] = parent2.persons[i];
        } else {
            child1->persons[i] = parent2.persons[i];
            child2->persons[i] = parent1.persons[i];
        }
    }

    free(bitstring);
}

/* Takes a pointer to chromosome and slighty alter it */
void genetic_mutation(Chromosome *chromo, float mutationrate) {

    /* Small chance of mutation */
    float rn = (rand() % 1000) / 1000.;
    if (rn <= mutationrate) {

        Person temp;

        /* Find two random indexes */
        int i = 0, j = 0;
        while (i == j && chromo->personCount > 0) {
            i = rand() % chromo->personCount;
            j = rand() % chromo->personCount;
        }

        /* Swaps two random elements */
        temp = chromo->persons[i];
        chromo->persons[i] = chromo->persons[j];
        chromo->persons[j] = temp;
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
        population[i].criteria = data.allCriteria;
        population[i].criteriaCount = data.criteriaCount;
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
        n = rand() % (data.personCount - i) + i;

        /* Swap index i and n */
        temp = chromosome->persons[n];
        chromosome->persons[n] = chromosome->persons[i];
        chromosome->persons[i] = temp;
    }
}

/* Takes a population and cleans it up, freeing all used memory */
void genetic_kill_population(Chromosome *population, int popsize) {
#ifdef _WIN32
    int i;
    /* Free all allocated memory for persons */
     for (i = 0; i < popsize; i++) {
        free(population->persons);
    } 

     free(population);
#endif
}
