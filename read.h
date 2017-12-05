
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

DataSet read_data();
FILE* filename_input();
void count_lines_and_data(FILE *fp, int *lineCount, int *personCount, int *criteriaCount);
void extract_data(FILE *fp, DataSet *data);
void extract_criteria(char *str, Criteria *cri);
void extract_person(char *str, Person *per, int criCount);