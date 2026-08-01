#include "file_exporter.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void check_file_exists(const char* filepath)
{
    FILE* fp = fopen(filepath, "r");
    assert(fp != NULL);
    fclose(fp);
}

void test_dfs_search(void)
{
    char found_path[512] = {0};
    bool found = dfs_search_file(".", "sll.c", found_path);
    assert(found == true);
    assert(strstr(found_path, "sll.c") != NULL);
    printf("test_dfs_search passed! Found: %s\n", found_path);
}

void test_copy_file_contents(void)
{
    char found_path[512] = {0};
    assert(dfs_search_file(".", "sll.c", found_path) == true);

    const char* test_dest = "./test_export/sll.c";
    bool copied = copy_file_contents(found_path, test_dest);
    assert(copied == true);

    check_file_exists(test_dest);
    printf("test_copy_file_contents passed!\n");
}

void test_export_file_pair(void)
{
    char c_path[512] = {0};
    char h_path[512] = {0};
    bool res = export_file_pair(".", "sll", "sll", "./test_export", c_path, h_path);
    assert(res == true);
    assert(strstr(c_path, "sll.c") != NULL);
    assert(strstr(h_path, "sll.h") != NULL);
    check_file_exists(c_path);
    check_file_exists(h_path);
    printf("test_export_file_pair passed!\n");
}

void test_structure_exporters(void)
{
    assert(export_sll(".", "./test_export/sll_out") == true);
    check_file_exists("./test_export/sll_out/sll.c");
    check_file_exists("./test_export/sll_out/sll.h");

    assert(export_dll(".", "./test_export/dll_out") == true);
    check_file_exists("./test_export/dll_out/dll.c");
    check_file_exists("./test_export/dll_out/dll.h");

    assert(export_bst(".", "./test_export/bst_out") == true);
    check_file_exists("./test_export/bst_out/bst.c");
    check_file_exists("./test_export/bst_out/bst.h");

    assert(export_circular_queue(".", "./test_export/queue_out") == true);
    check_file_exists("./test_export/queue_out/circular_queue.c");
    check_file_exists("./test_export/queue_out/queue.h");

    assert(export_stack(".", "./test_export/stack_out") == true);
    check_file_exists("./test_export/stack_out/stack.c");
    check_file_exists("./test_export/stack_out/stack.h");

    printf("test_structure_exporters passed!\n");
}

void test_advanced_data_structure_exporters(void)
{
    assert(export_avl(".", "./test_export/avl_out") == true);
    check_file_exists("./test_export/avl_out/avl.c");
    check_file_exists("./test_export/avl_out/avl.h");

    assert(export_heaps(".", "./test_export/heaps_out") == true);
    check_file_exists("./test_export/heaps_out/priority_queue.c");
    check_file_exists("./test_export/heaps_out/priority_queue.h");

    printf("test_advanced_data_structure_exporters passed!\n");
}

void test_export_generic_state(void)
{
    printf("Running test_export_generic_state...\n");

    // Test TXT export
    assert(export_generic_state("BloomFilter", "txt", "bit_array: 10101010") == true);
    check_file_exists("exports/BloomFilter_state.txt");

    // Test CSV export
    assert(export_generic_state("PriorityQueue", "csv", "index,val\n0,10\n1,20") == true);
    check_file_exists("exports/PriorityQueue_state.csv");

    // Test JSON export
    assert(export_generic_state("CMS", "json", "{\"width\": 10, \"depth\": 4}") == true);
    check_file_exists("exports/CMS_state.json");

    printf("test_export_generic_state passed!\n");
}

int main(void)
{
    test_dfs_search();
    test_copy_file_contents();
    test_export_file_pair();
    test_structure_exporters();
    test_advanced_data_structure_exporters();
    test_export_generic_state();
    return 0;
}
