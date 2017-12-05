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
        printf("(b) Debug final groups.\n");
        printf("(c) Export groups plain.\n");
        printf("(d) Export groups CSV.\n");
        printf("(q) Quit program.\n");

        /* Scan for input */
        scanf(" %c", &option);

        clear_screen();

        /* Switch over options */
        switch (option) {
            case 'a': print_all_groups(grps, _GroupCount, debug); break;
            case 'b': print_not_implemented(); break;
            case 'c': export_plain(grps, _GroupCount); break;
            case 'd': export_to_csv(grps, _GroupCount); break;
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
