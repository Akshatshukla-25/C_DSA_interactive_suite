#include "display_header.h"
#include "file_exporter.h"
#include "queue.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void circular_queue_demo(void)
{
    while (1)
    {
        display_header("Circular Queue Visualizer");
        Queue rollnos = {0};
        int queue_capacity_value;
        int queue_capacity_status = safe_input_int(
            &queue_capacity_value,
            "\nenter capacity number (N) of circular queue (2-100), enter '-1' to return: ", -1,
            100);

        if (queue_capacity_status == INPUT_EXIT_SIGNAL || queue_capacity_value == -1)
        {
            break;
        }
        if (queue_capacity_status == 0)
        {
            continue;
        }
        if (!init_circ_queue(queue_capacity_value, &rollnos))
        {
            printf("\nmalloc allocation failure");
            return;
        }

        while (1)
        {
            display_header("Circular Queue Operations");
            printf("[INFO] Front: %d, Rear: %d, Capacity: %d\n\n", rollnos.front, rollnos.rear,
                   rollnos.N);

            draw_unicode_box_header("LIVE QUEUE ARRAY VISUALIZER");
            printf("  Array Indices: ");
            for (int i = 0; i < rollnos.N; i++)
            {
                printf("[%02d] ", i);
            }
            printf("\n  Values:        ");
            for (int i = 0; i < rollnos.N; i++)
            {
                if (rollnos.arr[i] != NULL)
                {
                    printf("\033[1;32m%4d\033[0m ", *(int*)rollnos.arr[i]);
                }
                else
                {
                    printf("\033[1;90m   -\033[0m ");
                }
            }
            printf("\n");
            draw_unicode_box_footer();

            printf("\nOptions:\n");
            printf("1. Enqueue Element\n");
            printf("2. Dequeue Element\n");
            printf("3. Export Queue State (TXT, CSV, JSON)\n");
            printf("-1. Exit Circular Queue Demo\n");

            int circ_queue_choice;
            int circ_queue_status = safe_input_int(&circ_queue_choice, "\nEnter choice: ", -1, 3);

            if (circ_queue_status == INPUT_EXIT_SIGNAL || circ_queue_choice == -1)
            {
                destroy_circ_queue(&rollnos);
                break;
            }

            if (circ_queue_status == 0)
            {
                continue;
            }

            if (circ_queue_choice == 1)
            {
                int enqueue_val;
                int enqueue_val_status =
                    safe_input_int(&enqueue_val, "\nEnter value to enqueue (1-1000): ", 1, 1000);

                if (enqueue_val_status == INPUT_EXIT_SIGNAL)
                {
                    destroy_circ_queue(&rollnos);
                    return;
                }

                if (enqueue_val_status == 0)
                {
                    continue;
                }

                int* value = malloc(sizeof(int));
                *value = enqueue_val;
                if (enqueue(&rollnos, value) == -1)
                {
                    free(value);
                    printf("Queue is full (Circular Overflow)\n");
                }
            }
            else if (circ_queue_choice == 2)
            {
                void* removed = dequeue(&rollnos);
                if (removed == NULL)
                {
                    printf("\nQueue is empty\n");
                }
                else
                {
                    printf("\nDequeued element: %d\n", *(int*)removed);
                    free(removed);
                }
            }
            else if (circ_queue_choice == 3)
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
                        ptr += sprintf(ptr, "Circular Queue:\nFront: %d\nRear: %d\nN: %d\nArray:\n",
                                       rollnos.front, rollnos.rear, rollnos.N);
                        for (int i = 0; i < rollnos.N; i++)
                        {
                            if (rollnos.arr[i])
                                ptr += sprintf(ptr, "%d ", *(int*)rollnos.arr[i]);
                            else
                                ptr += sprintf(ptr, "- ");
                        }
                    }
                    else if (format_choice == 2)
                    {
                        char* ptr = details;
                        ptr += sprintf(ptr, "index,value\n");
                        for (int i = 0; i < rollnos.N; i++)
                        {
                            if (rollnos.arr[i])
                                ptr += sprintf(ptr, "%d,%d\n", i, *(int*)rollnos.arr[i]);
                        }
                    }
                    else
                    {
                        char* ptr = details;
                        ptr +=
                            sprintf(ptr,
                                    "{\n  \"data_structure\": \"CircularQueue\",\n  \"front\": "
                                    "%d,\n  \"rear\": %d,\n  \"capacity\": %d,\n  \"elements\": [",
                                    rollnos.front, rollnos.rear, rollnos.N);
                        bool first = true;
                        for (int i = 0; i < rollnos.N; i++)
                        {
                            if (rollnos.arr[i])
                            {
                                ptr +=
                                    sprintf(ptr, "%s%d", first ? "" : ", ", *(int*)rollnos.arr[i]);
                                first = false;
                            }
                        }
                        ptr += sprintf(ptr, "]\n}");
                    }

                    export_generic_state("CircularQueue", fmt, details);
                }
            }
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
}
