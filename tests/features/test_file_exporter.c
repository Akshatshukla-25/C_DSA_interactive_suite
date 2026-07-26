#include "file_exporter.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    FILE* fp = fopen(test_dest, "r");
    assert(fp != NULL);
    fclose(fp);

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
    printf("test_export_file_pair passed!\n");
}

void test_structure_exporters(void)
{
    assert(export_sll(".", "./test_export/sll_out") == true);
    assert(export_dll(".", "./test_export/dll_out") == true);
    assert(export_bst(".", "./test_export/bst_out") == true);
    assert(export_circular_queue(".", "./test_export/queue_out") == true);
    assert(export_stack(".", "./test_export/stack_out") == true);

    printf("test_structure_exporters passed!\n");
}

void test_advanced_data_structure_exporters(void)
{
    assert(export_avl(".", "./test_export/avl_out") == true);
    assert(export_heaps(".", "./test_export/heaps_out") == true);

    printf("test_advanced_data_structure_exporters passed!\n");
}

int main(void)
{
    test_dfs_search();
    test_copy_file_contents();
    test_export_file_pair();
    test_structure_exporters();
    test_advanced_data_structure_exporters();
    return 0;
}
