#include "file_exporter.h"

bool export_sll(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "sll", "sll", dest_dir, NULL, NULL);
}

bool export_dll(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "dll", "dll", dest_dir, NULL, NULL);
}

bool export_circular_queue(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "circular_queue", "queue", dest_dir, NULL, NULL);
}

bool export_stack(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "stack", "stack", dest_dir, NULL, NULL);
}
