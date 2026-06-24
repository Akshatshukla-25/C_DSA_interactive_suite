#ifndef DISPLAY_HEADER_H
#define DISPLAY_HEADER_H

/**
 * Clears the terminal screen and prints a formatted header for a module.
 *
 * The screen is cleared via clear_screen() (cross-platform), then a bordered
 * title such as
 *
 *     ════════════════════════════════════
 *      === SINGLY LINKED LIST ===
 *     ════════════════════════════════════
 *
 * is printed so the user always starts a demo on a clean screen.
 *
 * @param module_name Name of the module/demo to show in the header.
 */
void display_header(const char* module_name);

#endif // DISPLAY_HEADER_H
