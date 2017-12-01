#include "datastructs.c"
#include "read.h"

#define READPRINT 0 /*Debug variable decides if importent info is printet*/

void read_data() {
    
    int lineCount; /* Variablen lineCount is used to know how many lines there is in the file*/
	/*Open file and create a pointer to it*/
    FILE *fp;
    
	/* fp = fopen("datafile.txt", "r"); */
	filename_input(fp);
	/*Might not be neded*/ /*assert(fp != NULL); /*assert tells the user that something is wrong, in this case if the file cant be opened*/

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
    
	/* Close file */
    fclose(fp);
}

/* Ask user for file name */
void filename_input(FILE *fp) {
    char filename[MAX];

    do {
		/* Prompt for input */
		printf("Enter filename: ");
		scanf(" %s", filename);
		
		/* Make sure that the file format is .txt */
		if ( (strstr(filename,".txt") == NULL) ) {
			strcat(filename,".txt");
		}
		
		fp = fopen(filename, "r"); /* Set pointer to file */
		
		/* If the file can't be opened*/
		if (fp == NULL) {
			printf("Could not open file. Check file name and location of the file and try again\n");
		}
		
		else printf("Succes ! :D \n");
    } while (fp == NULL); /*???*/
	
}

/* Count lines and store in lineCount. Count criteria and store in criteriaCount. Count person's and store in personCount. */
void count_lines_and_data(FILE *fp, int *lineCount, int *criteriaCount, int *personCount) {
    char buffer[LINE_MAX_LEN];
    int mode = 0;
    *lineCount = 0;
    *criteriaCount = 0;
    *personCount = 0;
    
    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) { /* Save a line in 'buffer' and run until en of file */
        (*lineCount)++; 
        switch (buffer[0]) { /* Check for sign */
            case '"': mode ? (*personCount)++ : (*criteriaCount)++; break; /* Increment a variable depending on what value mode has */
            case '#': break;
            case '$': mode = 1; break; /* Set variable mode to 1 to signify the shift from criteria to person's */
            default: printf("! Error in line %d. Unexpected character '%c'.\n", *lineCount, buffer[0]); /* Print error if unknown sign, the line the error is on and the string stored in 'buffer' */
        }
    }
}

/* Used to extract data from file to variables */
void extract_data(FILE *fp, person *persons, int personCount, criteria *criterias, int criteriaCount) {
    char buffer[LINE_MAX_LEN];
    int mode = 0,
        lineCount = 0,
        p = 0,
        c = 0;
    
    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) {
        lineCount++;
        switch (buffer[0]) {
            case '"': /* If a '"' is read then depending on the value of mode either take data of a person or take data of a criteria */
                if (mode) {
                    extract_person(buffer, persons + p, criteriaCount);
                    p++;
                }
                else {
                    extract_criteria(buffer, criterias + c);
                    c++;
                }
                break;
            case '#': break; /* The '#' sign signifies a comment in the file and there for only has a 'break' */
            case '$': mode = 1; break; /* Set variable mode to 1 to signify the shift from criteria to person's */
        }
    }
}

void extract_criteria(char *str, criteria *entry) {
    char name[LINE_MAX_LEN];
    double weight;
    
	/* Scan for data and store in temporary variables */
    sscanf(str, " \"%[^\"]\" = %lf ", name, &weight);
	
#if READPRINT
    /* Print status on criteria*/
    printf("Criteria: %s = %.1lf\n", name, weight);
#endif

    /* Store name and weight in array of structs _Criteria*/
	strcpy(entry->name, name);
	entry->weight = weight;
}

void extract_person(char *str, person *entry, int criCount) {
    int i;
    char name[LINE_MAX_LEN];
    char *token;
    double cri[10];
    
	/* Scan for data and store in temporary variables */
    sscanf(str, " \"%[^\"]\" = ", name);
    
    token = strchr(str, '=') + 1; /* Sets the pointer token to after the '=' sign */
    token = strtok(token, ","); /* Go trough string 'token' and find the first ',' sign and replace it with a null character */
    for (i = 0; i < criCount; i++) {
        sscanf(token, " %lf ", cri + i); /* Save data from string 'token' */
        token = strtok(NULL, ","); /* Go trough string 'token' and find the next ',' sign and replace it with a null character */
    }

#if READPRINT
    /* Print status of data for a person */
    printf("Name: %s = ", name);
    for (i = 0; i < criCount; i++) {
        printf("%.1lf%s", cri[i], i < criCount - 1 ? ", " : "");
    }
    printf("\n");
#endif

    /* Store name and criteria values in array of structs _AllPersons */
	strcpy(entry->name, name);
	for (i = 0; i < criCount; i++) {
		entry->criteria[i] = cri[i];
	}
}