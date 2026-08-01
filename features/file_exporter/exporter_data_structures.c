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

bool export_bloom_filter(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "bloom_filter", "bloom_filter", dest_dir, NULL, NULL);
}

bool export_count_min_sketch(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "count_min_sketch", "count_min_sketch", dest_dir, NULL, NULL);
}

bool export_hyperloglog(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "hyperloglog", "hyperloglog", dest_dir, NULL, NULL);
}
