#include "datastructs.c"
#include "export.h"

/*exports data to csv file*/
void export_to_csv (group *groups, int groupCount) {
    int i, j, max_members = 0;
    FILE *fp;

    fp = fopen("result.csv","w+");
    assert(fp != NULL);

    /*finds the max number of members in a group*/
    for (i = 0; i <= groupCount; i++) {
        if (groups[i].memberCount > max_members) {
            max_members = groups[i].memberCount;
        }
    }
   
    /*prints header with groups*/
    fprintf(fp, ";");
    for (i = 0; i < groupCount; i++) {
        fprintf(fp, "%s %d;","Gruppe", (i+1));
    }
    fprintf(fp,"\n");

    /*prints the members*/
    for (i = 0; i < max_members; i++) {
        fprintf(fp, "Medlem %d;", (i+1)); 
        for (j = 0; j < groupCount; j++) {
           fprintf(fp, "%s;",groups[j].members[i].name);
        }
    fprintf(fp,"\n");
    }

    printf("\n\nCreated file: result.csv \n\n");
    fclose(fp);
}