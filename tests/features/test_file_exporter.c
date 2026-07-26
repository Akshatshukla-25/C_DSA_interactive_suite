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

int main(void)
{
    test_dfs_search();
    test_copy_file_contents();
    test_export_file_pair();
    return 0;
}
