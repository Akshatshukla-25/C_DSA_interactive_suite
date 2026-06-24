#include "clear_screen.h"
#include "cross_platform_timer.h"
#include <stdlib.h>

void clear_screen(void)
{
    if (!is_terminal_interactive()) {
        return;
    }
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

