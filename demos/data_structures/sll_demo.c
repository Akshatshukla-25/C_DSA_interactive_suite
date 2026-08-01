#include "display_header.h"
#include "file_exporter.h"
#include "safe_input.h"
#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_int(const void* data)
{
    if (data != NULL)
    {
        printf("\033[1;32m[%d]\033[0m", *(const int*)data);
    }
}

static int compare_ints(const void* a, const void* b)
{
    return *(const int*)a - *(const int*)b;
}

void sll_demo(void)
{
    Node* head = NULL;

    while (1)
    {
        display_header("Singly Linked List Visualizer");

        // Live visual display inside unicode box
        draw_unicode_box_header("LIVE LIST GRAPH representation");
        printf("  List: ");
        if (head == NULL)
        {
            printf("\033[1;31mEMPTY (NULL)\033[0m\n");
        }
        else
        {
            Node* curr = head;
            while (curr)
            {
                print_int(curr->data);
                if (curr->next)
                {
                    printf(" \033[1;90m──>\033[0m ");
                }
                curr = curr->next;
            }
            printf(" \033[1;90m──>\033[0m \033[1;31mNULL\033[0m\n");
        }
        printf("\n  Length: %d nodes\n", sll_getLength(head));
        draw_unicode_box_footer();

        printf("\nOptions:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete by Value\n");
        printf("5. Delete at Position\n");
        printf("6. Search for Value\n");
        printf("7. Reverse List\n");
        printf("8. Export List State (TXT, CSV, JSON)\n");
        printf("-1. Exit SLL Demo\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", -1, 8);
        if (status == INPUT_EXIT_SIGNAL || choice == -1)
        {
            break;
        }

        if (choice == 1)
        {
            int val;
            if (safe_input_int(&val, "Enter value to insert at beginning: ", 1, 1000) > 0)
            {
                int* data = malloc(sizeof(int));
                *data = val;
                sll_insertAtBeginning(&head, data);
            }
        }
        else if (choice == 2)
        {
            int val;
            if (safe_input_int(&val, "Enter value to insert at end: ", 1, 1000) > 0)
            {
                int* data = malloc(sizeof(int));
                *data = val;
                sll_insertAtEnd(&head, data);
            }
        }
        else if (choice == 3)
        {
            int val, pos;
            if (safe_input_int(&val, "Enter value to insert: ", 1, 1000) > 0)
            {
                if (safe_input_int(&pos, "Enter position: ", 0, sll_getLength(head)) > 0)
                {
                    int* data = malloc(sizeof(int));
                    *data = val;
                    sll_insertAtPosition(&head, data, pos);
                }
            }
        }
        else if (choice == 4)
        {
            int val;
            if (safe_input_int(&val, "Enter value to delete: ", 1, 1000) > 0)
            {
                sll_deleteByValue(&head, &val, compare_ints, free);
            }
        }
        else if (choice == 5)
        {
            int pos;
            if (safe_input_int(&pos, "Enter position to delete: ", 0, sll_getLength(head) - 1) > 0)
            {
                sll_deleteAtPosition(&head, pos, free);
            }
        }
        else if (choice == 6)
        {
            int val;
            if (safe_input_int(&val, "Enter value to search: ", 1, 1000) > 0)
            {
                int idx = sll_search(head, &val, compare_ints);
                if (idx != -1)
                {
                    printf("Value found at index: \033[1;32m%d\033[0m\n", idx);
                }
                else
                {
                    printf("\033[1;31mValue not found in list.\033[0m\n");
                }
            }
        }
        else if (choice == 7)
        {
            sll_reverseList(&head);
            printf("List reversed successfully!\n");
        }
        else if (choice == 8)
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
                    ptr += sprintf(ptr, "Singly Linked List:\n");
                    Node* curr = head;
                    while (curr)
                    {
                        ptr += sprintf(ptr, "[%d] -> ", *(int*)curr->data);
                        curr = curr->next;
                    }
                    ptr += sprintf(ptr, "NULL\n");
                }
                else if (format_choice == 2)
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "index,value\n");
                    Node* curr = head;
                    int idx = 0;
                    while (curr)
                    {
                        ptr += sprintf(ptr, "%d,%d\n", idx++, *(int*)curr->data);
                        curr = curr->next;
                    }
                }
                else
                {
                    char* ptr = details;
                    ptr += sprintf(
                        ptr, "{\n  \"data_structure\": \"SinglyLinkedList\",\n  \"nodes\": [");
                    Node* curr = head;
                    while (curr)
                    {
                        ptr += sprintf(ptr, "%d%s", *(int*)curr->data, curr->next ? ", " : "");
                        curr = curr->next;
                    }
                    ptr += sprintf(ptr, "]\n}");
                }

                export_generic_state("SinglyLinkedList", fmt, details);
            }
        }
        printf("\nPress Enter to continue...");
        getchar();
    }

    delete_sll(head, free);
}
