#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

group* genetic_algorithm(int popsize, int generations, float mutationrate);
void log_make_header(FILE *lgf, int popsize, int generations, float mutationrate);
void genetic_analyse(FILE *lgf, int gen, person*** population, int popsize);
void genetic_copy_chromosome(person **to, person **from);
double genetic_average_fitness(person ***population, int popsize);
double genetic_median_fitness(person ***population, int popsize);
int genetic_q_compare(const void * i, const void * j);
double fitness_chromosome(person **a);
double fitness_groups(group *g);
double fitness_group(group *g);
double average_criteria(group *g, int i);
double fitness_of_criteria(double t, double weight);
void genetic_selection(person ***population, int popsize, person ***par1, person ***par2);
void genetic_crossover(person **par1, person **par2, person **child1, person **child2);
void genetic_reset_chromosome(person **chromosome);
void genetic_mutation(person **child, float mutationrate);
person*** genetic_get_memory_for_pop(int popsize);
person*** genetic_generate_initial_population(int popsize);
void genetic_generate_chromosome(person **chromosome);
group* genetic_chromosome_to_groups(person **chromosome);