#include <stdio.h>
#include "help.h"

void launch_help_page(void) {
    // Clear terminal screen for that immersive "man page" feel
    printf("\033[H\033[2J"); 
    
    printf("=================================================================\n");
    printf("C DSA INTERACTIVE SUITE - USER MANUAL (man help)\n");
    printf("=================================================================\n\n");
    
    printf("DESCRIPTION\n");
    printf("    The C DSA Interactive Suite is a terminal-based application\n");
    printf("    designed to help you visualize and interact with Data Structures\n");
    printf("    and Algorithms implemented in C.\n\n");
    
    printf("NAVIGATION & COMMANDS\n");
    printf("    help        - Launches this help page from any input prompt.\n");
    printf("    X or x      - Exits the current menu, sub-suite, or application.\n");
    printf("    Numbers     - Choose specific menu items or menu paths.\n\n");
    
    printf("SUITE MODULES\n");
    printf("    • Linked Lists (Singly, Doubly, Circular)\n");
    printf("    • Stacks & Queues\n");
    printf("    • Trees & Graphs\n");
    printf("    • Sorting & Searching Visualizers\n\n");
    
    printf("=================================================================\n");
    printf("Press [ENTER] to exit the manual and resume your session...\n");
    printf("=================================================================\n");
    
    // Wait for user acknowledgment before returning
    getchar(); 
    
    // Clear screen again to restore the clean look of the app menu
    printf("\033[H\033[2J"); 
}