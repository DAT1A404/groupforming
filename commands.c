#include "datastructs.c"
#include "visual.h"
#include "utility.h"
#include "commands.h"

/* Dialog with user post algorithm. Allows user to print and export in various ways */
void show_commands(Group *grps, int groupCount) {
    
    do {
        
        char option;
        
        /* Ask user about what they wanna do next */
        set_color(LIGHTGREEN, BLACK);
        printf("What do you want to do now?\n");
        reset_color();
        
        /* Print options */
        printf("(a) Inspect final groups.\n");
        printf("(b) Debug final groups.\n");
        printf("(c) Export groups clean.\n");
        printf("(d) Export groups CSV.\n");
        printf("(q) Quit program.\n");
        
        /* Scan for input */
        scanf(" %c", &option);
        
        clear_screen();
        
        /* Switch over options */
        switch (option) {
            case 'a': print_all_groups(grps, groupCount); break;
            case 'b': print_not_implemented(); break;
            case 'c': print_not_implemented(); break;
            case 'd': print_not_implemented(); break;
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