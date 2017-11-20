#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX_SIZE 50

/* ====== GLOBALS =====*/
typedef struct{
	char name[40];
	int personID;
	double criteria[10];
} person;

double _Weights[10];
int _CriteriaCount;
/* ===================== */


int count_lines(FILE * file_pointer);

void input_buffer(char *buffer, FILE * file_pointer);

int check_line(char *buffer, char Hashtag, char Quotation, char Dollar);



int main(){
  int nr_of_lines = 0, line_check = 0, criteria_or_name = 0;
  char line[LINE_MAX_SIZE], line_buffer[LINE_MAX_SIZE];
  const char Hashtag = '#';
  const char Quotation = '"';
  const char Dollar = '$';
  _CriteriaCount = 0;
  
  FILE * file_pointer; /*Create a pointer to a file*/
  file_pointer = fopen("datafile.txt", "r"); /*Set parameters for pointer to file*/
  
  printf("t0\n");
  
  /*Check if file exists*/
  if (file_pointer == NULL){
    printf("Could not open file Datafile");
    return 0;
  }
 
  printf("t1\n");
 
  /*Determine number of lines in file*/
  nr_of_lines = count_lines(file_pointer);
  
  printf("t2\n");
  
  file_pointer = fopen("datafile.txt", "r"); /*Reset markør*/
  
 /*
  Read content of file
  If line starts with a # sign do not include
  Read criteria in a "" sign followed by a value after the = sign
  If a $ sign is read then 
  Read persons name in "" sign thereafter 
  Read the data values after the = sign, where each of the values are separated by a , sign
  */
  
  int i;
  for(i = 0; i <= nr_of_lines; i++) {
  input_buffer(line_buffer ,file_pointer);
  
  line_check = check_line(line_buffer, Hashtag, Quotation, Dollar);
  
  printf("Found char %d \n", line_check);
  
  
  if(line_check == 2){
    if(criteria_or_name == 0){
	  _CriteriaCount++;
	  
	}
	else{
	  
	  
	}
  }
  else if(line_check == 3){
	criteria_or_name = 1;
  }
  else{
    
  }
  
  puts(line_buffer);
  
  }
  
  
  file_pointer = fopen("datafile.txt", "r"); /*Reset markør*/
  
  printf("C count %d \n", _CriteriaCount);
  
  /*Print file*/ 
  while(!feof(file_pointer)){
	  fgets(line, 150, file_pointer);
	  puts(line);
  }
  
  printf("t3\n");
  
  printf("%d\n", nr_of_lines);
  
  fclose(file_pointer);
  
  return 0;
  
}

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
int check_line(char *buffer, char Hashtag, char Quotation, char Dollar){
  int i;
  
  for(i = 0; i < 2; i++) {
    if(buffer[i] == Hashtag || Quotation || Dollar){
      if(buffer[i] == Hashtag){ 
	    printf("Found char '%c'\n", Hashtag);
	    return 1;
	  }
	  else if(buffer[i] == Quotation){
	    printf("Found char '%c'\n", Quotation);
	    return 2;
	  }
	  else if(buffer[i] == Dollar){
	    printf("Found char '%c'\n", Dollar);
	    return 3;
      }
	  else{
		printf("Error could not find char sign \n");
		return 0;  
	  }
    }
  } 
  
}
