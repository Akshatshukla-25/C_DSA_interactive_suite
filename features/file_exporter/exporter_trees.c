#include "file_exporter.h"

bool export_bst(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "bst", "trees", dest_dir, NULL, NULL);
}

bool export_avl(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "avl", "trees", dest_dir, NULL, NULL);
}
