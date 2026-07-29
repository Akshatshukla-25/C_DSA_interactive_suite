#include "file_exporter.h"

bool export_bst(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "bst", "bst", dest_dir, NULL, NULL);
}

bool export_avl(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "avl", "avl", dest_dir, NULL, NULL);
}
