#include "display_header.h"
#include "file_exporter.h"
#include "safe_input.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_demo(void)
{
    stack* s = createStack();
    if (s == NULL)
    {
        printf("\nFailed to allocate memory for the Stack.\n");
        return;
    }

    printf("\nStack initialized. Operations are performed LIFO (Last In First Out).\n");
    printStackAsInts(s);

    while (1)
    {
        int choice;
        int status = safe_input_int(&choice,
                                    "\n--- Stack Operations Menu ---\n"
                                    "1. Push (Insert element onto Stack)\n"
                                    "2. Pop (Remove element from Stack)\n"
                                    "3. Peek (View top element)\n"
                                    "4. Export Stack State (TXT, CSV, JSON)\n"
                                    "enter choice ('-1' to exit, or 'help') : ",
                                    1, 4);

        if (status == INPUT_EXIT_SIGNAL)
        {
            break;
        }

        if (status == 0)
        {
            continue;
        }

        if (choice == 1)
        {
            int val;
            int val_status = safe_input_int(
                &val, "\nEnter integer value to push (1 to 100), or -1 to exit: ", 1, 100);
            if (val_status == INPUT_EXIT_SIGNAL)
            {
                break;
            }
            if (val_status == 0)
            {
                continue;
            }
            if (push(s, (void*)(intptr_t)val) == 1)
            {
                printf("\nSuccessfully pushed %d onto the stack.\n", val);
            }
            else
            {
                printf("\nFailed to push %d onto the stack (allocation failure).\n", val);
            }
            printStackAsInts(s);
        }
        else if (choice == 2)
        {
            if (isEmpty(s))
            {
                printf("\nStack Underflow: Cannot pop from an empty stack.\n");
            }
            else
            {
                int val = (int)(intptr_t)pop(s);
                printf("\nPopped element: %d\n", val);
            }
            printStackAsInts(s);
        }
        else if (choice == 3)
        {
            if (isEmpty(s))
            {
                printf("\nStack is empty: No element to peek.\n");
            }
            else
            {
                int val = (int)(intptr_t)peek(s);
                printf("\nTop element: %d\n", val);
            }
            printStackAsInts(s);
        }
        else if (choice == 4)
        {
            printf("\nChoose Export Format:\n1. TXT\n2. CSV\n3. JSON\n");
            int format_choice;
            if (safe_input_int(&format_choice, "Enter format choice (1-3): ", 1, 3) > 0)
            {
                const char* fmt = (format_choice == 1)   ? "txt"
                                  : (format_choice == 2) ? "csv"
                                                         : "json";
                char details[4096] = {0};

                if (format_choice == 1)
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "Stack Contents:\n");
                    Node* curr = s->top;
                    while (curr)
                    {
                        ptr += sprintf(ptr, "| %d |\n", (int)(intptr_t)curr->data);
                        curr = curr->next;
                    }
                    ptr += sprintf(ptr, "=====\n");
                }
                else if (format_choice == 2)
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "index,value\n");
                    Node* curr = s->top;
                    int idx = 0;
                    while (curr)
                    {
                        ptr += sprintf(ptr, "%d,%d\n", idx++, (int)(intptr_t)curr->data);
                        curr = curr->next;
                    }
                }
                else
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "{\n  \"data_structure\": \"Stack\",\n  \"elements\": [");
                    Node* curr = s->top;
                    while (curr)
                    {
                        ptr +=
                            sprintf(ptr, "%d%s", (int)(intptr_t)curr->data, curr->next ? ", " : "");
                        curr = curr->next;
                    }
                    ptr += sprintf(ptr, "]\n}");
                }

                export_generic_state("Stack", fmt, details);
            }
        }
    }

    destroyStack(s, NULL);
    printf("\nStack destroyed. Returning to Data Structures menu...\n");
}
