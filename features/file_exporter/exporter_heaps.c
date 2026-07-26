#include "file_exporter.h"

bool export_heaps(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "priority_queue", "priority_queue", dest_dir, NULL, NULL);
}
