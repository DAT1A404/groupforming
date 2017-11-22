#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "datastructs.h"
#include "utility.h"

void genetic_algorithm(int popsize, int generations, float mutationrate);
double genetic_average_fitness(person ***population, int popsize);
int genetic_q_compare(const void * i, const void * j);
double fitness_chromosome(person **a);
double fitness_group(group *g);
void genetic_selection(person ***population, int popsize, person **par1, person **par2);
void genetic_crossover(person **par1, person **par2, person **child1, person **child2);
void genetic_reset_chromosome(person **chromosome);
void genetic_mutation(person **child, float mutationrate);
person*** genetic_get_memory_for_pop(int popsize);
person*** genetic_generate_initial_population(int popsize);
void genetic_generate_chromosome(person **chromosome);
