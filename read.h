
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void read_data(person **allPersons, int *personCount, person **allCriteria, int *criteriaCount);
FILE* filename_input();
void count_lines_and_data(FILE *fp, int *lineCount, int *personCount, int *criteriaCount);
void extract_data(FILE *fp, DataSet *data);
void extract_criteria(char *str, criteria *cri);
void extract_person(char *str, person *per, int criCount);