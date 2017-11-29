#include "datastructs.c"
#include "read.h"

#define READPRINT 0

void read_data() {
    
    int lineCount;
    FILE *fp;
    
    fp = fopen("datafile.txt", "r");
    assert(fp != NULL);

    /* Count lines */
    count_lines_and_data(fp, &lineCount, &_CriteriaCount, &_PersonCount);

#if READPRINT
    /* Print status */
    printf("Line count: %d\nPerson count: %d\nCriteria count: %d\n", lineCount, _PersonCount, _CriteriaCount);
#endif
    
    /* Allocate memory */
    _AllPersons = (person*)malloc(_PersonCount * sizeof(person));
    _Criteria = (criteria*)malloc(_CriteriaCount * sizeof(criteria));
    
    /* Reset pointer and extract data */
    fseek(fp, 0, SEEK_SET);
    extract_data(fp, _AllPersons, _PersonCount, _Criteria, _CriteriaCount);
    
    fclose(fp);
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
                if (mode) {
                    extract_person(buffer, persons + p, criteriaCount);
                    p++;
                }
                else {
                    extract_criteria(buffer, criterias + c);
                    c++;
                }
                break;
            case '#': break;
            case '$': mode = 1; break;
        }
    }
}

void extract_criteria(char *str, criteria *entry) {
    char name[LINE_MAX_LEN];
    double weight;
    
    sscanf(str, " \"%[^\"]\" = %lf ", name, &weight);
#if READPRINT
    printf("Criteria: %s = %.1lf\n", name, weight);
#endif

	strcpy(entry->name, name);
	entry->weight = weight;
}

void extract_person(char *str, person *entry, int criCount) {
    int i;
    char name[LINE_MAX_LEN];
    char *token;
    double cri[10];
    
    sscanf(str, " \"%[^\"]\" = ", name);
    
    token = strchr(str, '=') + 1;
    token = strtok(token, ",");
    for (i = 0; i < criCount; i++) {
        sscanf(token, " %lf ", cri + i);
        token = strtok(NULL, ",");
    }

#if READPRINT
    printf("Name: %s = ", name);
    for (i = 0; i < criCount; i++) {
        printf("%.1lf%s", cri[i], i < criCount - 1 ? ", " : "");
    }
    printf("\n");
#endif

	strcpy(entry->name, name);
	for (i = 0; i < criCount; i++) {
		entry->criteria[i] = cri[i];
	}
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