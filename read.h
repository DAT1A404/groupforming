
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_MAX_LEN 200

void read_data();
FILE* filename_input();
void count_lines_and_data(FILE *fp, int *lineCount, int *criteriaCount, int *personCount);
void extract_data(FILE *fp, person *persons, int personCount, criteria *criterias, int criteriaCount);
void extract_criteria(char *str, criteria *entry);
void extract_person(char *str, person *entry, int criCount);