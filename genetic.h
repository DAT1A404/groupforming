#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* Local struct containing data about chromosomes.
    personCount and groupCount are nessary when sending
    a Chromosome to a function like qsort */
typedef struct {
    Person *persons;
    int personCount;
    Criteria *criteria;
    int criteriaCount;
    int groupCount;
} Chromosome;

Group* genetic_algorithm(GASettings settings, DataSet data, int groupCount);
void log_make_header(FILE *lgf, DataSet data, GASettings settings, int groupCount);
void genetic_analyse(FILE *lgf, int gen, Chromosome *population, int popsize);
double genetic_average_fitness(Chromosome *population, int popsize);
double genetic_median_fitness(Chromosome *population, int popsize);

Group* genetic_chromosome_to_groups(Chromosome chromo);

int genetic_q_compare(const void * i, const void * j);
double fitness_chromosome(Chromosome chromo);
double fitness_groups(Group *groups, int groupCount, Criteria *criteria, int criteriaCount);
double fitness_group(Group *group, Criteria *criteria, int criteriaCount);
double average_criteria(Group *g, int i);
double fitness_of_criteria(double t, double weight);

void genetic_selection(Chromosome *population, int popsize, Chromosome *par1, Chromosome *par2);
void genetic_crossover(Chromosome parent1, Chromosome parent2, Chromosome *child1, Chromosome *child2);
void genetic_mutation(Chromosome *chromo, float mutationrate);

Chromosome * genetic_get_empty_population(int popsize, DataSet data, int groupCount);
Chromosome * genetic_get_memory_for_pop(int popsize, int personCount);
Chromosome * genetic_generate_initial_population(int popsize, DataSet data, int groupCount);
void genetic_generate_chromosome(Chromosome *chromosome, DataSet data);
void genetic_kill_population(Chromosome *population, int popsize);