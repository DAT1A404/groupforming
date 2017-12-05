#include "datastructs.c"
#include "export.h"

/*exports data to csv file*/
void export_to_csv (group *groups, int groupCount) {
    int max_members;
    FILE *fp;

    /*create output file*/
    fp = fopen("result.csv","w+");
    assert(fp != NULL);

    /*find max number of members amongst the groups*/
    max_members = find_max_members (groups, groupCount);
    
    /*prints first row (header)*/
    make_header(groupCount, fp);

    /*prints all other rows (members)*/
    print_members(groups, groupCount, max_members, fp);

    printf("\n\nCreated file: result.csv \n\n");
    fclose(fp);
}

/*finds the max number of members in a group*/
int find_max_members(group *groups, int groupCount) {
    int i, max = 0;
    for (i = 0; i <= groupCount; i++) {
        if (groups[i].memberCount > max) {
            max = groups[i].memberCount;
        }
    }
    return max;
}

/*prints header to csv file*/
void make_header(int groupCount, FILE *fp) {
    int i;
    fprintf(fp, ";");
    for (i = 0; i < groupCount; i++) {
        fprintf(fp, "%s %d;","Gruppe", (i+1));
    }
    fprintf(fp,"\n");
}

/*prints all the members to the csv file*/
void print_members(group *groups, int groupCount, int max_members, FILE *fp) { 
    int i, j;
    for (i = 0; i < max_members; i++) {
        fprintf(fp, "Medlem %d;", (i+1)); 
        for (j = 0; j < groupCount; j++) {
           fprintf(fp, "%s;",groups[j].members[i].name);
        }
    fprintf(fp,"\n");
    }
}