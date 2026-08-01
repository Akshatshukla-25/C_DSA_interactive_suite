#include "bloom_filter.h"
#include "display_header.h"
#include "file_exporter.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bloom_filter_demo(void)
{
    BloomFilter* filter = bloom_init(100, 0.01);
    if (!filter)
    {
        printf("Failed to initialize Bloom Filter.\n");
        return;
    }

    while (1)
    {
        display_header("Bloom Filter (Set Membership) Visualizer");
        printf("[INFO] Bit Array Size: %zu bits, Hash Functions: %zu, Items Inserted: %zu\n\n",
               filter->bit_size, filter->num_hashes, filter->count);

        draw_unicode_box_header("LIVE BIT ARRAY GRID (First 64 Bits)");
        printf("  ");
        for (size_t i = 0; i < 64 && i < filter->bit_size; i++)
        {
            size_t byte_idx = i / 8;
            size_t bit_idx = i % 8;
            bool bit_val = (filter->bit_array[byte_idx] & (1 << bit_idx)) != 0;

            if (bit_val)
            {
                printf("\033[1;32m🟩[1]\033[0m ");
            }
            else
            {
                printf("\033[1;90m⬛[0]\033[0m ");
            }

            if ((i + 1) % 8 == 0)
            {
                printf("\n  ");
            }
        }
        printf("\n");
        draw_unicode_box_footer();

        printf("\nOptions:\n");
        printf("1. Add Key to Filter\n");
        printf("2. Check Key Membership\n");
        printf("3. Export Bloom Filter State (TXT, CSV, JSON)\n");
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
            printf("Enter string key to insert: ");
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                input_buf[strcspn(input_buf, "\n")] = '\0';
                if (strlen(input_buf) > 0)
                {
                    bloom_add(filter, input_buf, strlen(input_buf));
                    printf("Key '%s' successfully added to Bloom Filter!\n", input_buf);
                }
            }
        }
        else if (choice == 2)
        {
            char input_buf[256];
            printf("Enter string key to check: ");
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                input_buf[strcspn(input_buf, "\n")] = '\0';
                bool res = bloom_check(filter, input_buf, strlen(input_buf));
                printf("Key Check Result: %s\n", res ? "\033[1;32mMAY BE PRESENT\033[0m"
                                                     : "\033[1;31mDEFINITELY ABSENT\033[0m");
            }
        }
        else if (choice == 3)
        {
            printf("\nChoose Export Format:\n1. TXT (ASCII Grid)\n2. CSV (Data Pairs)\n3. JSON "
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
                    ptr += sprintf(ptr, "Bit Size: %zu\nHashes: %zu\nBit Array:\n",
                                   filter->bit_size, filter->num_hashes);
                    for (size_t i = 0; i < 64 && i < filter->bit_size; i++)
                    {
                        size_t byte_idx = i / 8;
                        size_t bit_idx = i % 8;
                        bool bit_val = (filter->bit_array[byte_idx] & (1 << bit_idx)) != 0;
                        ptr += sprintf(ptr, "%d", bit_val ? 1 : 0);
                    }
                }
                else if (format_choice == 2)
                {
                    char* ptr = details;
                    ptr += sprintf(ptr, "bit_size,num_hashes,count\n%zu,%zu,%zu\n",
                                   filter->bit_size, filter->num_hashes, filter->count);
                }
                else
                {
                    char* ptr = details;
                    ptr += sprintf(
                        ptr, "{\n  \"bit_size\": %zu,\n  \"num_hashes\": %zu,\n  \"count\": %zu\n}",
                        filter->bit_size, filter->num_hashes, filter->count);
                }

                export_generic_state("BloomFilter", fmt, details);
            }
        }
        printf("\nPress Enter to continue...");
        getchar();
    }

    bloom_free(filter);
}
