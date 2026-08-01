#include "count_min_sketch.h"
#include "display_header.h"
#include "file_exporter.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_min_sketch_demo(void)
{
    CountMinSketch* sketch = cms_init(0.01, 0.01);
    if (!sketch)
    {
        printf("Failed to initialize Count-Min Sketch.\n");
        return;
    }

    while (1)
    {
        display_header("Count-Min Sketch (Frequency Estimation) Visualizer");
        printf("[INFO] Matrix Dimensions: %zu Width x %zu Depth, Total stream items: %zu\n\n",
               sketch->width, sketch->depth, sketch->total_count);

        draw_unicode_box_header("LIVE CMS MATRIX GRID (Truncated to 10 Width x 4 Depth)");
        printf("  Depth\\Width ");
        for (size_t w = 0; w < 10 && w < sketch->width; w++)
        {
            printf("[%zu] ", w);
        }
        printf("\n  ------------");
        for (size_t w = 0; w < 10 && w < sketch->width; w++)
        {
            printf("----");
        }
        printf("\n");

        for (size_t d = 0; d < 4 && d < sketch->depth; d++)
        {
            printf("  Depth [%zu]:  ", d);
            for (size_t w = 0; w < 10 && w < sketch->width; w++)
            {
                uint32_t cell = sketch->table[d][w];
                if (cell > 0)
                {
                    printf("\033[1;32m%3u\033[0m ", cell);
                }
                else
                {
                    printf("\033[1;90m  -\033[0m ");
                }
            }
            printf("\n");
        }
        draw_unicode_box_footer();

        printf("\nOptions:\n");
        printf("1. Increment Frequency of Key\n");
        printf("2. Estimate Key Frequency\n");
        printf("3. Export Count-Min Sketch State (TXT, CSV, JSON)\n");
        printf("-1. Back to Probabilistic DS Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 3);
        if (status == INPUT_EXIT_SIGNAL || choice == -1)
        {
            break;
        }

        if (choice == 1)
        {
            char input_buf[256];
            int increment;
            printf("Enter item key to increment: ");
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                input_buf[strcspn(input_buf, "\n")] = '\0';
                if (safe_input_int(&increment, "Enter positive increment: ", 1, 10000) > 0)
                {
                    cms_add(sketch, input_buf, strlen(input_buf), increment);
                    printf("Item '%s' successfully incremented by %d!\n", input_buf, increment);
                }
            }
        }
        else if (choice == 2)
        {
            char input_buf[256];
            printf("Enter item key to estimate: ");
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                input_buf[strcspn(input_buf, "\n")] = '\0';
                uint32_t count = cms_estimate(sketch, input_buf, strlen(input_buf));
                printf("Estimated Frequency of '%s': \033[1;32m%u\033[0m\n", input_buf, count);
            }
        }
        else if (choice == 3)
        {
            printf("\nChoose Export Format:\n1. TXT (ASCII Table)\n2. CSV (Matrix values)\n3. JSON "
                   "(Raw Matrix)\n");
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
                    ptr += sprintf(ptr, "Width: %zu\nDepth: %zu\nTotal Count: %zu\n", sketch->width,
                                   sketch->depth, sketch->total_count);
                }
                else if (format_choice == 2)
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "width,depth,total_count\n%zu,%zu,%zu\n", sketch->width,
                                   sketch->depth, sketch->total_count);
                }
                else
                {
                    char* ptr = details;
                    ptr += sprintf(
                        ptr, "{\n  \"width\": %zu,\n  \"depth\": %zu,\n  \"total_count\": %zu\n}",
                        sketch->width, sketch->depth, sketch->total_count);
                }

                export_generic_state("CMS", fmt, details);
            }
        }
        printf("\nPress Enter to continue...");
        getchar();
    }

    cms_free(sketch);
}
