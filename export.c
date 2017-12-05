#include "datastructs.c"
#include "export.h"
#include "genetic.h"

 
void export_plain(group *grps, int _GroupCount)
{
	int i;
    int e;
    /* opening/creatign the txt file that the data is getting printeted to*/
    FILE* fptr = fopen("Formed_Groups.txt", "w");
    /*if the file can't open/create the txt file this error vil be printed, meybe create possiblileti for looping */
    if(fptr == NULL)
        {
        printf("Error: could not open 'Formed_Groups.txt'\n");
         exit(1);
        }
    /* printing data to the finale file, with the given info*/
    fprintf(fptr,"How Many Groups In Total: %d\n", _GroupCount);
    for (i = 0; i < _GroupCount; i++) 
    {
        if (i != 0) fprintf(fptr,"\n");
        fprintf(fptr,"Gruppe %d \n", grps[i].groupNumber +1);
        for (e = 0; e < grps[i].memberCount; e++) 
         {
          fprintf(fptr,"%s\n", grps[i].members[e].name);
         }
    }
    /*close the created fiel */
    fclose(fptr);
}