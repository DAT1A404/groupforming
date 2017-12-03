#include "datastructs.c"
#include "visual.h"
#include "utility.h"
#include "commands.h"

/* Dialog with user post algorithm. Allows user to print and export in various ways */
void show_commands(group *grps) {
    
    do {
        
        char option;
        
        /* Ask user about what they wanna do next */
        set_color(LIGHTGREEN, BLACK);
        printf("What do you wanna do now?\n");
        reset_color();
        
        /* Print options */
        printf("(a) Inspect final groups.\n");
        printf("(b) Export groups.\n");
        printf("(q) Quit program.\n");
        
        /* Scan for input */
        scanf(" %c", &option);
        
        clear_screen();
        
        /* Switch over options */
        switch (option) {
            case 'a': print_all_groups(grps, _GroupCount); break;
            case 'b':
                set_color(COLOR_ERROR, BLACK);
                printf("Not implemented yet :(\n");
                reset_color();
                break;
            case 'q': return;
        }
        
    } while (1);
}