#include "datastructs.c"
#include "export.h"
#include "genetic.h"

void export_plain(group *grps, int groupCount) {
    int i, e;
    /* opening/creating the txt file that the data is getting printeted to*/
    FILE* fp = fopen("generated-groups.txt", "w");
    /*if the file can't open/create the txt file this error vil be printed, maybe create possibility for looping */
    if(fp == NULL) {
        printf("Error: could not open 'generated-groups.txt'\n");
        return;
    }
    /* printing data to the finale file, with the given info*/
    fprintf(fp,"Groups generated: %d\n", groupCount);
    for (i = 0; i < groupCount; i++) {
        if (i != 0) fprintf(fp,"\n");
        fprintf(fp,"Gruppe %d \n", grps[i].groupNumber +1);
        for (e = 0; e < grps[i].memberCount; e++) {
          fprintf(fp,"%s\n", grps[i].members[e].name);
        }
    }
    printf("Exported generated groups to human readable textfile \"generated-groups.txt\"\n\n");
    /* close the created file pointer */
    fclose(fp);
}

/*exports data to csv file*/
void export_to_csv (group *groups, int groupCount) {
    int max_members;
    FILE *fp;

    /*create output file*/
    fp = fopen("result.csv","w");
    assert(fp != NULL);

    /*find max number of members amongst the groups*/
    max_members = find_max_members (groups, groupCount);

    /*prints first row (header)*/
    make_header(groupCount, fp);

    /*prints all other rows (members)*/
    print_members(groups, groupCount, max_members, fp);

    printf("Created and wrote file: result.csv \n\n");
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
