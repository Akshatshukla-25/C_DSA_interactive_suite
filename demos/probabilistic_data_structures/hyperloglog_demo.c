#include "display_header.h"
#include "file_exporter.h"
#include "hyperloglog.h"
#include "safe_input.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hyperloglog_demo(void)
{
    uint8_t precision = 6; // Use smaller precision so we can show it visually
    HyperLogLog* hll = hll_init(precision);
    if (!hll)
    {
        printf("Failed to initialize HyperLogLog.\n");
        return;
    }

    while (1)
    {
        display_header("HyperLogLog (Cardinality Estimator) Visualizer");
        uint64_t est = hll_count(hll);
        printf("[INFO] Registers: %zu (2^%d), Estimated distinct elements count: %llu\n\n", hll->m,
               precision, (unsigned long long)est);

        draw_unicode_box_header("LIVE HLL REGISTERS GRID (Showing 64 Registers)");
        printf("  ");
        for (size_t i = 0; i < 64 && i < hll->m; i++)
        {
            uint8_t val = hll->registers[i];
            if (val > 0)
            {
                printf("\033[1;32m%02x\033[0m ", val);
            }
            else
            {
                printf("\033[1;90m--\033[0m ");
            }

            if ((i + 1) % 8 == 0)
            {
                printf("\n  ");
            }
        }
        printf("\n");
        draw_unicode_box_footer();

        printf("\nOptions:\n");
        printf("1. Add Key to Stream\n");
        printf("2. Export HyperLogLog State (TXT, CSV, JSON)\n");
        printf("-1. Back to Probabilistic DS Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 2);
        if (status == INPUT_EXIT_SIGNAL || choice == -1)
        {
            break;
        }

        if (choice == 1)
        {
            char input_buf[256];
            printf("Enter item key to add: ");
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                input_buf[strcspn(input_buf, "\n")] = '\0';
                if (strlen(input_buf) > 0)
                {
                    hll_add(hll, input_buf, strlen(input_buf));
                    printf("Key '%s' successfully added to HyperLogLog stream!\n", input_buf);
                }
            }
        }
        else if (choice == 2)
        {
            printf("\nChoose Export Format:\n1. TXT (ASCII Registers)\n2. CSV (Values)\n3. JSON "
                   "(Raw Array)\n");
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
                    ptr += sprintf(ptr,
                                   "Registers count: %zu\nPrecision bits: %d\nEstimated Count: "
                                   "%llu\nRegisters:\n",
                                   hll->m, precision, (unsigned long long)est);
                    for (size_t i = 0; i < 64 && i < hll->m; i++)
                    {
                        ptr += sprintf(ptr, "%02x ", hll->registers[i]);
                    }
                }
                else if (format_choice == 2)
                {
                    char* ptr = details;
                    ptr +=
                        sprintf(ptr, "registers_m,precision,estimated_cardinality\n%zu,%d,%llu\n",
                                hll->m, precision, (unsigned long long)est);
                }
                else
                {
                    char* ptr = details;
                    ptr += sprintf(ptr,
                                   "{\n  \"registers_m\": %zu,\n  \"precision\": %d,\n  "
                                   "\"estimated_cardinality\": %llu\n}",
                                   hll->m, precision, (unsigned long long)est);
                }

                export_generic_state("HLL", fmt, details);
            }
        }
        printf("\nPress Enter to continue...");
        getchar();
    }

    hll_free(hll);
}
