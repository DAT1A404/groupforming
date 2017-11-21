#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX_SIZE 50 /*Defines the max size of a line that cann be read*/

/* ====== GLOBALS =====*/
/*person name, id and data*/
typedef struct{
	char name[40];
	int personID;
	double criteria[10];
} person;
/* _allPersons[i].name = "string name"*/
/*criteria name and weight*/
typedef struct {
    char name[50];
    double weight;
} criteria;

person *_AllPersons;
criteria *_Criteria;
int _CriteriaCount;
/* ===================== */


int count_lines(FILE * file_pointer);

void input_buffer(char *buffer, FILE * file_pointer);

int check_line(char *buffer, char Hashtag, char Quotation, char Dollar, int *xp);



int main(){
  int nr_of_lines = 0, /*Details the number of lines*/
  line_check = 0, /*Used to find out what sign is found*/
  criteria_or_name = 0, /*Used to know if the program is going to store criterias or names*/
  x = 0, i; /*variables used for loops*/

  int *xp;
	FILE * file_pointer; /*Create a pointer to a file*/
  char line[LINE_MAX_SIZE], line_buffer[LINE_MAX_SIZE];
  const char Hashtag = '#';
  const char Quotation = '"';
  const char Dollar = '$';
  _CriteriaCount = 0; /*Stores the amount of criterias that have been found*/

  xp = &x; /*Set pointer xp to x*/

	file_pointer = fopen("datafile.txt", "r"); /*Set parameters for pointer to file*/

  printf("Test0\n");

  /*Check if file exists*/
  if (file_pointer == NULL){
    printf("Error could not open file Datafile");
    return 0;
  }

  printf("Test1\n");

  /*Determine number of lines in file*/
  nr_of_lines = count_lines(file_pointer);

  printf("Test2\n");

  file_pointer = fopen("datafile.txt", "r"); /*Reset markør*/

 /*
  Read content of file
  If line starts with a # sign do not include
  Read criteria in a "" sign followed by a value after the = sign
  If a $ sign is read then
  Read persons name in "" sign thereafter
  Read the data values after the = sign, where each of the values are separated by a , sign
  */
  int y;
  char temp_buffer[LINE_MAX_SIZE];

  for(i = 0; i <= nr_of_lines; i++) {
	input_buffer(line_buffer ,file_pointer);

	line_check = check_line(line_buffer, Hashtag, Quotation, Dollar, xp);

	printf("Found char %d \n", line_check);

  	if(line_check == 2){
	    if(criteria_or_name == 0){ /*If criteria*/
		    /*struckt criteria: char name, double weight*/
			
			/*Find string between xp and y*/
			
			int t = 0;
			
			for(y = *xp + 1; line_buffer[y] != '"'; y++){
			
				temp_buffer[t] = line_buffer[y];
				t++;
			}
			temp_buffer[t] = '\0';
			
			
			printf("temp_buffer: %s \n", temp_buffer);
			//strcpy(_Criteria[_CriteriaCount].name, temp_buffer);
			/*_Criteria[_CriteriaCount].name = temp_buffer;*/
			/* _Criteria[_CriteriaCount].name = "string name"*/
			
			/* _Criteria[_CriteriaCount].weight = "value"*/
			
			
			_CriteriaCount++;
		}
		else{ /*If Name*/
			/*struckt person: char name, int personID, double criteria*/
			
			
			/*ID++*/
		}
	  }
	  else if(line_check == 3){
			criteria_or_name = 1;
	  }

	  puts(line_buffer);
  }

  file_pointer = fopen("datafile.txt", "r"); /*Reset markør*/

  printf("Criteria count: %d \n", _CriteriaCount);

  /*Print file*/
  while(!feof(file_pointer)){
	  fgets(line, 150, file_pointer);
	  puts(line);
  }

  printf("Test3\n");

  printf("Number of lines in file: %d\n", nr_of_lines);

  fclose(file_pointer);

  return 0;

}
/*Counts the number of lines in the file*/
int count_lines(FILE * file_pointer){
  int nr_of_lines = 0;
  char c;

  /*Extract characters from file and store in character c*/
  for (c = getc(file_pointer); c != EOF; c = getc(file_pointer)){
    if (c == '\n'){  /*Increment count if this character is newline*/
      nr_of_lines = nr_of_lines + 1;
    }
  }
  return nr_of_lines;

}

/*Input a new line from file into line_buffer*/
void input_buffer(char *buffer, FILE * file_pointer){

  fgets(buffer, LINE_MAX_SIZE, file_pointer);

}

/*Check line for a certain sign*/
int check_line(char *buffer, char Hashtag, char Quotation, char Dollar, int *xp){


  for(*xp = 0; buffer[*xp] != '\0'; (*xp)++) {
    if(buffer[*xp] == Hashtag || buffer[*xp] == Quotation || buffer[*xp] == Dollar){
      if(buffer[*xp] == Hashtag){
	    	printf("Found char '%c'\n", Hashtag);
	    	return 1;
	  	}
	  	else if(buffer[*xp] == Quotation){
	    	printf("Found char '%c'\n", Quotation);
	    	return 2;
	  	}
	  	else if(buffer[*xp] == Dollar){
	    	printf("Found char '%c'\n", Dollar);
	    	return 3;
    	}

    }
  }
	printf("Error could not find char sign \n");
	return 0;
}
