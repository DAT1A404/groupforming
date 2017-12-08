#include "datastructs.c"
#include "visual.h"
#include "utility.h"
#include "read.h"

#define LINE_MAX_LEN 200

#define READPRINT 0 /* Debug variable for printing verbosely */

#define MAX 40

DataSet read_data() {

    DataSet data;
    int lineCount; /* Variablen lineCount is used to know how many lines there is in the file*/

	/*Open file and create a pointer to it*/
    FILE *fp = filename_input();

    /* Count lines */
    count_lines_and_data(fp, &lineCount, &data.personCount, &data.criteriaCount);

#if READPRINT
    /* Print status */
    printf("Line count: %d\nPerson count: %d\nCriteria count: %d\n", lineCount, data.personCount, data.criteriaCount);
#endif

    /* Allocate memory */
    data.allPersons = (Person*)malloc(data.personCount * sizeof(Person));
    data.allCriteria = (Criteria*)malloc(data.criteriaCount * sizeof(Criteria));

    /* Reset pointer and extract data */
    fseek(fp, 0, SEEK_SET);
    extract_data(fp, &data);

	/* Close file */
    fclose(fp);

    return data;
}

/* Ask user for file name */
FILE* filename_input() {
	FILE *fp;
    char filename[MAX];

    do {
		/* Prompt for input */
		printf("Enter filename of data-file, if not ready yet, exit with \"q\": ");
		scanf(" %s", filename);
    /* if "q" written, exit program */
    if (strequal(filename, "q")) exit(EXIT_SUCCESS);

		/* Make sure that the file format is .txt */
		if ( (strstr(filename,".txt") == NULL) ) {
			strcat(filename,".txt");
		}

		fp = fopen(filename, "r"); /* Set pointer to file */

		/* If the file can't be opened*/
		if (fp == NULL) {
      set_color(COLOR_ERROR, BLACK);
			printf("Could not open file. Check file name and location of the file and try again\n");
      reset_color();
		} else
            printf("Succes!\n");

    } while (fp == NULL); /*As long as the pointer fp dosen't point to a file*/

	return fp;
}

/* Count lines and store in lineCount. Count criteria and store in criteriaCount. Count person's and store in personCount. */
void count_lines_and_data(FILE *fp, int *lineCount, int *personCount, int *criteriaCount) {
    char buffer[LINE_MAX_LEN];
    int mode = 0;
    *lineCount = 0;
    *personCount = 0;
    *criteriaCount = 0;

    /* Save a line in 'buffer' until end of file */
    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) {
        (*lineCount)++;
        switch (buffer[0]) { /* Check for sign */
            case '"': mode ? (*personCount)++ : (*criteriaCount)++; break; /* Increment a variable depending on what value mode has */
            case '#': break;
            case '$': mode = 1; break; /* Set variable mode to 1 to signify the shift from criterias to persons */
            default:
                set_color(COLOR_ERROR, BLACK);
                printf("! Error in line %d. Unexpected character '%c'.\n", *lineCount, buffer[0]); /* Print error if unknown sign, the line the error is on and the string stored in 'buffer' */
                reset_color();
        }
    }
}

/* Used to extract data from file to variables */
void extract_data(FILE *fp, DataSet *data) {
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
                    extract_person(buffer, data->allPersons + p, p, data->criteriaCount);
                    p++;
                }
                else {
                    extract_criteria(buffer, data->allCriteria + c);
                    c++;
                }
                break;
            case '#': break; /* The '#' sign signifies a comment in the file and there for only has a 'break' */
            case '$': mode = 1; break; /* Set variable mode to 1 to signify the shift from criteria to person's */
        }
    }
}

void extract_criteria(char *str, Criteria *cri) {
    char name[LINE_MAX_LEN];
    double weight, minimum;

	/* Scan for data and store in temporary variables,
  utilise return value of sscanf to check if min is present or should be set */
    switch (sscanf(str, " \"%[^\"]\" = %lf, %lf", name, &weight, &minimum)) {
      case 0: printf("Fatal error, function couldn't extract criteria!\n"); break;
      default: minimum = 0;
    }

#if READPRINT
    /* Print status on criteria and minimum */
    printf("Criteria: %s = %.1lf\n", name, weight);
    printf("Minimum: %s = %.1lf\n", name, minimum);
#endif

    /* Store name and weight in given location */
	strcpy(cri->name, name);
	cri->weight = weight;
  cri->minimum = minimum;
}

void extract_person(char *str, Person *per, int index, int criCount) {
    int i;
    char name[LINE_MAX_LEN];
    char *token;
    double cri[20];

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

    /* Store name and criteria values given location */
	strcpy(per->name, name);
	for (i = 0; i < criCount; i++) {
		per->criteria[i] = cri[i];
	}
    per->personID = index;
}
