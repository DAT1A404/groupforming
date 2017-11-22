
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_MAX_LEN 200

typedef struct {
    char name[40];
    int personID;
    double criteria[10];
} person;

typedef struct {
    char name[40];
    double weight;
} criteria;

person *_AllPersons;
int _PersonCount;
criteria *_Criteria;
int _CriteriaCount;

/* ///////////////////////////// */

void count_lines_and_data(FILE *fp, int *lineCount, int *criteriaCount, int *personCount);
void extract_data(FILE *fp, person *persons, int personCount, criteria *criterias, int criteriaCount);
void extract_criteria(char *str, criteria *entry);
void extract_person(char *str, person *entry, int criCount);

int main(void) {
    
    int lineCount;
    char buffer[LINE_MAX_LEN];
    FILE *fp;
    
    fp = fopen("datafile.txt", "r");
    assert(fp != NULL);

    /* Count lines */
    count_lines_and_data(fp, &lineCount, &_CriteriaCount, &_PersonCount);
    
    /* Print status */
    printf("Line count: %d\nPerson count: %d\nCriteria count: %d\n", lineCount, _PersonCount, _CriteriaCount);
    
    /* Allocate memory */
    _AllPersons = (person*)malloc(_PersonCount * sizeof(person));
    _Criteria = (criteria*)malloc(_CriteriaCount * sizeof(criteria));
    
    /* Reset pointer and extract data */
    fseek(fp, 0, SEEK_SET);
    extract_data(fp, _AllPersons, _PersonCount, _Criteria, _CriteriaCount);
    
    fclose(fp);
    return 0;
}

void extract_data(FILE *fp, person *persons, int personCount, criteria *criterias, int criteriaCount) {
    char buffer[LINE_MAX_LEN];
    int mode = 0,
        lineCount = 0,
        p = 0,
        c = 0;
    
    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) {
        lineCount++;
        switch (buffer[0]) {
            case '"':
                if (mode) extract_person(buffer, persons + p, criteriaCount);
                else extract_criteria(buffer, criterias + c);
                break;
            case '#': break;
            case '$': mode = 1; break;
            default: printf("! Error in line %d. Unexpected character '%c'.\n", lineCount, buffer[0]);
        }
    }
}

void extract_criteria(char *str, criteria *entry) {
    char name[LINE_MAX_LEN];
    double weight;
    
    sscanf(str, " \"%[^\"]\" = %lf ", name, &weight);
    
    printf("Criteria: %s| weight: %.1lf\n", name, weight);
}

void extract_person(char *str, person *entry, int criCount) {
    int i;
    char name[LINE_MAX_LEN];
    char *token;
    double cri[2];
    
    sscanf(str, " \"%[^\"]\" = ", name);
    
    token = strchr(str, '=') + 1;
    token = strtok(token, ",");
    for (i = 0; i < criCount; i++) {
        sscanf(token, " %lf ", cri + i);
        token = strtok(NULL, ",");
    }
    
    printf("Name: %s = ", name);
    for (i = 0; i < criCount; i++) {
        printf("%.1lf%s", cri[i], i < criCount - 1 ? ", " : "");
    }
    printf("\n");
}

/* Count lines. Store values in lineCount, criteriaCount, and personCount */
void count_lines_and_data(FILE *fp, int *lineCount, int *criteriaCount, int *personCount) {
    char buffer[LINE_MAX_LEN];
    int mode = 0;
    *lineCount = 0;
    *criteriaCount = 0;
    *personCount = 0;
    
    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) {
        (*lineCount)++;
        switch (buffer[0]) {
            case '"': mode ? (*personCount)++ : (*criteriaCount)++; break;
            case '#': break;
            case '$': mode = 1; break;
            default: printf("! Error in line %d. Unexpected character '%c'.\n", *lineCount, buffer[0]);
        }
    }
}