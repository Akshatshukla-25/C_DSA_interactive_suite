#include "file_exporter.h"

bool export_hash(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "linear_probing", "hash", dest_dir, NULL, NULL);
}
