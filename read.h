
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

DataSet read_data();
FILE* filename_input();
int count_lines_and_data(FILE *fp, int *lineCount, int *personCount, int *criteriaCount);
int extract_data(FILE *fp, DataSet *data);
int extract_criteria(char *str, Criteria *cri);
int extract_person(char *str, Person *per, int index, int criCount, int lineCount);
int check_dot(char *token, char *str);