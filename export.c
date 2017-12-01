#include <stdio.h>
#include <stdlib.h>

void printOutput();

int main(void)

{
    
    printOutput();
      return 0;
}

void printOutput()
{
    /* opening/creatign the txt file that the data is getting printeted to*/
    FILE* fptr = fopen("Formed_Groups.txt", "w");
    /*if the file can't open/create the txt file this error vil be printed, meybe create possiblileti for looping */
    if(fptr == NULL)
    {
        printf("Error: could not open 'Formed_Groups.txt'\n");
         exit(1);
    }
    /* printing/creatingthe finale file, with the given info*/
    fprintf(fptr, "Put the output here\n");
    /*close the created fiel */
    fclose(fptr);
}