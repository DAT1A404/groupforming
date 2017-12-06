#include "datastructs.c"
#include "visual.h"
#include "utility.h"
#include "export.h"
#include "commands.h"
#include "export.h"

/* Dialog with user post algorithm. Allows user to print and export in various ways */
void show_commands(group *grps, int debug) {

    do {

        char option;

        /* Ask user about what they wanna do next */
        set_color(GREEN, BLACK);
        printf("What do you want to do now?\n");
        reset_color();

        /* Print options */
        printf("(a) Inspect final groups.\n");
        printf("(b) Toggle debug flag. Currently %s.\n", debug?"ON":"OFF");
        printf("(c) Export groups plain.\n");
        printf("(d) Export groups CSV.\n");
        printf("(e) See specific group.\n");
        printf("(f) See specific person.\n");
        printf("(q) Quit program.\n");

        /* Scan for input */
        scanf(" %c", &option);

        clear_screen();

        /* Switch over options */
        switch (option) {
            case 'a': print_all_groups(grps, _GroupCount, debug); break;
            case 'b': debug = !debug; break;
            case 'c': export_plain(grps, _GroupCount); break;
            case 'd': export_to_csv(grps, _GroupCount); break;
            case 'e': see_group(grps, _GroupCount, debug); break;
            case 'f': see_person(grps, _GroupCount, debug); break;
            case 'q': return;
        }

    } while (1);
}

/* Prints an error message if options is not implemented yet */
void print_not_implemented() {
    set_color(COLOR_ERROR, BLACK);
    printf("Not implemented yet :(\n");
    reset_color();
}

/*prints a requested group*/
void see_group(group *grps, int _GroupCount, int debug) {
  int groupID;

  do {
    printf("%d groups present. Type the ID of the group you wish to inspect: ", _GroupCount );
    /* if an int is not input, terminate program, however if "f" or "q" is used, program switches in function-dialogue */
    if (scanf(" %d", &groupID) != 1) {
      printf("Input not recognised as an integer.\n");
      return;
    }
      /* checks if the input is a valid group ID */
    } while ( groupID <= 0 || groupID > _GroupCount );
      groupID--;
      /* print requested group */
      printf("\n");
      print_group(&(grps[groupID]), debug);
      printf("\n");

}

/* prints the group, which a person is in */
void see_person(group *grps, int _GroupCount, int debug) {
    int i, j, match = -1;
    char needle[40];

    printf("Which person do you want to search for?\n");
    scanf(" %[^\n]s", needle);

    /* searches all groups */
    for (i=0; i<_GroupCount; i++) {
        /* searches all members' names in the groups */
        for (j=0; j<grps[i].memberCount; j++) {
            /* if the person is found, save the location as match */
            if (strequal(grps[i].members[j].name, needle)) {
                match = i;
                break;
            }
        }
        if (strequal(grps[i].members[j].name, needle)) {
            break;
        }
    }

    /* if a match is found, print group */
    if (match != -1) {
        printf("\n\"%s\" found in group %d \n",needle, i + 1);
        print_group(&(grps[i]), debug);
        printf("\n");
    }
    else printf("\nPerson not found \n\n");
}
