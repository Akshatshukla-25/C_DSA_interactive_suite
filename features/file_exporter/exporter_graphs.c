#include "file_exporter.h"

bool export_graph(const char* root_dir, const char* dest_dir)
{
    return export_file_pair(root_dir, "bfs", "graph_traversals", dest_dir, NULL, NULL);
}
