#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "datastructs.h"
#include "visual.h"
#include "utility.h"
#include "read.h"

#define LINE_MAX_LEN 200
#define FILE_NAME_MAX_LENGTH 40

#define DEBUG_READ_PRINT 0 /* Debug variable for printing verbosely */


DataSet read_data() {

	int data_error_check = 0; /* Variable data_error_check is used to store a boolean value to know if there is an error*/
    DataSet data;

    int lineCount; /* Variable lineCount is used to know how many lines there is in the file*/
	
	do{
		
		/*Open file and create a pointer to it*/
		FILE *fp = filename_input();

		data_error_check = 0;
		
		/* Count lines */
		data_error_check = count_lines_and_data(fp, &lineCount, &data.personCount, &data.criteriaCount);
	  
		/* If there are no criterias then error */
		if(data.criteriaCount < 1){
			set_color(RED, BLACK);
			printf("Error not enough criteria to function \n");
			reset_color();
			data_error_check = 1;
		}
		/* If there is less than two people then error */
		if(data.personCount < 2){
			set_color(RED, BLACK);
			printf("Error not enough few people to function \n");
			reset_color();
			data_error_check = 1;
		}
		else;
		
	#if READPRINT
		/* Print status */
		printf("Line count: %d\nPerson count: %d\nCriteria count: %d\n", lineCount, data.personCount, data.criteriaCount);
	#endif

		/* Allocate memory */
		data.allPersons = (Person*)malloc(data.personCount * sizeof(Person));
		data.allCriteria = (Criteria*)malloc(data.criteriaCount * sizeof(Criteria));

		/* Reset pointer and extract data */
		fseek(fp, 0, SEEK_SET);
		data_error_check = extract_data(fp, &data);
		
		/* Close file */
		fclose(fp);
		
		/* If data_error_check is True then let the user know that the error is in the datafile */
		if(data_error_check == 1){
			set_color(RED, BLACK);
			printf(" Error in data-file!\n");
			reset_color();
		}
		
		
	} while(data_error_check == 1); /* When an error happens begin anew */

    return data;
}

/* Ask user for file name */
FILE* filename_input() {
	FILE *fp;
    char filename[FILE_NAME_MAX_LENGTH];

    do {
		/* Prompt for input */
		printf("Enter filename of data-file, or exit with \"q\": ");
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
            printf("Succes! File found\n");

    } while (fp == NULL); /*As long as the pointer fp dosen't point to a file*/

	return fp;
}

/* Count lines and store in lineCount. Count criteria and store in criteriaCount. Count person's and store in personCount. */
int count_lines_and_data(FILE *fp, int *lineCount, int *personCount, int *criteriaCount) {
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
            default: /* If none of the cases are True then there must be an error*/
                set_color(COLOR_ERROR, BLACK);
                printf("Error in line %d. Unexpected character '%c' \n", *lineCount, buffer[0]); /* Print error if unknown sign, the line the error is on and the string stored in 'buffer' */
                reset_color();
				return 1;
        }
    }
	return 0;
}

/* Used to extract data from file to variables */
int extract_data(FILE *fp, DataSet *data) {
    char buffer[LINE_MAX_LEN];
    int mode = 0,
        lineCount = 0,
        p = 0,
        c = 0;

    while(fgets(buffer, LINE_MAX_LEN, fp) != NULL) {
		int error_check = 0;
        lineCount++;
        switch (buffer[0]) {
            case '"': /* If a '"' is read then depending on the value of mode either take data of a person or take data of a criteria */
                if (mode) {
                    error_check = extract_person(buffer, data->allPersons + p, p, data->criteriaCount, lineCount);
                    p++;
                }
                else {
                    error_check = extract_criteria(buffer, data->allCriteria + c);
                    c++;
                }
                if(error_check == 1)
					return 1;
				else
					break;
            case '#': break; /* The '#' sign signifies a comment in the file and there for only has a 'break' */
            case '$': mode = 1; break; /* Set variable mode to 1 to signify the shift from criteria to person's */
        }
    }
	return 0;
}

int extract_criteria(char *str, Criteria *cri) {
    char name[NAME_MAX_LENGTH];
    double weight, minimum;

	/* Scan for data and store in temporary variables,
        utilise return value of sscanf to check if min is present or should be set */
    switch (sscanf(str, " \"%[^\"]\" = %lf, %lf", name, &weight, &minimum)) {
      case 0:
		set_color(RED, BLACK);
		printf("Fatal error, function couldn't extract criteria!\n");
		reset_color();
		return 1;
      case 3: break;
      default: minimum = 0;
    }

#if DEBUG_READ_PRINT
    /* Print status on criteria and minimum */
    printf("Criteria: %s = %.1lf\n", name, weight);
    printf("Minimum: %s = %.1lf\n", name, minimum);
#endif

    /* Store name and weight in given location */
	strcpy(cri->name, name);
	cri->weight = weight;
    cri->minimum = minimum;
	
	return 0;
}

int extract_person(char *str, Person *per, int index, int criCount, int lineCount) {
    int i, dot;
    char name[NAME_MAX_LENGTH];
    char *token;
    double cri[CRITERIA_MAX_COUNT];

	/* Scan for data and store in temporary variables */
    sscanf(str, " \"%[^\"]\" = ", name);
	
    token = strchr(str, '=') + 1; /* Sets the pointer token to after the '=' sign */
	
	/* Function that check for a double dot ',' sing if there is return a 1 to dot */
	dot = check_dot(token, str);
	
	if(dot == 1){
		set_color(RED, BLACK);
		printf("Error could not read value\n");
		reset_color();
		printf(" Name: %s - Criteria ',,' \n Line %d\n", name, lineCount);
		return 1;
	}
	else{
		strtok(token, ","); /* Go trough the file from pointer 'token' placement, find the first ',' sign and replace it with a null character */
    
		for (i = 0; i < criCount; i++) {
			if(*token == '\0' || sscanf(token, " %lf ", cri + i) != 1){   /* If there is a null character or if sscanf returns something that is not 1 then error. sscanf saves the data that comes after the pointer token*/
				set_color(RED, BLACK);
				printf("Error could not read value\n");
				reset_color();
				printf(" Name: %s - Criteria '%s' \n Line %d Criteria nr. %d \n", name, token, lineCount, i + 1 );
	
				return 1;
			}
			else
				token = strtok(NULL, ","); /* Go trough the file from last placement, find the next ',' sign and replace it with a null character */
		}
	}
	
#if DEBUG_READ_PRINT
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
	
	return 0;
}

int check_dot(char *token, char *str) {
	char *point_token = token;
	
	/* Go trough the string str from tokens placement and check for places where a double dot ',,' occurs */
	while (*point_token + 1 != '\0') {
		if (*point_token == ',' && *(point_token + 1) == ',') {
			/* ERROR FOUND */
			return 1;
		}
		point_token++;
	}
	
	return 0;
}
