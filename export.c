#include "datastructs.c"
#include "export.h"

void export_plain(group *grps, int _GroupCount)
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
    fprintf(fptr, "%d\n", _GroupCount);
    /*close the created fiel */
    fclose(fptr);
}

/*group pointer og group count*/