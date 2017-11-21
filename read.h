#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX_SIZE 50

int count_lines(FILE * file_pointer);
void input_buffer(char *buffer, FILE * file_pointer);
int check_line(char *buffer, char Hashtag, char Quotation, char Dollar, int *xp);