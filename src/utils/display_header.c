#include "display_header.h"
#include "clear_screen.h"
#include <stdio.h>

void display_header(const char* module_name)
{
    if (module_name == NULL)
    {
        module_name = "";
    }

    /* Start every module on a clean screen. */
    clear_screen();

    /* Cyan bordered title, consistent across all demos. */
    printf("\033[1;36m");
    printf("════════════════════════════════════════\n");
    printf("  === %s ===\n", module_name);
    printf("════════════════════════════════════════\n");
    printf("\033[0m\n");

    fflush(stdout);
}
