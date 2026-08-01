#include "display_header.h"
#include "file_exporter.h"
#include "queue.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void simple_queue_demo(void)
{
    while (1)
    {
        display_header("Simple Queue Visualizer");
        Queue q = {0};
        int queue_capacity_value;
        int queue_capacity_status = safe_input_int(
            &queue_capacity_value,
            "\nenter capacity number (N) of simple queue (1-100), enter '-1' to return: ", -1, 100);

        if (queue_capacity_status == INPUT_EXIT_SIGNAL || queue_capacity_value == -1)
        {
            break;
        }
        if (queue_capacity_status == 0)
        {
            continue;
        }
        if (!init_simple_queue(queue_capacity_value, &q))
        {
            printf("\nmalloc allocation failure");
            return;
        }

        while (1)
        {
            display_header("Simple Queue Operations");
            printf("[INFO] Front: %d, Rear: %d, Capacity: %d\n\n", q.front, q.rear, q.N);

            draw_unicode_box_header("LIVE QUEUE ARRAY VISUALIZER");
            printf("  Array Indices: ");
            for (int i = 0; i < q.N; i++)
            {
                printf("[%02d] ", i);
            }
            printf("\n  Values:        ");
            for (int i = 0; i < q.N; i++)
            {
                if (q.arr[i] != NULL)
                {
                    printf("\033[1;32m%4d\033[0m ", *(int*)q.arr[i]);
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
            printf("-1. Exit Simple Queue Demo\n");

            int simple_queue_choice;
            int simple_queue_status =
                safe_input_int(&simple_queue_choice, "\nEnter choice: ", -1, 3);

            if (simple_queue_status == INPUT_EXIT_SIGNAL || simple_queue_choice == -1)
            {
                destroy_simple_queue(&q);
                break;
            }

            if (simple_queue_status == 0)
            {
                continue;
            }

            if (simple_queue_choice == 1)
            {
                int enqueue_val;
                int enqueue_val_status =
                    safe_input_int(&enqueue_val, "\nEnter value to enqueue (1-1000): ", 1, 1000);

                if (enqueue_val_status == INPUT_EXIT_SIGNAL)
                {
                    destroy_simple_queue(&q);
                    return;
                }

                if (enqueue_val_status == 0)
                {
                    continue;
                }

                int* ptr = malloc(sizeof(int));
                *ptr = enqueue_val;

                if (enqueue_simple(&q, ptr) == -1)
                {
                    free(ptr);
                    printf(
                        "\nQueue is full (linear overflow - freed front slots cannot be reused)\n");
                }
            }
            else if (simple_queue_choice == 2)
            {
                void* removed = dequeue_simple(&q);
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
            else if (simple_queue_choice == 3)
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
                        ptr += sprintf(ptr, "Simple Queue:\nFront: %d\nRear: %d\nN: %d\nArray:\n",
                                       q.front, q.rear, q.N);
                        for (int i = 0; i < q.N; i++)
                        {
                            if (q.arr[i])
                                ptr += sprintf(ptr, "%d ", *(int*)q.arr[i]);
                            else
                                ptr += sprintf(ptr, "- ");
                        }
                    }
                    else if (format_choice == 2)
                    {
                        char* ptr = details;
                        ptr += sprintf(ptr, "index,value\n");
                        for (int i = 0; i < q.N; i++)
                        {
                            if (q.arr[i])
                                ptr += sprintf(ptr, "%d,%d\n", i, *(int*)q.arr[i]);
                        }
                    }
                    else
                    {
                        char* ptr = details;
                        ptr +=
                            sprintf(ptr,
                                    "{\n  \"data_structure\": \"SimpleQueue\",\n  \"front\": %d,\n "
                                    " \"rear\": %d,\n  \"capacity\": %d,\n  \"elements\": [",
                                    q.front, q.rear, q.N);
                        bool first = true;
                        for (int i = 0; i < q.N; i++)
                        {
                            if (q.arr[i])
                            {
                                ptr += sprintf(ptr, "%s%d", first ? "" : ", ", *(int*)q.arr[i]);
                                first = false;
                            }
                        }
                        ptr += sprintf(ptr, "]\n}");
                    }

                    export_generic_state("SimpleQueue", fmt, details);
                }
            }
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
}
