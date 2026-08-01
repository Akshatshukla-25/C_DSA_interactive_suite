#include "display_header.h"
#include "file_exporter.h"
#include "priority_queue.h"
#include "safe_input.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void priority_queue_demo(void)
{
    while (1)
    {
        display_header("Priority Queue (Heap) Visualizer");
        int max_min_heap_val;
        int max_min_heap_status = safe_input_int(
            &max_min_heap_val, "\nEnter 0 for min heap or 1 for max heap, -1 to return: ", -1, 1);

        if (max_min_heap_status == INPUT_EXIT_SIGNAL || max_min_heap_val == -1)
        {
            printf("\nExiting priority queue demo.....\n");
            return;
        }

        if (max_min_heap_status == 0)
            continue;

        priority_queue* pq = pq_init((HeapType)max_min_heap_val);
        if (pq == NULL)
        {
            printf("\nAllocation failed, Exiting demo.\n");
            return;
        }

        while (1)
        {
            display_header("Priority Queue Interactive Options");
            printf("[INFO] Heap Type: %s, Current Size: %d / %d\n\n",
                   pq->heapType == MIN_HEAP ? "MIN HEAP" : "MAX HEAP", pq->size, HEAP_CAPACITY);

            draw_unicode_box_header("LIVE HEAP ARRAY VISUALIZER");
            printf("  Array Indices: ");
            for (int i = 0; i < pq->size && i < 16; i++)
            {
                printf("[%02d] ", i);
            }
            printf("\n  Values:        ");
            for (int i = 0; i < pq->size && i < 16; i++)
            {
                printf("\033[1;32m%4d\033[0m ", pq->heap[i]);
            }
            printf("\n");
            draw_unicode_box_footer();

            printf("\nOptions:\n");
            printf("1. Insert Element\n");
            printf("2. Extract Top Element\n");
            printf("3. Peek Top Element\n");
            printf("4. Export Heap State (TXT, CSV, JSON)\n");
            printf("-1. Exit Heap Demo\n");

            int pq_choice;
            int pq_choice_status = safe_input_int(&pq_choice, "\nEnter choice: ", -1, 4);

            if (pq_choice_status == INPUT_EXIT_SIGNAL || pq_choice == -1)
            {
                destroy_pq(pq);
                break;
            }

            if (pq_choice_status == 0)
                continue;

            if (pq_choice == 1)
            {
                int insert_val;
                int insert_status =
                    safe_input_int(&insert_val, "\nEnter a number to insert: ", 0, INT_MAX);

                if (insert_status == INPUT_EXIT_SIGNAL)
                {
                    destroy_pq(pq);
                    return;
                }

                if (insert_status == 0)
                    continue;

                if (insert(pq, insert_val) == 0)
                {
                    printf("\nHeap is full.\n");
                    continue;
                }
            }
            else if (pq_choice == 2)
            {
                int extracted_element;
                bool extracted_element_status = extractTop(pq, &extracted_element);

                if (!extracted_element_status)
                {
                    printf("\nHeap is empty.\n");
                    continue;
                }

                printf("\nExtracted element: %d\n", extracted_element);
            }
            else if (pq_choice == 3)
            {
                int peek_element;
                bool peek_element_status = peek_pq(pq, &peek_element);

                if (!peek_element_status)
                {
                    printf("\nHeap is empty.\n");
                    continue;
                }

                printf("\nTop element is: %d\n", peek_element);
            }
            else if (pq_choice == 4)
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
                        ptr += sprintf(ptr, "HeapType: %s\nSize: %d\nArray:\n",
                                       pq->heapType == MIN_HEAP ? "MIN" : "MAX", pq->size);
                        for (int i = 0; i < pq->size; i++)
                        {
                            ptr += sprintf(ptr, "%d ", pq->heap[i]);
                        }
                    }
                    else if (format_choice == 2)
                    {
                        char* ptr = details;
                        ptr += sprintf(ptr, "index,value\n");
                        for (int i = 0; i < pq->size; i++)
                        {
                            ptr += sprintf(ptr, "%d,%d\n", i, pq->heap[i]);
                        }
                    }
                    else
                    {
                        char* ptr = details;
                        ptr += sprintf(
                            ptr, "{\n  \"heap_type\": \"%s\",\n  \"size\": %d,\n  \"heap\": [",
                            pq->heapType == MIN_HEAP ? "MIN" : "MAX", pq->size);
                        for (int i = 0; i < pq->size; i++)
                        {
                            ptr +=
                                sprintf(ptr, "%d%s", pq->heap[i], (i == pq->size - 1) ? "" : ", ");
                        }
                        ptr += sprintf(ptr, "]\n}");
                    }

                    export_generic_state("PriorityQueue", fmt, details);
                }
            }
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
}
