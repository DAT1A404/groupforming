#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

group* genetic_algorithm(int popsize, int generations, float mutationrate);
void log_make_header(FILE *lgf, DataSet data, GASettings settings, int groupCount);
void genetic_analyse(FILE *lgf, int gen, person*** population, int popsize);
void genetic_copy_chromosome(person **to, person **from);
double genetic_average_fitness(person ***population, int popsize);
double genetic_median_fitness(person ***population, int popsize);

int genetic_q_compare(const void * i, const void * j);
double fitness_chromosome(Chromosome chromo);
double fitness_groups(Group *groups, int groupCount, Criteria *criteria, int criteriaCount);
double fitness_group(Group *group, Criteria *criteria, int criteriaCount);
double average_criteria(group *g, int i);
double fitness_of_criteria(double t, double weight);

void genetic_selection(person ***population, int popsize, person ***par1, person ***par2);
void genetic_crossover(person **par1, person **par2, person **child1, person **child2);
void genetic_mutation(person **child, float mutationrate);

Chromosome * genetic_get_empty_population(int popsize, DataSet data, int groupCount);
Chromosome * genetic_get_memory_for_pop(int popsize, int personCount);
Chromosome * genetic_generate_initial_population(int popsize, DataSet data, int groupCount);
void genetic_generate_chromosome(Chromosome *chromosome, DataSet data);
void genetic_reset_chromosome(person **chromosome);

Group* genetic_chromosome_to_groups(Chromosome chromo);